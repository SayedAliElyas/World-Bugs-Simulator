#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <sys/types.h>
#include <vector>

class Client
{
public:
    Client();
    ~Client();

    bool start(const std::string& world,
               const std::string& redBug,
               const std::string& blackBug);
    
    void parseResponse(const std::string& response);
    std::vector<std::string> getCurrentMap() const;
    std::vector<bool> getOffsetRows() const;

    std::string step(int ticks);   // send STEP command
    std::string fetch();           // send FETCH command
    void quit();                   // send QUIT command
    void stop();
    std::string getresult() const;

private:
    int cmd_fd; // file descriptor for command pipe
    int data_fd; // file descriptor for data pipe
    pid_t sim_pid; // process ID of the simulator
    char* temp_dir; // temporary directory for pipes
    std::string cmd_pipe; // path to command pipe
    std::string data_pipe; // path to data pipe
    std::string readData(); // helper function to read from data pipe until "END"
    std::vector<std::string> currentMap; // contain each row of the world as string
    std::vector<bool> offsetRows; // track which rows have offsets
};
#endif