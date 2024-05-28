#include "ProgressBar.h"

using namespace wordCounter;

void ProgressBar::setProgress(float newPersentage) {
    persentage.store(newPersentage);
}

float ProgressBar::getProgress() const {
    return persentage.load();
}

std::atomic<float> *ProgressBar::getProgressPtr() {
    return &persentage;
}

