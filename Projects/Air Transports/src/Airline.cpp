//
// Created by simao on 12/27/2022.
//

#include "Airline.h"

Airline::Airline(string code, string name, string callSign, string country) {
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}

string Airline::getCode() const
{return this->code;}

string Airline::getName() const
{return this->name;}

string Airline::getCallSign() const
{return this->callSign;}

string Airline::getCountry() const
{return this->country;}

Airline::Airline() {

}





