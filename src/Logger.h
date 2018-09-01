//
//  Logger.h
//  BattleCity2018
//
//  Created by Lukas Reuter on 01.09.18.
//
#pragma once

#include "Config.h"
#include <Magnum/Magnum.h>

#ifdef DEBUG
#define LOGD(args) Magnum::Debug{} << args;
#else
#define LOGD(args)
#endif
