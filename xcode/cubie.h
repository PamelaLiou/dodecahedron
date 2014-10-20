#pragma once


class Base
{
    
public:
    
    
    
    virtual void nested(){
    //stuff
    };
    
    
};

class Cubie : public Base {
    
    void nested() override {
    //    Base::nested();
    }
    
private:
    
    Base* parent;
    
};