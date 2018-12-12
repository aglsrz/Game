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
};
//WALL=-1;
//FALL=-2;
//LAND=0;

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
	/*Для отладки*/
	void getfield();
	int getgrnum(){ return groups.size(); }
	Table & getTab(){ return schools; }


};
}