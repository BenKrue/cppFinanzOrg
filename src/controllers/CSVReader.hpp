#pragma once

#include <QString>
#include <QVector>
#include <QVariant>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QObject>

namespace csv {

class CSVReader : public QObject {
    Q_OBJECT
public:

    CSVReader(QObject *parent = nullptr);
    const QVector<QVector<QVariant>> &getData() const;
    const QStringList &getHeader() const;
    void saveCSV(const QString &filePath);
    void loadCSV(const QString &filePath);

    QStringList m_header;
    QVector<QVector<QVariant>> m_data;
private:

signals:
    QVector<QVector<QVariant>> changedData(QVector<QVector<QVariant>> data);

};
} // namespace csv