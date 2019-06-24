/**
 @file      DotSceneLoader.cpp
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include "DotSceneLoader.h"
#include "Logger.h"
#include <rapidxml.hpp>
//#include <Ogre.h>
//#include <Terrain/OgreTerrain.h>
//#include <Terrain/OgreTerrainGroup.h>
//#include <Terrain/OgreTerrainMaterialGeneratorA.h>

//#pragma warning(disable:4390)
//#pragma warning(disable:4305)

//TODO:

DotSceneLoader::DotSceneLoader() : mSceneMgr(nullptr), mTerrainGroup(nullptr)
{
    //mTerrainGlobalOptions = OGRE_NEW Ogre::TerrainGlobalOptions();
}

DotSceneLoader::~DotSceneLoader()
{
    if (mTerrainGroup)
    {
        //OGRE_DELETE mTerrainGroup;
    }

    //OGRE_DELETE mTerrainGlobalOptions;
}

void DotSceneLoader::parseDotScene(const std::string& SceneName, const std::string& groupName, const SceneManager& yourSceneMgr, Ogre::SceneNode* pAttachNode, const std::string& sPrependNode)
{/*
    // set up shared object values
    m_sGroupName = groupName;
    mSceneMgr = yourSceneMgr;
    m_sPrependNode = sPrependNode;
    staticObjects.clear();
    dynamicObjects.clear();

    rapidxml::xml_document<> XMLDoc;    // character type defaults to char

    rapidxml::xml_node<>* XMLRoot;

    Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(SceneName, groupName );
    char* scene = strdup(stream->getAsString().c_str());
    XMLDoc.parse<0>(scene);

    // Grab the scene node
    XMLRoot = XMLDoc.first_node("scene");

    // Validate the File
    if( getAttrib(XMLRoot, "formatVersion", "") == "")
    {
        Ogre::LogManager::getSingleton().logMessage( "[DotSceneLoader] Error: Invalid .scene File. Missing <scene>" );
        return;
    }

    // figure out where to attach any nodes we create
    mAttachNode = pAttachNode;
    if(!mAttachNode)
        mAttachNode = mSceneMgr->getRootSceneNode();

    // Process the scene
    processScene(XMLRoot);
  */
}

void DotSceneLoader::processScene(rapidxml::xml_node<>* XMLRoot)
{
    using namespace std;

    // Process the scene parameters
    string version = getAttrib(XMLRoot, "formatVersion", "unknown");

    string message = "[DotSceneLoader] Parsing dotScene file with version " + version;
    if (XMLRoot->first_attribute("ID")) {
        message += ", id " + string{ XMLRoot->first_attribute("ID")->value() };
    }
    if (XMLRoot->first_attribute("sceneManager")) {
        message += ", scene manager " + string{ XMLRoot->first_attribute("sceneManager")->value() };
    }
    if (XMLRoot->first_attribute("minOgreVersion")) {
        message += ", min. Ogre version " + string{ XMLRoot->first_attribute("minOgreVersion")->value() };
    }
    if (XMLRoot->first_attribute("author")) {
        message += ", author " + string{ XMLRoot->first_attribute("author")->value() };
    }

    LOGD(message);

    rapidxml::xml_node<>* pElement;

    // Process environment (?)
    pElement = XMLRoot->first_node("environment");
    if (pElement) {
        processEnvironment(pElement);
    }

    // Process nodes (?)
    pElement = XMLRoot->first_node("nodes");
    if (pElement) {
        processNodes(pElement);
    }

    // Process externals (?)
    pElement = XMLRoot->first_node("externals");
    if (pElement) {
        processExternals(pElement);
    }

    // Process userDataReference (?)
    pElement = XMLRoot->first_node("userDataReference");
    if (pElement) {
        processUserDataReference(pElement);
    }

    // Process octree (?)
    pElement = XMLRoot->first_node("octree");
    if (pElement) {
        processOctree(pElement);
    }

    // Process light (?)
    pElement = XMLRoot->first_node("light");
    if (pElement) {
        processLight(pElement);
    }

    // Process camera (?)
    pElement = XMLRoot->first_node("camera");
    if (pElement) {
        processCamera(pElement);
    }

    // Process terrain (?)
    pElement = XMLRoot->first_node("terrain");
    if (pElement) {
        processTerrain(pElement);
    }
}

