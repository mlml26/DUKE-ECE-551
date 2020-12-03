#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <string>
#include <iostream>
#include <exception>

using namespace std;

void error(string e);

/*
The "Failure" class inheritate the std::exception class and overwrite
the what() method to take a string and return that string.
 */
class Failure: public std::exception
{
private:
    string mErrMsg;

public:
  Failure(string errMsg):mErrMsg(errMsg){}
    const char* what() const noexcept
    {
        return mErrMsg.c_str();
    }
};

/*
The "FailurePrint" class inheritate the std::exception class.
*/
class FailurePrint: public std::exception
{
  //nothing
};

#endif
