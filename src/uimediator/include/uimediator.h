#pragma once

#include <QUrl>

#include "QObject"

namespace wordCounter {

    class UiMediator : public QObject {
        Q_PROPERTY(bool Play READ getPlay WRITE setPlay NOTIFY playChanged)
        Q_PROPERTY(bool Pause READ getPause WRITE setPause NOTIFY pauseChanged)
        Q_PROPERTY(bool Continue READ getContinue WRITE setContinue NOTIFY continueChanged)
        Q_PROPERTY(bool Stop READ getStop WRITE setStop NOTIFY stopChanged)

        Q_OBJECT
    public:
        UiMediator() = default;
        ~UiMediator() = default;

        void setPlay(bool const newPlay);
        bool getPlay() const;

        void setPause(bool const newPause);
        bool getPause() const;

        void setContinue(bool const newContinue);
        bool getContinue() const;

        void setStop(bool const newStop);
        bool getStop() const;

        Q_INVOKABLE void setUrl(QString url);
        QUrl getUrl();

    signals:
        void playChanged();
        void pauseChanged();
        void continueChanged();
        void stopChanged();

    private:
        bool play;
        bool pause;
        bool uicontinue;
        bool stop;

        QUrl url;

    };

}
