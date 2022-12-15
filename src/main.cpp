#include <interface.h>
#include <Auth.h>
#include <Counter.h>
#include <DataBase.h>
#include <iostream>
#include <WebManager.h>
#include <thread>
#include <vector>
#include <string>

using namespace std;

void conversation(WebManager new_manager, DB new_db, int sock)
{
    char buf[1024];
    int bytes_read;
    bytes_read = new_manager.receiving(sock, buf);
    string login = string(buf);
    login.pop_back();
    if (new_db.IDcheck(login)) {
        Auth new_auth(login, new_db.DataBaseP[login]);
        new_auth.GenSALT();
        string str_salt = new_auth.getSALT();
        char salt_buf[16];
        std::cout<<str_salt<<std::endl;
        str_salt.pop_back();
        strcpy(salt_buf, str_salt.c_str());
        new_manager.sending(sock, salt_buf, sizeof(salt_buf));
        bytes_read = new_manager.receiving(sock, buf);
        string pass = string(buf);
        pass.pop_back();
        std::cout<<new_auth.getstrHash()<<std::endl;
        std::cout<<new_auth.CompareHashes(pass)<<std::endl;
        if (new_auth.CompareHashes(pass)) {
        	new_manager.sending(sock, (void*)"OK", sizeof("OK"));
            uint32_t num_vectors;
            uint32_t vector_len;
            int16_t number;
            std::vector<int16_t> arr;
            bytes_read = new_manager.receiving(sock, (void*)num_vectors);
            for(int i =0; i<= num_vectors; i++) {
                bytes_read = new_manager.receiving(sock, (void*)vector_len);
                for(int i =0; i<= vector_len; i++) {
                    bytes_read = new_manager.receiving(sock, (void*)number);
                    arr.push_back(number);
                }
            }
            new_manager.sending(sock, (void*)(Counter().mean(arr)), sizeof(int16_t));
        } else {
            new_manager.sending(sock, Auth("NO","NO").ERRmsg, sizeof(Auth("NO","NO").ERRmsg));
            new_manager.closing(sock);
        }
        new_manager.closing(sock);
    } else {
        new_manager.sending(sock, Auth("NO","NO").ERRmsg, sizeof(Auth("NO","NO").ERRmsg));
        new_manager.closing(sock);
    }
}

int main(int argc, char **argv)
{
    Opts op(argc, argv);
    op.CheckFiles();
    DB new_db(op.getDataBaseName());
    WebManager new_manager(op.getPort());
    new_manager.new_bind();
    std::vector <thread> tr;
	new_manager.start_listening();
    while (true) {
        int sock = new_manager.accepting();
        tr.push_back(thread(conversation, new_manager, new_db, sock));
        for (std::vector<thread>::iterator it = tr.begin() ; it != tr.end(); ++it) {
                (*it).detach();
        }
    }
    return 0;
}
