// just type into console:
		// g++ main.cpp ../solution/solution.cpp
		// ... and it should work.

// extern headers:
#include <iostream>
#include <ctime>

// own headers:
#include "../solution/solution.h"

void error() {
	std::cerr << "\nunerwarteter Fehler\n";
	std::cin.sync();
	std::cin.get();
	std::cin.get();
	exit(1);
}

int main()
{
	using namespace std;

	int x, y;
	long long result = 0;
	cout << "Loesung fuer Parkettierungsaufgabe\n"
		<< "같같같같같같같같같같같같같같같같같\n\n"
		<< "Es soll ein x * y Feld aus quadratischen Kaestchen mit zusammenhaegenden Puzzelteilen aus drei Einzelquadraten befuellt werden"
		<< "\n\n\n"
		<< "x?\n";
	//cout << solution::aaa;
	if (!(cin >> x)) error();
	cout << "\ny?\n";
	if (!(cin >> y)) error();
	time_t begin = time(nullptr);
	/*solution::*/solve(x, y, result);
	time_t end = time(nullptr);
	cout << "\n\n\n"
		<< "Es gibt fuer ein " << x << " x " << y << " - Feld\n" << result << "\nMoeglichkeiten fuer eine Parkettierung.\n"
		<< "\nZeit:  " << end-begin << "s\n";
	cin.get();
	return 0;
}

