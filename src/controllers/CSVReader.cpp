#include "CSVReader.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>

namespace csv
{
    Q_LOGGING_CATEGORY(LC, "csv::CSVReader", QtDebugMsg);

    CSVReader::CSVReader(QObject *parent) : QObject(parent)
    {
    }

    CSVReader::~CSVReader()
    {
        qCDebug(LC) << __func__ << "destroyed";
    }

    const QStringList &CSVReader::getHeader() const
    {
        return m_header;
    }

    const QVector<QVector<QVariant>> &CSVReader::getData() const
    {
        return m_data;
    }

    void CSVReader::saveCSV(const QString &filePath)
    {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qCWarning(LC) << __func__ << "Fehler beim Öffnen der Datei zum Speichern:" << filePath;
            return;
        }

        QTextStream stream(&file);
        stream << m_header.join(",") << "\n";

        for (const auto &row : m_data)
        {
            QStringList rowStrings;
            for (const auto &cell : row)
            {
                rowStrings.append(cell.toString());
            }
            stream << rowStrings.join(",") << "\n";
        }

        file.close();
    }

    QString detectDelimiter(const QString &filePath)
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qCWarning(LC) << __func__ << "Konnte die Datei nicht öffnen:" << filePath << "Fehler:" << file.errorString();
            return QString();
        }

        QTextStream in(&file);
        QString firstLine = in.readLine();
        file.close();

        // Mögliche Trennzeichen
        QStringList delimiters = {";", "\t", "|"};
        QString detectedDelimiter;

        foreach (const QString &delimiter, delimiters)
        {
            if (firstLine.contains(delimiter))
            {
                detectedDelimiter = delimiter;
                break;
            }
        }

        if (detectedDelimiter.isEmpty())
        {
            qCWarning(LC) << __func__ << "Kein Trennzeichen gefunden in der Datei:" << filePath;
        }
        return detectedDelimiter;
    }

    void CSVReader::loadCSV(const QString &filePath)
    {
        QFile file(filePath);
        QString delimiter = detectDelimiter(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qCWarning(LC) << __func__ << "Fehler beim Öffnen der Datei:" << filePath << "Fehler:" << file.errorString();
            return;
        }

        QTextStream stream(&file);
        bool firstLine = true;

        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            QStringList values = line.split(delimiter);

            if (firstLine)
            {
                m_header = values;
                firstLine = false;
            }
            else
            {
                QVector<QVariant> row;
                for (const QString &value : values)
                {
                    row.append(value); // Hier könnten auch spezifische Datentyp-Umwandlungen erfolgen
                }
                m_data.append(row);
            }
        }
        // emit changedData(m_data);
        file.close();
    }

} // namespace dataModel