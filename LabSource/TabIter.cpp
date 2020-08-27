#include "TabIter.h"
using namespace Lab4;
using namespace std;
/*
int operator !=(const TabIter &) const;
int operator ==(const TabIter &) const;
pair<const string, vector<Skill>> & operator *();
pair<const string, vector<Skill>> * operator ->();
TabIter & operator ++();
TabIter operator ++(int);
*/

int TabIter::operator !=(const TabIter &it) const
{
	return cur != it.cur;
}
int TabIter::operator ==(const TabIter &it) const
{
	return cur == it.cur;
}
const pair<const string, vector<Skill> > & TabIter::operator *()
{
	return *cur;
}
const pair<const string, vector<Skill> > * TabIter::operator ->()
{
	return &*cur;
}
TabIter & TabIter::operator ++()
{
	++cur;
	return *this;
}
TabIter TabIter::operator ++(int)
{
	TabIter res(*this);
	++cur;
	return res;
}

