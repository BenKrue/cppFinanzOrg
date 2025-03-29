#include "CSVReader.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>


namespace csv {
    

Q_LOGGING_CATEGORY (LC, "csv::CSVReader", QtDebugMsg);

CSVReader::CSVReader(QObject *parent) : QObject(parent)
{
}

const QStringList &CSVReader::getHeader() const {
    return header;
}

const QVector<QVector<QVariant>> &CSVReader::getData() const {
    return m_data;
}

void CSVReader::saveCSV(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Fehler beim Öffnen der Datei zum Speichern:" << filePath;
        return;
    }

    QTextStream stream(&file);
    stream << header.join(",") << "\n";
    
    for (const auto &row : m_data) {
        QStringList rowStrings;
        for (const auto &cell : row) {
            rowStrings.append(cell.toString());
        }
        stream << rowStrings.join(",") << "\n";
    }

    file.close();
}

void CSVReader::loadCSV(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Fehler beim Öffnen der Datei:" << filePath;
        return;
    }

    QTextStream stream(&file);
    bool firstLine = true;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList values = line.split(";"); // Trennzeichen anpassen, falls nötig

        if (firstLine) {
            header = values;
            firstLine = false;
        } else {
            QVector<QVariant> row;
            for (const QString &value : values) {
                row.append(value); // Hier könnten auch spezifische Datentyp-Umwandlungen erfolgen
            }
            m_data.append(row);
        }
    }
    emit changedData(m_data);
    file.close();
}

} // namespace dataModel