//
// Created by marti on 13/10/2022.
//

#include <cstdlib>
#include <climits>
#include "Menu.h"

Menu::Menu() {}

void Menu::mainMenu() const {
    cout << endl;
    cout << " ========================================" << endl;
    cout << " ||       Schedule management for      ||" << endl;
    cout << " ||          L.EIC students            ||" << endl;
    cout << " ========================================" << endl;
    cout << endl;

    cout << " Choose an option:" << endl;
    cout << " [1] 1- List" << endl;
    cout << " [2] 2- Remove a student from a class/UC" << endl;
    cout << " [3] 3- Add a student to a class/UC" << endl;
    cout << " [4] 4- Change the class/UC of a student" << endl;
    cout << " [5] 5- Change a set of classes/UCs of a student" << endl;
    cout << " [6] 6- Confirm ALL the changes" << endl;
    cout << " [0] Exit" << endl;
    cout << endl;

}

void Menu::listMenu() const {

    cout << endl;
    cout << " ========================================" << endl;
    cout << " ||              List Menu             ||" << endl;
    cout << " ========================================" << endl;
    cout << endl;

    cout << " [1] 1- Show the occupation of a class" << endl;
    cout << " [2] 2- Show the occupation of a year" << endl;
    cout << " [3] 3- Show the occupation of a UC" << endl;
    cout << " [4] 4- List of students" << endl;
    cout << " [5] 5- List the students of a class" << endl;
    cout << " [6] 6- List the students of a year" << endl;
    cout << " [7] 7- List the students of a UC" << endl;
    cout << " [8] 8- List the schedule of a student" << endl;
    cout << " [9] 9- List the students with more than n UCs" << endl;
    cout << " [10] 10- Sort All the Students Alphabetically" << endl;
    cout << " [11] 11- Sort Students of a class Alphabetically" << endl;
    cout << " [12] 12- Sort Students of a year Alphabetically" << endl;
    cout << " [13] 13- Sort Students of a UC Alphabetically" << endl;
    cout << " [14] 14- Sort All the Students by Student Code" << endl;
    cout << " [15] 15- Sort Students of a class by Student Code" << endl;
    cout << " [16] 16- Sort Students of a year by Student Code" << endl;
    cout << " [17] 17- Sort Students of a UC by Student Code" << endl;
    cout << " [0] 0- Back" << endl;
    cout << endl;
}

bool Menu::pass() {
    if (cin.good()) return true;
    else {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "\n Invalid input!\n";
        return false;
    }
}

void Menu::runMain() {
    while (true) {
        mainMenu();
        cout << " >";

        int option;
        cin >> option;

        if (pass()) {
            switch (option) {
                case 1:
                    runList();
                    break;
                case 2:
                    runRemoveStudent();
                    break;
                case 3:
                    runAddStudent();
                    break;
                case 4:
                    runChangeStudentUcClass();
                    break;
                case 5:
                    runChangeStudentManyUcClass();
                    break;
                case 6:
                    endOfTheDay();
                    break;
                case 0:
                    exit(1);
                default:
                    cout << "\n Invalid input!\n";
            }
        }
    }
}

void Menu::runList() {
    bool running = true;
    string classe, ucCode; char year; int studentCode, numberUc;
    while (running) {
        listMenu();
        cout << " >";
        int option;
        cin >> option;
        cout << endl;

        if (pass()) {
            switch (option) {
                case 1:
                    cout << "Enter the class code: ";
                    cin >> classe;
                    cout << endl;
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    cout << "Occupation: " << tasks.occupationOfAClass(classe, ucCode);
                    cout << endl << endl;
                    break;
                case 2:
                    cout << "Enter the year: ";
                    cin >> year;
                    cout << endl;
                    tasks.occupationOfAYear(year);
                    cout << endl << endl;
                    break;
                case 3:
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.occupationOfAUc(ucCode);
                    cout << endl << endl;
                    break;
                case 4:
                    tasks.listStudents();
                    cout << endl << endl;
                    break;
                case 5:
                    cout << "Enter the class code: ";
                    cin >> classe;
                    cout << endl;
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.listStudentsOfAClass(classe, ucCode);
                    cout << endl << endl;
                    break;
                case 6:
                    cout << "Enter the year: ";
                    cin >> year;
                    cout << endl;
                    tasks.listStudentsOfAYear(year);
                    cout << endl << endl;
                    break;
                case 7:
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.listStudentsOfAUc(ucCode);
                    cout << endl << endl;
                    break;
                case 8:
                    cout << "Enter the Student code: ";
                    cin >> studentCode;
                    cout << endl;
                    tasks.listScheduleOfAStudent(studentCode);
                    cout << endl << endl;
                    break;
                case 9:
                    cout << "Enter number of UCs" << endl;
                    cin >> numberUc;
                    tasks.listStudentsMorenUC(numberUc);
                    cout<<endl<<endl;
                    break;
                case 10:
                    tasks.sortStudentsAlphabetically();
                    cout << endl << endl;
                    break;
                case 11:
                    cout << "Enter the class code: ";
                    cin >> classe;
                    cout << endl;
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.sortStudentsOfAClassAlphabetically(classe, ucCode);
                    cout << endl << endl;
                    break;
                case 12:
                    cout << "Enter the year code: ";
                    cin >> year;
                    cout << endl;
                    tasks.sortStudentsOfAYearAlphabetically(year);
                    cout << endl << endl;
                    break;
                case 13:
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.sortStudentsOfAUcAlphabetically(ucCode);
                    cout << endl << endl;
                    break;
                case 14:
                    tasks.sortStudentsNumerically();
                    cout << endl << endl;
                    break;
                case 15:
                    cout << "Enter the class code: ";
                    cin >> classe;
                    cout << endl;
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.sortStudentsOfAClassNumerically(classe, ucCode);
                    cout << endl << endl;
                    break;
                case 16:
                    cout << "Enter the year code: ";
                    cin >> year;
                    cout << endl;
                    tasks.sortStudentsOfAYearNumerically(year);
                    cout << endl << endl;
                    break;
                case 17:
                    cout << "Enter the UC code: ";
                    cin >> ucCode;
                    cout << endl;
                    tasks.sortStudentsOfAUcNumerically(ucCode);
                    cout << endl << endl;
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    cout << "\n Invalid input!\n";
            }
        }
    }
}


