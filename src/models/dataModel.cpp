#include "dataModel.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>


Q_LOGGING_CATEGORY (LC, "dataModel", QtDebugMsg);

dataModel::dataModel(QSharedPointer<calculator::Calculator> calculator, QSharedPointer<csv::CSVReader> csvReader, QObject *parent)
    : QObject(parent),
      m_calculator(calculator),
      m_csvReader(csvReader)
{
    QObject::connect(m_csvReader.data(), &csv::CSVReader::changedData, m_calculator.data(), &calculator::Calculator::calculateData);
    QObject::connect(m_calculator.data(), &calculator::Calculator::calculationsDone, this, &dataModel::setDataByCategory);

    getData();

}

void dataModel::getData()
{
    const QVector<QVector<QVariant>> &data = m_csvReader->getData();
    dataByCategory(data);
}

void dataModel::setDataByCategory(const QVector<QVector<QVariant>> &data)
{
    //qCDebug(LC) << __func__ << "setDataByCategory" << data;
}

void dataModel::dataByCategory(const QVector<QVector<QVariant>> &data) {
    QMap<QString, QVector<QVariant>> columnMap;

    if (data.isEmpty()) {
        return;
    }

    QVector<QVariant> headers = data[0];

    for (int col = 0; col < headers.size(); ++col) {
        QString columnName = headers[col].toString();

        for (int row = 1; row < data.size(); ++row) {
            columnMap[columnName].append(data[row][col]);
        }
    }
    m_columnMap = columnMap;
}