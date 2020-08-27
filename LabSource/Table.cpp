#include "Table.h"
#include "Skill.h"
#include <fstream>
using namespace Lab4;
using namespace std;
/*
*комментарий 
*/
Table::~Table(){
	map <const string, vector<Skill>> ::iterator p;
	for (p = arr.begin(); p != arr.end(); ++p)
	{
		(p->second).clear();
	}
}

bool Table::add_school(const string &str){
	map <const string, vector<Skill>> ::iterator p=arr.find(str);
	if (p == arr.end()) { //школа не найдена
		pair<string, vector<Skill> > pnew;
		pnew.first = str;
		arr.insert(pnew);
		return true;
	}
	else
		//throw std::exception("This school already exists.");
	return false;
}
bool Table::add_skill(const string str, const Skill & s){
	map <const string, vector<Skill>> ::iterator p = arr.find(str);
	if (p == arr.end())
		//throw std::exception("This school doesn't exist.");
		return false;
	(p->second).push_back(s);
	return true;
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

int Table::get_knowlevel(const string & school, const string &skill){
	map <const string, vector<Skill>> ::const_iterator p = arr.find(school);
	if (p == arr.end())
		throw std::exception("This school doesn't exist.");
	vector <Skill> pvect = p->second;
	for (int i = 0; i < (int)(pvect.size()); i++)
		if (pvect[i].name == skill)
			return pvect[i].knowlevel;
	throw std::exception("Skill not found.");
}
int Table::get_wasteEner(const string & school, const string &skill){
	map <const string, vector<Skill>> ::const_iterator p = arr.find(school);
	if (p == arr.end())
		throw std::exception("This school doesn't exist.");
	vector <Skill> pvect = p->second;
	for (int i = 0; i < (int)(pvect.size()); i++)
		if (pvect[i].name == skill)
			return pvect[i].wasteEner;
	throw std::exception("Skill not found.");
}
int Table::get_coefQuant(const string & school, const string &skill){
	map <const string, vector<Skill>> ::const_iterator p = arr.find(school);
	if (p == arr.end())
		throw std::exception("This school doesn't exist.");
	vector <Skill> pvect = p->second;
	for (int i = 0; i < (int)(pvect.size()); i++)
		if (pvect[i].name == skill)
			return pvect[i].coefQuant;
	throw std::exception("Skill not found.");
}
int Table::get_type(const string &school, const string &skill){
	map <const string, vector<Skill>> ::const_iterator p = arr.find(school);
	if (p == arr.end())
		throw std::exception("This school doesn't exist.");
	vector <Skill> pvect = p->second;
	for (int i = 0; i < (int)(pvect.size()); i++)
		if (pvect[i].name == skill)
			return pvect[i].type;
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
bool Table::getSkillList(const string& school){
	map <const string, vector<Skill>> ::iterator p = arr.find(school);
	if (p == arr.end())
		return false;
		vector <Skill> vect = p->second;
		for (int i = 0; i < vect.size(); ++i)
			cout << vect[i].name << endl;
		return true;
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
