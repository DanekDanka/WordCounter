#pragma once

#include <map>
#include "QString"

namespace wordCounter {
    class Histogram {
    public:
        std::map<QString, int> *getVocabulary();

        void countHistogram();

    private:
        std::map<QString, int> vocabulary;
        std::map<QString, int> histogram;

    };
}
