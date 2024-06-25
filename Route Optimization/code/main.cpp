#include <iostream>
#include "../code/data_structures/Graph.h"
using namespace std;

int main() {
    Graph g = Graph();
    int option1=-1;
    bool gn = false;
    while (option1!=0) {
        if(gn){
            g = Graph();
        }
        cout << "\n______________________________________________________________" << endl;
        cout << "             Please select the desired graph to test:         " << endl;
        cout << "                                                              " << endl;
        cout << "     [>]     Toy-Graphs                                       " << endl;
        cout << "         [1]     shipping                                     " << endl;
        cout << "         [2]     stadiums                                     " << endl;
        cout << "         [3]     tourism                                      " << endl;
        cout << "                                                              " << endl;
        cout << "     [>]     Real-World Graphs                                " << endl;
        cout << "         [4]     graph1                                       " << endl;
        cout << "         [5]     graph2                                       " << endl;
        cout << "         [6]     graph3                                       " << endl;
        cout << "                                                              " << endl;
        cout << "     [7]     Extra-Fully-Connected Graphs                     " << endl;
        cout << "                                                              " << endl;
        cout << "     [>]     Other files...                                   " << endl;
        cout << "         [8]     Using 1 file                                 " << endl;
        cout << "         [9]     Using 2 files                                " << endl;
        cout << "                                                              " << endl;
        cout << "     [0]     Exit                                             " << endl;
        cout << "______________________________________________________________" << endl;

        cout << "\nEnter an option: ";
        cin >> option1;
        switch (option1) {
            case 1: {
                g.parser_onefile("../data/Toy-Graphs/shipping.csv");
                gn = true;
            }break;
            case 2: {
                g.parser_onefile("../data/Toy-Graphs/stadiums.csv");
                gn = true;
            }break;
            case 3: {
                g.parser_onefile("../data/Toy-Graphs/tourism.csv");
                gn = true;
            }break;
            case 4: {
                g.parser_twofiles("../data/Real-world Graphs/graph1/edges.csv","../data/Real-world Graphs/graph1/nodes.csv");
                gn = true;
            }break;
            case 5: {
                g.parser_twofiles("../data/Real-world Graphs/graph2/edges.csv","../data/Real-world Graphs/graph2/nodes.csv");
                gn = true;
            }break;
            case 6: {
                g.parser_twofiles("../data/Real-world Graphs/graph3/edges.csv","../data/Real-world Graphs/graph3/nodes.csv");
                gn = true;
            }break;
            case 7: {
                string file_n;
                cout << "\nName of the desired .csv file: ";
                cin >> file_n;
                string path = "../data/Extra_Fully_Connected_Graphs/" + file_n + ".csv";
                g.parser_onefile(path);
                gn = true;
            }break;
            case 8: {
                string file_n;
                cout << "\nPath of the desired .csv file: ";
                cin >> file_n;
                g.parser_onefile(file_n);
                gn = true;
            }break;
            case 9: {
                string edges_n,nodes_n;
                cout << "\nPath of the desired edges .csv file: ";
                cin >> edges_n;
                cout << "\nPath of the desired nodes .csv file: ";
                cin >> nodes_n;
                g.parser_twofiles(edges_n,nodes_n);
                gn = true;
            }break;
            case 0:{
                option1 = 0;
                break;
            }
            default:
                break;
        }
        if (option1 == 0) {
            break;
        }
        int option2;
        cout << "\n______________________________________________________________" << endl;
        cout << "             Please select the desired algorithm:             " << endl;
        cout << "                                                              " << endl;
        cout << "     [1]     Backtracking                                     " << endl;
        cout << "     [2]     Triangular Approximation                         " << endl;
        cout << "     [3]     Christofides Algorithm                           " << endl;
        cout << "                                                              " << endl;
        cout << "     [0]     Change Graph                                     " << endl;
        cout << "______________________________________________________________" << endl;

        cout << "\nEnter an option: ";
        cin >> option2;
        switch (option2) {
            case 1:{
                g.backtrack_tsp();
                system("pause");
            }break;
            case 2:{
                g.triangularApproximation();
                system("pause");
            }break;
            default:
                break;
        }
    }
    return 0;
}
