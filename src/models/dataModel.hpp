#pragma once

#include "../controllers/calculator.hpp"
#include "../controllers/CSVReader.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QMap>

class dataModel : public QObject
{
    Q_OBJECT

public:
    explicit dataModel(QSharedPointer<calculator::Calculator> calculator, QSharedPointer<csv::CSVReader> csvReader, QObject *parent = nullptr);
    ~dataModel() = default;

    const QMap<QString, QVector<QVariant>> &getColumnMap() const { return m_columnMap; }

private:
    void getData();
    void dataByCategory(const QVector<QVector<QVariant>> &data);
    QMap<QString, QVector<QVariant>> m_columnMap;

    QSharedPointer<calculator::Calculator> m_calculator;
    QSharedPointer<csv::CSVReader> m_csvReader;

public slots:
    void setDataByCategory(const QVector<QVector<QVariant>> &data);

};