#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "readFromTxt.h"
#include "QUrl"
#include "iostream"
#include "future"
#include "thread"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("WordCounter", "WordCounterMain");

////////////////////////////////////////////////////////////////////////
    std::map<QString, int> map;
    std::atomic<float> pers;
    wordCounter::ReadFromTxt reader;
//    std::unique_lock<std::mutex> lock(wordCounter::mutex);
//    wordCounter::conditionVariable.notify_all();
    QUrl url;
    url.setPath("/home/danya/Documents/file.txt");
    reader.setFile(url);
    reader.setVocabulary(&map);
    reader.setPersentageAtomic(&pers);

    auto a = std::async(&wordCounter::ReadFromTxt::read, &reader);
//    reader.read();
    a.wait();

    std::cout << map.at("доступ");

//    thr.join();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return app.exec();
}
