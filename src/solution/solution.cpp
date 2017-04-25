#include <assert.h>
#include <strings.h>
#include <vector>
#include "solution.h"

#define for2D(point, x_start, y_start, x_end, y_end) Point point; for (point.y = y_start; point.y < y_end; point.y++) for (point.x = x_start; point.x < x_end; point.x++)
#define forBitmap(point, bitmap) for2D(point, bitmap.position.x, bitmap.position.y, bitmap.position.x + bitmap.size.x, bitmap.position.y + bitmap.size.y)

// TODO: Code kommentieren

struct Point
{
	int x;
	int y;
};

class Bitmap
{
private:

	Point size;
	Point position;
	bool *data;

	Point toRelative(Point absolute) const;

	Point toAbsolute(Point relative) const;

	bool getRelative(Point relative) const;

	void setRelative(Point relative, bool value);

public:

	Bitmap(int width, int height, bool *data);

	bool get(Point absolute) const;

	void set(Point absolute, bool value);

	void set(Bitmap& bitmap, bool value);

	bool getFalsePoint(Point& result) const;

	bool fits(Bitmap& bitmap) const;

	void zero();

	std::vector<Bitmap> getFittingPieces(Point pos) const;
};


Bitmap pieces[6] = {
	 Bitmap(3, 1, (bool[3]){ 1, 1, 1 }),
	 Bitmap(1, 3, (bool[3]){ 1, 1, 1 }),
	 Bitmap(2, 2, (bool[4]){ 0, 1, 1, 1 }),
	 Bitmap(2, 2, (bool[4]){ 1, 0, 1, 1 }),
	 Bitmap(2, 2, (bool[4]){ 1, 1, 0, 1 }),
	 Bitmap(2, 2, (bool[4]){ 1, 1, 1, 0 })
};



Bitmap::Bitmap(int width, int height, bool *data)
{
	assert(data != nullptr);

	this->size = {
		.x = width,
		.y = height
	};

	this->position = {
		.x = 0,
		.y = 0
	};

	this->data = data;
}

Point Bitmap::toRelative(Point absolute) const
{
	return {
		.x = absolute.x - this->position.x,
		.y = absolute.y - this->position.y
	};
}

Point Bitmap::toAbsolute(Point relative) const
{
	return {
		.x = relative.x + this->position.x,
		.y = relative.y + this->position.y
	};
}

bool Bitmap::getRelative(Point relative) const
{
	return relative.x < 0 || relative.x >= this->size.x || relative.y < 0 || relative.y >= this->size.y ?
		   true :
		   this->data[relative.y * this->size.x + relative.x];
}

void Bitmap::setRelative(Point relative, bool value)
{
	if (relative.x >= 0 && relative.x < this->size.x && relative.y >= 0 && relative.y < this->size.y)
	{
		this->data[relative.y * this->size.x + relative.x] = value;
	}
}

bool Bitmap::get(Point absolute) const
{
	return this->getRelative(this->toRelative(absolute));
}

void Bitmap::set(Point absolute, bool value)
{
	this->setRelative(this->toRelative(absolute), value);
}

void Bitmap::set(Bitmap &bitmap, bool value)
{
	forBitmap(absolute, bitmap)
	{
		if (bitmap.get(absolute))
		{
			this->set(absolute, value);
		}
	}
}

bool Bitmap::getFalsePoint(Point& result) const
{
	for2D(relative, 0, 0, this->size.y, this->size.y)
	{
		if (!this->getRelative(relative))
		{
			result = this->toAbsolute(relative);
			return true;
		}
	}

	return false;
}

bool Bitmap::fits(Bitmap& bitmap) const
{
	forBitmap(absolute, bitmap)
	{
		if (this->get(absolute) && bitmap.get(absolute))
		{
			return false;
		}
	}

	return true;
}

void Bitmap::zero()
{
	bzero(this->data, sizeof(*data) * this->size.x * this->size.y);
}

std::vector<Bitmap> Bitmap::getFittingPieces(Point pos) const
{
	std::vector<Bitmap> result;

	for (unsigned i = 0; i < 6; i++)
	{
		Bitmap piece = pieces[i];

		for2D(relative_to_piece, 0, 0, piece.size.x, piece.size.y)
		{
			if (piece.getRelative(relative_to_piece))
			{
				piece.position = {
					.x = pos.x - relative_to_piece.x,
					.y = pos.y - relative_to_piece.y
				};

				if (this->fits(piece))
				{
					result.push_back(piece);
				}
			}
		}
	}

	return result;
}

unsigned long long solve(Bitmap& matrix)
{
	Point free_point;
	if (!matrix.getFalsePoint(free_point))
	{
		return 1;
	}

	unsigned long long result = 0;
	std::vector<Bitmap> fitting_pieces = matrix.getFittingPieces(free_point);

	for (unsigned long i = 0; i < fitting_pieces.size(); i++)
	{
		Bitmap& piece = fitting_pieces[i];

		matrix.set(piece, true);

		result += solve(matrix);

		matrix.set(piece, false);
	}

	return result;
}

unsigned long long solve(int width, int height)
{
	if (width < 0 || height < 0) return 0;
	if (width % 3 != 0 && height % 3 != 0) return 0;

	bool data[width * height];
	Bitmap matrix = Bitmap(width, height, data);
	matrix.zero();

	return solve(matrix);
}
