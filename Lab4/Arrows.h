#include "Group.h"
#ifndef	ARROWS_H
#define ARROWS_H
using namespace std;
namespace Lab4{
	class Arrows : virtual public Group{
	protected:
		int rad;
	public:
		Arrows(): Group(), rad(0){}
		int gettype(){ return 2; }
		int fireAttack(Point );
		void loadrad(ifstream &);
	};
}
#endif