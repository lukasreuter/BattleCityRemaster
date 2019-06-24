#pragma once

#include "Singleton.h"
#include "Components.h"
#include "ScreenManager.h"
#include <time.h>
#include <vector>
#include <list>
#include <string>
#include <entt.hpp>


class MapManager : public Singleton<MapManager>
{
    static constexpr auto MAX = 62;  // 30 * 2 + 1
    static constexpr auto CELL = 65000;  // 30 * 30
    static constexpr auto WALL = 1;
    static constexpr auto PATH = 0;
    
    friend class PlayScreen;
public:
    MapManager();
    void Init();
    void Update(/*entityx::ptr<entityx::EntityManager>*/);
    int Collide(const Position& pos, const Magnum::Vector3& delta, const Orientation& ori) const;
    bool FireCollision(const Position& start, const Orientation& direction, std::string name);
    bool IsFree(float x, float z);
    void DeletePosition(Magnum::Vector3 pos);
    Magnum::Vector3 FindFreePos();
    
protected:
    //Ogre::RaySceneQuery *mRaySceneQuery;


    void InitMaze(int maze[MAX][MAX]);
    void MazeGenerator(std::vector<std::vector<bool>> maze, int size, int shiftx, int shiftz);
    int IsClosed(int maze[MAX][MAX], int x, int y);
    void PrintMaze(Registry& registry);

private:
    int _finalMaze[MAX][MAX];
};
