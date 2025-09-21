#include <QCoreApplication>
#include <QStandardPaths>
#include <QDebug>

class AppPaths
{
public:
    static QString getInstallLocation();
    static void setInstallLocation(const QString &installLocation);

    static QString getAppDataLocation();

    static QString getUserConfigLocation();

    static void setUserConfigLocation(const QString &userConfigLocation);

private:
    static QString installLocation;
    static QString userConfigLocation;
};

// QString AppPaths::installLocation;
// QString AppPaths::userConfigLocation;

// int main(int argc, char *argv[])
// {
//     QCoreApplication app(argc, argv);

//     QString installPath = AppPaths::getInstallLocation();
//     qDebug() << "Install path:" << installPath;

//     QString appDataPath = AppPaths::getAppDataLocation();
//     qDebug() << "App data path:" << appDataPath;

//     QString userConfigPath = AppPaths::getUserConfigLocation();
//     qDebug() << "User config path:" << userConfigPath;

//     AppPaths::setUserConfigLocation("/path/to/user/config");
//     userConfigPath = AppPaths::getUserConfigLocation();
//     qDebug() << "User config path (after setting):" << userConfigPath;

//     return app.exec();
// }