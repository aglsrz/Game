#include "Level.h"
#include "Group.h"
#include "Master.h"
#include "Soldiers.h"
#include "Table.h"
#include "Universal.h"
#include "Arrows.h"
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace Lab4;
using namespace std;
int sgn(int val)
{
	return (val>0) ? (1) : ((val<0) ? (-1) : (0));
}


Level::Level() : schools(), field(nullptr)
{
	SZ = { 0, 0 };
}


Level::~Level()
{
	for (int i = 0; i < SZ.y; i++)
		delete[] field[i];
	delete[] field;
	
}


Point Level::getSize() const{
	return SZ;
}
Level& Level::setSize(int n, int m)
{
	SZ.y = n;
	SZ.x = m;
	field = new Cell *[n];
	for (int i = 0; i < n; i++)
		field[i] = new Cell[m];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			field[i][j] = { 0, nullptr };
	return *this;

}
int  Level::getCellType(Point p) const{
	if ((p.x > SZ.x) || (p.y > SZ.y))
		throw std::exception("Invalid coordinates.");
	return field[p.y][p.x].type;
}

Level &  Level::setCellType(Point p, int t)
{
	if ((p.x > SZ.x) || (p.y > SZ.y))
		throw std::exception("Invalid coordinates.");
	if ((t<0) || (t>2))
		throw std::exception("Invalid type");
	field[p.y][p.x].type = t;
	return *this;
}

bool  Level::setGroup(Point p, Group * gr)//установить группу в точку (не переместить)
{
	if ((field[p.y][p.x].type != 0) || (field[p.y][p.x].busy != nullptr))
		return false;
	gr->setcoord(p); //изменение координат в классе группы
	field[p.y][p.x].busy = gr;
	return true;
}
bool Level::moveGroup(Point p1, Point p2){
	int d = 0;
	bool stop;
	int dx[4] = { 1, 0, -1, 0 };   // смещения, соответствующие соседям ячейки
	int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
	int x, y, k;
	if ((field[p1.y][p1.x].type != 0) || (field[p2.y][p2.x].type != 0))
		return false;
	if ((field[p1.y][p1.x].busy == nullptr) || (field[p2.y][p2.x].busy != nullptr))
		return false;
	int **matr = new int *[SZ.y];
	for (int i = 0; i <SZ.y; i++)
		matr[i] = new int[SZ.x];
	for (int i = 0; i < SZ.y; ++i)
	for (int j = 0; j < SZ.x; ++j)
		matr[i][j] =field[i][j].type;
	matr[p1.y][p1.x] = d;
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < SZ.y; ++y)
		for (x = 0; x < SZ.x; ++x)
		if (matr[y][x] == d)         // ячейка (x, y) помечена числом d
		{
			for (k = 0; k < 4; ++k)    // проходим по всем непомеченным соседям
			{
				int iy = y + dy[k], ix = x + dx[k];
				if ((iy >= 0) && (iy < SZ.y) && (ix >= 0) && (ix < SZ.x) && (matr[iy][ix] == 0) 
					&& ((field[iy][ix].busy == nullptr)) && ((field[iy][ix].type==0)))
				{
					stop = false;              // найдены непомеченные клетки
					matr[iy][ix] = d + 1;     
				}
			}
		}
		++d;
	} while ((!stop) && (matr[p2.y][p2.x] == 0));
	int len = matr[p2.y][p2.x];
	d = matr[p2.y][p2.x];
	for (int i = 0; i < SZ.y; i++)
		delete[] matr[i];
		delete[] matr;
	if (d == 0)  // путь не найден
		return false;
	if (field[p1.y][p1.x].busy->getvelocity() < len) // сравнение скорости отряда и длины кратчайшего пути
		return false;
	field[p1.y][p1.x].busy->setcoord(p2); //изменение координат в классе группы
	field[p2.y][p2.x].busy = field[p1.y][p1.x].busy;
	field[p1.y][p1.x].busy = nullptr;
	return true;	
}
bool Level::empty_field()
{
	for (int i = 0; i < SZ.y; ++i)
		for (int j = 0; j < SZ.x; ++j)
			if (field[i][j].empty_cell())
				return true;
	return false;
}

