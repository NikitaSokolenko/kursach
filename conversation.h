#include "Auth.h"
#include "Counter.h"
#include "DataBase.h"
#include <iostream>
#include "WebManager.h"
#include "ErrorTracker.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

/** 
 @brief Функция взаимодействия сервера с клиентом
 @details Алгоритм взаимодействия с клиентом:
	1. клиент устанавливает соединение
	2. клиент передает свой идентификатор ID
	3а. сервер передает случайное число SALT16 (при успешной идентификации)
	3б. сервер передает строку "ERR" и разрывает соединение(при ошибке
	идентификации)
	4. клиент передает HASHMD5( SALT16 || PASSWORD)
	5а. сервер передает OK при успешной аутентификации
	5б. сервер передает строку "ERR" и разрывает соединение(при ошибке
	аутентификации)
	начиная с шага 6 обмен в двоичном формате
	6. клиент посылает количество векторов ;
	7. клиент посылает размер первого вектора;
	8. клиент посылает все значения первого вектора одним блоком данных;
	9. сервер возвращает результат вычислений по первому вектору;
	10. шаги 7-9 повторяются для всех векторов
	11. клиент завершает соединение
 @param [in] port, порт, unsigned int
 @param [in] LogName, путь к файлу для записи логов, std::string
 @param [in] new_db, база данных пользователей, DB
 @param [in] sock, сокет, int
 @throw std::server_error в случае ошибки, критическая
 @code 
 type = invalid_argument, what ="Count Error"
 @endcode
*/

void conversation(unsigned int port, std::string LogName, DB new_db, int sock)
{
	try{
	WebManager new_manager(port);
    char buf[2048];
    int bytes_read;
    bytes_read = new_manager.receiving(sock, &buf, 2048);
	std::string USRlogIn = string(buf, bytes_read);
    for (uint i = 0; i < USRlogIn.size();i++){
		if (USRlogIn[i] == '\n'){
			USRlogIn.pop_back();}
	}
    std::cout<<USRlogIn<< USRlogIn.size()<<std::endl;
    new_db.IDcheck(USRlogIn);
        Auth new_auth(USRlogIn, new_db.DataBaseP[USRlogIn]);
        new_auth.GenSALT();
        string str_salt = new_auth.getSALT();
        char salt_buf[16];
        strcpy(salt_buf, str_salt.c_str());
        new_manager.sending(sock, salt_buf, sizeof(salt_buf));
        bytes_read = new_manager.receiving(sock, &buf, 2048);
        string pass = string(buf, bytes_read);
		for (uint i = 0; i < pass.size();i++){
		if (pass[i] == '\n'){
			pass.pop_back();}
	}
        new_auth.CompareHashes(pass);
            new_manager.sending(sock, new_auth.OKmsg, sizeof(new_auth.OKmsg));
            uint32_t num_vectors;
            uint32_t vector_len;
            bytes_read = new_manager.receiving(sock, &num_vectors, sizeof num_vectors);
            for(unsigned int i =0; i< num_vectors; i++) {
                bytes_read = new_manager.receiving(sock, &vector_len, sizeof vector_len);
                int16_t int_buf[vector_len];
                bytes_read = new_manager.receiving(sock, &int_buf, vector_len*sizeof(int16_t));
                std::vector<int16_t> arr;
                for(unsigned int i =0; i< vector_len; i++) {
                    arr.push_back(int_buf[i]);
                }
                new_manager.sending(sock, Counter().mean(arr), sizeof(int16_t));
            }
            close(sock);
            std::cout<<"done\n";
            return;
    } catch (const server_error & e) {
		ErrorTracker new_ErrTr;
		new_ErrTr.setLogName(LogName);
		new_ErrTr.write_log(e.what(), e.getState());
		if (e.getState()){
			exit(1);
		}
		WebManager ERR_send_manager(port);
        ERR_send_manager.sending(sock, Auth("NO","NO").ERRmsg, sizeof(Auth("NO","NO").ERRmsg));
        close(sock);
        return;
    }
}
