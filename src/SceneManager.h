//
//  SceneManager.hpp
//  CorradeInterconnect
//
//  Created by Lukas Reuter on 16.10.18.
//

#pragma once

#include "Singleton.h"
#include <Magnum/SceneGraph/Object.h>
#include <string>
#include <stdio.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>


class SceneManager : public Singleton<SceneManager>
{
    using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
    
public:
    Object3D* getSceneNode(std::string NodeName);
};
