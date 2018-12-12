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

	class Table{
	private:
		map <const string, vector<Skill> > arr;
	public:
		Table(){}
		~Table();
		//Table(const Table &);
		Table & add_school(const string &);
		Table & add_skill(const string ,const Skill &);
		Group getGroup(const string &, const string &) const;
		Table & changeGroup(const string &, const string &, const Group &);
		int getSchoolN() const;
		int getSkillsN(const string &) const;
		/*for otladka*/
		int getSkName(){
			map <const string, vector<Skill>> ::const_iterator p = arr.find("Magic");
			if (p == arr.end())
				throw std::exception("This school doesn't exist.");
			return (p->second)[0].coefQuant;
		}

		friend class TabIter;
		typedef TabIter Iter;
		Iter find(const string &)const;
		Iter begin() const;
		Iter end() const;
		//void download(ifstream &);
	};
}
#endif