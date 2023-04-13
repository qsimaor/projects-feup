//
// Created by simao on 12/27/2022.
//

#include <climits>
#include <algorithm>
#include "Menu.h"

using namespace std;

Menu::Menu(Data d) {
    this->d = d;
    this->displayLogo();
    this->buildGraph();
}

void Menu::displayLogo() const {
    cout << endl;
    cout << "+---------------------------------------------------------------------------------+" << endl;
    cout << "|              _        _______                                   _               |\n"
            "|        /\\   (_)      |__   __|                                 | |              |\n"
            "|       /  \\   _ _ __     | |_ __ __ _ _ __  ___ _ __   ___  _ __| |_ ___         |\n"
            "|      / /\\ \\ | | '__|    | | '__/ _` | '_ \\/ __| '_ \\ / _ \\| '__| __/ __|        |\n"
            "|     / ____ \\| | |       | | | | (_| | | | \\__ \\ |_) | (_) | |  | |_\\__ \\        |\n"
            "|    /_/    \\_\\_|_|       |_|_|  \\__,_|_| |_|___/ .__/ \\___/|_|   \\__|___/        |\n"
            "|                                               | |                               |\n"
            "|                                               |_|                               |\n"
            "+---------------------------------------------------------------------------------+"
         << endl;
    cout << endl;
}

void Menu::mainMenu() const {

    cout << endl << endl << endl << "------------------------------------------" << endl;
    cout <<         "|           M A I N    M E N U           |" << endl;
    cout <<         "------------------------------------------" << endl;

    cout << endl << " Choose an option:" << endl;
    cout << " 1 - Best way to fly from one location to another" << endl;
    cout << " 2 - Information about an airport" << endl;
    cout << " 3 - Exit" << endl;
    cout << endl;
}

void Menu::option1MenuDisplay() const {

    cout << endl << endl << endl << "------------------------------------------" << endl;
    cout <<                         "|       F L I G H T S    M E N U         |" << endl;
    cout <<                         "------------------------------------------" << endl;

    cout << endl << " Choose an option:" << endl;

    cout << " 1 - Airport to Airport" << endl;
    cout << " 2 - Airport to City" << endl;
    cout << " 3 - Airport to coordinates" << endl;

    cout << " 4 - City to Airport" << endl;
    cout << " 5 - City to city" << endl;
    cout << " 6 - City to Coordinates" << endl;

    cout << " 7 - Coordinates to Airport" << endl;
    cout << " 8 - Coordinates to City" << endl;
    cout << " 9 - Coordinates to Coordinates" << endl;

    cout << " 0 - Back" << endl;
    cout << endl;
}


string Menu::option2AirportDisplay() const {

    cout << endl << endl << endl << "------------------------------------------" << endl;
    cout <<                         "|       A I R P O R T    M E N U         |" << endl;
    cout <<                         "------------------------------------------" << endl;

    cout << endl << " Enter the Airport's Code:" << endl;
    cout << " > ";

    string option;
    cin >> option;

    return option;
}



void Menu::option2MenuDisplay() const {

    cout << endl << endl << endl << "------------------------------------------" << endl;
    cout <<                         "|       A I R P O R T    M E N U         |" << endl;
    cout <<                         "------------------------------------------" << endl;

    cout << endl << " Choose an option:" << endl;
    cout << " 1 - How many flight depart from this airport?" << endl;
    cout << " 2 - From how many different Airlines?" << endl;
    cout << " 3 - For how many different destinies?" << endl;
    cout << " 4 - For how many different countries?" << endl;
    cout << " 5 - How many airports, cities or countries are attainable using at most Y flights?" << endl;
    cout << " 0 - Back" << endl;
    cout << endl;
}

bool Menu::valid() {
    if (cin.good()) return true;
    else {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "\n Invalid input!\n";
        return false;
    }
}

