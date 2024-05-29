#pragma once
#include <atomic>
#include <QObject>


namespace wordCounter {
    class ProgressBar : public QObject {
        Q_PROPERTY(float persentage READ getPersentage WRITE setPersentage NOTIFY percentageChanged)

    Q_OBJECT

    public:
        explicit ProgressBar(QObject *parent = nullptr);
        ~ProgressBar() override = default;

        Q_INVOKABLE float getPersentage() const;
        void setPersentage(float persentage);

    signals:
        void percentageChanged(float progress);

    private:
        float persentage;

    };
}