bool Level::los(Point p1, Point p2)
	int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

	delta_x = p1.x-p2.x;
	/* delta_y is the same as delta_x using the y coordinates */
	delta_y = p1.y - p2.y;

	/* abs_delta_x & abs_delta_y: these are the absolute values of delta_x & delta_y */
	abs_delta_x = abs(delta_x);
	abs_delta_y = abs(delta_y);

	/* sign_x & sign_y: these are the signs of delta_x & delta_y */
	sign_x = sgn(delta_x);
	sign_y = sgn(delta_y);

	x = p2.x;
	y = p2.y;

	/* The following if statement checks to see if the line *
	* is x dominate or y dominate and loops accordingly    */
	if (abs_delta_x > abs_delta_y)
	{
		/* X dominate loop */
		/* t = twice the absolute of y minus the absolute of x*/
		t = abs_delta_y * 2 - abs_delta_x;
		do
		{
			if (t >= 0)
			{
				/* if t is greater than or equal to zero then *
				* add the sign of delta_y to y                    *
				* subtract twice the absolute of delta_x from t   */
				y += sign_y;
				t -= abs_delta_x * 2;
			}

			/* add the sign of delta_x to x      *
			* add twice the adsolute of delta_y to t  */
			x += sign_x;
			t += abs_delta_y * 2;

			/* check to see if we are at the player's position */
			if (x==p1.x && y==p1.y)//x == d.px && y == d.py
		 {
			 /* return that the monster can see the player */
			 return true;
		 }
			/* keep looping until the monster's sight is blocked *
			* by an object at the updated x,y coord             */
		} while (field[y][x].type!=-1);//sight_blocked(x, y) == FALSEуточнить стену

		/* NOTE: sight_blocked is a function that returns true      *
		* if an object at the x,y coord. would block the monster's *
		* sight                                                    */

		/* the loop was exited because the monster's sight was blocked *
		* return FALSE: the monster cannot see the player             */
		return false;
	}
	else
	{
		/* Y dominate loop, this loop is basically the same as the x loop */
		t = abs_delta_x * 2 - abs_delta_y;
		do
		{
			if (t >= 0)
			{
				x += sign_x;
				t -= abs_delta_y * 2;
			}
			y += sign_y;
			t += abs_delta_x * 2;
			if (x == p1.x && y == p1.y)
			{
				return true;
			}
		} while (field[y][x].type != -1);
		return false;
	}
	/*
	bool атака(точка точка)
	найти отряд в этой точке, проверить есть ли в другой точке отряд
	по типу взять нужный тип
	сделать фаератак либо обычную
	если юниверсал то вернуть циферку при которой перейду к отдельной функции атаки для юниверсалов
	если фаератака то вызвать лос алгоритм для двух точек, потом саму фаератаку
	взять группу которая находится в этой клетке, harmGr
	возвращается true или false
	*/
}