void DotSceneLoader::processNodes(rapidxml::xml_node<>* XMLNode)
{
    rapidxml::xml_node<>* pElement;

    // Process node (*)
    pElement = XMLNode->first_node("node");
    while (pElement)
    {
        processNode(pElement);
        pElement = pElement->next_sibling("node");
    }
/*
    // Process position (?)
    pElement = XMLNode->first_node("position");
    if (pElement)
    {
        mAttachNode->setPosition(parseVector3(pElement));
        mAttachNode->setInitialState();
    }

    // Process rotation (?)
    pElement = XMLNode->first_node("rotation");
    if (pElement)
    {
        mAttachNode->setOrientation(parseQuaternion(pElement));
        mAttachNode->setInitialState();
    }

    // Process scale (?)
    pElement = XMLNode->first_node("scale");
    if (pElement)
    {
        mAttachNode->setScale(parseVector3(pElement));
        mAttachNode->setInitialState();
    }
 */
}

void DotSceneLoader::processExternals(rapidxml::xml_node<>* XMLNode)
{
    //! @todo Implement this
}

void DotSceneLoader::processEnvironment(rapidxml::xml_node<>* XMLNode)
{
    rapidxml::xml_node<>* pElement;

    // Process camera (?)
    pElement = XMLNode->first_node("camera");
    if (pElement) {
        processCamera(pElement);
    }

    // Process fog (?)
    pElement = XMLNode->first_node("fog");
    if (pElement) {
        processFog(pElement);
    }

    // Process skyBox (?)
    pElement = XMLNode->first_node("skyBox");
    if (pElement) {
        processSkyBox(pElement);
    }

    // Process skyDome (?)
    pElement = XMLNode->first_node("skyDome");
    if (pElement) {
        processSkyDome(pElement);
    }

    // Process skyPlane (?)
    pElement = XMLNode->first_node("skyPlane");
    if (pElement) {
        processSkyPlane(pElement);
    }

    // Process clipping (?)
    pElement = XMLNode->first_node("clipping");
    if (pElement) {
        processClipping(pElement);
    }
/*
    // Process colourAmbient (?)
    pElement = XMLNode->first_node("colourAmbient");
    if(pElement)
        mSceneMgr->setAmbientLight(parseColour(pElement));
 */

    // Process colourBackground (?)
    //! @todo Set the background colour of all viewports (RenderWindow has to be provided then)
    pElement = XMLNode->first_node("colourBackground");
    if(pElement)
        ;//mSceneMgr->set(parseColour(pElement));

    // Process userDataReference (?)
    pElement = XMLNode->first_node("userDataReference");
    if (pElement) {
        processUserDataReference(pElement);
    }

}

void DotSceneLoader::processTerrain(rapidxml::xml_node<>* XMLNode)
{
    float worldSize = getAttribReal(XMLNode, "worldSize");
    int mapSize = std::stoi(XMLNode->first_attribute("mapSize")->value());
    int rows = std::stoi(XMLNode->first_attribute("rows")->value());
    int columns = std::stoi(XMLNode->first_attribute("columns")->value());
    bool colourmapEnabled = getAttribBool(XMLNode, "colourmapEnabled");
    int colourMapTextureSize = std::stoi(XMLNode->first_attribute("colourMapTextureSize")->value());

    auto lightdir = Magnum::Vector3{ 0.f, -0.3f, 0.75f }.normalized();
    /*
    Ogre::Light* l = mSceneMgr->createLight("tstLight");
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDirection(lightdir);
    l->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
    l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.6, 0.6, 0.6));

    mTerrainGlobalOptions->setMaxPixelError(1);
    mTerrainGlobalOptions->setCompositeMapDistance(2000);
    mTerrainGlobalOptions->setLightMapDirection(lightdir);
    mTerrainGlobalOptions->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobalOptions->setCompositeMapDiffuse(l->getDiffuseColour());

    mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, mapSize, worldSize);
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

    rapidxml::xml_node<>* pElement;
    rapidxml::xml_node<>* pPageElement;

    // Process terrain pages (*)
    pElement = XMLNode->first_node("terrainPages");
    while(pElement)
    {
        pPageElement = pElement->first_node("terrainPage");
        while(pPageElement)
        {
            processTerrainPage(pPageElement);
            pPageElement = pPageElement->next_sibling("terrainPage");
        }
        pElement = pElement->next_sibling("terrainPages");
    }
    mTerrainGroup->loadAllTerrains(true);

    // process blendmaps
    pElement = XMLNode->first_node("terrainPages");
    while(pElement)
    {
        pPageElement = pElement->first_node("terrainPage");
        while(pPageElement)
        {
            processBlendmaps(pPageElement);
            pPageElement = pPageElement->next_sibling("terrainPage");
        }
        pElement = pElement->next_sibling("terrainPages");
    }
    mTerrainGroup->freeTemporaryResources();
    //mTerrain->setPosition(mTerrainPosition);
     */
}

