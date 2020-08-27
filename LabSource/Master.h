#include <iostream>
#include <string>
#include <map>
#ifndef MASTER_H
#define MASTER_H
using namespace std;
namespace Lab4{
	class Master{
	private:
		string name;
		int id;
		int initiative;
		int curHealth;
		int maxHealth;
		int curEnerg;
		int maxEnerg;
		int coefAcc;
		int exp;
		map <const string, int> school;//список школ со знанием этой школы
	public:
		Master() : initiative(0), id(0), curHealth(0), maxHealth(0), curEnerg(0), maxEnerg(0), coefAcc(0), exp(0){}
		Master(int, string, int, int, int, int, int, int, int, map<const string, int>);
		Master & receiveEner();
		//уменьшение энергии
		void reduceEner(int n){
			curEnerg -= n;
			if (curEnerg < 0)
				curEnerg = 0;
		}
		void reduceH(int n){
			curHealth -= n;
		}
		void copy(const Master &);
		string getname(){ return name; }
		int getcurh(){ return curHealth; }
		int getinit(){ return initiative; }
		int getcurEn(){ return curEnerg; }
		bool ImprSchool(string name);
		Master & receiveExp();
		Master &  harmMaster(int);
		int getid(){ return id; }
		void setcurHealth(int);
		void setcurEner(int);
		void download(ifstream &);
		void imprExp(){ Master::exp += 5; }
		int getexp(){ return Master::exp; }
		void getschools(){
			map <const string, int>::iterator it = school.begin();
			for (it; it != school.end(); it++)
				cout << it->first << endl;
		}
		int getknowlevel(const string& str){
			map <const string, int>::const_iterator it = school.find(str);
			if (it == school.end())
				throw std::exception("This school doesn't exist in master's list.");
			return it->second;
		}
	};
}
#endif