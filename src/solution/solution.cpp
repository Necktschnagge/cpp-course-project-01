#include "solution.h"
#include <vector>
#include <iostream>

void ausgabe_matrix(const std::vector<std::vector<bool>>& matrix){
	int matrix_x = matrix.size();
	for (int i = 0; i < matrix_x; ++i){
		auto& zeilenvektor = matrix.at(i);
		for (unsigned int j = 0; j < zeilenvektor.size(); ++j){
				std::cout << zeilenvektor.at(j) << "  ";
		}

		std::cout << '\n';
	}

}

void solve(int matrix_x, int matrix_y, long long int& result){

	std::vector<std::vector<bool>> field(matrix_x); //

	for (int i = 0; i<matrix_x; ++i){
		field.at(i) = std::vector<bool>(matrix_y, false);
	}

	ausgabe_matrix(field);

/*
	for (int i= 0; i < matrix_x; ++i){
		for (int j = 0; j <matrix_y; ++j){
			std:: cout << field.at(i).at(j) << " ";
		}
		std::cout << '\n';
	}
*/
	// insert your code to solve the task
	result = 0;
}
