#pragma once
#include <vector>
#include <iostream>
class Counter
{
private:
int16_t result[1];
public:
    Counter(){};
    int16_t * mean(std::vector<int16_t> arr)
    {
    	for (std::vector<int16_t>::iterator it = arr.begin() ; it != arr.end(); ++it){
    	std::cout << ' ' << *it;}
  		std::cout << '\n';
        double avg = 0;
        for (uint32_t i = 0; i < arr.size(); i++) {
            avg += (arr[i] - avg) / (i + 1);
        }
        result[0] = avg;
        return result;
    }
};
