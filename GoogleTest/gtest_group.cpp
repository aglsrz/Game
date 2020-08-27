#include "..\Lab4\Group.h"
#include "gtest\gtest.h"
#include <iostream>
using namespace Lab4;
TEST(Test1, TestGroup){
	int a = 1;
	ASSERT_EQ(0,--a); //g.getinit(0)
}

TEST(ConstructorTest, TestGroup){
	Group g;
	ASSERT_EQ(0, g.getinit()); 
	ASSERT_EQ(0, g.getnum());
	ASSERT_EQ(0, g.getdead_num());
	ASSERT_EQ(0, g.getexp());
}

TEST(CloneTest, Groups)
{
	Group g(10, 15, 12, 5);
	Group pg;
	pg.copy(g);
	ASSERT_EQ(g.getinit(), pg.getinit());
	ASSERT_EQ(g.getnum(), pg.getnum());
	ASSERT_EQ(g.getdead_num(), pg.getdead_num());
	ASSERT_EQ(g.getexp(), pg.getexp());
}

TEST(SettersTest, Groups)
{
	Group g;
	int r;
	for (int i = 0; i < 10; ++i)
	{
		r = rand()%20 + 3;
		g.setvelocity(r);
		g.setdamage(r);
		g.setprotection(r);
		g.setnum(r);
		g.setexp(r);
		g.setmaster(r);
		ASSERT_EQ(r, g.getvelocity());
		ASSERT_EQ(r, g.getnum());
		ASSERT_EQ(r, g.getexp());
		ASSERT_EQ(r, g.getprotect());
		ASSERT_EQ(r, g.getdamage());
		ASSERT_EQ(r, g.getmast());
	}
}

TEST(TestException, Groups){
	Group g;
	int r;
	for (int i = 0; i < 10; ++i)
	{
		r = rand() % 9 - 10;
		ASSERT_THROW(g.setvelocity(r), std::exception);
		ASSERT_THROW(g.setnum(r), std::exception);
		ASSERT_THROW(g.setexp(r), std::exception);
		ASSERT_THROW(g.setprotection(r), std::exception);
	}
}
/*
ASSERT_NEAR((3789*pow((1-pow(654.0/3789,2.0/3)), 3.0/2)), a3.find_y(x3), err);
	ASSERT_THROW(a2.find_y(200), std::exception);
}*/
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}