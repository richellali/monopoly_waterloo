#ifndef _OBSERVER_H_
#define _OBSERVER_H_


class Subject;
class Cell;

class Observer {
  public:
    // Pass the Subject that called the notify method.
    virtual void notify( Subject & whoNotified ) = 0; 

    virtual ~Observer() = default;
};

#endif
