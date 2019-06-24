/**
 @file      SceneManager.cpp
 @author    Lukas Reuter
 @date      24.06.19

Copyright (c) 2019, Lukas Reuter
All rights reserved.

*/

#include "SceneManager.h"


Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>* SceneManager::getSceneNode(std::string NodeName)
{
    return new Object3D{};
};
