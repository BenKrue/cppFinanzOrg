#pragma once

#include <QObject>

namespace category
{

enum class categoryType { 
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

class Category : public QObject {
    Q_OBJECT
public:
    explicit Category(QObject *parent = nullptr);
};

}