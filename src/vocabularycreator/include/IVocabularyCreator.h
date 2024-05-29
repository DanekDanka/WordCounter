#pragma once
#include <map>
#include <mutex>
#include <QString>

namespace wordCounter {
    class IVocabularyCreator {
    public:
        IVocabularyCreator() = default;
        virtual ~IVocabularyCreator() = default;

        virtual void setWordCounts(std::map<QString, int> *inputMap) = 0;

        virtual void setVocabularyKey(std::vector<QString> *vocabularyKey) = 0;
        virtual void setVocabularyValue(std::vector<int> *vocabularyValue) = 0;

        virtual void setVocabulary(std::multimap<int, QString> *vocabulary) = 0;
        virtual void createVocabulary() = 0;

    };
}

