#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "info.h"
#include <memory>
// DO NOT MODIFY THIS FILE!

class Observer;

class Subject {
    protected: std::vector<std::shared_ptr<Observer>> observers;
  public:
    virtual void attach(std::shared_ptr<Observer> o);  
    void notifyObservers();
    virtual Info getInfo() const = 0;
};

#endif
