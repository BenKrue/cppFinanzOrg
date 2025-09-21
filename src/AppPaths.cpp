#include "AppPaths.hpp"

QString AppPaths::getInstallLocation()
{
    return installLocation;
}

void AppPaths::setInstallLocation(const QString &installLocation)
{
    AppPaths::installLocation = installLocation;
}

QString AppPaths::getAppDataLocation()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

QString AppPaths::getUserConfigLocation()
{
    return userConfigLocation;
}

void AppPaths::setUserConfigLocation(const QString &userConfigLocation)
{
    AppPaths::userConfigLocation = userConfigLocation;
}