void DotSceneLoader::processTerrainPage(rapidxml::xml_node<>* XMLNode)
{
    std::string name = getAttrib(XMLNode, "name");
    int pageX = std::stoi(XMLNode->first_attribute("pageX")->value());
    int pageY = std::stoi(XMLNode->first_attribute("pageY")->value());
    float worldSize = getAttribReal(XMLNode, "worldSize");
    int mapSize = std::stoi(XMLNode->first_attribute("mapSize")->value());
    bool colourmapEnabled = getAttribBool(XMLNode, "colourmapEnabled");
    int colourmapTexturesize = std::stoi(XMLNode->first_attribute("colourmapTexturesize")->value());
    int layerCount = std::stoi(XMLNode->first_attribute("layerCount")->value());

    /*
    Ogre::String filename = mTerrainGroup->generateFilename(pageX, pageY);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(pageX, pageY);
    }
    else
    {
        rapidxml::xml_node<>* pElement;

        pElement = XMLNode->first_node("position");
        if(pElement)
            mTerrainPosition = parseVector3(pElement);

        Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(name + Ogre::String(".ohm"), "General" );
        size_t size = stream.get()->size();
        if(size != mapSize * mapSize * 4)
        {
            OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Size of stream does not match terrainsize!", "TerrainPage" );
        }
        float* buffer = OGRE_ALLOC_T(float, size, Ogre::MEMCATEGORY_GEOMETRY);
        stream->read(buffer, size);

        Ogre::Terrain::ImportData& imp = mTerrainGroup->getDefaultImportSettings();
        imp.terrainSize = mapSize;
        imp.worldSize = worldSize;
        imp.inputFloat = buffer;
        imp.inputImage = 0;
        imp.deleteInputData = true;
        imp.minBatchSize = 33;
        imp.maxBatchSize = 65;

        imp.layerList.resize(layerCount);

        int count = 0;

        // Process layers (*)
        rapidxml::xml_node<>* pTerrainLayer;
        rapidxml::xml_node<>* pTerrainTextures;
        rapidxml::xml_node<>* pTerrainTexture;
        pElement = XMLNode->first_node("layers");
        while(pElement)
        {
            pTerrainLayer = pElement->first_node("layer");
            while(pTerrainLayer)
            {
                int worldSize = Ogre::StringConverter::parseInt(pTerrainLayer->first_attribute("worldSize")->value());
                pTerrainTextures = pTerrainLayer->first_node("textures");
                pTerrainTexture = pTerrainTextures->first_node("texture");
                while(pTerrainTexture)
                {
                    imp.layerList[count].textureNames.push_back(getAttrib(pTerrainTexture,"name",""));
                    imp.layerList[count].worldSize = (Ogre::Real)worldSize;
                    pTerrainTexture = pTerrainTexture->next_sibling("texture");
                }
                count++;
                // do stuff
                pTerrainLayer = pTerrainLayer->next_sibling("layer");
            }
            pElement = pElement->next_sibling("layers");
        }

        mTerrainGroup->defineTerrain(pageX, pageY, &imp);
    }
     */
}

void DotSceneLoader::processBlendmaps(rapidxml::xml_node<>* XMLNode)
{
    int pageX = std::stoi(XMLNode->first_attribute("pageX")->value());
    int pageY = std::stoi(XMLNode->first_attribute("pageY")->value());

    /*
    Ogre::String filename = mTerrainGroup->generateFilename(pageX, pageY);
    // skip this is terrain page has been saved already
    if (!Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        rapidxml::xml_node<>* pElement;

        // Process blendmaps (*)
        std::vector<Ogre::String> blendMaps;
        rapidxml::xml_node<>* pBlendmap;
        pElement = XMLNode->first_node("blendMaps");
        pBlendmap = pElement->first_node("blendMap");
        while(pBlendmap)
        {
            blendMaps.push_back(getAttrib(pBlendmap, "texture",""));
            pBlendmap = pBlendmap->next_sibling("blendMap");
        }

        for(int j = 1;j < mTerrainGroup->getTerrain(pageX, pageY)->getLayerCount();j++)
        {
            Ogre::TerrainLayerBlendMap *blendmap = mTerrainGroup->getTerrain(pageX, pageY)->getLayerBlendMap(j);
            Ogre::Image img;
            img.load(blendMaps[j-1],"General");
            int blendmapsize = mTerrainGroup->getTerrain(pageX, pageY)->getLayerBlendMapSize();
            if(img.getWidth() != blendmapsize)
                img.resize(blendmapsize, blendmapsize);

            float *ptr = blendmap->getBlendPointer();
            Ogre::uint8 *data = static_cast<Ogre::uint8*>(img.getPixelBox().data);

            for(int bp = 0;bp < blendmapsize * blendmapsize;bp++)
                ptr[bp] = static_cast<float>(data[bp]) / 255.0f;

            blendmap->dirty();
            blendmap->update();
        }
    }
*/
}

void DotSceneLoader::processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    //! @todo Implement this
}

