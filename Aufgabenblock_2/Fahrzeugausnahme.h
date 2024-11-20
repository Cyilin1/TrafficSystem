#ifndef FAHRZEUGAUSNAHME_H
#define FAHRZEUGAUSNAHME_H

#include <exception>
#include <iostream>
#include <string>

class Vehicle;
class Weg;

class Fahrzeugausnahme : public std::exception {
protected:
  Vehicle &p_Fahrzeug;
  Weg &p_Weg;

public:
  Fahrzeugausnahme(Vehicle &fzg, Weg &weg);

  virtual void vBearbeiten() const = 0;
};

class Losfahren : public Fahrzeugausnahme {
public:
  Losfahren(Vehicle &fzg, Weg &weg) : Fahrzeugausnahme(fzg, weg) {}

  void vBearbeiten() const override;
};

class Streckenende : public Fahrzeugausnahme {
public:
  Streckenende(Vehicle &fzg, Weg &weg) : Fahrzeugausnahme(fzg, weg) {}

  void vBearbeiten() const override;
};

#endif // FAHRZEUGAUSNAHME_H
