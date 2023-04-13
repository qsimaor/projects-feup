//
// Created by simao on 12/27/2022.
//

#ifndef AED_2223_PROJECT2_DATA_H
#define AED_2223_PROJECT2_DATA_H

#include <vector>
#include <cmath>
#include <unordered_map>
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "graph.h"

/**
 * Classe Data
 * @details esta classe lê os ficheiros
 */
class Data {

private:
    vector<Airline> airlines;
    vector<Airport> airports;
    vector<Flight> flights;
    Graph airlinesGraph;
    unordered_map<string, Airport> airportsMap;
    unordered_map<string, Airline> airlinesMap;

public:
    /**
     * Construtor por default
     */
    Data();
    /**
     * Retorna as airlines existentes na base de dados
     * @return sucesso ou insucesso
     */
    bool readAirlines();
    /**
     * Retorna os airports existentes na base de dados
     * @return sucesso ou insucesso
     */
    bool readAirports();
    /**
     * Retorna os flights existentes na base de dados
     * @return sucesso ou insucesso
     */
    bool readFlights();
    /**
     * Retorna as airlines num vetor
     * @return airlines em vetor
     */
    vector<Airline> getAirline() const;
    /**
     * Retorna os airport num vetor
     * @return airports em vetor
     */
    vector<Airport> getAirport() const;
    /**
     * Retorna os flights num vetor
     * @return flights em vetor
     */
    vector<Flight> getFlights() const;
    /**
     * Retorna os airports numa hash table
     * @return airports em hash table
     */
    const unordered_map<string, Airport> &getAirportsMap() const;
    /**
     * Retorna as airlines numa hash table
     * @return airlines em hash table
     */
    const unordered_map<string, Airline> &getAirlinesMap() const;
    /**
     * Fórmula haversine
     * @param lat1 latitude do 1 ponto
     * @param lon1 longitude do 1 ponto
     * @param lat2 latitude do 1 ponto
     * @param lon2 longitude do 1 ponto
     * @return
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif //AED_2223_PROJECT2_DATA_H
