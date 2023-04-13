//
// Created by gonzallito on 14-10-2022.
//

#ifndef PROJECT1_STUDENTS_CLASSES_H
#define PROJECT1_STUDENTS_CLASSES_H

#include <string>
#include <ostream>
#include <vector>

using namespace std;

/**
 * Classe Students_classes
 * @details esta classe gera os atributos usados no projeto
 */
class Students_classes {
private:
    int studentCode;
    string studentName;
    string ucCode;
    string classCode;
public:
    /**
     * Construtor por default
     */
    Students_classes();
    /**
     * Construtor dos atributos gerados
     * @param studentCode código do estudante em int
     * @param studentName nome do estudante em string
     * @param ucCode código da UC em string
     * @param classCode código da turma em string
     */
    Students_classes(int studentCode, const string &studentName, const string &ucCode, const string &classCode);
    /**
     * Retorna o código do estudante
     * @return código do estudante em int
     */
    int getStudentCode() const;
    /**
     * Atribui o código do estudante
     * @param studentCode código do estudante em int
     */
    void setStudentCode(int studentCode);
    /**
     * Retorna o nome do estudante
     * @return nome do estudante em string
     */
    const string &getStudentName() const;
    /**
     * Atribui o nome do estudante
     * @param studentName nome do estudante em string
     */
    void setStudentName(const string &studentName);
    /**
     * Retorna o código da UC
     * @return código da UC em string
     */
    const string &getUcCode() const;
    /**
     * Atribui o código da UC
     * @param ucCode código da UC em string
     */
    void setUcCode(const string &ucCode);
    /**
     * Retorna o código da turma
     * @return código da turma em string
     */
    const string &getClassCode() const;
    /**
     * Atribui o código da turma
     * @param classCode código da turma em string
     */
    void setClassCode(const string &classCode);
    /**
     * Operador de output
     * @param os ostream&
     * @param classes objeto da classe Students_classes
     * @return atributos dos objetos da classe Students_classes em string
     */
    friend ostream &operator<<(ostream &os, const Students_classes &classes);
    /**
     * Complexidade: O(n)
     * Calcula a diferença entre a turma com mais e menos elementos
     * @param studentsClasses vetor dos estudantes por turma
     * @param uc_code código da UC em string
     * @return diferença entre a turma com mais e menos elementos
     */
    static int evaluate_class_elements_difference(const vector<Students_classes>& studentsClasses, const string& uc_code);
};


#endif //PROJECT1_STUDENTS_CLASSES_H
