//
// Created by simao on 12/27/2022.
//

#ifndef AED_2223_PROJECT2_AIRPORT_H
#define AED_2223_PROJECT2_AIRPORT_H

#include <string>

using namespace std;

/**
 * Classe Airport
 * @details esta classe gera os atributos usados no projeto
 */
class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;

public:
    /**
     * Contrutor por default
     */
    Airport();
    /**
     * Construtor dos atributos gerados
     * @param code code do airport em string
     * @param name name do airport em string
     * @param city city do airport em string
     * @param country country do airport em string
     * @param latitude latitude do airport em string
     * @param longitude longitude do airport em string
     */
    Airport(string code, string name, string city, string country, string latitude, string longitude);
    /**
     * Retorna o code do airport
     * @return code do airport em string
     */
    string getCode() const;
    /**
     * Retorna o name do airport
     * @return name do airport em string
     */
    string getName() const;
    /**
     * Retorna a city do airport
     * @return city do airport em string
     */
    string getCity() const;
    /**
     * Retorna o country do airport
     * @return country do airport em string
     */
    string getCountry() const;
    /**
     * Retorna a latitude do airport
     * @return latitude do airport em string
     */
    string getLatitude() const;
    /**
     * Retorna a longitude do airport
     * @return longitude do airport em string
     */
    string getLongitude() const;
};


#endif //AED_2223_PROJECT2_AIRPORT_H
