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

    _update_list.start( DELAY_UPDATE_LIST );

    ui->threshold->setValue( _calibration.threshold() );

    updateUi();

    on_allDevice_stateChanged( 0 );
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
    repaintButtons( ui->swapAxis, _calibration.swap_axis() );
    repaintButtons( ui->invertX, _calibration.inversion_x() );
    repaintButtons( ui->invertY, _calibration.inversion_y() );
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
}

void MainWindow::on_invertX_clicked()
{
    _calibration.setInversion_x( !_calibration.inversion_x() );
}

void MainWindow::on_invertY_clicked()
{
    _calibration.setInversion_y( !_calibration.inversion_y() );
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
    messageBox.information(0, "Information",_xinput_calibrator->readAllStandardOutput()+_xinput_calibrator->readAllStandardError());
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
    /*if ( ui->availableDevice->count() == 0 )
    {
        parameters << "--fake";
    }*/
    parameters << "--misclick"<<QString::number(_calibration.threshold()) ;
    _xinput_calibrator = new QProcess( this );
    connect( _xinput_calibrator , SIGNAL(finished(int,QProcess::ExitStatus)), this,SLOT(xinputcalibratorFinished(int,QProcess::ExitStatus)));
    connect( _xinput_calibrator , SIGNAL(error(QProcess::ProcessError)), this,SLOT(xinputcalibratorError(QProcess::ProcessError)));
    _xinput_calibrator->start( command, parameters);


    return;
}

void MainWindow::on_threshold_editingFinished()
{
    _calibration.setThreshold( ui->threshold->value());
}

void MainWindow::on_test_clicked()
{
    QString command = XINPUT_COMMAND;
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

void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save settings for this device"),
                                                    "./"+_calibration.device_name()+".tsc",
                                                    tr("TouchScreenCalibration(*.tsc)"));
    if ( fileName != NULL && ! fileName.isEmpty() )
    {
        _calibration.saveToFile( fileName );
    }
}

void MainWindow::on_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select a TouchScreenCalibration file"), ".", tr("TouchScreenCalibration(*.tsc)"));
    if ( fileName != NULL && ! fileName.isEmpty() )
    {
        _calibration.loadFromFile( fileName );
    }
}

void MainWindow::on_apply_clicked()
{
    QSettings* settings = new QSettings(QDir::currentPath() + "/settings.ini", QSettings::IniFormat);
    int pos = 0;

    QString command_xinput = XINPUT_COMMAND;
    QString command;
    QTextStream stream_command( &command );
    stream_command<<command_xinput<< " set-prop "<< QString::number(_calibration.device_id())<<" \"Evdev Axis Inversion\" "<<QString::number(_calibration.inversion_x())<<" "<<QString::number(_calibration.inversion_y())<<"\n";
    stream_command<<command_xinput<< " set-prop "<< QString::number(_calibration.device_id())<<" \"Evdev Axes Swap\" "<<QString::number(_calibration.swap_axis())<<"\n";
    stream_command<<command_xinput<< " set-prop "<<"--type=int "<<"--format=32 "<< QString::number(_calibration.device_id())<<" \"Evdev Axis Calibration\" "<<QString::number(_calibration.x_min())<<" "<<QString::number(_calibration.x_max())<<" "<<QString::number(_calibration.y_min())<<" "<<QString::number(_calibration.y_max())<<"\n";

    QByteArray new_xsession;
    bool exec_found = false;
    QFile file(QDir::homePath()+"/.xsession");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text ))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        // include command before 'exec'
        if ( line.indexOf("exec") != -1)
        {
            new_xsession.append( stream_command.readAll() );
            file.seek( pos );
        }
        pos = file.pos();

        // ignor prev statement for the same device
        if ( line.indexOf("set-prop "+QString::number(_calibration.device_id())) != -1 )
        {
            continue;
        }
        if ( line.indexOf("--format=32 "+QString::number(_calibration.device_id())) != -1 )
        {
            continue;
        }
        new_xsession.append( line );
    }
    // we had exec for Xsession.
    if ( !exec_found )
    {
        new_xsession.append( stream_command.readAll() );
        if ( QFile::exists("/usr/bin/startkde") )
        {
            new_xsession.append("/usr/bin/startkde\n");
        }
        else if ( QFile::exists("/usr/bin/startgnome\n") )
        {
            new_xsession.append("/usr/bin/startgnome\n");
        }
        else if ( QFile::exists("/usr/bin/startxfce\n") )
        {
            new_xsession.append("/usr/bin/startxfce\n");
        }

    }
    file.seek( 0 );
    file.write( new_xsession );

    file.close();

    //settings->setValue("default_tsc_file",);
}


void MainWindow::on_allDevice_stateChanged(int arg1)
{
    ui->availableDevice->clear();

    if ( arg1 )
    {
        QString command_xinput = XINPUT_COMMAND;
        QStringList parameters;

        QByteArray data;

        parameters << "--list";
        _xinput_calibrator = new QProcess( this );
        _xinput_calibrator->start( command_xinput, parameters, QIODevice::ReadWrite);
        while ( _xinput_calibrator->waitForReadyRead() )
        {
            data.append(_xinput_calibrator->readAll());
        }
        QTextStream list(data);
        QString device;
        while ( !list.atEnd())
        {
            device = list.readLine();
            if ( device.indexOf("Virtual") != -1 )
            {
                if ( ui->allDevice->checkState() == Qt::PartiallyChecked && device.indexOf("Virtual core keyboard") != -1 )
                {
                    break;
                }
                continue;
            }
            ui->availableDevice->addItem( device.section('\t',0,0).split("↳").at(1),
                                          device.section('\t',1,1).split("=").at(1) );
        }
    }
    else
    {
        QString command = QDir::homePath()+"/xinput_calibrator/src/xinput_calibrator";
        QStringList parameters;
        QByteArray data;

        parameters << "--list";
        _xlist = new QProcess( this );
        _xlist->start( command, parameters );
        while ( _xlist->waitForReadyRead() )
        {
            data.append(_xlist->readAll()+_xlist->readAllStandardError());
        }
        if ( data.indexOf("No calibratable devices found") != -1 )
        {
            ui->startCalibration->setEnabled( false );
        }
        else
        {
            ui->startCalibration->setEnabled( true );
        }

    }
}

void MainWindow::on_availableDevice_currentIndexChanged(int index)
{
    _calibration.setDevice_id( ui->availableDevice->itemData( index ).toInt() );
    _calibration.setDevice_name( ui->availableDevice->itemText( index ) );
}
