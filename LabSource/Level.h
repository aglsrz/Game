#include <iostream>
#include <string>
#include <map>
#include "Group.h"
#include "Master.h"
#include "Table.h"

using namespace std;
namespace Lab4{
struct Cell{
	int type;
	Group *busy;
	bool empty_cell(){ //проверка пустоты клетки
		if ((type == 0) && (busy == nullptr))
			return true;
		else return false;
	}
};
/* WALL=-1;
FALL=-2;
LAND=0; */

class Level{
private:
	Point SZ;
	Cell **field;
	Table schools;
	vector<Group *> groups;
	Master masters[2];
public:
	Level();
	~Level();
	Point getSize() const;
	Level& setSize(int, int);
	int getCellType(Point) const;
	Level & setCellType(Point, int);
	bool moveGroup(Point , Point);
	bool setGroup(Point , Group *);
	bool los(Point, Point);
	void download();
	void loadlevel();
	bool save();
	bool attack(int& , Point);
	Point getgrcoord(int i) { return groups[i]->getcoord(); }//получить координаты i-ой группы в векторе 
	bool call_group(int , const string& , const string&);
	bool imprSch(int , const string &); //Улучшить школу мастера с данным индексом, название школы
	void receiveEn(int i) { masters[i].receiveEner(); }//Получение энергии
	void output();
	bool checkMasters();
	bool getSkills(const string& s){ return schools.getSkillList(s); }
	void sortMasters();
	Master getmaster(int i) { return masters[i]; }
	string getgrname(int i){ return groups[i]->getname(); }
	int getgrnum(){ return groups.size(); }
	Table & getTab(){ return schools; }
	bool empty_field(); //проверка, есть ли пустые ячейки поля (земля, нет отрядов)
	Group* createGroup(int, ifstream&);
	void sortgr();


};
}