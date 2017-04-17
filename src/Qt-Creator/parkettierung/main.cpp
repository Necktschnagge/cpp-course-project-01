// Einstiegspunkt in die Anwendung

// extern headers:
#include <iostream>

// own headers:
#include "../../solution/solution.h"

void error() {
    std::cerr << "\nunerwarteter Fehler\n";
    exit(1);
}

int main()
{
    using namespace std;

    int x, y;
    long long result = 0;

    cout << "Loesung fuer Parkettierungsaufgabe\n"
        << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n\n"
        << "Es soll ein x * y Feld aus quadratischen Kaestchen mit zusammenhaegenden Puzzelteilen aus drei Einzelquadraten befuellt werden"
        << "\n\n\n"
        << "x?\n";
    //cout << solution::aaa;
    if (!(cin >> x)) error();
    cout << "\ny?\n";
    if (!(cin >> y)) error();
    /*solution::*/solve(x, y, result);
    cout << "\n\n\n"
        << "Es gibt fuer ein " << x << " x " << y << " - Feld\n" << result << "\nMoeglichkeiten fuer eine Parkettierung.\n";
    return 0;
}

