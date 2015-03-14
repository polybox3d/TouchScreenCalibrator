#include "Calibration.h"

Calibration::Calibration(QObject *parent) :
    QObject(parent),_inversion_x(false),_inversion_y(false), _x_min(0), _x_max(0), _y_min(0), _y_max(0), _swap_axis(false), _device_id(8),_device_name("Noone")
{
}


void Calibration::loadFromFile(QString filename)
{
    QSettings* settings = new QSettings(filename, QSettings::IniFormat);


    this->_device_name = settings->value("device_name","Noone").toString();
    this->_device_id = settings->value("device_id", 0).toInt();

    this->_x_min = settings->value("x_min", 0 ).toInt();
    this->_x_max = settings->value("x_max", 0 ).toInt();

    this->_inversion_x = settings->value("inversion_x", false ).toBool();

    this->_y_min = settings->value("y_min", 0 ).toInt();
    this->_y_max = settings->value("y_max", 0 ).toInt();

    this->_inversion_y = settings->value("inversion_y", false ).toBool();

    this->_swap_axis = settings->value("swap_axis", false ).toBool();
    settings->sync();
    return;

}

int Calibration::saveToFile(QString path)
{
    QSettings* settings = new QSettings(path, QSettings::IniFormat);


    settings->setValue("device_name", this->_device_name);
    settings->setValue("device_id", this->_device_id);

    settings->setValue("x_min", this->_x_min);
    settings->setValue("x_max", this->_x_max);

    settings->setValue("inversion_x", this->_inversion_x);

    settings->setValue("y_min", this->_y_min );
    settings->setValue("y_max", this->_y_max);

    settings->setValue("inversion_y", this->_inversion_y);

    settings->setValue("swap_axis", this->_swap_axis);
    settings->sync();
    return 0;
}



bool Calibration::inversion_x () const {
  return _inversion_x;
}

void Calibration::setInversion_x ( bool inversion_x ) {
  _inversion_x = inversion_x;
}


bool Calibration::inversion_y () const {
  return _inversion_y;
}

void Calibration::setInversion_y ( bool inversion_y ) {
  _inversion_y = inversion_y;
}


bool Calibration::swap_axis () const {
  return _swap_axis;
}

void Calibration::setSwap_axis ( bool swap_axis ) {
  _swap_axis = swap_axis;
}



int Calibration::threshold () const {
  return _threshold;
}

void Calibration::setThreshold ( int threshold ) {
  _threshold = threshold;
}



int Calibration::x_min () const {
  return _x_min;
}

void Calibration::setX_min ( int x_min ) {
  _x_min = x_min;
}


int Calibration::x_max () const {
  return _x_max;
}

void Calibration::setX_max ( int x_max ) {
  _x_max = x_max;
}


int Calibration::y_min () const {
  return _y_min;
}

void Calibration::setY_min ( int y_min ) {
  _y_min = y_min;
}


int Calibration::y_max () const {
  return _y_max;
}

void Calibration::setY_max ( int y_max ) {
  _y_max = y_max;
}


int Calibration::device_id () const {
  return _device_id;
}

void Calibration::setDevice_id ( int device_id ) {
  _device_id = device_id;
}


QString Calibration::device_name () const {
  return _device_name;
}

void Calibration::setDevice_name ( QString device_name ) {
  _device_name = device_name;
}
