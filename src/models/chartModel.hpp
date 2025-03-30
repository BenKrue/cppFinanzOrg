#pragma once

#include <QAbstractListModel>
#include <QVector>
#include <QObject>

namespace models::dataModel
{
    class dataModel; // Vorwärtsdeklaration
}

class ChartModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        ValueRole = Qt::UserRole + 1
    };

    explicit ChartModel(QMap<QString, double> dataByCategory, QObject *parent = nullptr);
    ~ChartModel();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QMap<QString, double> m_dataByCategory;
};
