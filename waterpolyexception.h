#ifndef __WATERPOLYEXCEPTION__
#define __WATERPOLYEXCEPTION__
#include <string>
class WaterpolyException{
    std::string name;
    public:
    WaterpolyException(std::string name);
    std::string getExceptionName();
};

#endif
