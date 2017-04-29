#include "solution.h"
#include <iostream>

std::map < std::vector<std::vector<bool>>, unsigned long long > all;
std::list<std::vector<std::vector<bool>>> cur;
std::list<std::vector<std::vector<bool>>> nex;

std::list<std::vector<std::vector<bool>>>* pc;
std::list<std::vector<std::vector<bool>>>* pn;

int GX;
int GY;
int mind_zeile{ 0 };

bool new_free(int& xx, int& yy, const Field& field) {
	for (int x = mind_zeile; x < GX; ++x) {
		for (int y = 0; y < GY; ++y) {
			if (field.at(x).at(y) == false) {
				xx = x;
				yy = y;
				mind_zeile = x > 0 ? x - 1 : 0;
				return true;
			}
		}
	}
	return false;
}

bool adv_at(Field& field, int x, int y) {
	static bool dummy;
	try {
		return (field.at(x).at(y));
	}
	catch (...) {
		dummy = true;
		return dummy;
	}
}

const std::vector<std::vector<coord>> ntiles{
	{
		{0,0}, {0,1}, {0,2}
	},
	{
		{0,0}, {0,1}, {1,1}
	},
	{
		{0,0}, {0,1}, {1,0}
	},
	{
		{0,0}, {1,0}, {1,1}
	},
	{
		{0,0}, {1,0}, {2,0}
	},
	{
		{0,0}, {1,0}, {1,-1}
	}
};

const std::vector<Field> tiles = {
	{
		{0,1,1,1}, {0,0,0,0}, {0,0,0,0}
	},
	{
		{0,1,1,0}, {0,0,1,0}, {0,0,0,0}
	},
	{
		{0,1,1,0}, {0,1,0,0}, {0,0,0,0}
	},
	{
		{0,1,0,0}, {0,1,1,0}, {0,0,0,0}
	},
	{
		{0,1,0,0}, {0,1,0,0}, {0,1,0,0}
	},
	{
		{0,1,0,0}, {1,1,0,0}, {0,0,0,0}
	}
};

void solve(int matrix_x, int matrix_y, long long int& result){
	if (matrix_y > matrix_x) return solve(matrix_y, matrix_x, result);
	if ((matrix_x * matrix_y) % 3) { result = 0; return; }
	GX = matrix_x;
	GY = matrix_y;

	Field field = std::vector<std::vector<bool>>(matrix_x, std::vector<bool>(matrix_y, false));
	all[field] = 1;
	cur.push_back(field);

	pc = &cur;
	pn = &nex;
	int counter{ 0 };
	while (true)
	{
		std::cout << "Lege Teil Nr" << ++counter << '\n';
		//int cinner{ 0 };
		auto state_iter = pc->begin();
		while (state_iter != pc->end())
		{	
			//++cinner;
			auto state = *(state_iter++);
			
			int xn, yn;
			bool has_free = new_free(xn, yn, state);
			if (!has_free) {
				//std::cout << all[state] << "Möglichkeiten";
				result = all[state];
				return;
			}
			//std::cout << "es hat freie pläütze\n";
			
			for (auto tile : tiles) {
				Field nstate = state;
				// schauen ob man tile drauflegen kann.
				bool not_okay{ false };
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 4; ++j) {
						if (tile.at(i).at(j)) {
							if (adv_at(nstate, xn + i, yn + j - 1)) {
								not_okay = true;
								goto here;
							}
						}
					}
				}
	here:
				if (not_okay) continue;
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 4; ++j) {
						if (tile.at(i).at(j)) {
							nstate.at(xn + i).at(yn + j - 1) = true;
						}
					}
				}
				// nstate in die map hinzufügen
				try {
					all.at(nstate) += all.at(state);
				}
				catch (...) {
					all[nstate] = all.at(state);
					pn->push_back(nstate);
				}
				// nstate auf die neue liste setzen.

				//std::cout << "jetzt auf pn:" << pn->size() << std::endl;
			}// for tiles
		}

		for (const Field& item: *pc) {
			all.erase(item);
		}
		pc->clear();
		std::swap(pn, pc);
	}

	// insert your code to solve the task
	result = 0;
}
