#include <iostream>
#include "../code/data_structures/Graph.h"
using namespace std;

int main() {
    Graph g = Graph();
    int option1=-1;
    bool gn = false;
    string stations,network;
    do {
        cout << "\n____________________________________________________________" << endl;
        cout << "     [1]     Parse                                         " << endl;
        cout << "     [2]     Basic Service Metrics                         " << endl;
        cout << "     [3]     Max No. of Trains Between 2 Stations Using the" << endl;
        cout << "             Cheapest Path (Operation Cost Optimization)   " << endl;
        cout << "     [4]     Reliability and Sensitivity to Line Failures  " << endl;
        cout << "                                                           " << endl;
        cout << "     [0]     Exit                                          " << endl;
        cout << "___________________________________________________________" << endl;

        cout << "\nEnter an option: ";
        cin >> option1;
        switch (option1) {
            case 1: {
                if(gn){
                    g = Graph();
                }

                cout << "\nEnter the path of the desired stations data file: ";
                cin >> stations;
                cout << "\nEnter the path of the desired network data file: ";
                cin >> network;

                gn = g.parser(stations, network);

                if (!gn) {
                    cout << "\nERROR: Can't parse the data from the given files' paths!" << endl;
                }
                else {
                    cout << "\nParsed!" << endl;
                }
            }break;
            case 2: {
                if(gn==0){
                    cout << "\nERROR: You need to do '[1] Parse' before trying to access this menu!" << endl;
                }
                else{
                int option2 = -1;
                do{
                    cout << "\n______________________________________________________________________" << endl;
                    cout << "     [1]     Max Number of Trains that can simultaneously travel      " << endl;
                    cout << "             between two specific stations                            " << endl;
                    cout << "     [2]     The Pair(s) of Stations that Require the Most Amount of  " << endl;
                    cout << "             Trains (taking full advantage of the network's capacity) " << endl;
                    cout << "     [3]     Current Top-k Municipalities/Districts that need more    " << endl;
                    cout << "             budget to sustain its services                           " << endl;
                    cout << "     [4]     Max No. of Trains that arrive simultaneously at a station" << endl;
                    cout << "                                                                      " << endl;
                    cout << "     [0]     Back                                                     " << endl;
                    cout << "______________________________________________________________________" << endl;

                    cout << "\nEnter an option:";
                    cin >> option2;
                    switch(option2){
                        case 1:{
                            string sta_A,sta_B;
                            cout << "\nEnter the name of the source station:";
                            cin.ignore();
                            getline(cin,sta_A);
                            cout << "\nEnter the name of the target station:";
                            getline(cin,sta_B);
                            cin.clear();
                            auto trains = g.edmondsKarp(sta_A,sta_B);
                            cout << endl;
                            if(trains==0){
                                cout << "There's no connection between "<< sta_A << " and " << sta_B << endl;
                            }
                            else {
                                cout << "The max number of trains that can simultaneously travel between" << endl;
                                cout << sta_A << " and " << sta_B << " are " << trains << " trains." << endl;
                            }
                            system("pause");
                        }break;
                        case 2:{
                            auto pa = g.getPairs_MostAmountOfTrains();
                            cout << endl;
                            for(auto p:pa){
                                cout << p.first.first << " - " << p.first.second << endl;
                            }
                            cout << endl;
                            cout << "This/these pair(s) require " << pa[0].second << " trains when" << endl;
                            cout << "taking full advantage of the network's capacity." << endl;
                            cout << endl;
                            system("pause");
                        }break;
                        case 3:{
                            string md;
                            int k;
                            cout << "\nDo you want to search Municipalities(M/m) or Districts(D/d)?";
                            cin >> md;
                            cout << "\nHow big will the top be? ";
                            cin >> k;
                            if(md == "M" || md == "m"){
                                cout << "\nTOP " << k << " MUNICIPALITIES" << endl;
                                auto v = g.budgetMunicipalities(k);
                                int i = 1;
                                for (auto p: v){
                                    cout << "\n" << i << ". || " << p.first << " || " << p.second;
                                    i++;
                                }
                                cout << flush;
                                cout << endl;
                            }
                            else if(md == "D" || md == "d"){
                                cout << "\nTOP " << k << " DISTRICTS" << endl;
                                auto v = g.budgetDistricts(k);
                                int i = 1;
                                for (auto p:v){
                                    cout << "\n" << i << ". || " << p.first << " || " << p.second;
                                    i++;
                                }
                                cout << flush;
                                cout << endl;
                            }
                            system("pause");
                        }break;
                        case 4:{
                            string station;
                            cout << "\nEnter the name of the desired station:";
                            cin.ignore();
                            getline(cin,station);
                            auto v=g.findVertex(station);
                            if(v == nullptr){
                                cout << "\nERROR: You need to enter a valid station name!" << endl;
                            }
                            else{
                            double flow = g.maxTrainsAtStation(v->getName());
                            cout <<"\nThe max number of trains that arrive at " << station << " is " << flow << " trains." << endl;}
                            system("pause");
                        }break;
                    }
                }while(option2!=0);}
            }break;
            case 3: {
                if(gn==0){
                    cout << "\nERROR: You need to do '[1] Parse' before trying to access this menu!" << endl;
                }
                else{
                    string station1, station2;
                    cin.ignore();
                    cout << "\nName of first station?";
                    getline(cin,station1);
                    cout << "\nName of second station?";
                    getline(cin,station2);
                    cin.clear();

                    g.max_trains_min_cost(station1, station2);

                    system("pause");
                }

            }break;
            case 4: {
                if(gn==0){
                    cout << "\nERROR: You need to do '[1] Parse' before trying to access this menu!" << endl;
                }
                else{
                    int option4 = -1;
                    do {
                        cout << "\n__________________________________________________________________" << endl;
                        cout << "             Line Failures                                       " << endl;
                        cout << "_________________________________________________________________" << endl;
                        cout << "     [1]     Max Number of Trains that can simultaneously travel " << endl;
                        cout << "             between two specific stations                       " << endl;
                        cout << "     [2]     Top-k stations most affected by (a) failure(s)      " << endl;
                        cout << "                                                                 " << endl;
                        cout << "     [0]     Back                                                " << endl;
                        cout << "_________________________________________________________________" << endl;

                        cout << "\nEnter an option: ";
                        cin.ignore();
                        cin >> option4;
                        switch(option4){
                            case 1:{
                                Graph f = Graph();
                                f.parser(stations,network);
                                string station1, station2;
                                cout << "\nPlease input the name of the origin station: " << endl;
                                cin.ignore();
                                getline(cin,station1);
                                cout << "\nPlease input the name of the target station: " << endl;
                                getline(cin,station2);
                                bool options=true;
                                while(options){
                                    string cutstation,answer1,answer2,sta_A,sta_B;
                                    cout << "\nDo you want to remove a station or a line? Station(S/s) or Line(L/l): " << endl;
                                    getline(cin,answer1);
                                    if(answer1=="S" || answer1=="s") {
                                        cout << "\nPlease input the name of the station: " << endl;
                                        getline(cin, cutstation);
                                        f.removeVertex(cutstation);
                                    }
                                    else if(answer1=="L" || answer1=="l"){
                                        cout << "\nPlease input the name of the source station: " << endl;
                                        getline(cin, sta_A);
                                        cout << "\nPlease input the name of the target station: " << endl;
                                        getline(cin, sta_B);
                                        f.findVertex(sta_A)->removeEdge(sta_B);
                                    }
                                    else{
                                        cout << "\nInsert a valid character... " << endl;
                                    }
                                    cout << "\nDo you want to keep adding more failures to the network? Yes(Y/y) or No(N/n): " << endl;
                                    getline(cin,answer2);
                                    if(answer2=="Y" || answer2=="y"){
                                        continue;
                                    }
                                    else if (answer2=="N" || answer2=="n"){
                                        options=false;
                                    }
                                    else{
                                        cout << "\nInsert a valid character... " << endl;
                                    }
                                }
                                cout << flush;
                                auto trains = f.edmondsKarp(station1,station2);
                                if(trains==0){
                                    cout << "There's no connection between "<< station1 << " and " << station2 << endl;
                                }
                                else {
                                    cout << "The max number of trains that can simultaneously travel between" << endl;
                                    cout << station1 << " and " << station2 << " are " << trains << " trains." << endl;
                                }
                                system("pause");
                            }break;

                            case 2:{
                                Graph f = Graph();
                                f.parser(stations,network);
                                bool options=true;
                                while(options){
                                    string cutstation,answer1,answer2,sta_A,sta_B;
                                    cin.ignore();
                                    cout << "\nDo you want to remove a station or a line? Station(S/s) or Line(L/l): " << endl;
                                    getline(cin,answer1);
                                    if(answer1=="S" || answer1=="s") {
                                        cout << "\nPlease input the name of the station: " << endl;
                                        getline(cin, cutstation);
                                        f.removeVertex(cutstation);
                                    }
                                    else if(answer1=="L" || answer1=="l"){
                                        cout << "\nPlease input the name of the source station: " << endl;
                                        getline(cin, sta_A);
                                        cout << "\nPlease input the name of the target station: " << endl;
                                        getline(cin, sta_B);
                                        f.findVertex(sta_A)->removeEdge(sta_B);
                                    }
                                    else{
                                        cout << "\nInsert a valid character... " << endl;
                                    }
                                    char option;
                                    cout << "\nDo you want to keep adding more failures to the network? Yes (Press '1') or No (Press any key): " << endl;
                                    cin >> option;
                                    if (option == '1') {
                                        continue;
                                    } else {
                                        options = false;
                                    }
                                }
                                cout << flush;
                                int k;
                                cout << "\nHow big will the top be? ";
                                cin >> k;
                                cout << "\nTOP " << k << " MOST AFFECTED STATIONS" << endl;
                                auto v = g.differenceMaxFlowFailures(f,k);
                                int i = 1;
                                for (auto p:v){
                                    cout << "\n" << i << ". || " << p.first << " || " <<  p.second;
                                    i++;
                                }
                                cout << flush;
                                cout << endl;
                                system("pause");
                            }break;
                        }
                        cout << flush;
                    }while(option4!=0);}
            }break;
            default:
                break;
        }
    } while (option1!=0);
    return 0;
}