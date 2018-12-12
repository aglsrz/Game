#include <iostream>
#include <string>

#ifndef GROUP_H
#define GROUP_H
//в файле писатоь первой строкой тип
using namespace std;
namespace Lab4{

	struct Point{
		int x;
		int y;
	};

	class Group{
	protected:
		string name;
		string school;
		Point p;
		int initiative;
		int master;
		int velocity;
		int damage;
		int protection;
		int num;
		int dead_num;
		int exp;
	public:
		Group();
		Group* clone();
		//Group(const Group&); //копирующий конструктор
		int harmGroup(int);
		int getvelocity(){ return velocity; }
		int getdamage(){ return damage; }
		int getprotect(){ return protection; }
		int getnum(){ return num; }
		int getdead_num(){ return dead_num; }
		int getexp() { return exp; }
		string getname() { return name; }
		Group & setvelocity(int );
		Group & setdamage(int);
		Group & setprotection(int p);
		Group & setnum(int);
		Group & setexp(int);
		void setcoord(Point p2){ p = p2; }
		virtual int gettype(){ return 0; }
	    void download(ifstream &);//загрузить экземпл€р группы
	};

}

#endif