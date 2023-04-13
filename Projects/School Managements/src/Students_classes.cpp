//
// Created by gonzallito on 14-10-2022.
//

#include <vector>
#include <map>
#include "Students_classes.h"
#include <climits>

Students_classes::Students_classes() {}

Students_classes::Students_classes(int studentCode, const string &studentName, const string &ucCode,
                                   const string &classCode) : studentCode(studentCode), studentName(studentName),
                                                              ucCode(ucCode), classCode(classCode) {}

int Students_classes::getStudentCode() const {
    return studentCode;
}

void Students_classes::setStudentCode(int studentCode) {
    Students_classes::studentCode = studentCode;
}

const string &Students_classes::getStudentName() const {
    return studentName;
}

void Students_classes::setStudentName(const string &studentName) {
    Students_classes::studentName = studentName;
}

const string &Students_classes::getUcCode() const {
    return ucCode;
}

void Students_classes::setUcCode(const string &ucCode) {
    Students_classes::ucCode = ucCode;
}

const string &Students_classes::getClassCode() const {
    return classCode;
}

void Students_classes::setClassCode(const string &classCode) {
    Students_classes::classCode = classCode;
}

ostream &operator<<(ostream &os, const Students_classes &classes) {
    os << "studentCode: " << classes.studentCode << " studentName: " << classes.studentName << " ucCode: "
       << classes.ucCode << " classCode: " << classes.classCode;
    return os;
}


//  Para cada string de Turma diferente, guardar num vetor o numero de estudantes da respetiva turma e devolver a diferença entre a turma com mais e menos elementos
int Students_classes::evaluate_class_elements_difference(const vector<Students_classes>& studentsClasses, const string& uc_code){
    vector<Students_classes> uc_students_classes;
    for (auto student: studentsClasses){
        if (uc_code == student.getUcCode()){
            uc_students_classes.push_back(student);
        }
    }

    //vetor com contagem de elementos de cada turma
    map<string, int> class_element_count;

    for (auto student: uc_students_classes){
        if (class_element_count.find(student.getClassCode()) != class_element_count.end()){
            class_element_count[student.getClassCode()] += 1;
        }
        else {
            class_element_count[student.getClassCode()] = 1;
        }
    }

    pair<string, int> min, max;
    min.second = INT_MAX;
    max.second = 0;
    for (auto a_class: class_element_count) {
        if (a_class.second > max.second) max = a_class;
        if (a_class.second < min.second) min = a_class;
    }
    return max.second - min.second;
}
