#include "tableModel.hpp"

#include <QDateTime>
#include <QDebug>
#include <QLoggingCategory>

namespace models
{
    Q_LOGGING_CATEGORY(LC, "tableModel", QtDebugMsg);

    TableModel::TableModel(QSharedPointer<csv::CSVReader> csvReader, QObject *parent)
        : m_csvReader(csvReader), QAbstractTableModel(parent)
    {
    }

    TableModel::~TableModel() {
        qCDebug(LC) << __func__ << "destructor";
    }
    int TableModel::rowCount(const QModelIndex &) const
    {
        return m_csvReader->getData().size();
    }

    int TableModel::columnCount(const QModelIndex &) const
    {
        return m_csvReader->getHeader().size();
    }

    QVariant TableModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {

            return m_csvReader->getData().at(index.row()).at(index.column());
        }

        return QVariant();
    }

    bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid() && role == Qt::EditRole)
        {
            auto data = m_csvReader->getData().at(index.row()).at(index.column());
            data = value;
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
            return true;
        }
        return false;
    }

    void TableModel::updateCell(int row, int col, const QVariant &value)
    {
        if (row >= 0 && row < m_csvReader->getData().size() && col >= 0 && col < m_csvReader->getHeader().size())
        {
            QString filePath = "C:/src/cppFinanzOrg/FinanzOrg_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".csv";
            m_csvReader->saveCSV(filePath); // Backup erstellen
            QModelIndex index = createIndex(row, col);
            auto data = m_csvReader->getData().at(row).at(col);
            data = value;
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
                return m_csvReader->getHeader().at(section);
            else
                return section + 1;
        }
        return QVariant();
    }

    void TableModel::sort(int column, Qt::SortOrder order)
    {
        QVector<QVector<QVariant>> dataCopy = m_csvReader->getData();
        std::sort(dataCopy.begin(), dataCopy.end(), [column, order](const QVector<QVariant> &a, const QVector<QVariant> &b)
        {
            QVariant left = a[column];
            QVariant right = b[column];

            if (left.userType() == QMetaType::Int || left.userType() == QMetaType::Double) {
                return order == Qt::AscendingOrder ? left.toDouble() < right.toDouble() : left.toDouble() > right.toDouble();
            } else {
                return order == Qt::AscendingOrder ? left.toString() < right.toString() : left.toString() > right.toString();
            }
        });
        emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
    }
} // namespace models