void DotSceneLoader::processOctree(rapidxml::xml_node<>* XMLNode)
{
    //! @todo Implement this
}

void DotSceneLoader::processLight(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    // Process attributes
    std::string name = getAttrib(XMLNode, "name");
    std::string id = getAttrib(XMLNode, "id");

    /*
    // Create the light
    Ogre::Light *pLight = mSceneMgr->createLight(name);
    if(pParent)
        pParent->attachObject(pLight);

    Ogre::String sValue = getAttrib(XMLNode, "type");
    if(sValue == "point")
        pLight->setType(Ogre::Light::LT_POINT);
    else if(sValue == "directional")
        pLight->setType(Ogre::Light::LT_DIRECTIONAL);
    else if(sValue == "spot")
        pLight->setType(Ogre::Light::LT_SPOTLIGHT);
    else if(sValue == "radPoint")
        pLight->setType(Ogre::Light::LT_POINT);

    pLight->setVisible(getAttribBool(XMLNode, "visible", true));
    pLight->setCastShadows(getAttribBool(XMLNode, "castShadows", true));

    rapidxml::xml_node<>* pElement;

    // Process position (?)
    pElement = XMLNode->first_node("position");
    if(pElement)
        pLight->setPosition(parseVector3(pElement));

    // Process normal (?)
    pElement = XMLNode->first_node("normal");
    if(pElement)
        pLight->setDirection(parseVector3(pElement));

    pElement = XMLNode->first_node("directionVector");
    if(pElement)
    {
        pLight->setDirection(parseVector3(pElement));
        mLightDirection = parseVector3(pElement);
    }

    // Process colourDiffuse (?)
    pElement = XMLNode->first_node("colourDiffuse");
    if(pElement)
        pLight->setDiffuseColour(parseColour(pElement));

    // Process colourSpecular (?)
    pElement = XMLNode->first_node("colourSpecular");
    if(pElement)
        pLight->setSpecularColour(parseColour(pElement));

    if(sValue != "directional")
    {
        // Process lightRange (?)
        pElement = XMLNode->first_node("lightRange");
        if(pElement)
            processLightRange(pElement, pLight);

        // Process lightAttenuation (?)
        pElement = XMLNode->first_node("lightAttenuation");
        if(pElement)
            processLightAttenuation(pElement, pLight);
    }
    // Process userDataReference (?)
    pElement = XMLNode->first_node("userDataReference");
    if(pElement)
        ;//processUserDataReference(pElement, pLight);
*/
}

void DotSceneLoader::processCamera(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent)
{
    // Process attributes
    std::string name = getAttrib(XMLNode, "name");
    std::string id = getAttrib(XMLNode, "id");
    float fov = getAttribReal(XMLNode, "fov", 45.f);
    float aspectRatio = getAttribReal(XMLNode, "aspectRatio", 1.3333f);
    std::string projectionType = getAttrib(XMLNode, "projectionType", "perspective");

    /*
    // Create the camera
    Ogre::Camera *pCamera = mSceneMgr->createCamera(name);

    //TODO: make a flag or attribute indicating whether or not the camera should be attached to any parent node.
    //if(pParent)
    //   pParent->attachObject(pCamera);

    // Set the field-of-view
    //! @todo Is this always in degrees?
    //pCamera->setFOVy(Ogre::Degree(fov));

    // Set the aspect ratio
    //pCamera->setAspectRatio(aspectRatio);

    // Set the projection type
    if(projectionType == "perspective")
        pCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
    else if(projectionType == "orthographic")
        pCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);

    rapidxml::xml_node<>* pElement;

    // Process clipping (?)
    pElement = XMLNode->first_node("clipping");
    if(pElement)
    {
        Ogre::Real nearDist = getAttribReal(pElement, "near");
        pCamera->setNearClipDistance(nearDist);

        Ogre::Real farDist =  getAttribReal(pElement, "far");
        pCamera->setFarClipDistance(farDist);
    }

    // Process position (?)
    pElement = XMLNode->first_node("position");
    if(pElement)
        pCamera->setPosition(parseVector3(pElement));

    // Process rotation (?)
    pElement = XMLNode->first_node("rotation");
    if(pElement)
        pCamera->setOrientation(parseQuaternion(pElement));

    // Process normal (?)
    pElement = XMLNode->first_node("normal");
    if(pElement)
        ;//!< @todo What to do with this element?

    // Process lookTarget (?)
    pElement = XMLNode->first_node("lookTarget");
    if(pElement)
        ;//!< @todo Implement the camera look target

    // Process trackTarget (?)
    pElement = XMLNode->first_node("trackTarget");
    if(pElement)
        ;//!< @todo Implement the camera track target

    // Process userDataReference (?)
    pElement = XMLNode->first_node("userDataReference");
    if(pElement)
        ;//!< @todo Implement the camera user data reference

    // construct a scenenode is no parent
    if(!pParent)
    {
        Ogre::SceneNode* pNode = mAttachNode->createChildSceneNode(name);
        pNode->setPosition(pCamera->getPosition());
        pNode->setOrientation(pCamera->getOrientation());
        pNode->scale(1,1,1);
    }
*/
}

