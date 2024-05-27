#pragma once

#include "fabric.h"
#include "IFileReader.h"

namespace wordCounter {

    class Core {
    public:
        Core() = default;
        ~Core() = default;

        void init();

    private:
        Fabric fabric;
        std::unique_ptr<IFileReader> fileReader;

    };
}
