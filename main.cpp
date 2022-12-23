#include "interface.h"
#include "Auth.h"
#include "Counter.h"
#include "DataBase.h"
#include <iostream>
#include "WebManager.h"
#include "conversation.h"
#include <vector>
#include <string>
#include <map>
#include "ErrorTracker.h"

ErrorTracker ErrTr;

/** 
 @brief Функция main
 @details Инициализация сервера в случае появления критической ошибки завершает работу
*/

int main(int argc, char **argv)
{
	try{
    Opts op(argc, argv);
    ErrTr.setLogName(op.getLogFileName());
    op.CheckFiles();
    DB new_db(op.getDataBaseName());
    WebManager main_manager(op.getPort());
    main_manager.new_bind();
    std::cout<<"robit"<<std::endl;
    main_manager.start_listening();
    while (true) {
        int sock = main_manager.accepting();
        std::cout<<"got_it"<<std::endl;
        conversation(op.getPort(), op.getLogFileName(), new_db, sock);
    	}
	} catch (const server_error & e) {
		ErrTr.write_log(e.what(), e.getState());
        if (e.getState()){
			exit(1);
		}
    }
    return 0;
}
