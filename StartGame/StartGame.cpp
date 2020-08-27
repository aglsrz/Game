#include "..\LabSource\Group.h"
#include "..\LabSource\Arrows.h"
#include "..\LabSource\Level.h"
#include "..\LabSource\TempTab.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace Lab4;

template <class T>
int input(T &a)
{
	std::cin >> a;
	if (!std::cin.good())
		do
		{
			if (std::cin.eof())
				return 0;
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cout << "Wrong value. Repeate, please!" << std::endl;
			std::cin >> a;
		} while ((!std::cin.good()));
		return 1;
}

int main()
{
	int n;
	bool c1 = true;
	Point p;
	Level l;
	l.download();
	l.loadlevel();
	l.sortMasters();
	l.output();

	do{
		for (int i = 0; i < 2; ++i)
		{
			bool c = true;
			cout << "Choose option for " << l.getmaster(i).getname() << endl;
			cout << "1. Receive Energy\n2. Call Group\n3. Improve School" << endl;
			if (!input(n)){
				c1 = false;
				break;
			}
			if (n == 1){
				l.receiveEn(i);
				cout << "Current Energy: " << l.getmaster(i).getcurEn() << endl;
			}
			if (n == 2)
			{
				string sch, sk;
				cout << "Choose available school for this master:" << endl;
				l.getmaster(i).getschools();
				cout << "-->  ";
				if (!input(sch)){
					c1 = false;
					break;
				}
				cout << "Choose skill:\n";
				c = l.getSkills(sch);
				if (!c)
					cout << "School not found" << endl;
				
				if (c){
					cout << "-->  ";
					if (!input(sk)){
						c1 = false;
						break;
					}
					c = l.call_group(i, sch, sk);
					if (c)
						cout << "Group calling succeeded." << endl;
					else
						cout << "Group calling failed." << endl;
				}
			}
			if (n == 3){
				string sch;
				cout << "Choose available school for this master:" << endl;
				l.getmaster(i).getschools();
				cout << "-->  ";
				if (!input(sch)){
					c1 = false;
					break;
				} 
				c = l.imprSch(i, sch);
				if (c)
					cout << "Knowledge of the school is improved" << endl;
				else cout << "Improving is failed." << endl;
			}
			if (!c){
				--i;
				cout << "Choose option again." << endl;
			}
		}
		l.sortgr();
		l.output();

		if (c1)
		for (int i = 0; i < l.getgrnum(); ++i)
		{
			cout << "Choose option for " << l.getgrname(i) << endl << "1. Move group to point\n2. Attack the group in the point" << endl;
			if (!input(n)){
				c1 = false;
				break;
			}
			if (n == 1){
				cout << "Enter new coordinates for the group:" << endl;
				if (!input(p.y)){
					c1 = false;
					break;
				}
				if (!input(p.x)){
					c1 = false;
					break;
				}
				if (l.moveGroup(l.getgrcoord(i), p))
					cout << "Move succeeded." << endl;
				else
					cout << "Move failed." << endl;
			}
			if (n == 2){
				cout << "Enter coordinates of the point to attack:" << endl;
				if (!input(p.y)){
					c1 = false;
					break;
				}
				if (!input(p.x)){
					c1 = false;
					break;
				}
				if (!l.attack(i, p))
					cout << "Attack failed." << endl;
				else cout << "Attack succeeded." << endl;
			}
			l.output();
		}
	} while ((l.checkMasters())&&(c1));

	int m;
	if (!l.checkMasters()){
		if (l.getmaster(0).getcurh() > 0)
			m = 0;
		else m = 1;
		cout << l.getmaster(m).getname() << " is the winner!" << endl;
	}
	cout<<"End of the game.\nGood bye!" << endl;
	if (!l.save())
		cout << "Error";
	system("pause");
	return 0;
}