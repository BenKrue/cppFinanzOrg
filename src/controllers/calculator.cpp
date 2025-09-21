#include "calculator.hpp"

#include <QLOGGINGCATEGORY>
#include <QDebug>

namespace controllers
{
    namespace calculator
    {

        Q_LOGGING_CATEGORY(LC, "Calculator", QtDebugMsg);

        Calculator::Calculator(QObject *parent)
            : QObject(parent)
        {
        }

        Calculator::~Calculator()
        {
            qCDebug(LC) << __func__ << "destroyed";
        }

        double Calculator::sum(const double number)
        {
            return number;
        }
        QMap<QString, double> Calculator::calculateData(const QVariantList &category, const QVariantList &data)
        {
            double sum = 0.0000;
            if (category.size() == data.size())
            {
                QMap<QString, double> result;
                for (int i = 0; i < category.size(); ++i)
                {
                    if (category[i] == "Haus-Nebenkosten")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Haus-Nebenkosten"] += number;
                        }
                    }
                    if (category[i] == "Steuer")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Steuer"] += number;
                        }
                    }
                    if (category[i] == "Kredit")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Kredit"] += number;
                        }
                    }
                    if (category[i] == "Sparen")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Sparen"] += number;
                        }
                    }
                    if (category[i] == "Kommunikation")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Kommunikation"] += number;
                        }
                    }
                    if (category[i] == "Versicherung")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Versicherung"] += number;
                        }
                    }
                    if (category[i] == "Verein")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Verein"] += number;
                        }
                    }
                    if (category[i] == "Gewerkschaft")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Gewerkschaft"] += number;
                        }
                    }
                    if (category[i] == "Essen")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Essen"] += number;
                        }
                    }
                    if (category[i] == "Tanken")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Tanken"] += number;
                        }
                    }
                    if (category[i] == "Ausflüge")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Ausflüge"] += number;
                        }
                    }
                    if (category[i] == "Rechtsanwalt")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Rechtsanwalt"] += number;
                        }
                    }
                    if (category[i] == "Gehalt")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Gehalt"] += number;
                        }
                    }
                    if (category[i] == "Pflegegeld")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Pflegegeld"] += number;
                        }
                    }
                    if (category[i] == "Kindergeld")
                    {
                        bool ok;
                        double number = data[i].toString().replace(',', '.').toDouble(&ok);
                        if (ok)
                        {
                            result["Kindergeld"] += number;
                        }
                    }
                }
                return result;
            }
            return {};
        }

        double Calculator::sumByCategory(const QVector<QVariant> &data, enums::tabel::header headerType)
        {
            double sum = 0.0;

            for (const QVariant &value : data)
            {
                sum += value.toDouble();
            }
            return sum;
        }
    } // namespace calculator
} // namespace controllers