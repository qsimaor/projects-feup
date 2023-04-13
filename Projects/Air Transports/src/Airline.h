//
// Created by simao on 12/27/2022.
//

#ifndef AED_2223_PROJECT2_AIRLINE_H
#define AED_2223_PROJECT2_AIRLINE_H

#include <string>

using namespace std;

/**
 * Classe Airline
 * @details esta classe gera os atributos usados no projeto
 */
class Airline {

private:
    string code;
    string name;
    string callSign;
    string country;

public:
    /**
     * Construtor dos atributos gerados
     * @param code code das airlines em string
     * @param name name das airlines em string
     * @param callSign callSign das airlines em string
     * @param country country das airlines em string
     */
    Airline(string code, string name, string callSign, string country);
    /**
     * Retorna o code das airlines
     * @return name das airlines em string
     */
    string getCode() const;
    /**
     * Retorna o name das airlines
     * @return name das airlines em string
     */
    string getName() const;
    /**
     * Retorna o callSign das airlines
     * @return callSign das airlines em string
     */
    string getCallSign() const;
    /**
     * Retorna o country das airlines
     * @return country das airlines em string
     */
    string getCountry() const;
    /**
     * Construtor por default
     */
    Airline();
};


#endif //AED_2223_PROJECT2_AIRLINE_H