void Menu::runMainMenu() {
    //airlines.printGraph();
    while(true) {
        mainMenu();
        cout << " > ";

        int option;
        cin >> option;

        if (valid()) {
            switch (option) {
                case 1:
                    runOption1Menu();
                    break;
                case 2:
                    runOption2Menu();
                    break;
                case 3:
                    exit(1);
                default:
                    cout << "\n Invalid input!\n";
            }
        }
    }
}

void Menu::runOption1Menu() {
    while(true) {
        option1MenuDisplay();
        cout << " > ";

        int option;
        cin >> option;

        if (valid()) {
            switch (option) {
                case 1:
                    menuOption1();
                    break;
                case 2:
                    menuOption2();
                    break;
                case 3:
                    menuOption3();
                    break;
                case 4:
                    menuOption4();
                    break;
                case 5:
                    menuOption5();
                    break;
                case 6:
                    menuOption6();
                    break;
                case 7:
                    menuOption7();
                    break;
                case 8:
                    menuOption8();
                    break;
                case 9:
                    menuOption9();
                    break;
                case 0:
                    runMainMenu();
                    break;
                default:
                    cout << "\n Invalid input!\n";
            }
        }
    }
}

void Menu::runOption2Menu() {

    string airportCode = option2AirportDisplay();

    while(true) {
        option2MenuDisplay();

        cout << " > ";

        int option;
        cin >> option;

        if (valid()) {
            switch (option) {
                case 1:
                    menuOption21(airportCode);
                    break;
                case 2:
                    menuOption22(airportCode);
                    break;
                case 3:
                    menuOption23(airportCode);
                    break;
                case 4:
                    menuOption24(airportCode);
                    break;
                case 5:
                    menuOption25(airportCode);
                    break;
                case 0:
                    runMainMenu();
                    break;
                default:
                    cout << "\n Invalid input!\n";
            }
        }
    }
}





void Menu::buildGraph() {
    airlines.setN(d.getFlights().size());
    airlines.setHasDir(true);

    cout << endl << endl << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Wait a moment... We are processing the data from the files! (This may take a while)" << endl << endl;

    for (auto i : d.getFlights()) {
        double a1 = 0;
        double a2 = 0;
        double b1 = 0;
        double b2 = 0;
        //cout << i.getSource() << " - " << i.getTarget() << " - " << i.getAirline() << endl;
        for (auto j : d.getAirport()) {
            if (j.getCode() == i.getSource()) {
                a1 = stod(j.getLatitude());
                a2 = stod(j.getLongitude());
            }
            if (j.getCode() == i.getTarget()) {
                b1 = stod(j.getLatitude());
                b2 = stod(j.getLongitude());
            }
        }
        airlines.addEdge(i.getSource(), i.getTarget(), d.haversine(a1, a2, b1, b2), i.getAirline());
    }

    cout << "Process Completed!" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

}





