#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "uimediator.h"
#include "QQmlContext"

#include "readFromTxt.h"
#include "QUrl"
#include "iostream"
#include "future"
#include "thread"
#include "core.h"
#include "VocabularyCurrentModel.h"
// #include "vocabularymodel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // qmlRegisterType<wordCounter::UiMediator>("Mediator", 1, 0, "UiMediator");
    wordCounter::Core core;
    wordCounter::UiMediator *mediator = core.getUiMediator();
    core.init();

    auto *model = core.getVocabularyModel();
    // model->addItem("Item 1", 10);
    // model->addItem("Item 2", 30);
    // model->addItem("Item 3", 20);
    // model->addItem("Item 4", 40);
    // model->addItem("Item 5", 25);

    engine.rootContext()->setContextProperty("vocabularyModel", model);
    engine.rootContext()->setContextProperty("mediator", mediator);

    engine.loadFromModule("WordCounter", "WordCounterMain");



    // if (uiMediator) {
        // QObject::connect(uiMediator, &wordCounter::UiMediator::playChanged, &core, &wordCounter::Core::startCount);
    // }

    ////////////////////////////////////////////////////////////////////////
    // std::map<QString, int> map;
    //
    // std::atomic<float> pers;
    // wordCounter::ReadFromTxt reader;
    // QUrl url;
    // url.setPath("/home/danya/Documents/file.txt");
    // reader.setFile(url);
    // reader.setVocabulary(&map);
    // reader.setPersentageAtomic(&pers);
    //
    //
    // // auto a = std::async(&wordCounter::ReadFromTxt::read, &reader);
    // std::thread thr(&wordCounter::ReadFromTxt::read, &reader);
    // // reader.read();
    //
    // for (int i = 0; i < 1; i ++) {        // std::this_thread::sleep_for(std::chrono::microseconds(50));
    //
    //     // std::unique_lock<std::mutex> lock(wordCounter::mutex);
    //
    //
    //     wordCounter::mutex.lock();
    //     std::map<QString, int> copyMap = map;
    //     wordCounter::mutex.unlock();
    //
    //     std::multimap<int, QString> reverseMyMap;
    //     for (std::pair<QString, int> pair : copyMap) {
    //         reverseMyMap.insert(std::pair<int, QString>(pair.second, pair.first));
    //     }
    //
    //     qDebug() << i << "Reverse:\n";
    //     std::multimap<int, QString>::reverse_iterator it = reverseMyMap.rbegin();
    //     while (it != reverseMyMap.rend()) {
    //         qDebug() << it->first << ": " << it->second << '\n';
    //         ++it;
    //     }
    // }
    //
    // // a.wait();
    //
    // thr.join();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return app.exec();
}
