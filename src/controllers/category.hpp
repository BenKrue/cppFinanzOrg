#pragma once

#include <QObject>
#include <QSharedPointer>

// TODO: Kategorien hinzufügen und für die Berechnungen verwenden

namespace controllers
{
    namespace category
    {

        enum class categoryType
        {
            RECIPIENT,
            IDENTIFICATION,
            MEMBER_NUMBER,
            AMOUNT,
            PAYMENT_DATE,
            CATEGORY,
            BANK_ACCOUNT,
            OWNER,
            TAX_INFORMATION,
            REMARK
        };

        class Category : public QObject
        {
            Q_OBJECT
        public:
            explicit Category(QObject *parent = nullptr);
            ~Category();

            void setCategoryType(QString categoryType);
            controllers::category::categoryType getCategoryType();

        private:
            controllers::category::categoryType m_categoryType;
        };

    } // namespace category
} // namespace controllers