void Menu::menuOption1() {

    cout << endl << "Enter the Source Airport (ex: GKA)" << endl;
    cout << " > ";

    string airportSource;
    cin >> airportSource;

    cout << endl << "Enter the Target Airport (ex: VAI)" << endl;
    cout << " > ";

    string airportTarget;
    cin >> airportTarget;

    cout << endl << endl;

    //airlines.get_shortest_path("GKA", "VAI");    // ANSWER: GKA --- MAG --- VAI
    vector<string> path = airlines.get_shortest_path_code(airportSource, airportTarget);
    airlines.printPath(path);

    cout << endl << endl;



    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    vector<int> numeros;
    numeros.assign(path.size()-1, 0);

    for (int i = 0; i < path.size()-1; i++) {
        for (auto no : airlines.getNodes()) {
            if (no.name == path[i]) {
                for (auto edge : no.adj) {
                    if (edge.dest == path[i+1]) {
                        for (auto air: edge.airline) {
                            for (auto input : airlineCompanies) {
                                if (air == input)
                                    numeros[i] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    if (count(numeros.begin(), numeros.end(), 0)) {
        cout << endl << endl << "You CAN'T go from " << airportSource << " to " << airportTarget << " using only that company/companies!" << endl;
        return;
    }
    else
        cout << endl << endl << "You CAN go from " << airportSource << " to " << airportTarget << " using only that company/companies!" << endl;
}



void Menu::menuOption2() {

    cout << endl << "Enter the Source Airport (ex: ORY)" << endl;
    cout << " > ";

    string airportSource;
    cin >> airportSource;

    cout << endl << "Enter the Target City (ex: London)" << endl;
    cout << " > ";

    string cityTarget;
    cin >> cityTarget;

    cout << endl << endl;

    int max = INFINITY;
    int counter = 0;


    vector<vector<string>> pathFinal;


    for (auto j: d.getAirportsMap()) {
        if (j.second.getCity() == cityTarget) {
            auto auxCityTarget = j.first;
            vector<string> path1 = airlines.get_shortest_path_code(airportSource, auxCityTarget);
            if (path1.size() < max) {
                max = path1.size();
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            }
            else {
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto j: d.getAirportsMap()) {
                if (j.second.getCity() == cityTarget) {
                    auto auxCityTarget = j.first;
                    vector<string> path = airlines.get_shortest_path_code(airportSource, auxCityTarget);
                    if (path.size() == max && !path.empty()) {
                        airlines.printPath(path);
                    }
                }
            }
        }
    }
    cout << endl << endl;


    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from " << airportSource << " to " << cityTarget << " using only that company/companies!" << endl;
    }

}



void Menu::menuOption3() {

    cout << endl << "Enter the Source Airport (ex: ORY)" << endl;
    cout << " > ";

    string airportSource;
    cin >> airportSource;



    cout << endl << "Enter the Target Coordinates (ex: 51.510422, -0.159842) <-- London" << endl;
    cout << "latitude > ";
    double latTarget;
    cin >> latTarget;
    cout << endl << "longitude > ";
    double lonTarget;
    cin >> lonTarget;
    cout << endl << endl;



    cout << endl << "How far do you want the airport to be from the input location? (Km)" << endl;
    cout << " > ";
    double distanceInput;
    cin >> distanceInput;



    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;

    for (auto j: d.getAirportsMap()) {
        if (d.haversine(latTarget, lonTarget, stod(j.second.getLatitude()), stod(j.second.getLongitude())) < distanceInput) {
            auto auxCityTarget = j.first;
            vector<string> path1 = airlines.get_shortest_path_code(airportSource, auxCityTarget);
            if (path1.size() < max) {
                max = path1.size();
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            }
            else {
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto j: d.getAirportsMap()) {
                if (d.haversine(latTarget, lonTarget, stod(j.second.getLatitude()), stod(j.second.getLongitude())) < distanceInput) {
                    auto auxCityTarget = j.first;
                    vector<string> path = airlines.get_shortest_path_code(airportSource, auxCityTarget);
                    if (path.size() == max && !path.empty()) {
                        airlines.printPath(path);
                    }
                }
            }
        }
    }
    cout << endl << endl;


    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from " << airportSource << " to those coordinates using only that company/companies!" << endl;
    }
}



void Menu::menuOption4() {

    cout << endl << "Enter the Source City (ex: London)" << endl;
    cout << " > ";

    string citySource;
    cin >> citySource;

    cout << endl << "Enter the Target Airport (ex: ORY)" << endl;
    cout << " > ";

    string airportTarget;
    cin >> airportTarget;

    cout << endl << endl;

    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;

    for (auto i : d.getAirportsMap()) {
        if (i.second.getCity() == citySource) {
            auto auxCitySource = i.first;
            vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, airportTarget);
            if (path1.size() < max) {
                    max = path1.size();
                    airlines.printPath(path1);
                    pathFinal.push_back(path1);
                    if (!path1.empty())
                        counter++;
            }
            else {
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto i: d.getAirportsMap()) {
                if (i.second.getCity() == citySource) {
                    auto auxCitySource = i.first;
                    vector<string> path = airlines.get_shortest_path_code(auxCitySource, airportTarget);
                    if (path.size() == max && !path.empty()) {
                        airlines.printPath(path);
                    }
                }
            }
        }
    }
    cout << endl << endl;




    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from " << citySource << " to " << airportTarget << " using only that company/companies!" << endl;
    }
}



void Menu::menuOption5() {

    cout << endl << "Enter the Source City (ex: Paris)" << endl;
    cout << " > ";

    string citySource;
    cin >> citySource;

    cout << endl << "Enter the Target City (ex: London)" << endl;
    cout << " > ";

    string cityTarget;
    cin >> cityTarget;

    cout << endl << endl;

    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;


    for (auto i : d.getAirportsMap()) {
        if (i.second.getCity() == citySource) {
            auto auxCitySource = i.first;
            for (auto j: d.getAirportsMap()) {
                if (j.second.getCity() == cityTarget) {
                    auto auxCityTarget = j.first;
                    vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                    if (path1.size() < max) {
                        max = path1.size();
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                    else {
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                }
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto i : d.getAirportsMap()) {
                if (i.second.getCity() == citySource) {
                    auto auxCitySource = i.first;
                    for (auto j: d.getAirportsMap()) {
                        if (j.second.getCity() == cityTarget) {
                            auto auxCityTarget = j.first;
                            vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                            if (path1.size() == max && !path1.empty()) {
                                airlines.printPath(path1);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << endl << endl;






    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from " << citySource << " to " << cityTarget << " using only that company/companies!" << endl;
    }
}




void Menu::menuOption6() {

    cout << endl << "Enter the Source City (ex: Paris)" << endl;
    cout << " > ";

    string citySource;
    cin >> citySource;

    cout << endl << "Enter the Target Coordinates (ex: 51.510422, -0.159842) <-- London" << endl;
    cout << "latitude > ";
    double latTarget;
    cin >> latTarget;
    cout << endl << "longitude > ";
    double lonTarget;
    cin >> lonTarget;
    cout << endl << endl;



    cout << "How far do you want the airport to be from the input location? (Km)" << endl;
    cout << " > ";
    double distanceInput;
    cin >> distanceInput;


    cout << endl << endl;

    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;

    for (auto i : d.getAirportsMap()) {
        if (i.second.getCity() == citySource) {
            auto auxCitySource = i.first;
            for (auto j: d.getAirportsMap()) {
                if (d.haversine(latTarget, lonTarget, stod(j.second.getLatitude()), stod(j.second.getLongitude())) < distanceInput) {
                    auto auxCityTarget = j.first;
                    vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                    if (path1.size() < max) {
                        max = path1.size();
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                    else {
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                }
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto i : d.getAirportsMap()) {
                if (i.second.getCity() == citySource) {
                    auto auxCitySource = i.first;
                    for (auto j: d.getAirportsMap()) {
                        if (d.haversine(latTarget, lonTarget, stod(j.second.getLatitude()), stod(j.second.getLongitude())) < distanceInput) {
                            auto auxCityTarget = j.first;
                            vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                            if (path1.size() == max && !path1.empty()) {
                                airlines.printPath(path1);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << endl << endl;








    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from " << citySource << " to those coordinates using only that company/companies!" << endl;
    }
}



void Menu::menuOption7() {
    cout << endl << "Enter the Source Coordinates (ex: 48.835831, 2.394101) <-- Paris" << endl;
    cout << "latitude > ";
    double latSource;
    cin >> latSource;
    cout << endl << "longitude > ";
    double lonSource;
    cin >> lonSource;



    cout << endl << "How far do you want the airports to be from the input location? (Km)" << endl;
    cout << " > ";
    double distanceInput;
    cin >> distanceInput;

    cout << endl << endl;



    cout << endl << "Enter the Target Airport (ex: LTN)" << endl;
    cout << " > ";

    string airportTarget;
    cin >> airportTarget;

    cout << endl << endl;



    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;

    for (auto i : d.getAirportsMap()) {
        //cout << d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) << endl;
        if (d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) < distanceInput) {
            auto auxCitySource = i.first;
            vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, airportTarget);
            if (path1.size() < max) {
                max = path1.size();
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            } else {
                airlines.printPath(path1);
                pathFinal.push_back(path1);
                if (!path1.empty())
                    counter++;
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto i: d.getAirportsMap()) {
                if (d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) < distanceInput) {
                    auto auxCitySource = i.first;
                    vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, airportTarget);
                    if (path1.size() == max && !path1.empty()) {
                        airlines.printPath(path1);
                    }
                }
            }
        }
    }
    cout << endl << endl;







    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from those coordinates to " << airportTarget << " using only that company/companies!" << endl;
    }
}





void Menu::menuOption8() {

    cout << endl << "Enter the Source Coordinates (ex: 48.835831, 2.394101) <-- Paris" << endl;
    cout << "latitude > ";
    double latSource;
    cin >> latSource;
    cout << endl << "longitude > ";
    double lonSource;
    cin >> lonSource;


    cout << endl << "How far do you want the Source Airport to be from the input location? (Km)" << endl;
    cout << " > ";
    double distanceInput1;
    cin >> distanceInput1;




    cout << endl << "Enter the Target City (ex: London)" << endl;
    cout << " > ";

    string cityTarget;
    cin >> cityTarget;

    cout << endl << endl;



    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;

    for (auto i : d.getAirportsMap()) {
        //cout << d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) << endl;
        if (d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) < distanceInput1) {
            auto auxCitySource = i.first;
            for (auto j: d.getAirportsMap()) {
                if (j.second.getCity() == cityTarget) {
                    auto auxCityTarget = j.first;
                    vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                    if (path1.size() < max) {
                        max = path1.size();
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                    else {
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                }
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto i : d.getAirportsMap()) {
                if (d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) < distanceInput1) {
                    auto auxCitySource = i.first;
                    for (auto j: d.getAirportsMap()) {
                        if (j.second.getCity() == cityTarget) {
                            auto auxCityTarget = j.first;
                            vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                            if (path1.size() == max && !path1.empty()) {
                                airlines.printPath(path1);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << endl << endl;





    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from those coordinates to " << cityTarget << " using only that company/companies!" << endl;
    }
}





void Menu::menuOption9() {

    cout << endl << "Enter the Source Coordinates (ex: 48.835831, 2.394101) <-- Paris" << endl;
    cout << "latitude > ";
    double latSource;
    cin >> latSource;
    cout << endl << "longitude > ";
    double lonSource;
    cin >> lonSource;


    cout << endl << "How far do you want the Source Airport to be from the input location? (Km)" << endl;
    cout << " > ";
    double distanceInput1;
    cin >> distanceInput1;




    cout << endl << "Enter the Target Coordinates (ex: 51.510422, -0.159842) <-- London" << endl;
    cout << "latitude > ";
    double latTarget;
    cin >> latTarget;
    cout << endl << "longitude > ";
    double lonTarget;
    cin >> lonTarget;

    cout << endl << "How far do you want the Target Airport to be from the input location? (Km)" << endl;
    cout << " > ";
    double distanceInput2;
    cin >> distanceInput2;

    cout << endl << endl;



    int max = INFINITY;
    int counter = 0;

    vector<vector<string>> pathFinal;

    for (auto i : d.getAirportsMap()) {
        //cout << d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) << endl;
        if (d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) < distanceInput1) {
            auto auxCitySource = i.first;
            for (auto j: d.getAirportsMap()) {
                if (d.haversine(latTarget, lonTarget, stod(j.second.getLatitude()), stod(j.second.getLongitude())) < distanceInput2) {
                    auto auxCityTarget = j.first;
                    vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                    if (path1.size() < max) {
                        max = path1.size();
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                    else {
                        airlines.printPath(path1);
                        pathFinal.push_back(path1);
                        if (!path1.empty())
                            counter++;
                    }
                }
            }
        }
    }

    if (counter > 1) {
        cout << endl << endl << "Do you want the best option? (y/n)" << endl;
        cout << " > ";
        string answer;
        cin >> answer;
        cout << endl << endl;
        if (answer == "y") {
            for (auto i : d.getAirportsMap()) {
                if (d.haversine(latSource, lonSource, stod(i.second.getLatitude()), stod(i.second.getLongitude())) < distanceInput1) {
                    auto auxCitySource = i.first;
                    for (auto j: d.getAirportsMap()) {
                        if (d.haversine(latTarget, lonTarget, stod(j.second.getLatitude()), stod(j.second.getLongitude())) < distanceInput2) {
                            auto auxCityTarget = j.first;
                            vector<string> path1 = airlines.get_shortest_path_code(auxCitySource, auxCityTarget);
                            if (path1.size() == max && !path1.empty()) {
                                airlines.printPath(path1);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << endl << endl;





    cout << endl << "Do you want to specify the Airlines? (y/n)" << endl;
    cout << " > ";

    string answer;
    cin >> answer;

    cout << endl << endl;

    vector<string> airlineCompanies;

    if (answer == "y") {

        cout << "Enter Airline: ";
        string airlineCompany;
        cin >> airlineCompany;
        airlineCompanies.push_back(airlineCompany);

        while (airlineCompany != "n") {
            cout << "Enter Airline (n to stop): ";
            cin >> airlineCompany;
            airlineCompanies.push_back(airlineCompany);
        }

    }
    else
        return;

    cout << endl << endl;

    vector<vector<int>> aux;


    for (auto path : pathFinal) {

        vector<int> numeros;
        numeros.assign(path.size()-1, 0);

        for (int i = 0; i < path.size()-1; i++) {
            for (auto no : airlines.getNodes()) {
                if (no.name == path[i]) {
                    for (auto edge : no.adj) {
                        if (edge.dest == path[i+1]) {
                            for (auto air: edge.airline) {
                                for (auto input : airlineCompanies) {
                                    if (air == input)
                                        numeros[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        aux.push_back(numeros);
    }

    bool existsAux = false;

    for (int i = 0; i < aux.size(); ++i) {
        if (!count(aux[i].begin(), aux[i].end(), 0)) {
            vector<string> vecAux = pathFinal[i];
            string aux1 = vecAux[0];
            string aux2 = vecAux[vecAux.size()-1];
            vector<string> path2 = airlines.get_shortest_path_code(aux1, aux2);
            airlines.printPath(path2);
            existsAux = true;
        }
    }

    if (!existsAux) {
        cout << endl << endl << "You CAN'T go from one coordinates to the other using only that company/companies!" << endl;
    }
}



void Menu::menuOption21(string airportCode) {

    int res = 0;

    for (auto i : airlines.getNodes()) {
        if (i.name == airportCode) {
            for (auto e : i.adj) {
                for (auto air : e.airline) {
                    res++;
                }
            }
            cout << endl << endl;
            cout << "Number of flights departing from the Airport ---> " << res << endl;
        }
    }

    cout << endl << endl <<  "Do you want to see the full informations? (y/n)" << endl;

    string option;
    cin >> option;

    if (option == "y") {
        cout << endl << endl << "Flights:" << endl;
        for (auto i : airlines.getNodes()) {
            if (i.name == airportCode) {
                for (auto e : i.adj) {
                    for (auto air : e.airline) {
                        for (auto t: d.getAirportsMap()) {
                            if (t.first == e.dest) {
                                for (auto g : d.getAirlinesMap()) {
                                    if (g.first == air)
                                        cout << airportCode << " ---> " << e.dest << " (" << t.second.getName() << ")"
                                             << "  -----------------  " << air << " (" << g.second.getName() << ")" << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void Menu::menuOption22(string airportCode) {

    set<string> airlinesCompany;

    for (auto i : airlines.getNodes()) {
        if (i.name == airportCode) {
            for (auto e : i.adj) {
                for (auto air : e.airline) {
                    airlinesCompany.insert(air);
                }
            }

            cout << endl << endl;
            cout << "Number of Airlines departing from the Airport ---> " << airlinesCompany.size() << endl;
        }
    }

    cout << endl << endl <<  "Do you want to see the full informations? (y/n)" << endl;

    string option;
    cin >> option;

    if (option == "y") {
        cout << endl << endl << "Airlines:" << endl;
        for (auto inSet : airlinesCompany) {
            for (auto g : d.getAirlinesMap()) {
                if (g.first == inSet)
                    cout << inSet << "   (" << g.second.getName() << ")" << endl;
            }
        }
    }
}



void Menu::menuOption23(string airportCode) {

    for (auto i : airlines.getNodes()) {
        if (i.name == airportCode) {
            cout << endl << endl;
            cout << "Number of different Destinies with direct flight from the Airport ---> " << i.adj.size() << endl;
        }
    }

    cout << endl << endl <<  "Do you want to see the full informations? (y/n)" << endl;

    string option;
    cin >> option;

    if (option == "y") {
        cout << endl << endl << "Destinies:" << endl;
        for (auto i : airlines.getNodes()) {
            if (i.name == airportCode) {
                for (auto e : i.adj) {
                    for (auto pair : d.getAirportsMap()) {
                        if (pair.first == e.dest)
                            cout << airportCode << " ---> " << e.dest << "   (" << pair.second.getCity() << ")" << endl;
                    }
                }
            }
        }
    }

}



void Menu::menuOption24(string airportCode) {

    set<string> countries;

    for (auto i : airlines.getNodes()) {
        if (i.name == airportCode) {
            for (auto e : i.adj) {
                for (auto pair : d.getAirportsMap()) {
                    if (pair.first == e.dest)
                        countries.insert(pair.second.getCountry());
                }
            }
            cout << endl << endl;
            cout << "Number of different Countries with direct flight from the Airport ---> " << countries.size() << endl;
        }
    }

    cout << endl << endl <<  "Do you want to see the full informations? (y/n)" << endl;

    string option;
    cin >> option;

    if (option == "y") {
        cout << endl << endl << "Countries: " << endl;
        for (auto g : countries) {
            cout << g << endl;
        }
    }
}



void Menu::menuOption25(string airportCode) {

    cout << endl << endl << "Enter Y value: " << endl;
    cout << " > ";

    int value;
    cin >> value;
    cout << endl << endl;

    int res = 0;
    set<string> cities;
    set<string> countries;
    set<string> airports;


    airlines.bfs(airportCode, value);

    for (auto i: airlines.getNodes()) {
        if (i.dist <= value && i.dist > 0) {
            //cout << "nome: " << i.name << "---------" << i.dist << endl;
            airports.insert(i.name);
            unordered_map<string, Airport> airportsMap2 = d.getAirportsMap();
            cities.insert(airportsMap2[i.name].getCity());
            countries.insert(airportsMap2[i.name].getCountry());
        }
    }

    cout << endl << endl;
    cout << "Number of Airports attainable using at most " << value << " flights ---> " << airports.size() << endl;

    cout << endl << endl;
    cout << "Number of Cities attainable using at most " << value << " flights ---> " << cities.size() << endl;

    cout << endl << endl;
    cout << "Number of Countries attainable using at most " << value << " flights ---> " << countries.size() << endl;





    cout << endl << endl << "Do you want to see the full list of Airports? (y/n)" << endl;

    string option;
    cin >> option;

    if (option == "y") {

        cout << endl << endl << "Flights: " << endl;
        for (auto air: airports) {
            vector<string> path1 = airlines.get_shortest_path_code(airportCode, air);
            airlines.printPath(path1);
        }
    }





    cout << endl << endl << "Do you want to see the full list of Cities? (y/n)" << endl;

    string option1;
    cin >> option1;

    if (option1 == "y") {
        cout << endl << endl << endl
             << "----------------------------------------------------------------------------" << endl;
        cout << endl << endl << "Cities: " << endl;
        for (auto city: cities) {
            cout << city << endl;
        }
    }






    cout << endl << endl << "Do you want to see the full list of Countries? (y/n)" << endl;

    string option2;
    cin >> option2;

    if (option2 == "y") {

        cout << endl << endl << endl
             << "----------------------------------------------------------------------------" << endl;
        cout << endl << endl << "Countries: " << endl;
        for (auto country: countries) {
            cout << country << endl;
        }
    }
}

