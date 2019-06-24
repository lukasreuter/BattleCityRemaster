/**
 @file      Logger.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Config.h"
#include <Magnum/Magnum.h>

#ifdef DEBUG_LOG
    #define LOGD(args) Magnum::Debug{Magnum::Debug::isTty() ? Magnum::Debug::Flags{} : Magnum::Debug::Flag::DisableColors} << args;

    #define GREENBOLD Magnum::Debug::boldColor(Magnum::Debug::Color::Green)
    #define GREEN Magnum::Debug::color(Debug::Color::Green)
    #define REDBOLD Magnum::Debug::boldColor(Debug::Color::Red)
    #define RED Magnum::Debug::color(Debug::Color::Red)
    #define BLUEBOLD Magnum::Debug::boldColor(Debug::Color::Blue)
    #define BLUE Magnum::Debug::color(Debug::Color::Blue)
    #define YELLOWBOLD Magnum::Debug::boldColor(Debug::Color::Yellow)
    #define YELLOW Magnum::Debug::color(Debug::Color::Yellow)

    #define BOLD Magnum::Debug::boldColor(Debug::Color::Default)

    #define RESET Magnum::Debug::resetColor
#else
    #define LOGD(args)
    #define GREENBOLD
    #define GREEN
    #define REDBOLD
    #define RED
    #define BLUEBOLD
    #define BLUE
    #define YELLOWBOLD
    #define YELLOW
    #define BOLD
    #define RESET
#endif
