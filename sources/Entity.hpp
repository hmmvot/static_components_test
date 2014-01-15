//
//  Entity.h
//  engine
//
//  Created by hmmvot on 14.01.14.
//  Copyright (c) 2014 Alexander Sokolenko. All rights reserved.
//

#ifndef __engine__Entity__
#define __engine__Entity__

#include <type_traits>

class IEntity
{
public:
    virtual ~IEntity() {
        //
    }
};

template <class Gluer>
class Entity
    : public IEntity
{
public:
    
    // если в методах getComponent использовать static_cast, а не C-style type cast,
    // то в случае, когда Gluer не является наследником Component произойдет ошибка компиляции
    // (static_cast для non-void указателей разрешает только восходящее и нисходящее преобразования)
    
    //
    
    template <class Component>
    inline bool hasComponent() const {
        // TODO add more strict condition
        return std::is_base_of<Component, Gluer>::value;
    }
    
    template <class Component>
    inline const Component * const getComponent() const {
        if (hasComponent<Component>()) {
            return (Component *)(static_cast<const Gluer*>(this));
        }
        return NULL;
    }
    
    template <class Component>
    inline Component * getComponent() {
        if (hasComponent<Component>()) {
            return (Component *)(static_cast<Gluer*>(this));
        }
        return NULL;
    }
    
    //
    
    template <template <class _Gluer> class Component>
    inline bool hasComponent() const {
        // TODO add more strict condition
        return std::is_base_of<Component<Gluer>, Gluer>::value;
    }
    
    template <template <class _Gluer> class Component>
    inline const Component<Gluer> * const getComponent() const {
        if (hasComponent<Component>()) {
            return (Component<Gluer> *)(static_cast<const Gluer*>(this));
        }
        return NULL;
    }
    
    template <template <class _Gluer> class Component>
    inline Component<Gluer> * getComponent() {
        if (hasComponent<Component>()) {
            return (Component<Gluer> *)(static_cast<Gluer*>(this));
        }
        return NULL;
    }
};

#define COMPONENT(c) template getComponent<c>()

#endif /* defined(__engine__Entity__) */
