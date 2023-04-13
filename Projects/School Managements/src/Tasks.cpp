//
// Created by gonzallito on 24-10-2022.
//

#include <iostream>
#include <set>
#include <algorithm>
#include "Tasks.h"

typedef pair<int, string> pairs;

using namespace std;

Tasks::Tasks() {
    data.readStudentsClasses();
    data.readClasses();
}

int Tasks::occupationOfAClass(string classCode, string ucCode) {
    int occupation = 0;
    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode && i.getClassCode() == classCode) {
            occupation++;
        }
    }
    return occupation;
}

void Tasks::occupationOfAYear(char year) {
    set<int> s;
    for (auto i : data.getStudentsClasses()) {
        if (i.getClassCode()[0] == year)
            s.insert(i.getStudentCode());
    }
    cout << "Occupation: " << s.size();
}

void Tasks::occupationOfAUc(string ucCode) {
    int occupation = 0;
    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode)
            occupation++;
    }
    cout << "Occupation: " << occupation;
}

void Tasks::listStudents() {
    set<pairs> s;
    for (auto i : data.getStudentsClasses()) {
        pairs x = make_pair(i.getStudentCode(), i.getStudentName());
        s.insert(x);
    }
    for (auto const &x : s) {
        cout << x.first << " - " << x.second << endl;
    }
    cout << endl << "Number of Students: " << s.size() << endl;
}


void Tasks::listStudentsOfAClass(string classCode, string ucCode) {
    set<pairs> s;
    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode) {
            if (i.getClassCode() == classCode) {
                pairs x = make_pair(i.getStudentCode(), i.getStudentName());
                s.insert(x);
            }
        }
    }
    for (auto const &x : s) {
        cout << x.first << " - " << x.second << endl;
    }
    cout << endl << "Number of Students: " << s.size() << endl;
}

void Tasks::listStudentsOfAYear(char year) {
    set<pairs> s;
    for (auto i : data.getStudentsClasses()) {
        if (i.getClassCode()[0] == year) {
            pairs x = make_pair(i.getStudentCode(), i.getStudentName());
            s.insert(x);
        }
    }
    for (auto const &x : s) {
        cout << x.first << " - " << x.second << endl;
    }
    cout << endl << "Number of Students: " << s.size() << endl;
}

void Tasks::listStudentsOfAUc(string ucCode) {
    set<pairs> s;
    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode) {
            pairs x = make_pair(i.getStudentCode(), i.getStudentName());
            s.insert(x);
        }
    }
    for (auto const &x : s) {
        cout << x.first << " - " << x.second << endl;
    }
    cout << endl << "Number of Students: " << s.size() << endl;
}

void Tasks::listScheduleOfAStudent(int studentCode) {
    vector<string> days = {"Monday","Tuesday","Wednesday","Thursday","Friday"};
    list<Students_classes> filter;

    copy_if(data.getStudentsClasses().begin(), data.getStudentsClasses().end(), back_inserter(filter), [&studentCode](auto i){return i.getStudentCode() == studentCode;});
    for (auto i : filter) {
        for (auto j : data.getClasses()) {
            if (i.getUcCode() == j.getUcCode() && i.getClassCode() == j.getClassCode())
                cout << days[j.getWeekday()] << " - " << j.getStartHour() << " - " << j.getDuration() << " - " << j.getType() << endl;
        }
    }
}

void Tasks::listStudentsMorenUC (int n){
    set<pairs> s;
   for (auto i : data.getStudentsClasses()){
       int num=0;
       for (auto j:data.getStudentsClasses()){
           if (i.getStudentName()==j.getStudentName()){
               num++;
           }
       }
       if (num>n){
           pairs x = make_pair(i.getStudentCode(), i.getStudentName());
           s.insert(x);
       }
   }
    for (auto const &x : s) {
        cout << x.first << " - " << x.second << endl;
    }
    cout << endl << "Number of Students: " << s.size() << endl;
}

bool Tasks::removeStudentFromClass(Students_classes s) {
    vector<Students_classes> aux = data.getStudentsClasses();
    for (auto it = aux.begin(); it != aux.end(); it++) {
        if (it->getStudentCode() == s.getStudentCode() && it->getUcCode() == s.getUcCode()) {
            aux.erase(it);
            data.setStudentsClasses(aux);
            cout << endl << "Student " << it->getStudentName() << " deleted successfully from class " << it->getClassCode() << endl << endl;
            data.updateFiles();
            return true;
        }
    }
    return false;
}

int Tasks::getMaxStudentsPerClass(){
    return data.getMaxStudentsPerClass();
}

void Tasks::setMaxStudentsPerClass(int max){
    data.setMaxStudentsPerClass(max);
}

