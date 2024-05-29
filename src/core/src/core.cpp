#include "core.h"

#include <iostream>
#include <thread>
#include "readFromTxt.h"
#include "uimediator.h"

#include "QDebug"


using namespace wordCounter;


Core::Core(QObject *parent) : QObject(parent) {
    connect(&uiMediator, &UiMediator::playChanged,
            [=]() {
                play.store(uiMediator.getPlay());

                if (play.load() == true && !playingNow)
                    startCount();
            });

    connect(&uiMediator, &UiMediator::pauseChanged,
            [=]() {
                mutexVocabulary.lock();
            });

    connect(&uiMediator, &UiMediator::continueChanged,
            [=]() {
                mutexVocabulary.unlock();
            });

    connect(&uiMediator, &UiMediator::stopChanged,
            [=]() {
                play.store(false);
                playingNow = false;
                vocabularyModel.clearData();
            });

    connect(&uiMediator, &UiMediator::urlChanged,
            [=]() {
                url = uiMediator.getUrl();
                auto str = url.path();
                fileReader->setFile(str);
                qDebug() << url.path();
            });

    connect(this, &Core::vocabularyCreated,
            [=]() {
                if (vocabulary.empty())
                    return;

                vocabularyModel.clearData();
                auto iterator = vocabulary.rbegin();
                for (int i = 0; i < 15 && i < vocabulary.size(); ++i) {
                    QString srt = iterator->second;
                    int a = iterator->first;
                    vocabularyModel.addItem(srt, a);
                    ++iterator;
                }

                if (persentageCount >= 1) {
                    play.store(false);
                    playingNow = false;
                }
            });

}

UiMediator *Core::getUiMediator() {
    return &uiMediator;
}

CurrentVocabularyModel *Core::getVocabularyModel() {
    return &vocabularyModel;
}

void Core::init() {
    createClasses();
    initFileReader();
    uiMediator.setPersentage(persentage.load());
}

void Core::startCount() {
    playingNow = true;
    vocabularyKey.clear();
    vocabularyValue.clear();

    std::thread thr(&IFileReader::read, fileReader.get());
    thr.detach();

    std::atomic_bool &m = play;
    std::thread vocabularyCounter([this, &m]() {
        while (m.load() == true) {
            mutexVocabulary.lock();
            createVocabulary();

            emit vocabularyCreated();

            mutexPersentage.lock();
            float f = *fileReader->persentage();
            uiMediator.setPersentage(f);
            mutexPersentage.unlock();

            mutexVocabulary.unlock();
        }
    });
    vocabularyCounter.detach();

}

void Core::createClasses() {
    fileReader = Fabric::createFileReader();
    fileManager = Fabric::createFileManager();
    progressBar = Fabric::createProgressBar();
    histogram = Fabric::createHistogram();
    vocabularyCreator = Fabric::createVocabularyCreator();
}

void Core::initFileReader() {
    fileReader->setVocabulary(&wordCounts);
    fileReader->setAtomicCount(&play);

    vocabularyKey.resize(100);
    vocabularyValue.resize(100);

    fileReader->setVocabularyKey(&vocabularyKey);
    fileReader->setVocabularyValue(&vocabularyValue);

    fileReader->setPersentageAtomic(&persentage);
    fileReader->setPersentage(&persentageCount);
}

void Core::createVocabulary() {
    vocabulary.clear();
    vocabularyCreator->setVocabulary(&vocabulary);
    vocabularyCreator->setVocabularyKey(&vocabularyKey);
    vocabularyCreator->setVocabularyValue(&vocabularyValue);
    vocabularyCreator->createVocabulary();
}
