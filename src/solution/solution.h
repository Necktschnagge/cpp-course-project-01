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


class BigInt {
	unsigned long long lower;
	unsigned long long upper;

	BigInt() : lower(0), upper(0){}
	BigInt(unsigned long long l, unsigned long long u) : lower(l), upper(u) {}

	BigInt operator + (const BigInt& r) {
		unsigned long long zwischen = (lower + r.lower);
		return BigInt(zwischen & (0x7FFFFFFFFFFFFFFFLL), upper + r.upper + (!!((zwischen) & (1<<63))));
	}
	
	std::ostream& operator << (std::ostream& stream) {
		stream << lower;
		if (upper) {
			stream << "  +  2^63 * " << upper;
		}
		return stream;
	}
	
};
#endif
