#include "calculator.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>


namespace calculator {

Q_LOGGING_CATEGORY (LC, "Calculator", QtDebugMsg);

Calculator::Calculator(QObject *parent) 
    : QObject(parent)
{
    
}

void Calculator::calculateData(const QVector<QVector<QVariant>> &data)
{
    emit calculationsDone(data);
}

double Calculator::sumByCategory(const QVector<QVariant> &data, enums::categoryType categoryType)
{
    double sum = 0.0;


    for (const QVariant &value : data)
    {
        sum += value.toDouble();
    }
    return sum;
}
} // namespace calculator