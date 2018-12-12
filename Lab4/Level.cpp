#include "Level.h"
#include "Group.h"
#include "Master.h"
#include "Soldiers.h"
#include "Table.h"
#include "Universal.h"
#include "Arrows.h"
#include <fstream>
// включать фaйлы которые уже есть внутри других??
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
	//устанoвить размер массива, тогда все поля обнуляться - ?
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
	matr[p1.x][p1.y] = d;
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < SZ.y; ++y)
		for (x = 0; x < SZ.x; ++x)
		if (matr[y][x] == d)         // ячейка (x, y) помечена числом d
		{
			for (k = 0; k < 4; ++k)    // проходим по всем непомеченным соседям
			{
				int iy = y + dy[k], ix = x + dx[k];
				if ((iy >= 0) && (iy < SZ.y) && (ix >= 0) && (ix < SZ.x) && (matr[iy][ix] == 0))
				{
					stop = false;              // найдены непомеченные клетки
					matr[iy][ix] = d + 1;     
				}
			}
		}
		d++;
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

/*
атака:
группа.атака(точка)
передать точку и атакующую группу
если фаератак то проверить есть ли стена на пути (line of sight алгоритм)
*/

/* Line of sight code         *
* this is a Boolean function *
* that returns FALSE if the  *
* monster cannot see the     *
* player and TRUE if it can  *
*                            *
* It has the monsters x and y*
* coords as parameters       */
bool Level::los(Point p1, Point p2)//(coord monster_x, coord monster_y)
{
	int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

	/* Delta x is the players x minus the monsters x    *
	* d is my dungeon structure and px is the players  *
	* x position. monster_x is the monsters x position passed *
	* to the function.                                 */
	delta_x = p1.x-p2.x; //=d.px - monster_x;
	/* delta_y is the same as delta_x using the y coordinates */
	delta_y = p1.y - p2.y; //d.py - monster_y;

	/* abs_delta_x & abs_delta_y: these are the absolute values of delta_x & delta_y */
	abs_delta_x = abs(delta_x);
	abs_delta_y = abs(delta_y);

	/* sign_x & sign_y: these are the signs of delta_x & delta_y */
	sign_x = sgn(delta_x);
	sign_y = sgn(delta_y);

	/* x & y: these are the monster's x & y coords */
	x = p2.x;//вообще вроде не надо, но =monster_x;
	y = p2.y;// = monster_y;

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
	возвращается тру или фолс

	*/
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
	Group *g;
	fin.open("Group.txt"); // открыли файл для чтения отрядов
	fin >> n;//считали количество отрядов
	for (int i = 0; i < n; ++i)
	{
		fin >> t;//считали тип отряда
		if (t == 1)
		{
			g = new Soldiers;
			g->download(fin);
			Soldiers* arr = dynamic_cast<Soldiers*>(g);
			groups.push_back(arr);//записали отряд в вектор
		}
		if (t == 2){
			g = new Arrows;
			g->download(fin);
			Arrows* arr = dynamic_cast<Arrows*>(g);
			arr->loadrad(fin);
			groups.push_back(arr);//записали отряд в вектор
		}
		if (t==3)
		{ 
			g = new Universal;
			g->download(fin);
			Universal* arr = dynamic_cast<Universal*>(g);
			arr->loadrad(fin);
			groups.push_back(arr);//записали отряд в вектор
		}

			
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
	int a, b;
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
				p.x = j; p.y = i;
				field[i][j].busy = groups[k];
				groups[k]->setcoord(p);
				break;
			}
	}
	fin.close();
}
 
bool Level::save(){
	ofstream f("Save1.txt", ios_base::out | ios_base::trunc);
	//cout<<field[0][4].busy->getname() << endl;
	if (!f.is_open()) // если файл небыл открыт
		return false;
	f << SZ.y << endl << SZ.x << endl;
	for (int i = 0; i < SZ.y; ++i)
	for (int j = 0; j < SZ.x; ++j){
		f << field[i][j].type << endl;
		if (field[i][j].busy!=nullptr)
			f<< field[i][j].busy->getname() << endl;
		else 
			f << "null" << endl;
	}
	f.close();
	return true;
}

void Level::getfield(){
	for (int i = 0; i < SZ.y; ++i){
		for (int j = 0; j < SZ.x; ++j)
		if (field[i][j].busy != nullptr)
			cout << field[i][j].busy->getname() << endl  << field[i][j].busy->getdamage() << endl;
		else
			cout << "null" << endl;
		cout << endl;
	}
}