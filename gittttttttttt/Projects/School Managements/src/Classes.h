//
// Created by gonzallito on 15-10-2022.
//

#ifndef PROJECT1_CLASSES_H
#define PROJECT1_CLASSES_H

#include <string>
#include <ostream>
#include "vector"

using namespace std;

/**
 * @brief Enumeração dos dias da semana
 */
enum DaysOfWeek {Monday, Tuesday, Wednesday, Thursday, Friday};

/**
 * Classe Classes
 * @details esta classe gera os atributos usados no projeto
 */
class Classes {
private:
    string classCode;
    string ucCode;
    DaysOfWeek weekday;
    float startHour;
    float duration;
    string type;
public:
    /**
    * Construtor por default
    */
    Classes();
    /**
    * Construtor dos atributos gerados
    * @param classCode código da turma em string
    * @param ucCode código da UC em string
    * @param weekday dia da semana em float
    * @param startHour hora de início da aula em float
    * @param duration duração da aula em float
    * @param type tipo de aula em string
     */
    Classes(const string &classCode, const string &ucCode, const string &weekday, float startHour, float duration, const string &type);
    /**
     * Retorna o código da turma
     * @return código da turma em string
     */
    const string &getClassCode() const;
    /**
     * Retorna o código da UC
     * @return código da UC em string
     */
    const string &getUcCode() const;
    /**
     * Retorna o dia da semana
     * @return dia da semana
     */
    const DaysOfWeek &getWeekday() const;
    /**
     * Retorna a hora de ínicio de aula
     * @return hora de ínicio de aula em float
     */
    float getStartHour() const;
    /**
     * Atribui o código a turma
     * @param classCode código da turma em string
     */
    void setClassCode(const string &classCode);
    /**
     * Atribui o código a UC
     * @param ucCode código da UC em string
     */
    void setUcCode(const string &ucCode);
    /**
     * Atribui o dia da semana
     * @param weekday dia da semana
     */
    void setWeekday(const DaysOfWeek &weekday);
    /**
     * Atribui a hora de início da aula
     * @param startHour hora de início de aula em float
     */
    void setStartHour(float startHour);
    /**
     * Atribui a duração da aula
     * @param duration duração da aula em float
     */
    void setDuration(float duration);
    /**
     * Atribui o tipo de aula
     * @param type tipo da aula em string
     */
    void setType(const string &type);
    /**
     * Retorna a duração da aula
     * @return duração da aula em float
     */
    float getDuration() const;
    /**
     * Retorna o tipo de aula
     * @return tipo de aula em string
     */
    const string &getType() const;
    /**
    * Operador de output
    * @param os ostream&
    * @param classes objeto da classe Classes
    * @return atributos dos objetos da classe Classes em string
    */
    friend ostream &operator<<(ostream &os, const Classes &classes);
};


#endif //PROJECT1_CLASSES_H
