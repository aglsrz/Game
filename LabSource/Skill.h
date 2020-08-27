#include <string>

#include "Group.h"
#ifndef SKILL_H
#define SKILL_H

using namespace std;
namespace Lab4{
	struct Skill{
		string name;
		int knowlevel;
		int wasteEner;
		int coefQuant;
		int type;
		Group group; //��������� ��������
		Skill* clone(){
			Skill *snew= new Skill;
			(*snew).name = name;
			(*snew).knowlevel = knowlevel;
			(*snew).wasteEner = wasteEner;
			(*snew).coefQuant = coefQuant;
			(*snew).type = type;
			(*snew).group = group; //������ ��������� ���������� ����������� Group
			return snew;
		}
	};
}
#endif