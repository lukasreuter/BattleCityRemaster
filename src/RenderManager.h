/**
 @file      RenderManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include <map>
#include <entt.hpp>
#include <Magnum/Magnum.h>
#include <Magnum/SceneGraph/Camera.h>

//#include <Ogre.h>

class RenderManager : public Singleton<RenderManager>
{
public:
    ~RenderManager();
    void init(std::string windowTitle);
    void update(double dt);
    //void setFrameListener(Ogre::FrameListener *listener);
    //void attachCameraTo(Ogre::SceneNode* node, Magnum::Vector3 offset);

    inline Magnum::SceneGraph::Camera3D * GetCamera() const { return mCamera; }
    //inline Ogre::Viewport* GetViewport() const { return mViewport; }
    //inline Ogre::SceneManager* GetSceneManager() const { return mSceneMgr; }
    //inline Ogre::Root* GetRoot() const { return mRoot; }
    //inline Ogre::RenderWindow* GetRenderWindow() const { return mWindow; }

protected:
    void loadResources();

private:
    //Ogre::Root* mRoot;
    //Ogre::RenderWindow* mWindow;
    Magnum::SceneGraph::Camera3D * mCamera;
    //Ogre::Viewport* mViewport;
    //Ogre::SceneManager* mSceneMgr;
};
