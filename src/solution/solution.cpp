#include <assert.h>
#include <strings.h>
#include <vector>
#include "solution.h"

/**
 * Erstellt eine Variable `point` vom Typ `struct Point`, welche über jeden Punkt der angegebenen Fläche iteriert.
 */
#define for2D(point, x_start, y_start, x_end, y_end) Point point; for (point.y = y_start; point.y < y_end; point.y++) for (point.x = x_start; point.x < x_end; point.x++)

/**
 * Erstellt eine Variable `point` vom Typ `struct Point`, welche über jeden Punkt des angegebenen Bitmaps iteriert.
 */
#define forBitmap(point, bitmap) for2D(point, bitmap.position.x, bitmap.position.y, bitmap.position.x + bitmap.size.x, bitmap.position.y + bitmap.size.y)


struct Point
{
	int x;
	int y;
};

/**
 * Speichert ein 2D-Array von Booleans, welches sich an einer bestimmten Position in der Ebene befindet.
 */
class Bitmap
{
private:

	/**
	 * Größe des 2D-Arrays.
	 */
	Point size;

	/**
	 * Position des linken unternen "Pixels".
	 */
	Point position;

	/**
	 * Pointer auf das eigentliche Array.
	 */
	bool *data;

	/**
	 * Rechnet die gegebene absolute Koordinate (relativ zum Koordinatenursprung) in eine Koordinate relativ zur linken
	 * unteren Ecke des Bitmaps um.
	 */
	Point toRelative(Point absolute) const;

	/**
	 * Rechnet die gegebene relative Koordinate (relativ zur linken unteren Ecke des Bitmaps), in eine Absolute um.
	 */
	Point toAbsolute(Point relative) const;

	/**
	 * Gibt den Wert des Bitmaps an der gegebenen Koordinate (relativ zur linken unteren Ecke) zurück.
	 * Liegt die Koordinate auserhalb des Bitmaps, wird `true` zurückgegeben.
	 */
	bool getRelative(Point relative) const;

	/**
	 * Setzt den Wert des Bitmaps an der gegebenen Koordinate (relativ zur linken unteren Ecke).
	 * Liegt die Koordinate auserhalb des Bitmaps, passiert nichts.
	 */
	void setRelative(Point relative, bool value);

public:

	/**
	 * Erstellt ein neues Bitmap mit gegebener Größe.
	 * Die Position wird auf (0, 0) initialisiert.
	 *
	 * ACHTUNG: Diese Klasse kümmert sich nicht um die Speicherverwaltung des unterliegenden bool-Arrays.
	 *          Sie verwendet lediglich den hier übergebenen Pointer um auf die einzelnen Elemente zuzugreifen.
	 */
	Bitmap(int width, int height, bool *data);

	/**
	 * Gibt den Wert des Bitmaps an der gegebenen Koordinate zurück.
	 * Liegt die Koordinate auserhalb des Bitmaps, wird `true` zurückgegeben.
	 */
	bool get(Point absolute) const;

	/**
	 * Setzt den Wert des Bitmaps an der gegebenen Koordinate.
	 * Liegt die Koordinate außerhalb des Bitmaps, passiert nichts.
	 */
	void set(Point absolute, bool value);

	/**
	 * Setzt alle Punkte, die in `bitmap` gesetzt sind, in `this` auf `value`.
	 */
	void set(Bitmap& bitmap, bool value);

	/**
	 * Sucht nach einem Punkt im Bitmap, der auf `false` gesetzt ist.
	 * Der erste gefundene Punkt wird in `result` gespeichert.
	 *
	 * @return `true` gdw. ein Punkt gefunden wurde.
	 */
	bool getFalsePoint(Point& result) const;

	/**
	 * Überprüft, ob `bitmap` in `this` "hineinpasst", d.h. kein Punkt in beiden Bitmaps auf `true` gesetzt ist.
	 */
	bool fits(Bitmap& bitmap) const;

	/**
	 * Setzt das komplette Bitmap auf 0 (false).
	 */
	void zero();

	/**
	 * Gibt eine Liste mit allen "Puzzelstücken" zurück, die so in `this` passen, dass sie den Punkt `pos` bedecken.
	 *
	 * ACHTING: Die zurückgegebenen Bitmaps verweisen auf die gleichen bool-Arrays, wie die Bitmaps aus `pieces`.
	 *          Also diese lieber nicht verändern!
	 */
	std::vector<Bitmap> getFittingPieces(Point pos) const;
};


/**
 * Array aller "Puzzelstücke"
 */
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
				// Für jedes gesetzte Pixel (`relative_to_piece`) in `piece`, welches also `pos` überdecken könnte:
				// rechne die Startkoordinaten aus, die `piece` haben müsste, sodass dieses Pixel auf `pos` fällt.
				piece.position = {
					.x = pos.x - relative_to_piece.x,
					.y = pos.y - relative_to_piece.y
				};

				// Wenn `piece` an dieser Position in die Matrix passt, füge es zur Liste hinzu.
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
		// Wenn es keinen freien Pixel gibt, hat das Problem genau eine Lösung.
		return 1;
	}

	unsigned long long result = 0;
	std::vector<Bitmap> fitting_pieces = matrix.getFittingPieces(free_point);

	for (unsigned long i = 0; i < fitting_pieces.size(); i++)
	{
		// für jedes Teil (`piece`), dass noch in `matrix` passt
		Bitmap& piece = fitting_pieces[i];

		// löse das Problem für die Matrix ohne `piece`
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
