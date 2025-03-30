#include "dataModel.hpp"

#include "../controllers/calculator.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>

namespace models
{
    namespace dataModel
    {

        Q_LOGGING_CATEGORY(LC, "dataModel", QtDebugMsg);

        dataModel::dataModel(QSharedPointer<csv::CSVReader> csvReader, QObject *parent)
            : QObject(parent),
              m_csvReader(csvReader)
        {
            getData();
        }

        dataModel::~dataModel()
        {
            qCDebug(LC) << __func__ << "destructor";
        }

        void dataModel::getData()
        {
            const QVector<QVector<QVariant>> &data = m_csvReader->getData();
            dataByCategory(data);
        }

        QMap<QString, double> dataModel::getDataByCategory()
        {
            return {}; //m_dataByCategory;
        }

        void dataModel::dataByCategory(const QVector<QVector<QVariant>> &data)
        {
            QMap<QString, QVector<QVariant>> columnMap;
            if (data.isEmpty())
            {
                return;
            }

            auto headers = m_csvReader->getHeader();
            for (int col = 0; col < headers.size(); ++col)
            {
                for (int row = 0; row < data.size(); ++row)
                {
                    columnMap[headers[col]].append(data[row][col]);
                }
            }
            auto dataByCategory = m_calculator->calculateData(columnMap.value("Kategorie"), columnMap.value("Betrag [Monat]"));
            QVariantList dataList;
            QVariantList dataCategory;
            for (auto it = dataByCategory.begin(); it != dataByCategory.end(); ++it) {
                dataList.append(QVariant(it.value()));
                dataCategory.append(QVariant(it.key()));
            }
            m_werte = dataList;
            m_dataByCategory = dataCategory;
            m_columnMap = columnMap;
            emit categoryChanged();
            emit werteChanged();
        }

    } // namespace dataModel
} // namespace models
