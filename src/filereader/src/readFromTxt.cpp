
#include <QFile>
#include <QDebug>
#include "readFromTxt.h"

using namespace wordCounter;

void ReadFromTxt::setFile(QUrl &url) {
    this->url = url;
}

void ReadFromTxt::setVocabulary(std::map<QString, int> *map) {
    vocabulary = map;
}

void ReadFromTxt::setPersentageAtomic(std::atomic<float> *pers) {
    persentage = pers;
}

std::atomic<float> * ReadFromTxt::progress() {
    return persentage;
}

std::map<QString, int> *ReadFromTxt::getVocabulary() {
    return vocabulary;
}

void ReadFromTxt::read() {
    QFile file(url.url());

    try {
        file.open(QIODevice::ReadOnly | QFile::Text);
    } catch (...) {
        qDebug() << "ERROR!! File" << url.url() << " can't open!";
        exceptionPtr = std::current_exception();
        return;
    }

    QTextStream stream(&file);
    size = file.size();
    qint64 i = 0;
    QChar ch;
    QString word = "";

    while (!stream.atEnd() && !count) {
        stream >> ch;
        ++i;
        persentage->store(i / size);

        if (ch.isSpace()) {
            if (!word.isEmpty()) {
//                std::unique_lock<std::mutex> lock(mutex);
//                conditionVariable.wait(lock);
                if ((*vocabulary)[word] == 0)
                    (*vocabulary)[word] = 1;
                else
                    (*vocabulary)[word]++;
                word.clear();
            }
        } else {
            word.append(ch);
        }
    }

    file.close();

}
