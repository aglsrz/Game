#include "Group.h"

#ifndef	SOLDIERS_H
#define SOLDIERS_H


using namespace std;
namespace Lab4{
	class Soldiers : virtual public Group{
	public:
		Soldiers() : Group(){}
		int gettype(){ return 1; }
		int nearAttack(Point);
	};
}
#endif