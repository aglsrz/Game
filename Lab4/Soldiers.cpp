#include "Soldiers.h"
using namespace  Lab4;

int Soldiers::nearAttack(Point pn)
{
	if (((p.x - pn.x) <= 1) && ((p.x - pn.x) >= 1) && ((p.y - pn.y) <= 1) && ((p.y - pn.y) >= 1))
		return damage;
	return 0;//Если клетка не соседняя
}
