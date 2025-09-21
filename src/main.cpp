#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QLoggingCategory>
#include <QScreen>
#include <QShortcut>
#include <QKeySequence>
#include <QQuickWindow>
#include <QKeyEvent>

#include "models/chartModel.hpp"
#include "models/dataModel.hpp"
#include "models/tableModel.hpp"
#include "controllers/CSVReader.hpp"
#include "controllers/calculator.hpp"
#include "AppPaths.hpp"

class ReloadHandler : public QObject
{
    Q_OBJECT
public:
    ReloadHandler(QQmlApplicationEngine &engine, const QUrl &url)
        : m_engine(engine), m_url(url) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_R)
            {
                qDebug() << "Reloading QML...";
                reloadQml();
                return true; // Event verbraucht
            }
        }
        return QObject::eventFilter(obj, event);
    }

private:
    void reloadQml()
    {
        // Alte Root-Objekte zerstören
        for (QObject *obj : m_engine.rootObjects())
            obj->deleteLater();

        m_engine.clearComponentCache();
        m_engine.load(m_url);
    }

    QQmlApplicationEngine &m_engine;
    QUrl m_url;
};

QString AppPaths::installLocation;
QString AppPaths::userConfigLocation;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QString installPath = AppPaths::getInstallLocation();
    qDebug() << "Install path:" << installPath;

    QString appDataPath = AppPaths::getAppDataLocation();
    qDebug() << "App data path:" << appDataPath;

    QString userConfigPath = AppPaths::getUserConfigLocation();
    qDebug() << "User config path:" << userConfigPath;

    AppPaths::setUserConfigLocation("/path/to/user/config");
    userConfigPath = AppPaths::getUserConfigLocation();
    qDebug() << "User config path (after setting):" << userConfigPath;

    QLoggingCategory::setFilterRules("qt.qml.warning=true\nqt.qml.info=true\nqt.qml.debug=true");
    app.setWindowIcon(QIcon(":/images/f_icon.ico"));

    QQmlApplicationEngine engine;

    const QScreen *screen = QGuiApplication::primaryScreen();
    const QSizeF size = screen->size();
    const QSizeF sizeF = screen->size();
    const QSize sizeI = screen->size();

    engine.rootContext()->setContextProperty("screenWidth", size.width());
    engine.rootContext()->setContextProperty("screenHeight", size.height());
    engine.rootContext()->setContextProperty("screenWidthF", sizeF.width());
    engine.rootContext()->setContextProperty("screenHeightF", sizeF.height());
    engine.rootContext()->setContextProperty("screenWidthI", sizeI.width());
    engine.rootContext()->setContextProperty("screenHeightI", sizeI.height());

    QSharedPointer<csv::CSVReader> csvReader;
    csvReader = QSharedPointer<csv::CSVReader>::create();
    csvReader->loadCSV(appDataPath + "/FinanzOrg.csv");
    csvReader->loadCSV("C:/src/cpp Projekte/cppFinanzOrg/FinanzOrg.csv");

    TableModel myTableModel(csvReader, &engine);
    engine.rootContext()->setContextProperty("tableModel", &myTableModel);
    ChartModel myChartModel(dataModel.getDataByCategory(), &engine);

    // QList<QVariant> werte;
    // QList<QVariant> category;
    // for (int i = 0; i < myChartModel.rowCount(); i++)
    // {

    //     werte.append(myChartModel.data(myChartModel.index(i, 0), 257).toDouble());
    //     category.append(dataModel.getDataByCategory().keys()[i]);
    //     qCDebug(LC) << werte[i];
    //     qCDebug(LC) << category[i];
    // }
    // engine.rootContext()->setContextProperty("werte", werte);
    // engine.rootContext()->setContextProperty("category", category);
    engine.rootContext()->setContextProperty("dataModel", &dataModel);

#ifdef Live_Reload
    const QUrl url(QStringLiteral("qrc:/qml/ApplicationWindows.qml"));
#else
    const QUrl url(QUrl::fromLocalFile("qml/ApplicationWindows.qml"));
#endif

    engine.load(url);

    ReloadHandler handler(engine, url);
    app.installEventFilter(&handler);

    return app.exec();
}

#include "main.moc"