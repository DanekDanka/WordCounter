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
}


UiMediator *Core::getUiMediator() {
    return &uiMediator;
}

void Core::init() {
    createClasses();
    initFileReader();

    uiMediator.setPersentage(persentage);
}

void Core::startCount() {
    playingNow = true;
    vocabularyKey.clear();
    vocabularyValue.clear();

    std::thread thr(&IFileReader::read, fileReader.get());
    // thr.detach(); //TODO убрать

    std::atomic_bool &m = play;

    //TODO исправить на true
    std::thread vocabularyCounter([this, &m]() {
        while (m.load() == true) {
            std::this_thread::sleep_for(std::chrono::microseconds(10)); //TODO возможно убрать
            // mutex.lock();
            createVocabulary();
            // mutex.unlock();
        }
    });
    vocabularyCounter.detach();

    thr.join();

    // float per = persentage.load();

    uiMediator.setPersentage(persentageCount);
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
}

void Core::initFileReader() {
    fileReader->setVocabulary(&wordCounts);

    vocabularyKey.resize(100);
    vocabularyValue.resize(100);

    fileReader->setVocabularyKey(&vocabularyKey);
    fileReader->setVocabularyValue(&vocabularyValue);

    fileReader->setPersentageAtomic(&persentage);
    fileReader->setPersentage(&persentageCount);
    QUrl url; // = uiMediator->getUrl();
    url.setPath("/home/danya/Documents/file.txt"); //TODO убрать
    fileReader->setFile(url);
}

void Core::createVocabulary() {
    vocabulary.clear();
    vocabularyCreator->setVocabulary(&vocabulary);
    // vocabularyCreator->setWordCounts(&wordCounts);

    vocabularyCreator->setVocabularyKey(&vocabularyKey);
    vocabularyCreator->setVocabularyValue(&vocabularyValue);

    mutexVocabulary.lock();
    vocabularyCreator->createVocabulary();
    mutexVocabulary.unlock();
}
