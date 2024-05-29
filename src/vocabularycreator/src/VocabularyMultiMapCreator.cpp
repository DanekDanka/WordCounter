#include "VocabularyMultiMapCreator.h"
// #include "core.h"

using namespace wordCounter;


VocabularyMultiMapCreator::VocabularyMultiMapCreator() {
}

void VocabularyMultiMapCreator::setWordCounts(std::map<QString, int> *inputMap) {
    // this->inputMap = inputMap;
}

void VocabularyMultiMapCreator::setVocabularyKey(std::vector<QString> *vocabularyKey) {
    this->vocabularyKey = vocabularyKey;
}

void VocabularyMultiMapCreator::setVocabularyValue(std::vector<int> *vocabularyValue) {
    this->vocabularyValue = vocabularyValue;
}

void VocabularyMultiMapCreator::setVocabulary(std::multimap<int, QString> *vocabulary) {
    this->vocabularyCurrent = vocabulary;
}


void VocabularyMultiMapCreator::createVocabulary() {
    if (vocabularyValue->empty() || vocabularyKey->empty())
        return;

    if (!vocabularyCurrent->empty())
        vocabularyCurrent->clear();

    if (!vocabulary.empty())
        vocabulary.clear();

    for (int i = 0; i < vocabularyValue->size(); ++i) {
        vocabulary.insert(std::pair<int, QString>(vocabularyValue->at(i), vocabularyKey->at(i)));
    }

    std::multimap<int, QString>::reverse_iterator it = vocabulary.rbegin();
    int count = 0;
    while (it != vocabulary.rend() && count < 15) {
        vocabularyCurrent->insert(std::pair<int, QString>(it->first, it->second));
        ++it;
        ++count;
    }
}
