#pragma once
#include <QObject>
#include "fabric.h"
#include "IFileReader.h"
#include "uimediator.h"

namespace wordCounter {

    class Core : public QObject {
        Q_OBJECT

    public:
        explicit Core(UiMediator *mediator, QObject *parent = nullptr);
        explicit Core(QObject *parent = nullptr);
        ~Core() = default;

        void init();
        void startCount();

    private:
        Fabric fabric;
        std::unique_ptr<IFileReader> fileReader;
        std::unique_ptr<FileManager> fileManager;
        std::unique_ptr<ProgressBar> progressBar;
        std::unique_ptr<Histogram> histogram;

        std::map<QString, int> vocabulary;
        std::atomic<float> persentage;

        UiMediator * uiMediator {nullptr};

    };
}
