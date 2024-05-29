#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QQmlContext"

#include "uimediator.h"
#include "core.h"
#include "VocabularyCurrentModel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    wordCounter::Core core;
    wordCounter::UiMediator *mediator = core.getUiMediator();
    core.init();

    auto *model = core.getVocabularyModel();

    engine.rootContext()->setContextProperty("vocabularyModel", model);
    engine.rootContext()->setContextProperty("mediator", mediator);
    engine.rootContext()->setContextProperty("Core", &core);

    engine.loadFromModule("WordCounter", "WordCounterMain");
    return app.exec();
}
