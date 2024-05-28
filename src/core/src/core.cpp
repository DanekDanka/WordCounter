#include "core.h"


using namespace wordCounter;

void Core::init() {
     fileReader = fabric.createFileReader();
     fileManager = fabric.createFileManager();
     progressBar = fabric.createProgressBar();
     histogram = fabric.createHistogram();
}