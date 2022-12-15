#pragma once
#include <map>
#include <string>

class Auth
{
private:
    
    std::string SALT;
    std::string Id;
    std::string password;
    std::string strHash;
    char sep = ':';

public:
    Auth(std::string ID, std::string pass);
    void GenSALT();
    char ERRmsg[3] = {'E', 'R','R'};
    bool CompareHashes(std::string ClientHash);
    std::string getSALT()
    {
        return SALT;
    }
    std::string getId()
    {
        return Id;
    }
    std::string getpass()
    {
        return password;
    }
    std::string getstrHash()
    {
        return strHash;
    }
};
