#pragma once
#include <string>
#include <map>

using namespace std;

/**
@brief Класс для получения параметров коммандной строки
*/

class Opts
{
private:
    string DataBaseName = "DB.txt"; ///< Путь к файлу с базой данных
    string LogFileName = "log.txt"; ///< Путь к файлу для записи логов
    int Port = 33333; ///< Порт, на котором работает сервер
    void usage(const char* progName); ///<вывод подсказки и останов
public:
/** 
 @brief Конструктор, внутри которого считываются параметры командной строки
 @details Параметры  командной строки:
	1)-b Путь к файлу с базой данных, необязательный
	2)-l Путь к файлу для записи логов, необязательный
	3)-p Порт, на котором работает сервер, необязательный
	4)-h вызов подсказки
	При ошибках в параметрах вызывается справка и программа завершает работу
 @param [in] int argc
 @param [in] char **argv
*/

    Opts(int argc, char **argv);

/** 
 @brief Проверка роботоспособности файлов базы данных и лога
 @return bool, если нет ошибок в фалах - true, иначе false
 @throw std::invalid_argument в случае проблем с файлами, критическая 
 @code 
 type = invalid_argument, what ="Wrong DB File Name" или what ="Wrong Log File Name"
 @endcode
*/

	bool CheckFiles();
    string getDataBaseName() ///<Возвращает путь к файлу с базой данных 
    {
        return DataBaseName;
    }
    string getLogFileName() ///<Возвращает путь к файлу для записи логов
    {
        return LogFileName;
    }
    int getPort() ///<Порт, на котором работает сервер
    {
        return Port;
    }
};
