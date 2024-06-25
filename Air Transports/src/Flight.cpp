//
// Created by simao on 12/28/2022.
//

#include "Flight.h"

Flight::Flight(string source, string target, string airline) {
    this->source = source;
    this->target = target;
    this->airline = airline;
}

string Flight::getSource() const
{return this->source;}

string Flight::getTarget() const
{return this->target;}

string Flight::getAirline() const
{return this->airline;}