void DotSceneLoader::processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode* pParent)
{
    // Construct the node's name
    std::string name = m_sPrependNode + getAttrib(XMLNode, "name");

    /*
    // Create the scene node
    Ogre::SceneNode *pNode;
    if(name.empty())
    {
        // Let Ogre choose the name
        if(pParent)
            pNode = pParent->createChildSceneNode();
        else
            pNode = mAttachNode->createChildSceneNode();
    }
    else
    {
        // Provide the name
        if(pParent)
            pNode = pParent->createChildSceneNode(name);
        else
            pNode = mAttachNode->createChildSceneNode(name);
    }

    // Process other attributes
    Ogre::String id = getAttrib(XMLNode, "id");
    bool isTarget = getAttribBool(XMLNode, "isTarget");

    rapidxml::xml_node<>* pElement;

    // Process position (?)
    pElement = XMLNode->first_node("position");
    if(pElement)
    {
        pNode->setPosition(parseVector3(pElement));
        pNode->setInitialState();
    }

    // Process rotation (?)
    pElement = XMLNode->first_node("rotation");
    if(pElement)
    {
        pNode->setOrientation(parseQuaternion(pElement));
        pNode->setInitialState();
    }

    // Process scale (?)
    pElement = XMLNode->first_node("scale");
    if(pElement)
    {
        pNode->setScale(parseVector3(pElement));
        pNode->setInitialState();
    }

    // Process lookTarget (?)
    pElement = XMLNode->first_node("lookTarget");
    if(pElement)
        processLookTarget(pElement, pNode);

    // Process trackTarget (?)
    pElement = XMLNode->first_node("trackTarget");
    if(pElement)
        processTrackTarget(pElement, pNode);

    // Process node (*)
    pElement = XMLNode->first_node("node");
    while(pElement)
    {
        processNode(pElement, pNode);
        pElement = pElement->next_sibling("node");
    }

    // Process entity (*)
    pElement = XMLNode->first_node("entity");
    while(pElement)
    {
        processEntity(pElement, pNode);
        pElement = pElement->next_sibling("entity");
    }

    // Process light (*)
    //pElement = XMLNode->first_node("light");
    //while(pElement)
    //{
    //   processLight(pElement, pNode);
    //   pElement = pElement->next_sibling("light");
    //}

    // Process camera (*)
    pElement = XMLNode->first_node("camera");
    while(pElement)
    {
        processCamera(pElement, pNode);
        pElement = pElement->next_sibling("camera");
    }

    // Process particleSystem (*)
    pElement = XMLNode->first_node("particleSystem");
    while(pElement)
    {
        processParticleSystem(pElement, pNode);
        pElement = pElement->next_sibling("particleSystem");
    }

    // Process billboardSet (*)
    pElement = XMLNode->first_node("billboardSet");
    while(pElement)
    {
        processBillboardSet(pElement, pNode);
        pElement = pElement->next_sibling("billboardSet");
    }

    // Process plane (*)
    pElement = XMLNode->first_node("plane");
    while(pElement)
    {
        processPlane(pElement, pNode);
        pElement = pElement->next_sibling("plane");
    }

    // Process userDataReference (?)
    pElement = XMLNode->first_node("userDataReference");
    if(pElement)
        processUserDataReference(pElement, pNode);
*/
}

