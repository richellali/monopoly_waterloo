#include "slc.h"
#include <iostream>
#include <cstdlib>
#include "player.h"
#include "grid.h"
#include <time.h>

//SLC::SLC(int position, std::string name) :Building(position, name) {}

SLC::SLC(std::string name, int pos):NonProperty(name, pos), strategy{nullptr}{}

void SLC::event(Player & p) {
    std::cerr << "Welcome to SLC!" << std::endl;
    //srand(time(NULL));
    int probability = std::rand() % 100;
    // rare prob(1%) of receving a dc cup and leave SLC
    if (probability == 1 && p.getDCCups() < 4) {
        std::cerr << "Congratulation! You receive a winning Roll Up the Rim cup! "
         << "You can use it for leave the DC Tims line for free!" << std::endl;
        p.setDCCups(1);
        return;
    }

    probability = std::rand() % 24;
    if (probability < 3) {
        strategy = std::make_unique<Back3>();
    } else if (probability < 7) {
        strategy = std::make_unique<Back2>();
    } else if (probability < 11) {
        strategy = std::make_unique<Back1>();
    } else if (probability < 14) {
        strategy = std::make_unique<Forward1>();
    } else if (probability < 18) {
        strategy = std::make_unique<Forward2>();
    } else if (probability < 22) {
        strategy = std::make_unique<Forward3>();
    } else if (probability < 23) {
        strategy = std::make_unique<GoDC>();
    } else {
        strategy = std::make_unique<OSAP>();
    }
    strategy->dosth(p);
}


//StrategySLC::StrategySLC(Info info) : buildingInfo{info}{}

// all strategies
void Back3::dosth(Player & p) {
    std::cerr << "Move back 3 steps :(" << std::endl;
    p.move(-3); 
}

void Back2::dosth(Player & p) {
    std::cerr << "Move back 2 steps :(" << std::endl;
    p.move(-2);
}

void Back1::dosth(Player & p) {
    std::cerr << "Move back 1 steps :(" << std::endl;
    p.move(-1);
}

void Forward3::dosth(Player & p) {
    std::cerr << "Move forward 3 steps :)" << std::endl;
    p.move(3);
}

void Forward2::dosth(Player & p) {
    std::cerr << "Move forward 2 steps :)" << std::endl;
    p.move(2);
}

void Forward1::dosth(Player & p) {
    std::cerr << "Move forward 1 steps :)" << std::endl;
    p.move(1);
}

void GoDC::dosth(Player & p) {
    std::cerr << "Move to DC Times Line :(" << std::endl;
    p.goTim();
}

void OSAP::dosth(Player & p) {
    std::cerr << "Collect OSAP :)" << std::endl;
    p.collectOSAP();
}

