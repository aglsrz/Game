#include "Arrows.h"
#include <math.h>
#include <fstream>

using namespace Lab4;
int Arrows::fireAttack(Point pn)
{
	int d;
	d= sqrt((pn.x - p.x)*(p.y - pn.y)*(p.x - pn.x)*(p.y - pn.y));
	if (d > rad)
		return 0;
	return damage;
}
void Arrows::loadrad(ifstream &f){
	int n;
	f >> n;
	rad = n;
}