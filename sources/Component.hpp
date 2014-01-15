//
//  Component.h
//  engine
//
//  Created by hmmvot on 14.01.14.
//  Copyright (c) 2014 Alexander Sokolenko. All rights reserved.
//

#ifndef __engine__Component__
#define __engine__Component__

#include <type_traits>

#include "Entity.hpp"
#include "Collector.hpp"


template <class IComponent, class Gluer>
class Component
    : public IComponent
    , public Collector<IComponent>
{
    static inline void __CHECK_INHERITANCE() {
        // Этот метод будет вызван при создании первого объекта этого класса;
        // Если поместить static_assert за пределами метода,
        // то на момент их обработки компилятором класс Gluer не будет полным;
        
        static_assert(
            std::is_base_of<Entity<Gluer>, Gluer>::value,
            "Gluer must be an Entyty<Gluer>"
        );
        
        static_assert(
            std::is_base_of<Component<IComponent, Gluer>, Gluer>::value,
            "Gluer must be a Component"
        );
    }
    
public:
    Component() {
        __CHECK_INHERITANCE();
    }
    
    virtual ~Component() {
        //
    }
    
    inline const Gluer * const getEntity() const {
        return static_cast<const Gluer *>(this);
    }
    
    inline Gluer * getEntity() {
        return static_cast<Gluer *>(this);
    }
    
protected:
    
};

#define ENTITY this->getEntity()

#endif /* defined(__engine__Component__) */