void Menu::runRemoveStudent() {
    string ucCodes;
    int studentCodes;

    cout << endl;
    cout << "Enter the Student Code: ";
    cin >> studentCodes;
    cout << endl;
    cout << "Enter the UC code: ";
    cin >> ucCodes;
    cout << endl;

    Students_classes s;
    s.setStudentCode(studentCodes);
    s.setUcCode(ucCodes);


    pedidos.push(make_pair(1, s));

    //tasks.removeStudentFromClass(s);

    cout << endl << endl;
}

void Menu::runAddStudent() {

    int studentCode, maxStudentsPerClass; string studentName; string ucCode; string classCode;

    cout << endl;
    cout << "Max students per class is: " << tasks.getMaxStudentsPerClass();
    cout << endl;
    cout << "Set new max students per class (0 if no change) : ";
    cin >> maxStudentsPerClass;
    if (maxStudentsPerClass != 0)
        tasks.setMaxStudentsPerClass(maxStudentsPerClass);
    cout << endl;
    cout << "Enter the Student Code: ";
    cin >> studentCode;
    cout << endl;
    cout << "Enter the Student Name: ";
    cin >> studentName;
    cout << endl;
    cout << "Enter the UC Code: ";
    cin >> ucCode;
    cout << endl;
    cout << "Enter the Class code: ";
    cin >> classCode;
    cout << endl;

    Students_classes s(studentCode, studentName, ucCode, classCode);

    pedidos.push(make_pair(2, s));

    //tasks.addStudentToClass(s);

    cout << endl << endl;
}

void Menu::runChangeStudentUcClass() {

    int studentCode; string studentName; string ucCode; string oldClassCode; string newClassCode;

    cout << endl;
    cout << "Enter the Student Code: ";
    cin >> studentCode;

    cout << endl;
    cout << "Enter the Student Name: ";
    cin >> studentName;

    cout << endl;
    cout << "Enter the UC Code: ";
    cin >> ucCode;

    cout << endl;
    cout << "Enter the Class code you want to CHANGE: ";
    cin >> oldClassCode;

    cout << endl;
    cout << "Enter the NEW Class code: ";
    cin >> newClassCode;
    cout << endl;


    Students_classes s(studentCode, studentName, ucCode, newClassCode);

    pedidos.push(make_pair(3, s));

    //tasks.removeStudentFromClass(s);

    //tasks.addStudentToClass(s);

    cout << endl << endl;
}

void Menu::runChangeStudentManyUcClass() {

    int studentCode; string studentName; string ucCode; string oldClassCode; string newClassCode; char yn;

    while(true) {
        cout << endl;
        cout << "Enter the Student Code: ";
        cin >> studentCode;

        cout << endl;
        cout << "Enter the Student Name: ";
        cin >> studentName;

        cout << endl;
        cout << "Enter the UC Code: ";
        cin >> ucCode;

        cout << endl;
        cout << "Enter the Class code you want to CHANGE: ";
        cin >> oldClassCode;

        cout << endl;
        cout << "Enter the NEW Class code: ";
        cin >> newClassCode;
        cout << endl;


        Students_classes s(studentCode, studentName, ucCode, newClassCode);

        pedidos.push(make_pair(3, s));

        //tasks.removeStudentFromClass(s);

        //tasks.addStudentToClass(s);

        cout << endl << endl;

        cout << "Do you want to change another? [y/n]";
        cin >> yn;
        cout << endl;

        if (yn == 'n' || yn == 'N')
            break;
    }
}

void Menu::endOfTheDay() {
    while(!pedidos.empty()){
        pair<int, Students_classes> pedido = pedidos.front();
        pedidos.pop();

        if(pedido.first == 1) {
            if(!tasks.removeStudentFromClass(pedido.second)) {
                recusados.push(make_pair(pedido.first, pedido.second));
            }
        }

        else if(pedido.first == 2) {
            if(!tasks.addStudentToClass(pedido.second))
                recusados.push(make_pair(pedido.first, pedido.second));
        }

        else if(pedido.first == 3) {
            if(!tasks.removeStudentFromClass(pedido.second))
                recusados.push(make_pair(pedido.first, pedido.second));
            if(!tasks.addStudentToClass(pedido.second))
                recusados.push(make_pair(pedido.first, pedido.second));
        }
    }
}

