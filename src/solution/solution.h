/*
* This is the header file to import the solution to any ide or project.
*/
#ifndef SOLUTION_H
#define SOLUTION_H
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
//#include <boost//multiprecision/cpp_int.hpp>

using Field = std::vector<std::vector<bool>>;


void solve(int matrix_x, int matrix_y, long long int& result);


struct coord {
	int x;
	int y;
};

#endif