void Level::sortgr(){
	Group *g;
	for (int i = 1; i < groups.size(); ++i)
	{
		for (int r = 0; r < groups.size() - i; r++)
		{
			if (groups[r]->getinit() <groups[r+1]->getinit())
			{
				g = groups[r]->clone();
				groups[r] = groups[r+1];
				groups[r + 1] = g;
			}
		}
	}
}
void Level::sortMasters(){
	if (masters[0].getinit() < masters[1].getinit())
	{
		Master m;
		m.copy( masters[0]);
		masters[0].copy(masters[1]);
		masters[1].copy(m);
	}
}
bool Level::attack(int &i, Point p)//индекс атакующей группы, атакуемая точка
{
	int d, t=0;
	Group *gr = groups[i];

	if ((gr->getcoord().x == p.x) && (gr->getcoord().y == p.y)){
		cout << "Coordinates error.\n";
		return false;
	}
	if (field[p.y][p.x].busy == nullptr)
	{
		cout << "BUSY ERROR" << endl;
		return false;
	}
	if (gr->getmast() == field[p.y][p.x].busy->getmast()){
		cout << "Groups have the same master" << endl;
		return false;
	}
	if (gr->gettype() == 3)
	{
		cout << "1.Near Attack \n2.Fire Attack" << endl;
		cin >> t;
		if (!std::cin.good()){
			std::cin.clear();
			std::cin.ignore(80, '\n');
			return false;
		}
	}
	if ((gr->gettype() == 1) || (t==1))
	{
		Soldiers* s = dynamic_cast<Soldiers*>(gr);
		d=s->nearAttack(p);
		if (d == 0){
			cout << "d==0\n";
			return false;
		}
		if (field[p.y][p.x].busy->harmGroup(d)) //если группа уничтожена
		{
			for (int j = 0; j < groups.size(); ++j)
				if (groups[j] == field[p.y][p.x].busy){
					int m = groups[j]->getmast();
					masters[1 - m].imprExp();
					masters[m].reduceH(masters[1 - m].getexp());
					groups.erase(groups.begin() + j);
					cout << "GROUP DESTROYED" <<endl;
					if (j < i)
						--i;
					field[p.y][p.x].busy = nullptr;
					break;
				}

		}
		return true;
	}
	if ((gr->gettype() == 2) || (t == 2)){
		Arrows* ar = dynamic_cast<Arrows*>(gr);
		d = ar->fireAttack(p);
		if ((d == 0) || (!los(ar->getcoord(), p)))
		{
			cout << "d==0 fire attak" << endl;
			return false;
		}
			
		if (field[p.y][p.x].busy->harmGroup(d))
		{
			for (int j = 0; j < groups.size(); ++j)
				if ((groups[j]->getcoord().x == field[p.y][p.x].busy->getcoord().x) && (groups[j]->getcoord().y == field[p.y][p.x].busy->getcoord().y)){
					int m = groups[j]->getmast();
					masters[1 - m].imprExp();
					masters[m].reduceH(masters[1 - m].getexp());
					groups.erase(groups.begin() + j);
				cout << "GROUP DELETED" << endl;
				if (j < i)
					--i;
				field[p.y][p.x].busy = nullptr;
				break;

			}
		}
		return true;
	}
	}

bool Level::call_group(int i, const string& school, const string& skill){ //i - индекс призывателя
	if (!empty_field()) //проверка на наличие свободных клеток
		return false;	
	if (masters[i].getcurEn() < schools.get_wasteEner(school, skill))
	{
		cout << "Master doesn't have enough energy for this skill\n";
		return false;
	}
	//проверка на достаточность уровня знания школы
	int kn = masters[i].getknowlevel(school); //уровень знания данной школы призывателем
	if (kn < schools.get_knowlevel(school, skill))
	{
		cout << "Master doesn't have knowlege level for this skill\n";
		return false;
	}
	Group gr=schools.getGroup(school, skill);
	
	int N; //количество существ в отряде
	N = kn*schools.get_coefQuant(school, skill);

	masters[i].reduceEner(schools.get_wasteEner(school, skill)); 
	gr.setnum(N);
	gr.setmaster(i);//masters[i].getid()
	int t = schools.get_type(school, skill);
	//поместить в первую свободную клетку
	Point p;
	Group *pg=nullptr;
	if (t == 1)
		pg = new Soldiers;
	if (t == 2){
		pg = new Arrows;
	}
	if (t == 3){
		pg = new Universal;
		//
	}
	pg->copy(gr);
	for (int i = 0; i < SZ.y; ++i)
		for (int j = 0; j < SZ.x; ++j)
			if (field[i][j].empty_cell())
			{
				//pg = gr.clone();
				p.y = i; p.x = j;
				setGroup(p, pg );
				groups.push_back(pg);
				return true;
			}
	return false;
}

Group* Level::createGroup(int t, ifstream& fin){
	Group *g;// = nullptr;
	if (t == 1)
	{
		g = new Soldiers;
		g->download(fin);
		Soldiers* arr = dynamic_cast<Soldiers*>(g);
		return arr;
	}
	if (t == 2){
		g = new Arrows;
		g->download(fin);
		Arrows* arr = dynamic_cast<Arrows*>(g);
		arr->loadrad(fin);
		return arr;
	}
	if (t == 3)
	{
		g = new Universal;
		g->download(fin);
		Universal* arr = dynamic_cast<Universal*>(g);
		arr->loadrad(fin);
		return arr;
	}
	return nullptr;
}

