#include <exception>
#include <ctime>
#include <string>

class ErrorTracker
{
private:
    std::string LogFileName;
public:
    ErrorTracker(std::string LogName);
    void write_log(std::string what);
};
