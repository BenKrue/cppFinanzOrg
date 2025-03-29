#pragma once

#include <QAbstractTableModel>
#include <QVector>

class TableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit TableModel(QStringList header, QVector<QVector<QVariant>> data, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Q_INVOKABLE void updateCell(int row, int col, const QVariant &value);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;


private:
    QVector<QVector<QVariant>> m_data;
    QStringList m_header;
};