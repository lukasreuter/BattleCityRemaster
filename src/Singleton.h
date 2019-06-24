/**
 @file      Singleton.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

// use this for manager type classes that will always be assigned during the execution of the game
template <class T>
struct Singleton {
    [[nodiscard]]
    inline static T& GetRef() {
        static T mInstance;
        return mInstance;
    }
};
