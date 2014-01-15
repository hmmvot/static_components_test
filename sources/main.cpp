//
//  main.cpp
//  engine
//
//  Created by hmmvot on 28.12.13.
//  Copyright (c) 2013 Alexander Sokolenko. All rights reserved.
//

#include <iostream>

#include "Component.hpp"
#include "Entity.hpp"

class ISomeComponent1
{
public:
    virtual void f() = 0;
    virtual void f1() = 0;
};

template <class Gluer>
class SomeComponent1
    : public Component<ISomeComponent1, Gluer>
{
public:
    virtual void f() override {
        std::cout << "SomeComponent1::f()" << std::endl;
    }
    
    virtual void f1() override {
        std::cout << "SomeComponent1::f1()" << std::endl;
    }
};

class ISomeComponent2
{
public:
    virtual void f() = 0;
    virtual void f2() = 0;
};


template <class Gluer>
class SomeComponent2
    : public Component<ISomeComponent2, Gluer>
{
public:
    virtual void f() override {
        std::cout << "SomeComponent2::f(): " << ENTITY->COMPONENT(SomeComponent1) << std::endl;
    }
    
    virtual void f2() override {
        std::cout << "SomeComponent2::f2()" << std::endl;
    }
};


class SomeEntity
    : public Entity<SomeEntity>
//    , public SomeComponent1<SomeEntity>
    , public SomeComponent2<SomeEntity>
{
public:
    void do_smth() {
        ISomeComponent1 * c1 = this->COMPONENT(SomeComponent1);
        ISomeComponent2 * c2 = this->COMPONENT(SomeComponent2);
        
        std::cout   << "b: " << this << std::endl
                    << "1: " << c1 << std::endl
                    << "2: " << c2 << std::endl;
        
        c1 ? c1->f1() : void();
        c1 ? c1->f() : void();
        
        c2 ? c2->f2() : void();
        c2 ? c2->f() : void();
    }
};


int main(int argc, const char * argv[])
{
    SomeEntity * e = new SomeEntity();
    
    e->do_smth();
    
    Collector<ISomeComponent1>::getCollection();
    
    delete e;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
