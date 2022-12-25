#pragma once

#include <exception>
#include <ctime>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

/**
@brief Класс для обработки ошибок
*/

class ErrorTracker
{
private:
    std::string LogFileName; ///< Путь к файлу с логом ошибок
public:
	ErrorTracker(){}; ///< Конструктор без параметров
    void setLogName(std::string LogName); ///<Функция, устанавливающая путь к файлу с логом ошибок

/** 
 @brief Запись ошибки в лог
 @details Записывает время, тип и критичность ошибки
 @param [in] what, тип ошибки, std::string
 @param [in] Critical, критичность ошибки (Критическая - true, Штатная - false), std::string
*/

    void write_log(std::string what, bool Critical);
	~ErrorTracker(){}; ///< Деструктор
};

/**
@brief Класс ошибок
@details Наследует от класса std::invalid_argument
*/

class server_error: public std::invalid_argument {
private:
bool State = false; ///<Статус критичности ошибки
public:

/**
 @brief Конструктор ошибок с строкой в качестве параметра
 @param [in] what_arg, тип ошибки, const std::string.
 @param [in] critical, критическа ошибка - true, штатная - false, bool
*/

explicit server_error (const std::string& what_arg, bool critical = false):
std::invalid_argument(what_arg) {State = critical;}

/**
 @brief Конструктор ошибок с си-строкой в качестве параметра
 @param [in] what_arg, тип ошибки, const char*.
 @param [in] critical, критическа ошибка - true, штатная - false, bool
*/

explicit server_error (const char* what_arg,  bool critical = false):
std::invalid_argument(what_arg) {State = critical;}
bool getState() const {return State;} ///<Возвращает статус критичности ошибки
};
