#pragma once

#include "CSVReader.hpp"
#include "../global_Enums.hpp"

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include <QList>
#include <QVariantMap>
#include <QMap>

namespace calculator {

class Calculator : public QObject {
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = nullptr);

private:


signals:
    void calculationsDone(const QVector<QVector<QVariant>> &data);

public slots:
    void calculateData(const QVector<QVector<QVariant>> &data);
    double sumByCategory(const QVector<QVariant> &data, enums::categoryType categoryType);

};

}