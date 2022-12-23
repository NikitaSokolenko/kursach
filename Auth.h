/** @file Auth.h
 *  @author Соколенко Н.С.
 *  @version 1.0
 *  @date 18.12.2022
 *  @copyright ИБСТ ПГУ
 *  @brief Класс для аутентификации клиента на сервере 
 */

#pragma once
#include <map>
#include <string>
#include "ErrorTracker.h"

/**
@brief Класс для аутентификации клиента на сервере
*/
class Auth
{
private:
    
    std::string SALT; ///< Соль для вычисления хэша
    std::string Id; ///< Идентификатор клиента
    std::string password; ///< Пароль клиента
    std::string strHash; ///< Хэш в виде шестнадцатиричных цифр

public:

/** 
 @brief Конструктор для установки идентификатора и пароля клиента
 @param [in] ID, идентификатор клиента, std::string.
 @param [in] pass, пароль клиента, std::string.
*/

    Auth(std::string ID, std::string pass);

/** 
 @brief Генерация случайной соли для вычисления хэша
 @details Соль - 64-х разрядное число, представленное в виде строки
 из 16-ти шестнадцатиричных цифр
*/

    void GenSALT();
    char ERRmsg[3] = {'E', 'R','R'}; ///< Сообщение, отсылаемое клиенту при ошибке его обрабоки
    char OKmsg[2] = {'O', 'K'}; ///< Сообщение, отсылаемое клиенту при успешной авторизации

/** 
 @brief Сравнение хэша, присылаемого клиентом и хэша, вычисляемого внутри метода
 @details Вычисляет MD5 хэш от строки SALT+password и сравнивает его с
 хэшем, который присылает клиент
 @param [in] ClientHash, хэш клиента, std::string
 @return bool, если хэши совпадают - true, иначе false
 @throw std::server_error в случае несовпадения хэшей, штатная
 @code 
 type = invalid_argument, what ="Invalid hash"
 @endcode
*/

    bool CompareHashes(std::string ClientHash);
    std::string getSALT() ///< Возвращает соль
    {
        return SALT;
    }
    std::string getId() ///< Возвращает идентефикатор
    {
        return Id;
    }
    std::string getpass() ///< Возвращает пароль
    {
        return password;
    }
    std::string getstrHash() ///< Возвращает хэш
    {
        return strHash;
    }
};
