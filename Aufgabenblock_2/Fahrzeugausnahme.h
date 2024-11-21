#ifndef FAHRZEUGAUSNAHME_H
#define FAHRZEUGAUSNAHME_H

#include <exception>
#include <iostream>
#include <string>

class Vehicle;
class Weg;

class VehicleException : public std::exception {
protected:
  Vehicle &m_vehicle;
  Weg &p_Weg;

public:
  VehicleException(Vehicle &vehicle, Weg &weg);

  virtual void handleException() const = 0;
};

class StartException : public VehicleException {
public:
  StartException(Vehicle &vehicle, Weg &weg) : VehicleException(vehicle, weg) {}

  void handleException() const override;
};

class EndOfPathException : public VehicleException {
public:
  EndOfPathException(Vehicle &vehicle, Weg &weg)
      : VehicleException(vehicle, weg) {}

  void handleException() const override;
};

#endif // FAHRZEUGAUSNAHME_H
