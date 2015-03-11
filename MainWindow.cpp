#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _xinput_calibrator = NULL;
    _increasedValue = 1 ;
    _update_ui.start( DELAY_UPDATE_UI );
    connect(&_update_ui, SIGNAL(timeout()), this, SLOT(updateUi()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUi()
{
    ui->min_x->setText( QString::number(_calibration.x_min()));
    ui->max_x->setText( QString::number(_calibration.x_max()));

    ui->min_y->setText( QString::number(_calibration.y_min()));
    ui->max_y->setText( QString::number(_calibration.y_max()));

}

void MainWindow::on_xMaxMore_clicked()
{
    _calibration.setX_max( _calibration.x_max() + _increasedValue );
}
void MainWindow::on_xMaxMinus_clicked()
{
    _calibration.setX_max( _calibration.x_max() - _increasedValue );
}

void MainWindow::on_xMinMore_clicked()
{
    _calibration.setX_min( _calibration.x_min() + _increasedValue );
}

void MainWindow::on_xMinMinus_clicked()
{
    _calibration.setX_min( _calibration.x_min() - _increasedValue );
}

void MainWindow::on_yMinMinus_clicked()
{
    _calibration.setY_min( _calibration.y_min() - _increasedValue );
}

void MainWindow::on_yMinMore_clicked()
{
    _calibration.setY_min( _calibration.y_min() + _increasedValue );
}

void MainWindow::on_yMaxMinus_clicked()
{
    _calibration.setY_max( _calibration.y_max() - _increasedValue );
}

void MainWindow::on_yMaxMore_clicked()
{
    _calibration.setY_max( _calibration.y_max() + _increasedValue );
}


void MainWindow::on_swapAxis_clicked()
{
    _calibration.setSwap_axis( !_calibration.swap_axis() );
    repaintButtons( ui->swapAxis, _calibration.swap_axis() );
}

void MainWindow::on_invertX_clicked()
{
    _calibration.setInversion_x( !_calibration.inversion_x() );
    repaintButtons( ui->invertX, _calibration.inversion_x() );
}

void MainWindow::on_invertY_clicked()
{
    _calibration.setInversion_y( !_calibration.inversion_y() );
    repaintButtons( ui->invertY, _calibration.inversion_y() );
}

void MainWindow::repaintButtons(QPushButton *b, bool state)
{
    if( state )
    {
        b->setStyleSheet("color: rgb(55, 240, 75);");
    }
    else
    {
        b->setStyleSheet("color: rgb(95, 141, 211);");
    }

}
void MainWindow::xinputcalibratorFinished(int exitCode, QProcess::ExitStatus exitStatus )
{

    QMessageBox messageBox;
    messageBox.information(0, "Information",_xinput_calibrator->readAll());
    messageBox.setFixedSize(500,200);

}

void MainWindow::xinputcalibratorError(QProcess::ProcessError error)
{
    QMessageBox messageBox;
    messageBox.critical(0,"Error", tr("\n\nError on starting xinput_calibrator ")+_xinput_calibrator->readAllStandardError()+"\n\n");
    messageBox.setFixedSize(500,200);
}

void MainWindow::on_startCalibration_clicked()
{
    if ( _xinput_calibrator != NULL && ! _xinput_calibrator->atEnd() )
    {
        _xinput_calibrator->kill();
    }
    QString command = "../xinput_calibrator/src/xinput_calibrator";
    QStringList parameters;
    if ( ui->availableDevice->count() == 0 )
    {
        parameters << "--fake";
    }
    _xinput_calibrator = new QProcess( this );
    connect( _xinput_calibrator , SIGNAL(finished(int,QProcess::ExitStatus)), this,SLOT(xinputcalibratorFinished(int,QProcess::ExitStatus)));
    connect( _xinput_calibrator , SIGNAL(error(QProcess::ProcessError)), this,SLOT(xinputcalibratorError(QProcess::ProcessError)));
    _xinput_calibrator->start( command, parameters);


    return;
    /*QString command = "../xinput_calibrator/src/xinput_calibrator";
    QStringList parameters;
    parameters << "--list";
    _xinput_calibrator = new QProcess( this );
    connect( _xinput_calibrator , SIGNAL(finished(int,QProcess::ExitStatus)), this,SLOT(xinputcalibratorFinished(int,QProcess::ExitStatus)));
    connect( _xinput_calibrator , SIGNAL(error(QProcess::ProcessError)), this,SLOT(xinputcalibratorError(QProcess::ProcessError)));
    _xinput_calibrator->start( command, parameters);*/
}

void MainWindow::on_threshold_editingFinished()
{
    _calibration.setThreshold( ui->threshold->value());
}

void MainWindow::on_test_clicked()
{
    QString command = "/usr/bin/xinput";
    QStringList parameters;


    parameters << "set-prop"<< QString::number(_calibration.device_id())<<"Evdev Axis Inversion"<<QString::number(_calibration.inversion_x())<<QString::number(_calibration.inversion_y());
    _xinput_calibrator = new QProcess( this );
    _xinput_calibrator->execute( command, parameters);

    parameters.clear();
    parameters << "set-prop"<< QString::number(_calibration.device_id())<<"Evdev Axes Swap"<<QString::number(_calibration.swap_axis());
    _xinput_calibrator = new QProcess( this );
    _xinput_calibrator->execute( command, parameters);

    parameters.clear();
    parameters << "set-prop"<<"--type=int"<<"--format=32"<< QString::number(_calibration.device_id())<<"Evdev Axis Calibration"<<QString::number(_calibration.x_min())<<QString::number(_calibration.x_max())<<QString::number(_calibration.y_min())<<QString::number(_calibration.y_max());
    _xinput_calibrator = new QProcess( this );
    _xinput_calibrator->execute( command, parameters);

}
