#include <UnitTest++/UnitTest++.h>
#include "Counter.h"
#include <iostream>
#include <string>

using namespace std;


SUITE(meanTest)
{
	TEST(Default) {
		std::vector<int16_t> arr ={10, 20 ,30 ,40, 50};
		CHECK_EQUAL(30,*( Counter().mean(arr)));
	}
	TEST(NotInteger) {
		std::vector<int16_t> arr ={20, 30 ,60};
		CHECK_EQUAL(36,*( Counter().mean(arr)));
	}
	TEST(Negative) {
		std::vector<int16_t> arr ={-10, -20 ,-30 ,-40, -50};
		CHECK_EQUAL(-30,*( Counter().mean(arr)));
	}
	TEST(MaximumPositive) {
		std::vector<int16_t> arr ={32767, 32767 ,32767};
		CHECK_EQUAL(32767,*( Counter().mean(arr)));
	}
	TEST(MaximumNegative) {
		std::vector<int16_t> arr ={-32768, -32768 ,-32768};
		CHECK_EQUAL(-32768,*( Counter().mean(arr)));
	}
	TEST(Different) {
		std::vector<int16_t> arr ={10, -20 ,30 ,-40};
		CHECK_EQUAL(-5,*( Counter().mean(arr)));
	}
	TEST(Owerflow) {
			std::vector<int16_t> arr ={};
		CHECK_THROW(Counter().mean(arr),server_error);
	}
}


int main()
{
	return UnitTest::RunAllTests();
}
