
// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
#include<random>
#include<fstream>
using namespace std;

enum class LogLevel{
    INFO,
    DEBUG,
    ERROR
};

class LoggerObserver{
    public:
    virtual void log(LogLevel level,const string& message)=0;
    virtual ~LoggerObserver()=default;
    
};


class ConsoleLogger : public LoggerObserver{
    public:
     void log(LogLevel level,const string& message) override
     {
         cout<<"[CONSOLE] "<<toString(level)<<message<<endl;
     }
     private:
     string toString(LogLevel level)
     {
         if(level==LogLevel::INFO) return "INFO";
         else if(level==LogLevel::ERROR) return "ERROR";
         else return "DEBUG";
     }
};



class FileLogger:public LoggerObserver{
    ofstream file;
    public:
    
     FileLogger(const string& filename="log.txt")
     {
         file.open(filename,ios::app);
     }
     
     ~FileLogger()
     {
         if(file.is_open())
         {
             file.close();
         }
     }
     
     
     void log(LogLevel level,const string& message) override
     {   
         if(file.is_open())
         {
             file<<toString(level)<<message<<"\n";
         }
         cout<<"[FILELOG] "<<toString(level)<<message<<endl;
     }
     private:
     string toString(LogLevel level)
     { 
         if(level==LogLevel::INFO) return "INFO";
         else if(level==LogLevel::ERROR) return "ERROR";
         else return "DEBUG";
     }
    
};

class DBLogger:public LoggerObserver{
    
    public:
     void log(LogLevel level,const string& message) override
     {
         cout<<"[DBLOG] "<<toString(level)<<message<<endl;
     }
     private:
     string toString(LogLevel level)
     {
         if(level==LogLevel::INFO) return "INFO";
         else if(level==LogLevel::ERROR) return "ERROR";
         else return "DEBUG";
     }
    
};
class LogManager{
    vector<shared_ptr<LoggerObserver>> observers;
    
    LogManager(){}
//ensure that there is only one instance of Logmanager
public:
 static LogManager& getInstance()
 {
     static LogManager instance;
     return instance;
 }
LogManager(const LogManager&)=delete;
LogManager& operator=(const LogManager&)=delete;


void addObserver(shared_ptr<LoggerObserver> ob)
{
    observers.push_back(ob);
}

void log(LogLevel level,const string& message)
{
    for(auto it:observers)
    {
        it->log(level,message);
    }
}


};

int main() {
    // Write C++ code here
   auto& logger = LogManager::getInstance();

    logger.addObserver(std::make_shared<ConsoleLogger>());
    logger.addObserver(std::make_shared<FileLogger>("log.txt"));
    logger.addObserver(std::make_shared<DBLogger>());

    logger.log(LogLevel::INFO, " Application started");
    logger.log(LogLevel::DEBUG, " Debugging main flow");
    logger.log(LogLevel::ERROR, " Something went wrong");

    return 0;
}