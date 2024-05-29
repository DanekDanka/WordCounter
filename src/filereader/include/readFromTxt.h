#pragma once

#include <QUrl>
#include <mutex>
#include <condition_variable>
#include "IFileReader.h"

namespace wordCounter {

    class ReadFromTxt : public IFileReader {
    Q_OBJECT

    public:
        ReadFromTxt() = default;

        ~ReadFromTxt() override = default;

        void setFile(QString &url) override;

        std::map<QString, int> *getVocabulary() override;

        void read() override;

        void setPersentageAtomic(std::atomic<float> *pers) override;
        std::atomic<float> * progress() override;

        void setPersentage(float *persentage) override;
        float *persentage() override;

        void setVocabulary(std::map<QString, int> *map) override;

        void setVocabularyValue(std::vector<int> *vocabularyValue) override;
        void setVocabularyKey(std::vector<QString> *vocabularyKey) override;
        void setAtomicCount(std::atomic<bool> *newCount) override;


    private:
        QUrl url;
        std::map<QString, int> *vocabulary;

        std::vector<QString> *vocabularyKey;
        std::vector<int> *vocabularyValue;

        std::atomic<float> *progressCount = {nullptr};
        float *persentageCount = {nullptr};

        qint64 size = {0};

        std::atomic<bool> *count = {nullptr};

        std::exception_ptr exceptionPtr = {nullptr};

    };
}