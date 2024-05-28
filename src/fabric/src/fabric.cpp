#include "fabric.h"
#include "readFromTxt.h"

using namespace wordCounter;

//std::unique_ptr<QObject> Fabric::createObject(Object object) {
//    switch (object) {
//        case Object::fileReader:
//            return std::make_unique<ReadFromTxt>();
////        case Object::fileManager:
////            return
//    }
//}


std::unique_ptr<IFileReader> Fabric::createFileReader() {
    return std::make_unique<ReadFromTxt>();
}

std::unique_ptr<FileManager> Fabric::createFileManager() {
    return std::make_unique<FileManager>();
}

std::unique_ptr<ProgressBar> Fabric::createProgressBar() {
    return std::make_unique<ProgressBar>();
}

std::unique_ptr<Histogram> Fabric::createHistogram() {
    return std::make_unique<Histogram>();
}
