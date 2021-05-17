#include "waterpolyexception.h"
WaterpolyException::WaterpolyException(std::string name)
:name{name}{}

std::string WaterpolyException::getExceptionName(){
    return name;
}