bool Tasks::addStudentToClass(Students_classes student) {

    if (occupationOfAClass(student.getClassCode(),student.getUcCode()) >= data.getMaxStudentsPerClass()){
        cout << "Class is full" << endl;
        return false;
    }

    list<Classes> classSchedule;
    copy_if(data.getClasses().begin(), data.getClasses().end(), back_inserter(classSchedule), [&student](auto i){return i.getUcCode() == student.getUcCode() && i.getClassCode() == student.getClassCode();});

    list<Students_classes> studentSchedule;
    copy_if(data.getStudentsClasses().begin(), data.getStudentsClasses().end(), back_inserter(studentSchedule), [&student](auto i){return i.getStudentCode() == student.getStudentCode();});


    vector<Students_classes> aux = data.getStudentsClasses();

    if (studentSchedule.empty()) {
        aux.push_back(student);
        data.setStudentsClasses(aux);
        cout << "Student " << student.getStudentName() << " added successfully to class " << student.getClassCode() << endl << endl;
        data.updateFiles();
        return true;
    }

    if (classSchedule.empty()){
        cout << "There are no classes and/or no UCs with that designation" << endl;
        return false;
    }

    for (auto c : studentSchedule) {
        if (c.getUcCode() == student.getUcCode()){
            cout << "Student already assigned to another class in this UC" << endl;
            return false;
        }
    }


    for (auto i : studentSchedule) {
        for (auto j : data.getClasses())
            if (i.getUcCode() == j.getUcCode() && i.getClassCode() == j.getClassCode()){
                for (auto newClass : classSchedule) {
                    if ((newClass.getWeekday() != j.getWeekday()))
                        continue;
                    else if (newClass.getType()=="T" || j.getType()=="T"){
                        aux.push_back(student);
                        data.setStudentsClasses(aux);
                        cout << "Student " << student.getStudentName() << " added successfully to class " << student.getClassCode() << endl << endl;
                        data.updateFiles();
                        return true;
                    }
                    else
                        if ((newClass.getStartHour() <= j.getStartHour() &&
                             newClass.getStartHour() + newClass.getDuration() > j.getStartHour())
                            || (newClass.getStartHour() < j.getStartHour() + j.getDuration() &&
                                newClass.getStartHour() + newClass.getDuration() >= j.getStartHour() + j.getDuration())
                            || (newClass.getStartHour() > j.getStartHour() &&
                                newClass.getStartHour() + newClass.getDuration() < j.getStartHour() + j.getDuration())) {
                            cout << "Can't add" << endl;
                            return false;
                        }
                }
        }
    }

    aux.push_back(student);
    data.setStudentsClasses(aux);
    cout << "Student " << student.getStudentName() << " added successfully to class " << student.getClassCode() << endl << endl;

    data.updateFiles();

    return true;

}




bool compareFunction (pair<int, string> a, pair<int, string> b) {return a.second<b.second;}


void Tasks::sortStudentsAlphabetically() {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        pairs x = make_pair(i.getStudentCode(), i.getStudentName());
        s.insert(x);
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunction);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}

void Tasks::sortStudentsOfAClassAlphabetically(string classCode, string ucCode) {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode) {
            if (i.getClassCode() == classCode) {
                pairs x = make_pair(i.getStudentCode(), i.getStudentName());
                s.insert(x);
            }
        }
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunction);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}

void Tasks::sortStudentsOfAYearAlphabetically(char year) {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        if (i.getClassCode()[0] == year) {
            pairs x = make_pair(i.getStudentCode(), i.getStudentName());
            s.insert(x);
        }
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunction);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}

void Tasks::sortStudentsOfAUcAlphabetically(string ucCode) {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode) {
            pairs x = make_pair(i.getStudentCode(), i.getStudentName());
            s.insert(x);
        }
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunction);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}











bool compareFunctionNum (pair<int, string> a, pair<int, string> b) {return a.first<b.first;}


void Tasks::sortStudentsNumerically() {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        pairs x = make_pair(i.getStudentCode(), i.getStudentName());
        s.insert(x);
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunctionNum);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}

void Tasks::sortStudentsOfAClassNumerically(string classCode, string ucCode) {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode) {
            if (i.getClassCode() == classCode) {
                pairs x = make_pair(i.getStudentCode(), i.getStudentName());
                s.insert(x);
            }
        }
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunctionNum);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}

void Tasks::sortStudentsOfAYearNumerically(char year) {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        if (i.getClassCode()[0] == year) {
            pairs x = make_pair(i.getStudentCode(), i.getStudentName());
            s.insert(x);
        }
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunctionNum);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}

void Tasks::sortStudentsOfAUcNumerically(string ucCode) {
    set<pairs> s;
    set<pairs> finalSet;
    vector<pairs> v;

    for (auto i : data.getStudentsClasses()) {
        if (i.getUcCode() == ucCode) {
            pairs x = make_pair(i.getStudentCode(), i.getStudentName());
            s.insert(x);
        }
    }

    for (auto p : s) {
        v.push_back(p);
    }

    sort(v.begin(), v.end(), compareFunctionNum);

    for (auto p : v) {
        finalSet.insert(p);
        cout << p.first << " - " << p.second << endl;
    }
}
