#include "tableModel.hpp"

#include <QDateTime>
#include <QDebug>
#include <QLoggingCategory>


TableModel::TableModel(QSharedPointer<csv::CSVReader> csvReader, QObject *parent)
    : m_csvReader(csvReader), QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex &) const
{
    return m_csvReader->m_data.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return m_csvReader->m_header.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return m_csvReader->m_data[index.row()][index.column()];
    }

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_csvReader->m_data[index.row()][index.column()] = value;
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

void TableModel::updateCell(int row, int col, const QVariant &value)
{
    if (row >= 0 && row < m_csvReader->m_data.size() && col >= 0 && col < m_csvReader->m_header.size())
    {
        QString filePath = "C:/src/cppFinanzOrg/FinanzOrg_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".csv";
        m_csvReader->saveCSV(filePath); // Backup erstellen
        QModelIndex index = createIndex(row, col);
        m_csvReader->m_data[row][col] = value;
        setData(index, value, Qt::EditRole);
        m_csvReader->saveCSV("C:/src/cppFinanzOrg/FinanzOrg.csv");
    }
    else
    {
        qWarning() << "Ungültige Zeilen- oder Spaltennummer:" << row << col;
    }
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return m_csvReader->m_header[section];
        else
            return section + 1;
    }
    return QVariant();
}

void TableModel::sort(int column, Qt::SortOrder order)
{
    std::sort(m_csvReader->m_data.begin(), m_csvReader->m_data.end(), [column, order](const QVector<QVariant> &a, const QVector<QVariant> &b)
              {
        QVariant left = a[column];
        QVariant right = b[column];

        if (left.userType() == QMetaType::Int || left.userType() == QMetaType::Double) {
            return order == Qt::AscendingOrder ? left.toDouble() < right.toDouble() : left.toDouble() > right.toDouble();
        } else {
            return order == Qt::AscendingOrder ? left.toString() < right.toString() : left.toString() > right.toString();
        } });

    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
