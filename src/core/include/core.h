#pragma once

#include <QObject>
#include "fabric.h"
#include "IFileReader.h"
#include "uimediator.h"
#include "VocabularyCurrentModel.h"

namespace wordCounter {

    class Core : public QObject {
        Q_OBJECT

    public:
        explicit Core(QObject *parent = nullptr);
        ~Core() override = default;

        UiMediator *getUiMediator();
        CurrentVocabularyModel *getVocabularyModel();

        void init();
        void startCount();

    private:
        void createClasses();
        void initFileReader();
        void createVocabulary();


        std::unique_ptr<IFileReader> fileReader;
        std::unique_ptr<FileManager> fileManager;
        std::unique_ptr<ProgressBar> progressBar;
        std::unique_ptr<Histogram> histogram;
        std::unique_ptr<IVocabularyCreator> vocabularyCreator;

        std::vector<QString> vocabularyKey;
        std::vector<int> vocabularyValue;

        std::map<QString, int> wordCounts;
        std::multimap<int, QString> vocabulary;
        std::atomic<float> persentage {0};
        float persentageCount {0};

        std::atomic<bool> play {false};
        bool playingNow {false};

        UiMediator uiMediator;
        CurrentVocabularyModel vocabularyModel;

    };
}
