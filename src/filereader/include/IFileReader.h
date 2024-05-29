#pragma once

#include <mutex>
#include <condition_variable>
#include "QObject"

namespace wordCounter {
    static std::mutex mutexVocabulary;
    static std::mutex mutexPersentage;
    class IFileReader : public QObject {
        Q_GADGET

    public:
        IFileReader() = default;
        virtual ~IFileReader() = default;

        virtual void setFile(QUrl &url) = 0;
        virtual std::map<QString, int>* getVocabulary() = 0; //TODO убрать потом
        virtual void read() = 0;
        virtual std::atomic<float> * progress() = 0;

        virtual float *persentage() = 0;
        virtual void setPersentage(float *persentage) = 0;

        virtual void setVocabulary(std::map<QString, int> *map) = 0;
        virtual void setVocabularyValue(std::vector<int> *vocabularyValue) = 0;
        virtual void setVocabularyKey(std::vector<QString> *vocabularyKey) = 0;


        virtual void setPersentageAtomic(std::atomic<float> *pers) = 0;

    };

}
