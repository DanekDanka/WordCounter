#pragma once

#include "QObject"
#include "IFileReader.h"

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
    };


}