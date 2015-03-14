#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QAction>

#include "Calibration.h"

#define DELAY_UPDATE_UI 50 // ms
#define XINPUT_COMMAND "/usr/bin/xinput"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateUi();

private slots:
    void on_xMaxMore_clicked();

    void on_xMinMore_clicked();

    void on_xMaxMinus_clicked();

    void on_xMinMinus_clicked();

    void on_yMinMinus_clicked();

    void on_yMinMore_clicked();

    void on_yMaxMinus_clicked();

    void on_yMaxMore_clicked();

    void on_swapAxis_clicked();

    void on_invertX_clicked();

    void on_invertY_clicked();

    void on_startCalibration_clicked();

    void xinputcalibratorFinished(int,QProcess::ExitStatus);
    void xinputcalibratorError(QProcess::ProcessError);


    void on_threshold_editingFinished();

    void on_test_clicked();

    void on_save_clicked();

    void on_load_clicked();

    void on_apply_clicked();

    void on_allDevice_stateChanged(int arg1);

    void on_availableDevice_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Calibration _calibration;
    QTimer _update_ui;
    int _increasedValue;
    QProcess* _xinput_calibrator;

    void repaintButtons( QPushButton* b, bool state);
};

#endif // MAINWINDOW_H
