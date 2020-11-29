#include "function.h"
#include <iostream>
using namespace std;

int error(string e){
  cerr << e << endl;
  return(EXIT_FAILURE);
}

/*
#include <iostream>
#include <exception>
#include <string>
class Failure: public std::exception
{
private:
    std::string mErrMsg;

public:
  Failure(std::string errMsg):mErrMsg(errMsg){}
    const char* what() const noexcept
    {
        return mErrMsg.c_str();
    }
};
*/
