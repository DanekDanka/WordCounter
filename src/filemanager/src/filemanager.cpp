#include "filemanager.h"

using namespace wordCounter;

void FileManager::setUrl(QUrl newUrl) {
    url = newUrl;
}

QUrl FileManager::getUrl() {
    return url;
}
