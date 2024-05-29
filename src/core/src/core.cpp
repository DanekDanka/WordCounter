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
                // url.setPath(uiMediator.getUrl());
                fileReader->setFile(str);
                qDebug() << url.path();
            });

    connect(this, &Core::vocabularyCreated,
            [=]() {

                // mutexPersentage.lock();
                // // uiMediator.setPersentage(persentageCount);
                // uiMediator.setPersentage(*fileReader->persentage());
                // mutexPersentage.unlock();

                if (vocabulary.empty())
                    return;

                vocabularyModel.clearData();
                auto iterator = vocabulary.rbegin();
                // mutexVocabulary.lock();
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
                // mutexVocabulary.unlock();
            });

    // connect(this, &Core::vocabularyCreated,
    //         [=]() {
    //             mutexPersentage.lock();
    //             // uiMediator.setPersentage(persentageCount);
    //             float f = *fileReader->persentage();
    //             uiMediator.setPersentage(f);
    //             mutexPersentage.unlock();
    //         });
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

    // uiMediator.setPersentage(0.5);
    uiMediator.setPersentage(persentage.load());
}

void Core::startCount() {
    playingNow = true;
    vocabularyKey.clear();
    vocabularyValue.clear();

    std::thread thr(&IFileReader::read, fileReader.get());
    // fileReader->read();
    thr.detach(); //TODO убрать

    std::atomic_bool &m = play;//TODO исправить на true
    std::thread vocabularyCounter([this, &m]() {
        while (m.load() == true) {
            // std::this_thread::sleep_for(std::chrono::microseconds(10)); //TODO возможно убрать

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

    // mutexPersentage.lock();
    // float f = *fileReader->persentage();
    // uiMediator.setPersentage(f);
    // mutexPersentage.unlock();

    // thr.join();

    // float per = persentage.load();

    // uiMediator.setPersentage(persentageCount);


    // auto iterator = vocabulary.rbegin();
    // for (int i = 0; i < 15; ++i) {
    //     vocabularyModel.addItem(iterator->second, iterator->first);
    //     ++iterator;
    // }

    // while (play.load()) {
    //     std::cout << "Reverse:\n";
    //     auto iterator = vocabulary.rbegin();
    //     while (iterator != vocabulary.rend()) {
    //         mutex.lock();
    //         std::cout << iterator->first << ": " << iterator->second.toStdString() << '\n';
    //         ++iterator;
    //         mutex.unlock();
    //     }
    // }
}

void Core::createClasses() {
    fileReader = Fabric::createFileReader();
    fileManager = Fabric::createFileManager();
    progressBar = Fabric::createProgressBar();
    histogram = Fabric::createHistogram();
    vocabularyCreator = Fabric::createVocabularyCreator();
    // vocabularyModel = Fabric::createVocabularyModelCreator();
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
    QString str = "/home/danya/Documents/text.txt"; //TODO убрать
    // qDebug() << url.path();
    fileReader->setFile(str);
}

void Core::createVocabulary() {
    vocabulary.clear();
    vocabularyCreator->setVocabulary(&vocabulary);
    // vocabularyCreator->setWordCounts(&wordCounts);

    vocabularyCreator->setVocabularyKey(&vocabularyKey);
    vocabularyCreator->setVocabularyValue(&vocabularyValue);

    // mutexVocabulary.lock();
    vocabularyCreator->createVocabulary();
    // mutexVocabulary.unlock();
}
