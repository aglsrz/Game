#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace Lab4{

	template <class T, class P>
	struct Pair{
		T first;
		P second;
	};

	template <class T, class P>
	class MyMap
	{
	private:
		vector < Pair<T, P> > arr;

	public:
		Pair<T, P> find(const T &) const;
		bool insert(const T &, const P &inf);
		int size() const{ return arr.size(); }
	};

	template <class T, class P>
	Pair<T, P> MyMap<T, P>::find(const T &key) const{
		for (int i = 0; i < arr.size(); ++i)
			if (arr[i].first == key)
				return arr[i];
		throw exception("This key doesn't exist.");
	}

	template <class T, class P>
	bool MyMap<T, P>::insert(const T &key, const P &inf){
		try{
			find(key);
			return false;
		}
		catch (exception &ex){
			Pair<T, P> p = { key, inf };
			arr.push_back(p);
			return true;
		}
	}

	class TempTab{
	private:
		MyMap <const string, vector<Skill> > arr;
	public:
		TempTab(){}
		~TempTab();
		bool add_school(const string &);
		bool add_skill(const string, const Skill &);
		Group getGroup(const string &, const string &) const;
		void changeGroup(const string &, const string &, const Group &);
		int getSchoolN() const { return arr.size(); }
	
	};

	bool TempTab::add_school(const string &str){
		vector<Skill> vect;
		return arr.insert(str, vect);
	}

	bool TempTab::add_skill(const string str, const Skill &skill){
		try{
			Pair <const string, vector<Skill> > p=arr.find(str);
			p.second.push_back(skill);
			return true;
		}
		catch (exception &ex) {
			return false;
		}
	}

	Group TempTab::getGroup(const string &school, const string &skill) const{
		try{
			Pair <const string, vector<Skill> > p = arr.find(school);
			vector <Skill> pvect = p.second;
			for (int i = 0; i < (int)(pvect.size()); i++)
			if (pvect[i].name == skill)
				return pvect[i].group;
		}
		catch (exception &ex) {
			throw std::exception("Skill not found.");
		}
		throw std::exception("Skill not found.");
	}
	void TempTab::changeGroup(const string &school, const string &skill, const Group &gr){
		try{
			Pair <const string, vector<Skill> > p = arr.find(school);
			vector <Skill> pvect = p.second;
			for (int i = 0; i < (int)(pvect.size()); i++)
			if (pvect[i].name == skill)
				pvect[i].group = gr;
		}
		catch (exception &ex) {
			throw std::exception("Skill not found.");
		}
		throw std::exception("Skill not found.");
	}
}


