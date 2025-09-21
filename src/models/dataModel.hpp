#pragma once

#include "../controllers/CSVReader.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QMap>

// forward declaration of class
namespace controllers
{
    namespace calculator
    {
        class Calculator;
    }
}

namespace models
{
    namespace dataModel
    {

        class dataModel : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QVariantList werte READ werte NOTIFY werteChanged)
            Q_PROPERTY(QVariantList category READ category NOTIFY categoryChanged)

        public:
            explicit dataModel(QSharedPointer<csv::CSVReader> csvReader, QObject *parent = nullptr);
            ~dataModel();

            const QMap<QString, QVector<QVariant>> &getColumnMap() const { return m_columnMap; }
            QVariantList getDataByCategory();

            QVariantList werte() const { return m_werte; }
            QVariantList category() const { return m_dataByCategory; }

        private:
            void getData();
            void dataByCategory(const QVector<QVector<QVariant>> &data);
            QMap<QString, QVector<QVariant>> m_columnMap;

            QVariantList m_dataByCategory;
            QVariantList m_werte;

            QSharedPointer<csv::CSVReader> m_csvReader;
            QSharedPointer<controllers::calculator::Calculator> m_calculator{nullptr};

        signals:
            void werteChanged();
            void categoryChanged();
        };

    } // namespace dataModel
} // namespace models