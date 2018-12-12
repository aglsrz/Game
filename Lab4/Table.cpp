#include "Table.h"
#include "Skill.h"
#include <fstream>
using namespace Lab4;
using namespace std;

Table::~Table(){
	map <const string, vector<Skill>> ::iterator p;
	for (p = arr.begin(); p != arr.end(); ++p)
	{
		(p->second).clear();
	}
}

Table & Table::add_school(const string &str){
	map <const string, vector<Skill>> ::iterator p=arr.find(str);
	if (p == arr.end()) { //школа не найдена
		pair<string, vector<Skill> > pnew;
		pnew.first = str;
		arr.insert(pnew);
	}
	else
		throw std::exception("This school already exists.");
	return *this;
}
Table & Table::add_skill(const string str, const Skill & s){
	map <const string, vector<Skill>> ::iterator p = arr.find(str);
	if (p == arr.end()) 
		throw std::exception("This school doesn't exist.");
	(p->second).push_back(s);
	return *this;
}

Group Table::getGroup(const string & school, const string & skill) const{
	map <const string, vector<Skill>> ::const_iterator p = arr.find(school);
	if (p == arr.end())
		throw std::exception("This school doesn't exist.");
	vector <Skill> pvect = p->second;
	for (int i = 0; i < (int)(pvect.size()); i++)
		if (pvect[i].name == skill)
			return pvect[i].group;
	throw std::exception("Skill not found.");
	}


Table & Table::changeGroup(const string & school, const string &skill, const Group &gr)
{
	map <const string, vector<Skill>> ::iterator p = arr.find(school);
	if (p == arr.end())
		throw std::exception("This school doesn't exist.");
	vector <Skill> pvect = p->second;
	for (int i = 0; i < pvect.size(); i++)
	if (pvect.at(i).name == skill)
		pvect.at(i).group = gr;
	throw std::exception("Skill not found.");
	return *this;
}
int Table::getSchoolN() const{
	return arr.size();
}
int Table::getSkillsN(const string & school) const{
		map <const string, vector<Skill>> ::const_iterator p = arr.find(school);
		if (p == arr.end())
			throw std::exception("This school doesn't exist.");
		return (p->second).size();
}
Table::Iter Table::find(const string &s) const
{
	map<const string, vector<Skill> >::const_iterator p = arr.find(s);
	return TabIter(p);
}

Table::Iter Table::begin() const
{
	return TabIter(arr.begin());
}
Table::Iter Table::end() const
{
	return TabIter(arr.end());
}
/*void Table::download(ifstream &f)
{

	string str;
	int i;
	int N;  // оличество школ в таблице
	f >> N;
	for (int j = 0; j < N; ++j)
	{
		f >> str;
		add_school(str);
		f >> str; 

		//pair<const string, int> p(str, i);
		//school.insert(p);
	}
}*/

