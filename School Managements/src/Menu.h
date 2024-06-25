//
// Created by marti on 13/10/2022.
//

#ifndef PROJECT1_MENU_H
#define PROJECT1_MENU_H

#include <iostream>
#include "string"
#include "Tasks.h"
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/**
 * Classe Menu
 * @details esta classe gera o interface
 */
class Menu {
private:
    Tasks tasks;
    queue<pair<int, Students_classes>> pedidos;
    stack<pair<int, Students_classes>> recusados;
public:
    /**
     * Construtor por default
     */
    Menu();
    /**
     * Gera o menu principal
     */
    void mainMenu() const;
    /**
     * Gera o menu quando o usuário escolhe a opção List
     */
    void listMenu() const;
    /**
     * Lê a opção do usuário
     * @return sucesso ou insucesso
     */
    bool pass();
    /**
     * Complexidade: O(n)
     * Corre o menu principal
     */
    void runMain();
    /**
     * Complexidade: O(n)
     * Corre o menu List quando o usuário escolhe essa opção
     */
    void runList();
    /**
     * Remove o estudante de uma turma/UC
     */
    void runRemoveStudent();
    /**
     * Adiciona o estudante a uma turma/UC
     */
    void runAddStudent();
    /**
     * Altera a turma/UC de um estudante
     */
    void runChangeStudentUcClass();
    /**
     * Complexidade: O(n)
     * Altera um conjunto de turmas/UCs de um estudante
     */
    void runChangeStudentManyUcClass();
    /**
     * Complexidade: O(n)
     * Realiza os pedidos
     */
    void endOfTheDay();
};


#endif //PROJECT1_MENU_H
