#include "interface.h"
#include "Auth.h"
#include "Counter.h"
#include "DataBase.h"
#include <iostream>
#include "WebManager.h"
#include "ErrorTracker.h"
#include <thread>
#include <vector>
#include <string>
#include <map>

using namespace std;


void conversation(unsigned int port, std::string LogName, DB new_db, int sock)
{
	try{
	WebManager new_manager(port);
    char buf[2048];
    int bytes_read;
    bytes_read = new_manager.receiving(sock, &buf, 2048);
     std::cout<<string(buf, bytes_read)<<std::endl;
    new_db.IDcheck(string(buf, bytes_read));
        Auth new_auth(string(buf, bytes_read), new_db.DataBaseP[string(buf, bytes_read)]);
        new_auth.GenSALT();
        string str_salt = new_auth.getSALT();
        char salt_buf[16];
        strcpy(salt_buf, str_salt.c_str());
        new_manager.sending(sock, salt_buf, sizeof(salt_buf));
        bytes_read = new_manager.receiving(sock, &buf, 2048);
        string pass = string(buf, bytes_read);
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
