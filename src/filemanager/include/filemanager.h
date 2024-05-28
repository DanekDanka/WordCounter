#pragma once
#include <QUrl>

namespace wordCounter {
    class FileManager {
    public:
        FileManager() = default;

        ~FileManager() = default;

        void setUrl(QUrl newUrl);

        QUrl getUrl();

    private:
        QUrl url;
    };
}
