#include "Calibration.h"

Calibration::Calibration(QObject *parent) :
    QObject(parent),_inversion_x(false),_inversion_y(false), _x_min(0), _x_max(0), _y_min(0), _y_max(0), _swap_axis(false), _device_id(8),_device_name("Noone")
{
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
