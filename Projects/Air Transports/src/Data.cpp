//
// Created by simao on 12/27/2022.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Data.h"

using namespace std;


Data::Data() : airlinesGraph(airlinesGraph) {
    airlines = {};
    airports = {};
    flights = {};
}

bool Data::readAirlines() {
    fstream file_airlines("../Database/airlines.csv");
    string line, word;


    if (!file_airlines.is_open()) {
        cout << "Failed to open file\n";
        return false;
    }

    getline(file_airlines, line);
    string code; string name; string callSign; string country;

    while(getline(file_airlines, line)) {

        stringstream iss(line);

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callSign, ',');
        getline(iss, country, ',');

        Airline airline(code, name, callSign, country);
        airlines.push_back(airline);
        airlinesMap[code] = airline;
    }

    file_airlines.close();
    return true;
}

bool Data::readAirports() {
    fstream file_airports("../Database/airports.csv");
    string line, word;

    if (!file_airports.is_open()) {
        cout << "Failed to open file\n";
        return false;
    }

    getline(file_airports, line);
    string code; string name; string city; string country; string latitude; string longitude;

    while(getline(file_airports, line)) {

        stringstream iss(line);

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, ',');

        Airport airport(code, name, city, country, latitude, longitude);
        airports.push_back(airport);
        airportsMap[code] = airport;
    }
    file_airports.close();
    return true;
}

bool Data::readFlights() {
    fstream file_flights("../Database/flights.csv");
    string line, word;

    if (!file_flights.is_open()) {
        cout << "Failed to open file\n";
        return false;
    }

    getline(file_flights, line);
    string target; string source; string airline;


    while(getline(file_flights, line)) {
        stringstream iss(line);

        getline(iss, target, ',');
        getline(iss, source, ',');
        getline(iss, airline, ',');

        Flight flight(target, source, airline);
        flights.push_back(flight);
    }

    file_flights.close();
    return true;
}

vector<Airline> Data::getAirline() const
{return this->airlines;}

vector<Airport> Data::getAirport() const
{return this->airports;}

vector<Flight> Data::getFlights() const
{return this->flights;}

const unordered_map<string, Airport> &Data::getAirportsMap() const {
    return airportsMap;
}

const unordered_map<string, Airline> &Data::getAirlinesMap() const {
    return airlinesMap;
}


double Data::haversine(double lat1, double lon1, double lat2, double lon2) {
    // convert degrees to radians
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;

    // haversine formula
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = std::pow(std::sin(dlat / 2), 2) + std::cos(lat1) * std::cos(lat2) * std::pow(std::sin(dlon / 2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double R = 6371; // Radius of the Earth in kilometers
    double d = R * c;

    return d;
}


