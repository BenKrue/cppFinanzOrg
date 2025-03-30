#pragma once

#include "../global_Enums.hpp"

#include <QObject>
#include <QString>
#include <QList>
#include <QVariantMap>
#include <QMap>

// TODO: Klasse erstellen, die die Berechnungen macht und die Daten an die View weitergibt
namespace controllers
{
    namespace calculator
    {

        class Calculator : public QObject
        {
            Q_OBJECT
        public:
            explicit Calculator(QObject *parent = nullptr);
            ~Calculator();

            QMap<QString, double> calculateData(const QVariantList &category, const QVariantList &data);
            double sumByCategory(const QVector<QVariant> &data, enums::categoryType categoryType);

        signals:
            void calculationsDone(const QVector<QVector<QVariant>> &data);

        private:
            double sum(const double number);
        };

    } // namespace calculator
} // namespace controllers