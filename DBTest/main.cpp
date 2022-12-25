#include <UnitTest++/UnitTest++.h>
#include "DataBase.h"
#include <iostream>
#include <string>

using namespace std;


SUITE(costructorTest)
{
	TEST(Default) {
		CHECK_EQUAL(true, DB("DB.txt").IDcheck("user"));
	}
	TEST(wrongDB) {
		CHECK_THROW(DB("noDB.txt"),server_error);
	}
}

SUITE(methodTest)
{
	TEST(rightID) {
		CHECK_EQUAL(true, DB("DB.txt").IDcheck("pasha"));
	}
	TEST(wrongID) {
		CHECK_THROW(DB("DB.txt").IDcheck("hacker"),server_error);
	}
}


int main()
{
	return UnitTest::RunAllTests();
}
