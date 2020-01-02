#include "ResourceManager.h"
#include"MapManager.h"
#include"PlayScene.h"
#include"Sound.h"
ResourceManager * ResourceManager::__instance = NULL;






ResourceManager *ResourceManager::GetInstance()
{
	if (__instance == NULL) __instance = new ResourceManager();
	return __instance;
}

// Kiểm tra xem có dữ liệu grid chưa, chưa thì build ra vì Map ediptor không thay đổi
// được grid size của object layer
void ResourceManager::BuildGrid(const std::string& filePath)
{


	char* fileLoc = new char[filePath.size() + 1]; // 1

	   //TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("map");
	xml_attribute<>* gridAtribute = rootNode->first_attribute("CellSize");
	if (gridAtribute == NULL)
	{
		xml_attribute<>* atribute = doc.allocate_attribute("CellSize", "256");
		rootNode->append_attribute(atribute);

	}
	else {
		return;
	}
	for (xml_node<>* child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) {

		int id = std::atoi(child->first_attribute("id")->value()); // lay ID Object group
		std::string objectGroupName = std::string(child->first_attribute("name")->value()); // lay ten object group
		for (xml_node<>* smailchild = child->first_node(); smailchild; smailchild = smailchild->next_sibling()) {
			int x = 0, y = 0, w = 0, h = 0;
			x = std::stof(smailchild->first_attribute("x")->value());
			y = std::stof(smailchild->first_attribute("y")->value());
			w = std::atoi(smailchild->first_attribute("width")->value());
			h = std::atoi(smailchild->first_attribute("height")->value());
			int scid = std::atoi(smailchild->first_attribute("id")->value()); // lay ID
			
		
			xml_attribute<>* cellX = doc.allocate_attribute("cellcol", "256");
			smailchild->append_attribute(cellX);
			


		}



	}


	std::ofstream theFile(filePath.c_str());
	theFile << doc;
	theFile.close();
}
void ResourceManager::LoadData(const std::string& filePath)
{
	DebugOut(L"[LOADER] Load resource \n");
	char* fileLoc = new char[filePath.size() + 1]; // 1

		   //TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("game");

	CTextures* textures = CTextures::GetInstance();
	
	//load texture
	xml_node<>* texturesNode = rootNode->first_node("textures");
	for (xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling()){
		int id = std::atoi(child->first_attribute("id")->value());
		int red = std::atoi(child->first_attribute("red")->value());
		int green = std::atoi(child->first_attribute("green")->value());
		int blue = std::atoi(child->first_attribute("blue")->value());
		std::string path = std::string(child->first_attribute("path")->value()); // lay path
		std::wstring cover = std::wstring(path.begin(), path.end());
		textures->Add(id, cover.c_str(), D3DCOLOR_XRGB(red,green,blue));
	}



	//Load map
	MapManager* maps = MapManager::GetInstance();
	xml_node<>* mapsNode = rootNode->first_node("maps");
	for (xml_node<>* child = mapsNode->first_node(); child; child = child->next_sibling()) {
		std::string mapId = std::string(child->first_attribute("id")->value());
		int texId = std::atoi(child->first_attribute("texid")->value());
		std::string path = std::string(child->first_attribute("path")->value()); // lay path
		std::wstring cover = std::wstring(path.begin(), path.end());
		maps->AddMap(mapId, path, textures->Get(texId));
		//BuildGrid(path);
	}

	//load Sprite
	xml_node<>* spritesNode = rootNode->first_node("sprites");
	for (xml_node<>* child = spritesNode->first_node(); child; child = child->next_sibling()) {
		int texId = std::atoi(child->first_attribute("texid")->value());
		std::string path = std::string(child->first_attribute("path")->value()); // lay path
		LoadSprites(path, textures->Get(texId));
	}

	CAnimations* animations = CAnimations::GetInstance();
	//load animation
	xml_node<>* animationsNode = rootNode->first_node("animations");
	for (xml_node<>* child = animationsNode->first_node(); child; child = child->next_sibling()) {
		std::string path = std::string(child->first_attribute("path")->value()); // lay path
		LoadAnimations(path, animations);
	}

	//load sound
	Sound* sound = Sound::GetInstance();
	xml_node<>* soundNode = rootNode->first_node("sounds");
	for (xml_node<>* child = soundNode->first_node(); child; child = child->next_sibling()) {
		std::string path = std::string(child->first_attribute("path")->value()); // lay path
		int id = std::atoi(child->first_attribute("id")->value());
		std::wstring cover = std::wstring(path.begin(), path.end());
		LPTSTR cpath = (LPTSTR)cover.c_str();
		eSound val = static_cast<eSound>(id);
		sound->AddSound(val, cpath);
	}

	
}
void ResourceManager::LoadSceneData(const std::string& filePath, std::unordered_map<int, MiniScene*>& miniScene)
{
	char* fileLoc = new char[filePath.size() + 1]; // 1

		   //TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	
	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("game");
	//load miniscene
	xml_node<>* sceneNode = rootNode->first_node("scene");
	xml_node<>* miniSceneNode = sceneNode->first_node("playscene");
	for (xml_node<>* child = miniSceneNode->first_node(); child; child = child->next_sibling()) 
	{
		MiniScene* mscene = new MiniScene();
		int ID = std::atoi(child->first_attribute("ID")->value());
		int preID = std::atoi(child->first_attribute("preID")->value());
		int nextID = std::atoi(child->first_attribute("nextID")->value());
		int revivalScene = std::atoi(child->first_attribute("revivalScene")->value());
		int area = std::atoi(child->first_attribute("area")->value());
		int entryPoint = std::atoi(child->first_attribute("entryPoint")->value());
		int stageID = std::atoi(child->first_attribute("stateID")->value());
		std::string name = std::string(child->first_attribute("name")->value()); // lay path
		std::string map = std::string(child->first_attribute("map")->value()); // lay path
		mscene->id = ID;
		mscene->mapID = map;
		mscene->name = name;
		mscene->nextMiniScene = nextID;
		mscene->preMiniScene = preID;
		mscene->revivalSceneID = revivalScene;
		mscene->state = stageID;
		mscene->areaID = area;
		mscene->entryPointID = entryPoint;
		miniScene.insert(std::make_pair(ID, mscene));
	}
}
void ResourceManager::LoadSprites(const std::string & filePath, LPDIRECT3DTEXTURE9 tex)
{

	
	char* fileLoc = new char[filePath.size() + 1]; // 1

		   //TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("resource");
	xml_node<>* spriteSheetNode = rootNode->first_node("spritesheet");
	xml_node<>* spriteNode = spriteSheetNode->first_node("sprite");
	xml_node<>* frameNode = spriteNode->first_node("frame");
	//DebugOut(L"Left=%d top=%d right=%d bottom=%d", l, t, r, b);
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	for (xml_node<> *child = spriteSheetNode->first_node(); child; child = child->next_sibling()) {
		string id = std::string(child->first_attribute("ID")->value()); // lay ID
		for (xml_node<> *smailchild = child->first_node(); smailchild; smailchild = smailchild->next_sibling()) {
			// lay thong tin vi tri
			int l = std::atoi(smailchild->first_attribute("x")->value());
			int t = std::atoi(smailchild->first_attribute("y")->value());
			int width = std::atoi(smailchild->first_attribute("width")->value());
			int height = std::atoi(smailchild->first_attribute("height")->value());
			int r = l + width;
			int b = t + height;
			sprites->Add(id, l, t, r, b, tex);
		}

	}
	

	

	
}
void ResourceManager::LoadAnimations(const std::string & filePath, CAnimations* animations)
{
	char* fileLoc = new char[filePath.size() + 1]; // 1

		   //TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("resource");
	xml_node<>* listaniNode = rootNode->first_node("animations");

	LPANIMATION ani;
	for (xml_node<> *child = listaniNode->first_node(); child; child = child->next_sibling())
	{
		string id = std::string(child->first_attribute("ID")->value()); // lay ID
		int defaulttime = std::atoi(child->first_attribute("defaulttime")->value());
		ani = new CAnimation(defaulttime);
		for (xml_node<> *smailchild = child->first_node(); smailchild; smailchild = smailchild->next_sibling()) 
		{
			
			string spriteId = std::string(smailchild->first_attribute("spriteID")->value()); // lay ID
			ani->Add(spriteId);
		}
		animations->Add(id, ani);
	}
}
ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}
