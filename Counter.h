#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include "ErrorTracker.h"

/**
@brief Класс для вычислений по вектору
*/

class Counter
{
private:
int16_t result[1]; ///< Результат вычислений
public:
    Counter(){}; ///<Конструктор без параметров

/** 
 @brief Вычисляет среднее арифметическое по вектору
 @param [in] arr, вектор, std::vector<int16_t>
 @return указатель на массив с результатом, int16_t *
 @throw std::server_error в случае ошибки, критическая
 @code 
 type = invalid_argument, what ="Count Error"
 @endcode
*/

    int16_t * mean(std::vector<int16_t> arr)
    {
		try{
    	for (std::vector<int16_t>::iterator it = arr.begin() ; it != arr.end(); ++it){
    	std::cout << ' ' << *it;}
  		std::cout << '\n';
        double avg = 0;
        for (uint32_t i = 0; i < arr.size(); i++) {
            avg += (arr[i] - avg) / (i + 1);
        }
        result[0] = avg;
		}catch(std::exception &e){
			throw server_error(std::string("Count Error"), true);
			}									
        return result;
    }
};
