//
// Created by simao on 12/27/2022.
//

#ifndef AED_2223_PROJECT2_MENU_H
#define AED_2223_PROJECT2_MENU_H

#include <iostream>
#include <set>
#include "Data.h"

using namespace std;

/**
 * Classe Menu
 * @details esta classe gera o interface e as tarefas
 */
class Menu {

private:
    Data d;
    Graph airlines;

public:
    /**
     * @param d d
     */
    Menu(Data d);
    /**
     * Display logo
     */
    void displayLogo() const;
    /**
     * Gera o menu principal
     */
    void mainMenu() const;
    /**
     * Gera o menu quando o usuário escolhe a opção 1 do menu principal
     */
    void option1MenuDisplay() const;
    /**
     * Gera o menu quando o usuário escolhe a opção 2 do menu principal, seguido do code do airport
     * @return code do airport
     */
    string option2AirportDisplay() const;
    /**
     * Gera o menu depois do usuário inserir o code do aiport da opção 2 do menu principal
     */
    void option2MenuDisplay() const;
    /**
     * Lê a opção do usuário se é válida
     * @return sucesso ou insucesso
     */
    bool valid();
    /**
     * Corre o menu principal
     */
    void runMainMenu();
    /**
     * Corre o menu da opção 1 do menu principal
     */
    void runOption1Menu();
    /**
     * Corre o menu da opção 2 do menu principal
     */
    void runOption2Menu();
    /**
     * Constrói o grafo
     * \complexity: O(|N|^2)
     */
    void buildGraph();
    /**
     * Executa a opção 1 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption1();
    /**
     * Executa a opção 2 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption2();
    /**
     * Executa a opção 3 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption3();
    /**
     * Executa a opção 4 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption4();
    /**
     * Executa a opção 5 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption5();
    /**
     * Executa a opção 6 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption6();
    /**
     * Executa a opção 7 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption7();
    /**
     * Executa a opção 8 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption8();
    /**
     * Executa a opção 9 dentro da opção 1 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption9();
    /**
     * Executa a opção 1 dentro da opção 2 do menu principal
     * \complexity: O(|N|^5)
     */
    void menuOption21(string airportCode);
    /**
     * Executa a opção 2 dentro da opção 2 do menu principal
     * \complexity: O(|N|^3)
     */
    void menuOption22(string airportCode);
    /**
     * Executa a opção 3 dentro da opção 2 do menu principal
     * \complexity: O(|N|^3)
     */
    void menuOption23(string airportCode);
    /**
     * Executa a opção 4 dentro da opção 2 do menu principal
     * \complexity: O(|N|^3)
     */
    void menuOption24(string airportCode);
    /**
     * Executa a opção 5 dentro da opção 2 do menu principal
     * \complexity: O(|N|^3)
     */
    void menuOption25(string airportCode);
};


#endif //AED_2223_PROJECT2_MENU_H
