#pragma once

// use this for manager type classes that will always be assigned during the execution of the game
template <class T>
struct Singleton {
    static T& GetRef() {
        static T mInstance;
        return mInstance;
    }
};