/*
void DotSceneLoader::processLookTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    //! @todo Is this correct? Cause I don't have a clue actually

    // Process attributes
    Ogre::String nodeName = getAttrib(XMLNode, "nodeName");

    Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT;
    Ogre::String sValue = getAttrib(XMLNode, "relativeTo");
    if(sValue == "local")
        relativeTo = Ogre::Node::TS_LOCAL;
    else if(sValue == "parent")
        relativeTo = Ogre::Node::TS_PARENT;
    else if(sValue == "world")
        relativeTo = Ogre::Node::TS_WORLD;

    rapidxml::xml_node<>* pElement;

    // Process position (?)
    Ogre::Vector3 position;
    pElement = XMLNode->first_node("position");
    if(pElement)
        position = parseVector3(pElement);

    // Process localDirection (?)
    Ogre::Vector3 localDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;
    pElement = XMLNode->first_node("localDirection");
    if(pElement)
        localDirection = parseVector3(pElement);

    // Setup the look target
    try
    {
        if(!nodeName.empty())
        {
            Ogre::SceneNode *pLookNode = mSceneMgr->getSceneNode(nodeName);
            position = pLookNode->_getDerivedPosition();
        }

        pParent->lookAt(position, relativeTo, localDirection);
    }
    catch(Ogre::Exception & e)
    {
        Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error processing a look target!");
    }
}*/
/*
void DotSceneLoader::processTrackTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    // Process attributes
    Ogre::String nodeName = getAttrib(XMLNode, "nodeName");

    rapidxml::xml_node<>* pElement;

    // Process localDirection (?)
    Ogre::Vector3 localDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;
    pElement = XMLNode->first_node("localDirection");
    if(pElement)
        localDirection = parseVector3(pElement);

    // Process offset (?)
    Ogre::Vector3 offset = Ogre::Vector3::ZERO;
    pElement = XMLNode->first_node("offset");
    if(pElement)
        offset = parseVector3(pElement);

    // Setup the track target
    try
    {
        Ogre::SceneNode *pTrackNode = mSceneMgr->getSceneNode(nodeName);
        pParent->setAutoTracking(true, pTrackNode, localDirection, offset);
    }
    catch(Ogre::Exception &e)
    {
        Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error processing a track target!");
    }
}*/
/*
void DotSceneLoader::processEntity(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    // Process attributes
    Ogre::String name = getAttrib(XMLNode, "name");
    Ogre::String id = getAttrib(XMLNode, "id");
    Ogre::String meshFile = getAttrib(XMLNode, "meshFile");
    Ogre::String materialFile = getAttrib(XMLNode, "materialFile");
    bool isStatic = getAttribBool(XMLNode, "static", false);;
    bool castShadows = getAttribBool(XMLNode, "castShadows", true);
    static int counter = 0;

    // TEMP: Maintain a list of static and dynamic objects
    if(isStatic)
        staticObjects.push_back(name);
    else
        dynamicObjects.push_back(name);

    rapidxml::xml_node<>* pElement;

    // Process vertexBuffer (?)
    pElement = XMLNode->first_node("vertexBuffer");
    if(pElement)
        ;//processVertexBuffer(pElement);

    // Process indexBuffer (?)
    pElement = XMLNode->first_node("indexBuffer");
    if(pElement)
        ;//processIndexBuffer(pElement);

    // Create the entity
    Ogre::Entity *pEntity = 0;
    try
    {


        //
         // Controllare se l'entity già esisteva era troppo disturbo
         //
        Ogre::ResourcePtr m =  Ogre::MeshManager::getSingleton().getByName(meshFile, m_sGroupName);
        if(m.isNull()){
            Ogre::MeshManager::getSingleton().load(meshFile, m_sGroupName);

        }else {
            name = name + std::to_string(++counter);
        }

        pEntity = mSceneMgr->createEntity(name, meshFile);
        pEntity->setCastShadows(castShadows);
        pParent->attachObject(pEntity);

        if(!materialFile.empty())
            pEntity->setMaterialName(materialFile);
    }
    catch(Ogre::Exception &e)
    {
        Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error loading an entity!");
        Ogre::LogManager::getSingletonPtr()->logMessage(e.getDescription());
    }

    // Process userDataReference (?)
    pElement = XMLNode->first_node("userDataReference");
    if(pElement)
        processUserDataReference(pElement, pEntity);


}*/
/*
void DotSceneLoader::processParticleSystem(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    // Process attributes
    Ogre::String name = getAttrib(XMLNode, "name");
    Ogre::String id = getAttrib(XMLNode, "id");
    Ogre::String file = getAttrib(XMLNode, "file");

    // Create the particle system
    try
    {
        Ogre::ParticleSystem *pParticles = mSceneMgr->createParticleSystem(name, file);
        pParent->attachObject(pParticles);
    }
    catch(Ogre::Exception & e)
    {
        Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error creating a particle system!");
    }
}*/
/*
void DotSceneLoader::processBillboardSet(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    //! @todo Implement this
}

void DotSceneLoader::processPlane(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
    //! @todo Implement this
}*/
void DotSceneLoader::processFog(rapidxml::xml_node<>* XMLNode)
{
    // Process attributes
    double expDensity = getAttribReal(XMLNode, "density", 0.001);
    double linearStart = getAttribReal(XMLNode, "start", 0.0);
    double linearEnd = getAttribReal(XMLNode, "end", 1.0);

    /*
    Ogre::FogMode mode = Ogre::FOG_NONE;
    Ogre::String sMode = getAttrib(XMLNode, "mode");
    if(sMode == "none")
        mode = Ogre::FOG_NONE;
    else if(sMode == "exp")
        mode = Ogre::FOG_EXP;
    else if(sMode == "exp2")
        mode = Ogre::FOG_EXP2;
    else if(sMode == "linear")
        mode = Ogre::FOG_LINEAR;

    rapidxml::xml_node<>* pElement;

    // Process colourDiffuse (?)
    Ogre::ColourValue colourDiffuse = Ogre::ColourValue::White;
    pElement = XMLNode->first_node("colour");
    if(pElement)
        colourDiffuse = parseColour(pElement);

    // Setup the fog
    mSceneMgr->setFog(mode, colourDiffuse, expDensity, linearStart, linearEnd);
    */
}

