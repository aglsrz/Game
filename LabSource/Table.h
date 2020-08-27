#include <iostream>
#include <string>
#include <map>
#include "Group.h"
#include "TabIter.h"
#include <vector>
#ifndef	TABLE_H
#define TABLE_H


using namespace std;
namespace Lab4{

	/*
	*Класс, представляющий собой таблицу школ. 
	*Каждый элемент таблицы содержит название и список умений.
	*Каждое умение содержит название, описатель существа, минимальное знание школы для этого существа,
	*коэффициент численностиот знания школы и затрачивемую энергию.
	*Для удобства доступа к таблице определен класс-итератор.
	*/
	class Table{
	private:
		map <const string, vector<Skill> > arr;
	public:
		Table(){}
		~Table();
		/*
		*Метод, позволяющий добавить школу в твблицу.
		*/
		bool add_school(const string &);
		//Добавление умения в таблицу.
		bool add_skill(const string ,const Skill &);
		int get_knowlevel(const string &, const string &);
		int get_wasteEner(const string &, const string &);
		int get_coefQuant(const string &, const string &);
		int get_type(const string &, const string &);
		//Получить существо по названию школы и умения.
		Group getGroup(const string &, const string &) const;
		Table & changeGroup(const string &, const string &, const Group &);
		int getSchoolN() const;
		int getSkillsN(const string &) const;
		bool getSkillList(const string &);
		friend class TabIter;
		typedef TabIter Iter;
		Iter find(const string &)const;
		Iter begin() const;
		Iter end() const;
	};
}
#endif