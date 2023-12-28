//
// Created by gonzallito on 24-10-2022.
//

#ifndef PROJECT1_TASKS_H
#define PROJECT1_TASKS_H


#include "Data.h"
#include <set>
#include <list>

typedef pair<int, string> pairs;

/**
 * Classe Tasks
 * @details esta classe faz as listagens
 */
class Tasks {
private:
    Data data;
public:
    /**
     * Construtor por default
     */
    Tasks();
    /**
     * Complexidade: O(n)
     * Gera o número de pessoas por turma
     * @param classCode código da turma em string
     * @param ucCode código da UC em string
     * @return número de pessoas por tuma em int
     */
    int occupationOfAClass(string classCode, string ucCode);
    /**
     * Complexidade: O(n)
     * Gera o número de pessoas de um certo ano
     * @param year ano em char
     */
    void occupationOfAYear(char year);
    /**
     * Complexidade: O(n)
     * Gera o número de pessoas por UC
     * @param ucCode código da UC em string
     */
    void occupationOfAUc(string ucCode);
    /**
     * Complexidade: O(n)
     * Gera uma lista de estudantes
     */
    void listStudents();
    /**
     * Complexidade: O(n)
     * Gera uma lista de estudantes por turma
     * @param classCode código da turma em string
     * @param ucCode código da UC em string
     */
    void listStudentsOfAClass(string classCode, string ucCode);
    /**
     * Complexidade: O(n)
     * Gera uma lista de estudantes por ano
     * @param year ano em char
     */
    void listStudentsOfAYear(char year);
    /**
     * Complexidade: O(n)
     * Gera uma lista de estudantes por UC
     * @param ucCode código da UC em string
     */
    void listStudentsOfAUc(string ucCode);
    /**
     * Complexidade: O(n^2)
     * Gera o horário de um estudante
     * @param studentCode código do estudante em int
     */
    void listScheduleOfAStudent(int studentCode);
    /**
     * Complexidade: O(n)
     * Remove um estudante da turma
     * @param studentCodes código do estudante
     * @param ucCodes código da UC
     */
    bool removeStudentFromClass(Students_classes s);
    /**
     * Complexidade: O(n)
     * Retorna o máximo de estudantes por turma
     * @return maxímo de estudantes por turma em int
     */
    int getMaxStudentsPerClass();
    /**
     * Atribui o máximo de estudantes por turma
     * @param max máximo de estudantes por turma em int
     */
    void setMaxStudentsPerClass(int max);
    /**
     * Complexidade: O(n^3)
     * Verifica se é possível adicionar o estudante
     * @param student estudante
     * @return sucesso ou insucesso
     */
    bool addStudentToClass(Students_classes student);
    /**
     * Complexidade: O(n^2)
     * Gera uma lista de estudantes com mais que um certo número de UCs
     * @param n número de UCs
     */
    void listStudentsMorenUC (int n);
    /**
     * Complexidade: O(n)
     * Ordena os alunos alfabeticamente
     */
    void sortStudentsAlphabetically();
    /**
     * Complexidade: O(n)
    * Ordena os alunos alfabeticamente por turma
    */
    void sortStudentsOfAClassAlphabetically(string classCode, string ucCode);
    /**
     * Complexidade: O(n)
    * Ordena os alunos alfabeticamente por ano
    */
    void sortStudentsOfAYearAlphabetically(char year);
    /**
     * Complexidade: O(n)
    * Ordena os alunos alfabeticamente por UC
    */
    void sortStudentsOfAUcAlphabetically(string ucCode);
    /**
     * Complexidade: O(n)
    * Ordena os alunos por número
    */
    void sortStudentsNumerically();
    /**
     * Complexidade: O(n)
    * Ordena os alunos por número dentro da turma
    */
    void sortStudentsOfAClassNumerically(string classCode, string ucCode);
    /**
     * Complexidade: O(n)
    * Ordena os alunos por número dentro do mesmo ano
    */
    void sortStudentsOfAYearNumerically(char year);
    /**
     * Complexidade: O(n)
    * Ordena os alunos por número dentro da mesma UC
    */
    void sortStudentsOfAUcNumerically(string ucCode);
};


#endif //PROJECT1_TASKS_H
