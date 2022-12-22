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



int main(int argc, char **argv)
{
    Opts op(argc, argv);
    ErrorTracker ErrTr(op.getLogFileName());
    op.CheckFiles();
    DB new_db(op.getDataBaseName());
    WebManager new_manager(op.getPort());
    //ErrorTracker new_error_tracker(op.getLogFileName());
    new_manager.new_bind();
    //std::vector <thread> tr;
    std::cout<<"robit"<<std::endl;
    new_manager.start_listening();
    while (true) {
        int sock = new_manager.accepting();
        /*while (tr.size() > 9) {
            sleep(1);
        }*/
        std::cout<<"got_it"<<std::endl;
        /*tr.push_back(thread(conversation, new_manager, new_db, sock));
        for (std::vector<thread>::iterator it = tr.begin() ; it != tr.end(); ++it) {
            (*it).detach();

        }*/
        conversation(new_manager, new_db, sock);
    }
    return 0;
}
