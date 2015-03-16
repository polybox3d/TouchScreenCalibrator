#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QSettings>
#include <QMessageBox>
#include <QFontDatabase>

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
    /***
     *  Check If XINPUT and XINPUT_CALIBRATOR are isntalled :)
     *
     * **/
    /** Font Awsome Version 4.3.0  -- http://fortawesome.github.io/Font-Awesome/ -- **/
    QFontDatabase::addApplicationFont(":/fontawesome-webfont.ttf");

    if ( ! QFile::exists("/usr/bin/xinput") )
    {
        QMessageBox::critical(0, QWidget::tr("Error, missing package: xinput"), QWidget::tr("Error, xinput package is not installed.  \n \n Use this command :  \t sudo apt-get install xinput \n") );
    }
    else if ( ! QFile::exists( QDir::homePath()+ "/xinput_calibrator") )
    {
        QMessageBox::critical(0, QWidget::tr("Error, missing folder: xinput_calibrator"), QWidget::tr("Error, xinput_calibrator folder not found.  \n \n Commands :  \t cd ~; git clone https://github.com/tias/xinput_calibrator.git \n") );
    }
    else if ( ! QFile::exists( QDir::homePath()+ "/xinput_calibrator/src/xinput_calibrator") )
    {
        QMessageBox::critical(0, QWidget::tr("Error, missing executable: xinput_calibrator"), QWidget::tr("Error, xinput_calibrator executable not found.  \n \n Use this command :  \n\n cd ~/xinput_calibrator && ./autogen.sh && make  \n") );
    }
    else
    {
        MainWindow w;
        w.show();

        return a.exec();
    }
}
