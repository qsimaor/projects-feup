//
// Created by gonzallito on 15-10-2022.
//

#ifndef PROJECT1_DATA_H
#define PROJECT1_DATA_H

#include <vector>
#include "Classes.h"
#include "Students_classes.h"

using namespace std;

/**
 * Classe Data
 * @details esta classe lê os ficheiros
 */
class Data {
private:
    vector<Classes> classes;
    vector<Students_classes> studentsClasses;
    int maxStudentsPerClass;
public:
    /**
     * Construtor por default
     */
    Data();
    /**
     * Lê as turmas existentes na base de dados
     * @return sucesso ou insucesso
     */
    bool readClasses();
    /**
     * Lê as turmas dos estudantes existentes na base de dados
     * @return sucesso ou insucesso
     */
    bool readStudentsClasses();
    /**
     * Retorna um vetor com as turmas
     * @return vetor com as turmas
     */
    const vector<Classes> &getClasses() const;
    /**
     * Retorna um vetor com os estudantes por turma
     * @return vetor com os estudantes por turma
     */
    const vector<Students_classes> &getStudentsClasses() const;
    /**
     * Atribui ao vetor as turmas
     * @param classes vetor das turmas
     */
    void setClasses(const vector<Classes> &classes);
    /**
     * Atribui ao vetor os estudantes por turma
     * @param studentsClasses  vetor dos estudantes por turma
     */
    void setStudentsClasses(const vector<Students_classes> &studentsClasses);
    /**
     * Retorna o máximo de estudantes por turma
     * @return máximo de estudantes por turma em int
     */
    int getMaxStudentsPerClass() const;
    /**
     * Atribui o máximo de estudantes por turma
     * @param maxStudentsPerClass máximo de estudantes por turma em int
     */
    void setMaxStudentsPerClass(int maxStudentsPerClass);
    /**
     * Complexidade: O(n)
     * Atualiza os ficheiros
     */
    void updateFiles();

};


#endif //PROJECT1_DATA_H
