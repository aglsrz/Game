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
	*�����, �������������� ����� ������� ����. 
	*������ ������� ������� �������� �������� � ������ ������.
	*������ ������ �������� ��������, ��������� ��������, ����������� ������ ����� ��� ����� ��������,
	*����������� ������������� ������ ����� � ������������ �������.
	*��� �������� ������� � ������� ��������� �����-��������.
	*/
	class Table{
	private:
		map <const string, vector<Skill> > arr;
	public:
		Table(){}
		~Table();
		/*
		*�����, ����������� �������� ����� � �������.
		*/
		bool add_school(const string &);
		//���������� ������ � �������.
		bool add_skill(const string ,const Skill &);
		int get_knowlevel(const string &, const string &);
		int get_wasteEner(const string &, const string &);
		int get_coefQuant(const string &, const string &);
		int get_type(const string &, const string &);
		//�������� �������� �� �������� ����� � ������.
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