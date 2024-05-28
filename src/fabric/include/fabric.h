#pragma once

#include "filemanager.h"
#include "histogram.h"
#include "QObject"
#include "IFileReader.h"
#include "ProgressBar.h"

namespace wordCounter {

//    enum class Object{
//        fileManager,
//        fileReader,
//        histogram,
//        uiMediator
//    };

    class Fabric {
    public:
        Fabric() = default;
        ~Fabric() = default;

//        std::unique_ptr<QObject> createObject(Object object);
        std::unique_ptr<IFileReader> createFileReader();
        std::unique_ptr<FileManager> createFileManager();
        std::unique_ptr<ProgressBar> createProgressBar();
        std::unique_ptr<Histogram> createHistogram();

    };


}
