#pragma once
#include <vector>
class Counter
{
public:
    Counter(){};
    int16_t* mean(std::vector<int16_t> arr)
    {
        double avg = 0;
        for (uint32_t i = 0; i < arr.size(); i++) {
            avg += (arr[i] - avg) / (i + 1);
        }
        int16_t avgn = avg;
        int16_t avgn_m[1] = {avgn};
        return avgn_m;
    }
};
