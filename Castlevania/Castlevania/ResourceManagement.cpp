#include "ResourceManagement.h"


ResourceManagement * ResourceManagement::__instance = NULL;






ResourceManagement *ResourceManagement::GetInstance()
{
	if (__instance == NULL) __instance = new ResourceManagement();
	return __instance;
}
void ResourceManagement::LoadSprites(const std::string & filePath)
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
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(0);
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
			sprites->Add(id, l, t, r, b, texSimon);
		}

	}
	

	

	
}
ResourceManagement::ResourceManagement()
{
}


ResourceManagement::~ResourceManagement()
{
}
