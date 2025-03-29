#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QLoggingCategory>
#include <QScreen>

#include "models/tableModel.hpp"
#include "models/dataModel.hpp"
#include "controllers/CSVReader.hpp"
#include "controllers/calculator.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

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
    QSharedPointer<calculator::Calculator> calculator;
    calculator = QSharedPointer<calculator::Calculator>::create();
    dataModel dataModel(calculator, csvReader);

    csvReader->loadCSV("C:/src/cppFinanzOrg/FinanzOrg.csv");

    const QStringList &header = csvReader->getHeader();
    const QVector<QVector<QVariant>> &data = csvReader->getData();

    TableModel myTableModel(header, data, &engine);
    engine.rootContext()->setContextProperty("tableModel", &myTableModel);

    const QUrl url(QStringLiteral("qrc:/qml/ApplicationWindows.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    if(engine.rootObjects().isEmpty()){
        qWarning() << "Unable to load QML";
    }

    return app.exec();
}
