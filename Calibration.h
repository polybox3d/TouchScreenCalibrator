#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QObject>

class Calibration : public QObject
{
    Q_OBJECT
public:
    explicit Calibration(QObject *parent = 0);


    bool inversion_x () const;
    void setInversion_x ( bool inversion_x ) ;

    bool inversion_y () const;
    void setInversion_y ( bool inversion_y ) ;

    bool swap_axis () const;
    void setSwap_axis ( bool swap_axis ) ;

    int x_min () const;
    void setX_min ( int x_min ) ;

    int x_max () const;
    void setX_max ( int x_max ) ;

    int y_min () const;
    void setY_min ( int y_min ) ;

    int y_max () const;
    void setY_max ( int y_max ) ;

    int device_id () const;
    void setDevice_id ( int device_id ) ;


    int threshold () const;
    void setThreshold ( int threshold ) ;

    QString getXInputFormat();


signals:

public slots:
private:
    bool _inversion_x;
    bool _inversion_y;

    bool _swap_axis;

    int _x_min;
    int _x_max;

    int _y_min;
    int _y_max;

    int _threshold;

    int _device_id;
    QString _device_name;

};

#endif // CALIBRATION_H
