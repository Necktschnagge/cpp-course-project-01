/*
* This is the header file to import the solution to any ide or project.
*/
#ifndef SOLUTION_H
#define SOLUTION_H

#ifdef _MSC_VER
#include "../Visual-Studio/parkettierung/parkettierung/stdafx.h"
#endif // _MSC_VER

#include <iostream>
#include <vector>
#include <map>
#include <list>

//#include <boost//multiprecision/cpp_int.hpp>

using Field = std::vector<std::vector<bool>>;


void solve(int matrix_x, int matrix_y, long long int& result);


struct coord {
	int x;
	int y;
};

#if false
// Zeug das noch nicht funktioniert...
class BigInt {
	unsigned long long lower;
	unsigned long long upper;
public:
	BigInt() : lower(0), upper(0){}
	BigInt(unsigned long long l, unsigned long long u) : lower(l), upper(u) {}

	BigInt operator + (const BigInt& r) {
		unsigned long long zwischen = (lower + r.lower);
		return BigInt(zwischen & (0x7FFFFFFFFFFFFFFFLL), upper + r.upper + (!!((zwischen) & (1ULL<<63))));
	}
	
	void /*const BigInt&*/ operator = (int x) {
		lower = x;
		upper = 0;
		//return *this;
	}

	friend std::ostream& operator << (std::ostream& stream, const BigInt& i);
	
};

std::ostream& operator << (std::ostream& stream, const BigInt& i) {
	stream << i.lower;
	if (i.upper) {
		stream << "  +  2^63 * " << i.upper;
	}
	return stream;
}
#else
using BigInt = long long int;
#endif
#endif