void DotSceneLoader::processSkyBox(rapidxml::xml_node<>* XMLNode)
{
    using namespace Magnum::Math;

    // Process attributes
    bool active = getAttribBool(XMLNode, "active", false);
    if (not active) return;

    std::string material = getAttrib(XMLNode, "material", "BaseWhite");
    double distance = getAttribReal(XMLNode, "distance", 5000);
    bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);

    rapidxml::xml_node<>* pElement;

    // Process rotation (?)
    auto rotation = Quaternion<float>{ IdentityInit };
    pElement = XMLNode->first_node("rotation");
    if (pElement) {
        rotation = parseQuaternion(pElement);
    }

    /*
    // Setup the sky box
    mSceneMgr->setSkyBox(true, material, distance, drawFirst, rotation, m_sGroupName);
     */
}

void DotSceneLoader::processSkyDome(rapidxml::xml_node<>* XMLNode)
{
    // Process attributes
    std::string material = XMLNode->first_attribute("material")->value();
    double curvature = getAttribReal(XMLNode, "curvature", 10);
    double tiling = getAttribReal(XMLNode, "tiling", 8);
    double distance = getAttribReal(XMLNode, "distance", 4000);
    bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);

    rapidxml::xml_node<>* pElement;

    // Process rotation (?)
    auto rotation = Magnum::Quaternion{ Magnum::Math::IdentityInit };
    pElement = XMLNode->first_node("rotation");
    if (pElement) {
        rotation = parseQuaternion(pElement);
    }

    /*
    // Setup the sky dome
    mSceneMgr->setSkyDome(true, material, curvature, tiling, distance, drawFirst, rotation, 16, 16, -1, m_sGroupName);
     */
}

void DotSceneLoader::processSkyPlane(rapidxml::xml_node<>* XMLNode)
{
    // Process attributes
    std::string material = getAttrib(XMLNode, "material");
    float planeX = getAttribReal(XMLNode, "planeX", 0.f);
    float planeY = getAttribReal(XMLNode, "planeY", -1.f);
    float planeZ = getAttribReal(XMLNode, "planeX", 0.f);
    float planeD = getAttribReal(XMLNode, "planeD", 5000.f);
    float scale = getAttribReal(XMLNode, "scale", 1000.f);
    float bow = getAttribReal(XMLNode, "bow", 0.f);
    float tiling = getAttribReal(XMLNode, "tiling", 10.f);
    bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);

    /*
    // Setup the sky plane
    Ogre::Plane plane;
    plane.normal = Ogre::Vector3(planeX, planeY, planeZ);
    plane.d = planeD;
    mSceneMgr->setSkyPlane(true, plane, material, scale, tiling, drawFirst, bow, 1, 1, m_sGroupName);
     */
}

void DotSceneLoader::processClipping(rapidxml::xml_node<>* XMLNode)
{
    //! @todo Implement this

    // Process attributes
    double fNear = getAttribReal(XMLNode, "near", 0);
    double fFar = getAttribReal(XMLNode, "far", 1);
}
/*
void DotSceneLoader::processLightRange(rapidxml::xml_node<>* XMLNode, Ogre::Light* pLight)
{
    // Process attributes
    Ogre::Real inner = getAttribReal(XMLNode, "inner");
    Ogre::Real outer = getAttribReal(XMLNode, "outer");
    Ogre::Real falloff = getAttribReal(XMLNode, "falloff", 1.0);

    // Setup the light range
    pLight->setSpotlightRange(Ogre::Angle(inner), Ogre::Angle(outer), falloff);
}

void DotSceneLoader::processLightAttenuation(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight)
{
    // Process attributes
    Ogre::Real range = getAttribReal(XMLNode, "range");
    Ogre::Real constant = getAttribReal(XMLNode, "constant");
    Ogre::Real linear = getAttribReal(XMLNode, "linear");
    Ogre::Real quadratic = getAttribReal(XMLNode, "quadratic");

    // Setup the light attenuation
    pLight->setAttenuation(range, constant, linear, quadratic);
}*/


std::string DotSceneLoader::getAttrib(rapidxml::xml_node<>* XMLNode, const std::string& attrib, const std::string& defaultValue)
{
    auto* first = XMLNode->first_attribute(attrib.c_str());
    return (first)
        ? first->value()
        : defaultValue;
}

