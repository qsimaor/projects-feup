#include "src/Menu.h"

int main() {

    Data d;
    d.readFlights();
    d.readAirports();
    d.readAirlines();

    Menu menu(d);
    menu.runMainMenu();

    return 0;
}
