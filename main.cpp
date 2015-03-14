#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QSettings* settings = new QSettings(QDir::currentPath() + "/settings.ini", QSettings::IniFormat);
    settings->setValue("default_device_id", "8");
    settings->sync();

    QCoreApplication::setOrganizationName("Polybox3D");
    QCoreApplication::setOrganizationDomain("www.polybox3d.com");
    QCoreApplication::setApplicationName("TouchScreenCalibrator");
    /***  GIT_VERSION defined in .pro file ***/
    QCoreApplication::setApplicationVersion( GIT_VERSION );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
