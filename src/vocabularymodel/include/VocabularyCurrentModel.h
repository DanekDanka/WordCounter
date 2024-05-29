#pragma once

#include <qtmetamacros.h>
#include <QAbstractListModel>
#include <QString>
#include <QVector>

namespace wordCounter {
    class CurrentVocabularyModel : public QAbstractListModel {
        Q_OBJECT

    public:
        struct DataItem {
            QString name;
            int value;
        };

        explicit CurrentVocabularyModel(QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;
        void addItem(const QString &name, int value);

        Q_INVOKABLE QVariantMap get(int index) const;
        Q_INVOKABLE int maxCount() const;

        void clearData();

    private:
        QVector<DataItem> m_items;

        enum {
            NameRole = Qt::UserRole + 1,
            ValueRole
        };
    };
}