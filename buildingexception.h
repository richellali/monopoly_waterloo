#ifndef __BUILDINGEXCEPTION__
#define __BUILDINGEXCEPTION__
#include "waterpolyexception.h"
class BuildingException: public WaterpolyException{
    public:
    BuildingException(std::string name);
};
#endif


