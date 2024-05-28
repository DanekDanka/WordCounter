#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "uimediator.h"

#include "readFromTxt.h"
#include "QUrl"
#include "iostream"
#include "future"
#include "thread"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    qmlRegisterType<wordCounter::UiMediator>("Mediator", 1, 0, "UiMediator");


    engine.loadFromModule("WordCounter", "WordCounterMain");

    ////////////////////////////////////////////////////////////////////////
    std::map<QString, int> map;
    std::vector<QString> key;
    std::vector<u_int> value;

    std::atomic<float> pers;
    wordCounter::ReadFromTxt reader;
    //    std::unique_lock<std::mutex> lock(wordCounter::mutex);
    //    wordCounter::conditionVariable.notify_all();
    QUrl url;
    url.setPath("/home/danya/Documents/file.txt");
    reader.setFile(url);
    reader.setVocabulary(&map);
    reader.setVocabularyKey(&key);
    reader.setVocabularyValue(&value);
    reader.setPersentageAtomic(&pers);

    // auto a = std::async(&wordCounter::ReadFromTxt::read, &reader);
    // a.wait();
    reader.read();
    //
    // std::cout << map.at("Некоторые");
    // qDebug() << key.at(0) << " " << value.at(0);



    for (auto i = 0; i < key.size(); ++i) {
        qDebug() << key.at(i) << " " << value.at(i);
    }

    //    thr.join();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return app.exec();
}
