#include "core.h"

#include "uimediator.h"


using namespace wordCounter;

Core::Core(QObject *parent) : QObject(parent) {

}

Core::Core(UiMediator *mediator, QObject *parent) : QObject(parent) {
    uiMediator = mediator;
    connect(mediator, &UiMediator::playChanged,
            this, &Core::startCount);
}

void Core::init() {
    fileReader = fabric.createFileReader();
    fileManager = fabric.createFileManager();
    progressBar = fabric.createProgressBar();
    histogram = fabric.createHistogram();
}

void Core::startCount() {
    fileReader->read();
}
