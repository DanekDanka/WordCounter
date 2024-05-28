#pragma once

#include <QUrl>
#include <mutex>
#include <condition_variable>
#include "IFileReader.h"

namespace wordCounter {

    static std::mutex mutex;
    static std::condition_variable conditionVariable;

    class ReadFromTxt : public IFileReader {
    Q_OBJECT

    public:
        ReadFromTxt() = default;

        ~ReadFromTxt() override = default;

        void setFile(QUrl &url) override;

        std::map<QString, int> *getVocabulary() override;

        void read() override;

        std::atomic<float> * progress() override;

        void setVocabulary(std::map<QString, int> *map) override;
        void setVocabularyKey(std::vector<QString> *key) override;
        void setVocabularyValue(std::vector<u_int> *value) override;



        void setPersentageAtomic(std::atomic<float> *pers) override;

    private:
        QUrl url;
        std::map<QString, int> *vocabulary;
        std::atomic<float> *persentage = {nullptr};
        qint64 size = {0};

        std::vector<QString> *vocabularyKey;
        std::vector<u_int> *vocabularyValue;

        bool count = {false};

        std::exception_ptr exceptionPtr = {nullptr};

    };
}