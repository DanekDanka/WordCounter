#pragma once

#include "QObject"
#include "filemanager.h"
#include "histogram.h"
#include "IFileReader.h"
#include "ProgressBar.h"
#include "IVocabularyCreator.h"
#include "VocabularyCurrentModel.h"

namespace wordCounter {
    class Fabric {
    public:
        Fabric() = default;

        ~Fabric() = default;

        static std::unique_ptr<IFileReader> createFileReader();

        static std::unique_ptr<FileManager> createFileManager();

        static std::unique_ptr<ProgressBar> createProgressBar();

        static std::unique_ptr<Histogram> createHistogram();

        static std::unique_ptr<IVocabularyCreator> createVocabularyCreator();

        // static std::unique_ptr<CurrentVocabularyModel> createVocabularyModel();
    };
}
