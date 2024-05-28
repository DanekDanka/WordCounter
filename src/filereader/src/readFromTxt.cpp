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

void ReadFromTxt::setVocabularyKey(std::vector<QString> *key) {
    vocabularyKey = key;
}

void ReadFromTxt::setVocabularyValue(std::vector<u_int> *value) {
    vocabularyValue = value;
}

void ReadFromTxt::setPersentageAtomic(std::atomic<float> *pers) {
    persentage = pers;
}

std::atomic<float> *ReadFromTxt::progress() {
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

                bool stored = {false};
                for (auto i = 0; i < vocabularyKey->size(); ++i) {
                    if (word == vocabularyKey->at(i)) {
                        vocabularyValue->at(i)++;

                        if ((vocabularyValue->at(i) > vocabularyValue->at(i - 1)) && (i > 0)) {
                            swap(vocabularyValue[i], vocabularyValue[i - 1]);
                            swap(vocabularyKey[i], vocabularyKey[i - 1]);
                        }
                        stored = true;
                        break;
                    }
                }
                if (!stored) {
                    vocabularyKey->push_back(word);
                    vocabularyValue->push_back(1);
                }

                word.clear();
            }
        } else {
            word.append(ch);
        }
    }

    for (auto i = 1; i < vocabularyKey->size(); ++i) {
        if ((vocabularyValue->at(i) > vocabularyValue->at(i - 1)) && (i > 0)) {
            swap(vocabularyValue[i], vocabularyValue[i - 1]);
            swap(vocabularyKey[i], vocabularyKey[i - 1]);
        }
    }


    file.close();
}
