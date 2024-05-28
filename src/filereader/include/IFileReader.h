#pragma once

#include <mutex>
#include <condition_variable>
#include "QObject"

namespace wordCounter {

    class IFileReader : public QObject {
        Q_GADGET

    public:
        IFileReader() = default;
        virtual ~IFileReader() = default;

        virtual void setFile(QUrl &url) = 0;
        virtual std::map<QString, int>* getVocabulary() = 0; //TODO убрать потом
        virtual void read() = 0;
        virtual std::atomic<float> * progress() = 0;
        virtual void setVocabulary(std::map<QString, int> *map) = 0;
        virtual void setVocabularyKey(std::vector<QString> *key) = 0;
        virtual void setVocabularyValue(std::vector<u_int> *value) = 0;
        virtual void setPersentageAtomic(std::atomic<float> *pers) = 0;

    };

}
