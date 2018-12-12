#include "..\Lab4\Group.h"
#include "..\Lab4\Arrows.h"
#include "..\Lab4\Level.h"
#include "..\Lab4\TempTab.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace Lab4;
int main()
{
	Level l;
	l.download();
	l.loadlevel();
	l.getfield();
	if (!l.save())
		cout << "Error";
	
	/*MyMap<string, int> tab;
	tab.insert("Magic", 1);
	try{
		Pair<string, int> p = tab.find("mMagic");
		cout << p.first;
	}
	catch (exception &ex){
		cout << ex.what() << endl;
	}
	try{
		Pair<string, int> p = tab.find("Magic");
		cout <<p.first <<p.second;
	}
	catch (exception &ex){
		cout << ex.what() << endl;
	}*/
	system("pause");
	return 0;
}