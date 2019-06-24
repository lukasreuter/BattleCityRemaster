/**
 @file      MapManager.cpp
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include "MapManager.h"
#include "Factory.h"
#include "Components.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include "RenderManager.h"
#include "Logger.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


MapManager::MapManager()
{
    //mRaySceneQuery = RenderManager::getPtr()->getSceneManager()->createRayQuery(Ogre::Ray());
}

void MapManager::Init()
{
    //void receive(const KeyPressedEvent &event);
    //events->subscribe<KeyReleasedEvent>(*this);


    std::vector<std::vector<bool>> maze;
    srand(time(0));
    int toAdd = rand() % 2 + 8;
    for (auto i = 0; i < 62; i += toAdd)
    {
        for (auto j = 0; j < 62; j += toAdd)
        {
            MazeGenerator(maze, 7, i, j);
        }
        toAdd = rand() % 2 + 8;
    }

    LOGD(GREENBOLD << "MapManager" << RESET << "configured")
}

void MapManager::InitMaze(int maze[MAX][MAX])
{
    for (auto a = 0; a < MAX; ++a)
    {
        for (auto b = 0; b < MAX; ++b)
        {
            maze[a][b] = (a % 2 == PATH || b % 2 == PATH)
                ? WALL
                : PATH;
        }
    }
}

void MapManager::MazeGenerator(std::vector<std::vector<bool>> maze, int size, int shiftx, int shiftz)
{
    using namespace std;

    const int maze_size_x = size;
    const int maze_size_y = size;
    list<pair<int, int>> drillers;

    maze.resize(maze_size_y);
    for (auto y = 0; y < maze_size_y; ++y)
    {
         maze[y].resize(maze_size_x);
    }

    for (auto x = 0; x < maze_size_x; ++x)
    {
        for (auto y = 0; y < maze_size_y; ++y)
        {
            maze[y][x] = false;
        }
    }

    drillers.emplace_back(maze_size_x / 2, maze_size_y / 2);
    while (not drillers.empty())
    {
        list<pair<int, int>>::iterator m, _m;
        m = drillers.begin();
        _m = drillers.end();
        while (m != _m)
        {
            bool remove_driller = false;
            switch (rand() % 4)
            {
                case 0:
                    (*m).second -= 2;
                    if ((*m).second < 0 || maze[(*m).second][(*m).first])
                    {
                        remove_driller = true;
                        break;
                    }
                    maze[(*m).second + 1][(*m).first] = true;
                    break;
                case 1:
                    (*m).second += 2;
                    if ((*m).second >= maze_size_y || maze[(*m).second][(*m).first])
                    {
                        remove_driller = true;
                        break;
                    }
                    maze[(*m).second - 1][(*m).first] = true;
                    break;
                case 2:
                    (*m).first -= 2;
                    if ((*m).first < 0 || maze[(*m).second][(*m).first])
                    {
                        remove_driller = true;
                        break;
                    }
                    maze[(*m).second][(*m).first + 1] = true;
                    break;
                case 3:
                    (*m).first += 2;
                    if ((*m).first >= maze_size_x || maze[(*m).second][(*m).first])
                    {
                        remove_driller = true;
                        break;
                    }
                    maze[(*m).second][(*m).first - 1] = true;
                    break;
            }
            if (remove_driller)
                m = drillers.erase(m);
            else
            {
                drillers.emplace_back((*m).first, (*m).second);
                // uncomment the line below to make the maze easier
                // if (rand() % 2)
                drillers.emplace_back((*m).first, (*m).second);

                maze[(*m).second][(*m).first] = true;
                ++m;
            }
        }
    }

    for (auto y = 0; y < maze_size_y; ++y)
    {
        for (auto x = 0; x < maze_size_x; ++x)
        {
            if (maze[y][x])
            {
                //Factory::GetRef().createBlock((x+shiftx-(125/4))*4, 0, (-125/4+y+shiftz)*4, "Wall");
                _finalMaze[y + shiftz][x + shiftx] = WALL;
                // std::cout<<(x+shiftx-(125/4))*4<<" "<<(-125/4+y+shiftz)*4<<std::endl;
            }
        }
    }
}

int MapManager::IsClosed(int maze[MAX][MAX], int x, int y)
{
    return (maze[x - 1][y] == WALL &&
            maze[x][y - 1] == WALL &&
            maze[x][y + 1] == WALL &&
            maze[x + 1][y] == WALL)
        ? WALL
        : PATH;
}

void MapManager::PrintMaze(Registry& registry)
{
    // metal threshold choice instead of bricks
    constexpr int pMetalTreshold = 15;
    int p = 0;
    std::string material;

    for (int i = 0; i < 62; ++i)
    {
        _finalMaze[0][i]  = WALL;
        _finalMaze[61][i] = WALL;
        _finalMaze[i][0]  = WALL;
        _finalMaze[i][61] = WALL;
    }

    _finalMaze[0][0] = 2;
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
        {
            if (_finalMaze[i][j] == WALL)
            {
                p = rand() % 100;
                material = (i == 0 || i == MAX - 1 || j == 0 || j == MAX - 1 || p < pMetalTreshold)
                    ? "Metal"
                    : "Wall";

                Factory::createBlock(registry, (j - 125 / 4) * 4, 0, (i - 125 / 4) * 4, material);
          }
        }
    }
}

int MapManager::Collide(const Position& pos, const Magnum::Vector3& delta, const Orientation& ori) const
{
    using namespace Magnum;

    auto dt = delta * 4;
    Vector3 newPos = pos.position + dt - Vector3::zAxis(ori.orientation.axis().z());

    if ((newPos.x() + 125) / 4 < 0 || (newPos.x() + 125) / 4 > MAX)
        return PATH;
    if ((newPos.z() + 125) / 4 < 0 || (newPos.z() + 125) / 4 > MAX)
        return PATH;
    if (_finalMaze[int((newPos.z() + 125) / 4)][int(newPos.x() + 125) / 4] == WALL)
        return WALL;

    newPos = pos.position + dt - 2 * Vector3::xAxis(ori.orientation.axis().x());
    if (_finalMaze[int((newPos.z() + 125) / 4)][int(newPos.x() + 125) / 4] == WALL)
        return WALL;
    newPos = pos.position + dt + 2 * Vector3::xAxis(ori.orientation.axis().x());
    if (_finalMaze[int((newPos.z() + 125) / 4)][int(newPos.x() + 125) / 4] == WALL)
        return WALL;

    return PATH;
}

bool MapManager::FireCollision(const Position& start, const Orientation& direction, std::string name)
{
    /*
    Ogre::Ray ray(start->position,-direction->orientation.zAxis());
    mRaySceneQuery->setRay(ray);
    Ogre::RaySceneQueryResult& results = mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;
    //itr = result.begin();
    //itr++;
    */
    long min = 100'000;
    std::string minName = "";
    /*
    for (itr = results.begin(); itr != results.end(); ++itr)
    {
        if (min > itr->distance && itr->distance > 0)
        {
            min = itr->distance;
            minName = itr->movable->getParentSceneNode()->getName();
        }
      //  std::cout << itr->movable->getParentSceneNode()->getName() << " " << itr->distance << " ";
    }
    */
    std::cout << minName << std::endl;
    if (name == minName) {
        return true;
    }
    std::cout << std::endl;
    return false;
}

bool MapManager::IsFree(float x, float z)
{
    return _finalMaze[int((z + 125) / 4)][int(x + 125) / 4] != WALL;
}

void MapManager::DeletePosition(Magnum::Vector3 pos)
{
    _finalMaze[int(pos.z() + 125) / 4][int(pos.x() + 125) / 4] = PATH;
}

Magnum::Vector3 MapManager::FindFreePos()
{
    int x, z;
    do {
        x = (rand() % 220) - 110;
        z = (rand() % 220) - 110;
        LOGD(x << "-" << z);
    } while (not IsFree(x, z));

    return Magnum::Vector3{ static_cast<float>(x), 1, static_cast<float>(z) };
}