void Level::download()
{
	int n, t;
	string str; 
	/*загрузка мастеров призыва*/
	ifstream fin("Master.txt");
	for (int i = 0; i < 2; ++i)
		masters[i].download(fin);
	fin.close();
	/*загрузка отрядов*/
	fin.open("Group.txt"); // открыли файл для чтения отрядов
	fin >> n;//считали количество отрядов
	for (int i = 0; i < n; ++i)
	{
		fin >> t;//считали тип отряда
		groups.push_back(createGroup(t, fin));
	}
	fin.close(); // закрываем файл
	/*Загрузка таблицы школ*/
	fin.open("Table.txt");
	Skill sk;
	Group gr;
	string str1;
	fin >> n;
	for (int j = 0; j < n; ++j)
	{
		int a, b;
		fin >> str;
		schools.add_school(str);
		fin >> str1 >> t >> a >> b;
		sk.name = str1;
		sk.knowlevel = t;
		sk.wasteEner = a;
		sk.coefQuant = b;
		fin >> t; //тип группы
		sk.type = t;
		gr.download(fin);
		/*копирующий конструктор для групп*/
		sk.group = *(gr.clone());
		/*Skill.clone() возвращает копию с новым адресом*/
		schools.add_skill(str, *(sk.clone()));
			
	}
	fin.close();
	system("pause");
}
/*
*загрузка размера поля 
*самого поля
*координат и численности групп
*/
void Level::loadlevel()
{
	ifstream fin("Save.txt");
	string str;
	Point p;
	int a, b, N;
	fin >>a>>b ;
	setSize(a, b);
	for (int i = 0; i < SZ.y; ++i)
	for (int j = 0; j < SZ.x; ++j){
		fin >> a;
		field[i][j].type = a;
		fin >>str; //считываем имя отряда, ищем в списке отрядов, записываем указатель
		
		if (str != "null")
			for (int k = 0; k < groups.size(); ++k)
			if (groups[k]->getname() == str)
			{
				fin >> N;
				p.x = j; p.y = i;
				groups[k]->setcoord(p);
				groups[k]->setnum(N);
				field[i][j].busy = groups[k];
				break;
			}
	}
	fin.close();
}
 
bool Level::save(){
	ofstream f("Save1.txt", ios_base::out | ios_base::trunc);
	if (!f.is_open()) // если файл не был открыт
		return false;
	f << SZ.y << endl << SZ.x << endl;
	for (int i = 0; i < SZ.y; ++i)
	for (int j = 0; j < SZ.x; ++j){
		f << field[i][j].type << endl;
		if (field[i][j].busy != nullptr){
			f << field[i][j].busy->getname() << endl;
			f << field[i][j].busy->getnum() << endl;
		}
		else 
			f << "null" << endl;
	}
	f.close();
	return true;
}

void Level::output(){
	char mas[3] = { '^', '#', '_' }; // fall, wall, land
	char c;
	string s, s1;
	cout << endl;
	for (int i = 0; i < 80; ++i)
		cout << "_";
	cout << endl;
	cout << "First master " << masters[0].getname() << " (" << masters[0].getcurh() << ")" << endl;
	cout << "Second master " << masters[1].getname() << " (" << masters[1].getcurh() << ")" << endl<<endl;
	for (int i = 0; i < SZ.y; ++i){
		for (int j = 0; j < SZ.x; ++j)
			if (field[i][j].busy == nullptr)
				cout << setw(6) << mas[field[i][j].type + 2];
			else{
				c = (field[i][j].busy->getname())[0];
				if (field[i][j].busy->getmast() == 0)
					c = tolower(c);
				s1 = to_string(field[i][j].busy->getnum());
				s += c; s += "("; s += s1;  s += ")";
				cout << setw(6) << s;
				s.erase();
			}
			cout << endl;
	}
	}
bool Level::checkMasters(){ //Проверка, не кончилось ли здоровье у одного из мастеров
	for (int i = 0; i < 2; ++i)
		if (masters[i].getcurh()<=0)
			return false;
	return true;
}
bool Level::imprSch(int i, const string &school){
	return masters[i].ImprSchool(school);
}
