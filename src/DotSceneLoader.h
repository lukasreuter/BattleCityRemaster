#pragma once

// Includes
//#include <OgreString.h>
//#include <OgreVector3.h>
//#include <OgreQuaternion.h>
//#include <OgreResourceGroupManager.h>
#include <rapidxml.hpp>
#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Quaternion.h>
#include <Magnum/Math/Color.h>
#include <vector>
#include <string>

//#include "rapidxml.hpp"

// Forward declarations
namespace Ogre
{
    class SceneManager;
    class SceneNode;
    class TerrainGroup;
    class TerrainGlobalOptions;
}

struct nodeProperty
{
    std::string nodeName;
    std::string propertyNm;
    std::string valueName;
    std::string typeName;

    nodeProperty(const std::string& node, const std::string& propertyName, const std::string& value, const std::string& type)
            : nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
};

class SceneManager;


class DotSceneLoader
{
public:
    Ogre::TerrainGlobalOptions* mTerrainGlobalOptions;

    DotSceneLoader();
    virtual ~DotSceneLoader();

    void parseDotScene(const std::string& SceneName, const std::string& groupName, const SceneManager& yourSceneMgr, Ogre::SceneNode* pAttachNode = nullptr, const std::string& sPrependNode = "");
    std::string getProperty(const std::string& ndNm, const std::string& prop);

    inline Ogre::TerrainGroup* getTerrainGroup() const { return mTerrainGroup; }

    std::vector<nodeProperty> nodeProperties;
    std::vector<std::string> staticObjects;
    std::vector<std::string> dynamicObjects;

protected:
    void processScene(rapidxml::xml_node<>* XMLRoot);

    void processNodes(rapidxml::xml_node<>* XMLNode);
    void processExternals(rapidxml::xml_node<>* XMLNode);
    void processEnvironment(rapidxml::xml_node<>* XMLNode);
    void processTerrain(rapidxml::xml_node<>* XMLNode);
    void processTerrainPage(rapidxml::xml_node<>* XMLNode);
    void processBlendmaps(rapidxml::xml_node<>* XMLNode);
    void processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent = nullptr);
//    void processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::Entity *pEntity);
    void processOctree(rapidxml::xml_node<>* XMLNode);
    void processLight(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent = nullptr);
    void processCamera(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent = nullptr);

    void processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent = nullptr);
    void processLookTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent);
    void processTrackTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent);
    void processEntity(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent);
    void processParticleSystem(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent);
    void processBillboardSet(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent);
    void processPlane(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent);

    void processFog(rapidxml::xml_node<>* XMLNode);
    void processSkyBox(rapidxml::xml_node<>* XMLNode);
    void processSkyDome(rapidxml::xml_node<>* XMLNode);
    void processSkyPlane(rapidxml::xml_node<>* XMLNode);
    void processClipping(rapidxml::xml_node<>* XMLNode);

//    void processLightRange(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight);
//    void processLightAttenuation(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight);

    std::string getAttrib(rapidxml::xml_node<>* XMLNode, const std::string& parameter, const std::string& defaultValue = "");
    float getAttribReal(rapidxml::xml_node<>* XMLNode, const std::string& parameter, float defaultValue = 0);
    bool getAttribBool(rapidxml::xml_node<>* XMLNode, const std::string& parameter, bool defaultValue = false);

    Magnum::Vector3 parseVector3(rapidxml::xml_node<>* XMLNode);
    Magnum::Quaternion parseQuaternion(rapidxml::xml_node<>* XMLNode);
    Magnum::Color4 parseColour(rapidxml::xml_node<>* XMLNode);

    Ogre::SceneManager* mSceneMgr;
    Ogre::SceneNode* mAttachNode;
    std::string m_sGroupName;
    std::string m_sPrependNode;
    Ogre::TerrainGroup* mTerrainGroup;
    Magnum::Vector3 mTerrainPosition;
    Magnum::Vector3 mLightDirection;
};
