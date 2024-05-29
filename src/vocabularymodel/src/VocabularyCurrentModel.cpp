#include "VocabularyCurrentModel.h"

using namespace wordCounter;


CurrentVocabularyModel::CurrentVocabularyModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int CurrentVocabularyModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant CurrentVocabularyModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_items.count())
        return QVariant();

    const DataItem &item = m_items[index.row()];

    switch (role) {
        case NameRole:
            return item.name;
        case ValueRole:
            return item.value;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> CurrentVocabularyModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    return roles;
}

void CurrentVocabularyModel::addItem(const QString &name, int value) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items.append({name, value});
    endInsertRows();
}

QVariantMap CurrentVocabularyModel::get(int index) const {
    if (index < 0 || index >= m_items.size())
        return QVariantMap();

    QVariantMap item;
    item["name"] = m_items.at(index).name;
    item["value"] = m_items.at(index).value;
    return item;
}
