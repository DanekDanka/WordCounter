#include "fabric.h"
#include "readFromTxt.h"
#include "../../vocabularycreator/include/VocabularyMultiMapCreator.h"

using namespace wordCounter;

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

std::unique_ptr<IVocabularyCreator> Fabric::createVocabularyCreator() {
    return std::make_unique<VocabularyMultiMapCreator>();
}
