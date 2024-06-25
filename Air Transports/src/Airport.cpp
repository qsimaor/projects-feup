//
// Created by simao on 12/27/2022.
//

#include "Airport.h"

Airport::Airport() {}

Airport::Airport(string code, string name, string city, string country, string latitude, string longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getCode() const
{return this->code;}

string Airport::getName() const
{return this->name;}

string Airport::getCity() const
{return this->city;}

string Airport::getCountry() const
{return this->country;}

string Airport::getLatitude() const
{return this->latitude;}

string Airport::getLongitude() const
{return this->longitude;}
