#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H

// Includes
//#include <OgreString.h>
//#include <OgreVector3.h>
//#include <OgreQuaternion.h>
//#include <OgreResourceGroupManager.h>
#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector3.h>
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

    class nodeProperty
    {
    public:
        std::string nodeName;
        std::string propertyNm;
        std::string valueName;
        std::string typeName;

        nodeProperty(const std::string &node, const std::string &propertyName, const std::string &value, const std::string &type)
            : nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
    };

    class DotSceneLoader
    {
    public:
        Ogre::TerrainGlobalOptions *mTerrainGlobalOptions;

        DotSceneLoader();
        virtual ~DotSceneLoader();

        void parseDotScene(const std::string &SceneName, const std::string &groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode = nullptr, const std::string &sPrependNode = "");
        std::string getProperty(const std::string &ndNm, const std::string &prop);

        Ogre::TerrainGroup* getTerrainGroup() { return mTerrainGroup; }

        std::vector<nodeProperty> nodeProperties;
        std::vector<std::string> staticObjects;
        std::vector<std::string> dynamicObjects;

    protected:
        //! @todo fix these
        //void processScene(rapidxml::xml_node<>* XMLRoot);

        //void processNodes(rapidxml::xml_node<>* XMLNode);
        //void processExternals( rapidxml::xml_node<>* XMLNode);
        //void processEnvironment( rapidxml::xml_node<>* XMLNode);
        //void processTerrain(rapidxml::xml_node<>* XMLNode);
        //void processTerrainPage(rapidxml::xml_node<>* XMLNode);
        /*void processBlendmaps(rapidxml::xml_node<>* XMLNode);
        void processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);
        void processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::Entity *pEntity);
        void processOctree(rapidxml::xml_node<>* XMLNode);
        void processLight(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);
        void processCamera(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);

        void processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);
        void processLookTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processTrackTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processEntity(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processParticleSystem(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processBillboardSet(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processPlane(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);

        void processFog(rapidxml::xml_node<>* XMLNode);
        void processSkyBox(rapidxml::xml_node<>* XMLNode);
        void processSkyDome(rapidxml::xml_node<>* XMLNode);
        void processSkyPlane(rapidxml::xml_node<>* XMLNode);
        void processClipping(rapidxml::xml_node<>* XMLNode);

        void processLightRange(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight);
        void processLightAttenuation(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight);

        Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, const Ogre::String &defaultValue = "");
        Ogre::Real getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, Ogre::Real defaultValue = 0);
        bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, bool defaultValue = false);

        Ogre::Vector3 parseVector3(rapidxml::xml_node<>* XMLNode);
        Ogre::Quaternion parseQuaternion(rapidxml::xml_node<>* XMLNode);
        Ogre::ColourValue parseColour(rapidxml::xml_node<>* XMLNode);
         */


        Ogre::SceneManager *mSceneMgr;
        Ogre::SceneNode *mAttachNode;
        std::string m_sGroupName;
        std::string m_sPrependNode;
        Ogre::TerrainGroup* mTerrainGroup;
        Magnum::Vector3 mTerrainPosition;
        Magnum::Vector3 mLightDirection;
    };

#endif // DOT_SCENELOADER_H
