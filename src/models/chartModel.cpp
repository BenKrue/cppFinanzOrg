#include "chartModel.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>

Q_LOGGING_CATEGORY(LC1, "chartModel", QtDebugMsg);

ChartModel::ChartModel(QVariantList dataByCategory, QObject *parent)
    : m_dataByCategory(dataByCategory), QAbstractListModel(parent)
{
    // Beispiel-Daten
    // @TODO daten für Diagramm aus QMap<QString, double> m_dataByCategory vom dataModel holen
    // m_data << 10 << 20 << 30 << 40 << 50;
}

ChartModel::~ChartModel()
{
    qCDebug(LC1) << __func__ << "destructor";
}
int ChartModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_dataByCategory.size();
}

QVariant ChartModel::data(const QModelIndex &index, int role) const
{
    // if (!index.isValid() || index.row() < 0 || index.row() >= m_dataByCategory.size())
    //     return QVariant();

    // if (role == ValueRole)
    // {
    //     auto it = m_dataByCategory.begin();
    //     for (int i = 0; i < index.row(); ++i)
    //     {
    //         ++it;
    //     }
    //     return it.value();
    // }

    return QVariant();
}

QHash<int, QByteArray> ChartModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    return roles;
}
