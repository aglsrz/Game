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
		Master & ImprSchool(string name);
		Master & receiveExp();
		Master &  harmMaster(int);
		void setcurHealth(int);
		void setcurEner(int);
		void download(ifstream &);
	};
}
#endif