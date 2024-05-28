#include "histogram.h"


using namespace wordCounter;

std::map<QString, int> *Histogram::getVocabulary() {
    return &vocabulary;
}

void Histogram::countHistogram() {
    std::array<int, 15> value;
    std::array<QString, 15> key;

    foreach (vocabulary) {

    }
}

