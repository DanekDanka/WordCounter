#include "uimediator.h"
#include "qdebug.h"

using namespace wordCounter;

void UiMediator::setPlay(const bool newPlay) {
    play = newPlay;
    emit playChanged();

    if (play)
        qDebug() << "TRUE";
    else
        qDebug() << "FALSE";
}

bool UiMediator::getPlay() const {
    return play;
}

void UiMediator::setPause(bool const newPause) {
    pause = newPause;
    emit pauseChanged();
}

bool UiMediator::getPause() const {
    return pause;
}

void UiMediator::setContinue(bool const newContinue) {
    uicontinue = newContinue;
    emit continueChanged();
}

bool UiMediator::getContinue() const {
    return uicontinue;
}

void UiMediator::setStop(bool const newStop) {
    stop = newStop;
    emit stopChanged();
}

bool UiMediator::getStop() const {
    return stop;
}

void UiMediator::setUrl(QUrl url) {
    this->url = url;
}

QUrl UiMediator::getUrl() {
    return url;
}


//UiMediator:
