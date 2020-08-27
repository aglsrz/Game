#include "Master.h"
#include <fstream>
using namespace std;
namespace Lab4{
	Master::Master(int init, string str, int mid, int curH, int maxH, int curEn,int maxEn, int coefA, int ex, map<const string, int> arr)
	{
		initiative = init;
		name = str;
		id = mid;
		maxHealth = maxH;
		setcurHealth(curH);
		maxEnerg = maxEn;
		setcurEner(curEn);
		coefAcc = coefA;
		exp = ex;
		school = arr;

	}
	void Master::copy(const Master&m)
	{
		initiative = m.initiative;
		name = m.name;
		id = m.id;
		maxHealth = m.maxHealth;
		curHealth = m.curHealth;
		maxEnerg = m.maxEnerg;
		curEnerg = m.curEnerg;
		coefAcc = m.coefAcc;
		exp = m.exp;
		school = m.school;
	}
	void Master::setcurHealth(int curH){
		if (curH > maxHealth)
			throw std::exception("Invalid current health.");
		curHealth = curH;
	}

	void Master::setcurEner(int curEn){
		if (curEn > maxEnerg)
			throw std::exception("Invalid current energy.");
		curEnerg = curEn;
	}

	Master & Master::receiveEner(){
		curEnerg += coefAcc;
		return *this;
	}
	bool Master::ImprSchool(string name){
		//school[name]++;
		map <const string, int>::iterator it = school.find(name);
		if (it == school.end())
			return false; // Школа не найдена
		++(it->second);
		return true;
	}
	Master & Master::receiveExp(){
		exp++;
		return *this;

	}
	Master & Master::harmMaster(int){
		curHealth--;
		return *this;
	}
	void Master::download(ifstream &f){
		
		string str;
		int i;
		f >> str;
		name = str;
		f >> i; id = i;
		f >> i;	initiative = i;
		f >> i;	maxHealth=i;
		f >> i; setcurHealth(i);
		f >> i;	maxEnerg = i;	
		f >> i;	setcurEner(i);
		f >> i;	coefAcc = i;
		f >> i;	exp= i;
		int N;//Количество школ в списке
		f >> N;
		for (int j = 0; j < N; ++j)
		{
			f >> str; f >> i;
			pair<const string, int> p (str, i);
		//	cout << p.first << " School" << endl;
			school.insert(p);
		}
	}
}