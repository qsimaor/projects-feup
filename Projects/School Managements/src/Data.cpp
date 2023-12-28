//
// Created by gonzallito on 15-10-2022.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Data.h"

using namespace std;

Data::Data() {
    maxStudentsPerClass = 20;
}

const vector<Classes> &Data::getClasses() const{
    return classes;
}

const vector<Students_classes> &Data::getStudentsClasses() const {
    return studentsClasses;
}

void Data::setClasses(const vector<Classes> &classes) {
    Data::classes = classes;
}

void Data::setStudentsClasses(const vector<Students_classes> &studentsClasses) {
    Data::studentsClasses = studentsClasses;
}


bool Data::readClasses() {
    fstream file("../Database/classes.csv");
    string line, word;

    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return false;
    }

    string classCode; string ucCode; string weekday; float startHour; float duration; string type;

    getline(file, line);
    while (getline(file, line)) {
        int i = 0;
        stringstream iss(line);
        while(getline(iss,word,',')){
            if (i == 0)
                classCode = word;
            else if(i==1)
                ucCode = word;
            else if(i==2)
                weekday = word;
            else if(i==3)
                startHour = stof(word);
            else if(i==4)
                duration = stof(word);
            else if(i==5) {
                type = word;
            }
            i++;
        }
        Classes c(classCode, ucCode, weekday, startHour, duration, type);
        classes.push_back(c);
    }
    file.close();
    return true;
}

bool Data::readStudentsClasses() {
    fstream file("../Database/students_classes.csv");
    string line, word;

    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return false;
    }

    int studentCode; string studentName; string ucCode; string classCode;

    getline(file, line);
    while (getline(file, line)) {
        int i = 0;
        stringstream iss(line);
        while(getline(iss,word,',')){
            if (i == 0)
                studentCode = stoi(word);
            else if(i==1)
                studentName = word;
            else if(i==2)
                ucCode = word;
            else if(i==3)
                classCode = word;
            i++;
        }
        Students_classes s(studentCode, studentName, ucCode, classCode);
        studentsClasses.push_back(s);
    }
    file.close();
    return true;
}

int Data::getMaxStudentsPerClass() const {
    return maxStudentsPerClass;
}

void Data::setMaxStudentsPerClass(int maxStudentsPerClass) {
    Data::maxStudentsPerClass = maxStudentsPerClass;
}

void Data::updateFiles() {
    vector<string> days = {"Monday","Tuesday","Wednesday","Thursday","Friday"};

    ofstream myFile("../Database/classes.csv");

    myFile << "ClassCode,UcCode,Weekday,StartHour,Duration,Type" << endl;

    for (auto c : classes) {
        myFile << c.getClassCode() << "," << c.getUcCode() << "," << days[c.getWeekday()] << "," << c.getStartHour() << "," << c.getDuration() << "," << c.getType() << endl;
    }
    myFile.close();

    myFile.open("../Database/students_classes.csv");

    myFile << "StudentCode,StudentName,UcCode,ClassCode" << endl;

    for (auto s : studentsClasses) {
        myFile << s.getStudentCode() << "," << s.getStudentName() << "," << s.getUcCode() << "," << s.getClassCode() << endl;
    }
    myFile.close();
}
