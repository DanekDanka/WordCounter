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