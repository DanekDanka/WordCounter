#include <QFile>
#include <QDebug>
#include "readFromTxt.h"
#include <QObject>

using namespace wordCounter;

void ReadFromTxt::setFile(QString &url) {
    this->url.setPath(url);
}

void ReadFromTxt::setVocabulary(std::map<QString, int> *map) {
    vocabulary = map;
}

void ReadFromTxt::setVocabularyValue(std::vector<int> *vocabularyValue) {
    this->vocabularyValue = vocabularyValue;
}

void ReadFromTxt::setVocabularyKey(std::vector<QString> *vocabularyKey) {
    this->vocabularyKey = vocabularyKey;
}

void ReadFromTxt::setAtomicCount(std::atomic<bool> *newCount) {
    count = newCount;
}

void ReadFromTxt::setPersentageAtomic(std::atomic<float> *pers) {
    progressCount = pers;
}

std::atomic<float> *ReadFromTxt::progress() {
    return progressCount;
}

void ReadFromTxt::setPersentage(float *persentage) {
    persentageCount = persentage;
}

float * ReadFromTxt::persentage() {
    return persentageCount;
}

std::map<QString, int> *ReadFromTxt::getVocabulary() {
    return vocabulary;
}

void ReadFromTxt::read() {
    QFile file(url.path());
    try {
        file.open(QIODevice::ReadOnly | QFile::Text);
    } catch (...) {
        qDebug() << "ERROR!! File" << url.url() << " can't open!";
        exceptionPtr = std::current_exception();
        return;
    }
    QString in = file.readAll();
    size = static_cast<qint64>(in.length());
    file.close();
    file.open(QIODevice::ReadOnly | QFile::Text);

    qint64 i = 0;
    QChar ch;
    QString word = "";

    QTextStream stream(&file);

    while (!stream.atEnd() && count->load()) {
        stream >> ch;
        ++i;
        *persentageCount = static_cast<float>(i) / static_cast<float>(size);

        if (ch.isSpace()) {
            if (!word.isEmpty()) {

                mutexVocabulary.lock();

                bool stored = {false};
                for (auto i = 0; i < vocabularyKey->size(); ++i) {
                    if (word == vocabularyKey->at(i)) {
                        vocabularyValue->at(i)++;
                        stored = true;
                        break;
                    }
                }
                if (!stored) {
                    vocabularyKey->push_back(word);
                    vocabularyValue->push_back(1);
                }
                mutexVocabulary.unlock();

                word.clear();
            }
        } else {
            word.append(ch);
        }
    }
    file.close();
}
