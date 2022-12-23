#include "interface.h"
#include "Auth.h"
#include "Counter.h"
#include "DataBase.h"
#include <iostream>
#include "WebManager.h"
#include "conversation.h"
//#include <thread>
#include <vector>
#include <string>
#include <map>
#include "ErrorTracker.h"

ErrorTracker ErrTr;

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
		
        /*while (tr.size() > 9) {
            sleep(1);
        }*/
        std::cout<<"got_it"<<std::endl;
        /*tr.push_back(thread(conversation, new_manager, new_db, sock));
        for (std::vector<thread>::iterator it = tr.begin() ; it != tr.end(); ++it) {
            (*it).detach();

        }*/
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
