//
// Created by simao on 12/28/2022.
//

#ifndef AED_2223_PROJECT2_FLIGHT_H
#define AED_2223_PROJECT2_FLIGHT_H

#include <string>

using namespace std;

/**
 * Classe Flight
 * @details esta classe gera os atributos usados no projeto
 */
class Flight {

private:
    string source;
    string target;
    string airline;

public:
    /**
     * Construtor dos atributos gerados
     * @param source source dos flights em string
     * @param target target dos flights em string
     * @param airline airline dos flights em string
     */
    Flight(string source, string target, string airline);
    /**
     * Retorna o source dos flights
     * @return source dos flights em string
     */
    string getSource() const;
    /**
     * Retorna o target dos flights
     * @return target dos flights em string
     */
    string getTarget() const;
    /**
     * Retorna a airline dos flights
     * @return airline dos flights em string
     */
    string getAirline() const;

};


#endif //AED_2223_PROJECT2_FLIGHT_H
