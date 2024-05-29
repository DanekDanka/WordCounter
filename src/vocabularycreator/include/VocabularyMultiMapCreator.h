#pragma once
#include <map>
#include <QString>
#include "IVocabularyCreator.h"

namespace wordCounter {
    class VocabularyMultiMapCreator : public IVocabularyCreator {

    public:
        VocabularyMultiMapCreator();
        ~VocabularyMultiMapCreator() override = default;

        void setWordCounts(std::map<QString, int> *inputMap) override;

        void setVocabularyKey(std::vector<QString> *vocabularyKey) override;
        void setVocabularyValue(std::vector<int> *vocabularyValue) override;

        void setVocabulary(std::multimap<int, QString> *vocabulary) override;
        void createVocabulary() override;

    private:
        // std::map<QString, int> *inputMap;
        std::multimap<int, QString> *vocabularyCurrent;
        std::multimap<int, QString> vocabulary;

        std::vector<QString> *vocabularyKey;
        std::vector<int> *vocabularyValue;
    };
}
