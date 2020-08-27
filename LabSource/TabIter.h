#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Group.h"
#include "Skill.h"
#ifndef	TABITER_H
#define TABITER_H

using namespace std;
namespace Lab4{

	class TabIter{
	private:
		map < const string, vector< Skill > >::const_iterator cur;
	public:
		TabIter();
		TabIter(map < const string, vector<Skill> >::iterator it) :cur(it){}
		TabIter(map < const string, vector<Skill> >::const_iterator it) :cur(it){}
		int operator !=(const TabIter &) const;
		int operator ==(const TabIter &) const;
		const pair<const string, vector<Skill>> & operator *();
		const pair<const string, vector<Skill>> * operator ->();
		TabIter & operator ++();
		TabIter operator ++(int);
	};
}
#endif