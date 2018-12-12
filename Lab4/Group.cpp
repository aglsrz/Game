#include "Group.h"
#include <fstream>
using namespace std;
using namespace Lab4;

namespace Lab4{
	Group::Group() : initiative(0), num(0), dead_num(0), exp(0){}
	Group* Group::clone() {
		Group *g = new Group;
		g->initiative = initiative;
		g->name = name;
		g->p = p;
		g->school = school;
		g->master = master;
		g->velocity = velocity;
		g->damage = damage;
		g->num = num;
		g->dead_num = dead_num;
		g->exp = exp;
		g->protection = protection;
		return g;
	}

	//Получить урон 
	int Group::harmGroup(int d)
	{
		int x = d - protection;
		dead_num += x;
		num -= x;
		if (num <= 0)
			return 1;//если отряд уничтожен
		return 0;//если остались в живых
	}
	Group & Group::setvelocity(int v){
		if (v<=0)
			throw std::exception("Invalid velocity.");
		velocity = v;
		return *this;
	}
	Group & Group::setdamage(int d){
		damage = d;
		return *this;
	}
	Group & Group::setprotection(int p){
		if (p <= 0)
			throw std::exception("Invalid protrction.");
		protection = p;
		return *this;
	}
	Group & Group::setnum(int N)
	{
		if (N <= 0)
			throw std::exception("Invalid number of group members.");
		num = N;
		return *this;
	}
	Group & Group::setexp(int ex){
		if (ex < 0)
			throw std::exception("Invalid value of experince.");
		exp = ex;
		return *this;
	}
	void Group::download(ifstream &f){
		string str;
		Point p;
		int i;
		f >> str;	name = str;
		f >> str; school = str;
		f >> p.x >> p.y;
		setcoord(p);
		f >> i;	initiative = i;
		f >> i;	master = i;
		f >> i;	setvelocity(i);
		f >> i;	setdamage(i);
		f >> i;	setprotection(i);
		f >> i;	setnum(i);
		f >> i;	dead_num = i;
		f >> i;	setexp(i);
	}
}