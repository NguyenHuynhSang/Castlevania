#include "ResourceManagement.h"
#include"MapManager.h"

ResourceManagement * ResourceManagement::__instance = NULL;






ResourceManagement *ResourceManagement::GetInstance()
{
	if (__instance == NULL) __instance = new ResourceManagement();
	return __instance;
}
void ResourceManagement::LoadData(const std::string& filePath)
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

}
void ResourceManagement::LoadSprites(const std::string & filePath, LPDIRECT3DTEXTURE9 tex)
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
void ResourceManagement::LoadAnimations(const std::string & filePath, CAnimations* animations)
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
ResourceManagement::ResourceManagement()
{
}


ResourceManagement::~ResourceManagement()
{
}
