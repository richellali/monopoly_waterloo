#ifndef _INFO_H
#define _INFO_H
#include <string>


struct Info {
    int position = 0;
    std::string name;
    int order;
    bool isBankrupt = false;
    bool liabilityToBank = false;
    bool needAuction = false;
};

#endif

