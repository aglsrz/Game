#include "Soldiers.h"
using namespace  Lab4;

int Soldiers::nearAttack(Point pn)
{
	cout << damage << "Damage of the soldier\n";
	cout << p.y << ", " << p.x << " Coordinates\n";
	cout << pn.y << ", " << pn.x << " Coordinates of rthe point\n\n";
	int dx = p.x - pn.x;
	int dy = p.y - pn.y;
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	if ((dx <= 1) && (dy<=1))

	/*if ((((p.x - pn.x) <= 1) || ((p.x - pn.x) >= 1))&&
		(((p.y - pn.y) <= 1) || ((p.y - pn.y) >= 1)))*/
		return damage;
	return 0;//Если клетка не соседняя
}
