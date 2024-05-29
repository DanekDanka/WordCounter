#include "uimediator.h"
#include "qdebug.h"

using namespace wordCounter;

void UiMediator::setPlay(const bool newPlay) {
    // play = newPlay;
    play = true;
    emit playChanged();
}

bool UiMediator::getPlay() const {
    return play;
}

void UiMediator::setPause(bool const newPause) {
    pause = newPause;
    // pause = true;
    // play = false;

    emit pauseChanged();
    // emit playChanged();
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
    play = false;
    emit playChanged();
    emit stopChanged();
}

bool UiMediator::getStop() const {
    return stop;
}

void UiMediator::setUrl(QString url) {
    this->url = QUrl(url);
    emit urlChanged();
}

QUrl UiMediator::getUrl() {
    return url;
}

float UiMediator::getPersentage() const {
    return persentage;
}

void UiMediator::setPersentage(float persentage) {
    this->persentage = persentage;
    emit percentageChanged(persentage);
}


//UiMediator:
