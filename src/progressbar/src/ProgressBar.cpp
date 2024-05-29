#include "ProgressBar.h"

using namespace wordCounter;

ProgressBar::~ProgressBar() = default;

float ProgressBar::getPersentage() const {
    return persentage;
}

void ProgressBar::setPersentage(float persentage) {
    this->persentage = persentage;
    emit percentageChanged(persentage);
}