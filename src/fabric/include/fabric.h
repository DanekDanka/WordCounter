#pragma once

#include "QObject"

namespace wordCounter {

    enum class Object{
        fileManager,
        fileReader,
        histogram,
        uiMediator
    };

    class Fabric {
    public:
        Fabric() = default;
        QObject* createObject(Object object);
    };

}