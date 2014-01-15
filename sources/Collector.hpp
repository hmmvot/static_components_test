//
//  Collector.h
//  engine
//
//  Created by hmmvot on 15.01.14.
//  Copyright (c) 2014 Alexander Sokolenko. All rights reserved.
//

#ifndef __engine__Collector__
#define __engine__Collector__

#include <type_traits>
#include <list>

template <class T>
class Collector
{
public:
    typedef std::list<T*> Collection;
    
    Collector() {
        static_assert(std::is_base_of<Collector<T>, T>::value, "");
        
        T * ptr = static_cast<T*>(this);
        collection.push_back(ptr);
    }
    
    ~Collector() {
        T * ptr = static_cast<T*>(this);
        collection.remove(ptr);
    }
    
    static inline const Collection& getCollection() {
        return collection;
    }

private:
    static Collection collection;
};

#endif /* defined(__engine__Collector__) */