float DotSceneLoader::getAttribReal(rapidxml::xml_node<>* XMLNode, const std::string& attrib, float defaultValue)
{
    auto* first = XMLNode->first_attribute(attrib.c_str());
    return (first)
        ? std::stof(first->value())
        : defaultValue;
}

bool DotSceneLoader::getAttribBool(rapidxml::xml_node<>* XMLNode, const std::string &attrib, bool defaultValue)
{
    auto* first = XMLNode->first_attribute(attrib.c_str());
    return (first)
        ? std::string{ first->value() } == "true"
        : defaultValue;
}

Magnum::Vector3 DotSceneLoader::parseVector3(rapidxml::xml_node<>* XMLNode)
{
    return Magnum::Vector3{
        std::stof(XMLNode->first_attribute("x")->value()),
        std::stof(XMLNode->first_attribute("y")->value()),
        std::stof(XMLNode->first_attribute("z")->value())
    };
}

Magnum::Quaternion DotSceneLoader::parseQuaternion(rapidxml::xml_node<>* XMLNode)
{
    //! @todo cleanup

    Magnum::Quaternion orientation;

    if (XMLNode->first_attribute("qx"))
    {
        orientation.vector().x() = std::stof(XMLNode->first_attribute("qx")->value());
        orientation.vector().y() = std::stof(XMLNode->first_attribute("qy")->value());
        orientation.vector().z() = std::stof(XMLNode->first_attribute("qz")->value());
        orientation.scalar() = std::stof(XMLNode->first_attribute("qw")->value());
    }
    if (XMLNode->first_attribute("qw"))
    {
        orientation.scalar() = std::stof(XMLNode->first_attribute("qw")->value());
        orientation.vector().x() = std::stof(XMLNode->first_attribute("qx")->value());
        orientation.vector().y() = std::stof(XMLNode->first_attribute("qy")->value());
        orientation.vector().z() = std::stof(XMLNode->first_attribute("qz")->value());
    }
    else if (XMLNode->first_attribute("axisX"))
    {
        Magnum::Vector3 axis{
            std::stof(XMLNode->first_attribute("axisX")->value()),
            std::stof(XMLNode->first_attribute("axisY")->value()),
            std::stof(XMLNode->first_attribute("axisZ")->value())
        };
        float angle = std::stof(XMLNode->first_attribute("angle")->value());
        orientation = Magnum::Quaternion{ axis, angle };
    }
    else if (XMLNode->first_attribute("angleX"))
    {
        orientation = Magnum::Quaternion{
            Magnum::Vector3{
                std::stof(XMLNode->first_attribute("angleX")->value()),
                std::stof(XMLNode->first_attribute("angleY")->value()),
                std::stof(XMLNode->first_attribute("angleZ")->value())
        } };
    }
    else if (XMLNode->first_attribute("x"))
    {
        orientation.vector().x() = std::stof(XMLNode->first_attribute("x")->value());
        orientation.vector().y() = std::stof(XMLNode->first_attribute("y")->value());
        orientation.vector().z() = std::stof(XMLNode->first_attribute("z")->value());
        orientation.scalar() = std::stof(XMLNode->first_attribute("w")->value());
    }
    else if (XMLNode->first_attribute("w"))
    {
        orientation.scalar() = std::stof(XMLNode->first_attribute("w")->value());
        orientation.vector().x() = std::stof(XMLNode->first_attribute("x")->value());
        orientation.vector().y() = std::stof(XMLNode->first_attribute("y")->value());
        orientation.vector().z() = std::stof(XMLNode->first_attribute("z")->value());
    }

    return orientation;
}

Magnum::Color4 DotSceneLoader::parseColour(rapidxml::xml_node<>* XMLNode)
{
    return Magnum::Color4{
        std::stof(XMLNode->first_attribute("r")->value()),
        std::stof(XMLNode->first_attribute("g")->value()),
        std::stof(XMLNode->first_attribute("b")->value()),
        XMLNode->first_attribute("a") != nullptr ? std::stof(XMLNode->first_attribute("a")->value()) : 1
    };
}

std::string DotSceneLoader::getProperty(const std::string& ndNm, const std::string& prop)
{
    for (unsigned int i = 0 ; i < nodeProperties.size(); i++ )
    {
        if (nodeProperties[i].nodeName == ndNm && nodeProperties[i].propertyNm == prop)
        {
            return nodeProperties[i].valueName;
        }
    }

    return "";
}

/*
void DotSceneLoader::processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::Entity* pEntity)
{
    std::string str = XMLNode->first_attribute("id")->value();
    pEntity->setUserAny(Ogre::Any(str));
}
*/
