#include "CTileMap.h"
#include"define.h"

CTileMap * CTileMap::__instance = NULL;

CTileMap *CTileMap::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMap();
	return __instance;
}


void CTileMap::LoadMap(const std::string& filePath)
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
	//lấy thông tin map
	int mapCol = std::atoi(rootNode->first_attribute("width")->value());
	int mapRow = std::atoi(rootNode->first_attribute("height")->value());
	int tilewidth = std::atoi(rootNode->first_attribute("tilewidth")->value());
	int tileheight = std::atoi(rootNode->first_attribute("tileheight")->value());
	this->mapCol = mapCol;
	this->mapRow = mapRow;
	this->tileWidth = tilewidth;
	this->tileHeight = tileheight;
	//lấy thông tin tilesheet
	xml_node<>* tilesetNode = rootNode->first_node("tileset");
	string tilesetName = std::string(tilesetNode->first_attribute("name")->value());
	int columns = std::atoi(tilesetNode->first_attribute("columns")->value());
	int tilecount = std::atoi(tilesetNode->first_attribute("tilecount")->value());
	int tilesetrow = tilecount % columns == 0 ? tilecount / columns : tilecount / columns + 1;
	this->tileSheetCol = columns;
	this->tileSheetRow = tilesetrow;




	matrix = new int*[mapRow];
	for (int i = 0; i < mapRow; i++)
	{
		matrix[i] = new int[mapCol];
	}

	xml_node<>* layerNode = rootNode->first_node("layer");
	xml_node<>* dataNode = layerNode->first_node("data");
	xml_node<>* gridnode = dataNode->first_node("tile");



	int i = 0, j = 0;
	//matran tile
	for (xml_node<> *child = dataNode->first_node(); child; child = child->next_sibling()) {
		int n = std::stoi(child->first_attribute("gid")->value());
		//DebugOut(L"Grid=%d \n", n);
		matrix[i][j] = n;
		//DebugOut(L"M[%d][%d]=%d  \n", i, j, n);
		j++;
		if (j > mapCol - 1)
		{
			i++;
			j = 0;
		}
	}
	int id = 1;		// id of tileset
	CTextures* tex = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texTileSet = tex->Get(1000);

	for (int i = 0; i < this->tileSheetRow; i++)
	{
		for (int j = 0; j < this->tileSheetCol; j++)
		{

			CSprites::GetInstance()->Add(std::to_string(id), j*this->tileHeight, i*this->tileHeight, j*this->tileHeight + this->tileHeight, i*this->tileHeight + this->tileHeight, texTileSet);
			id++;
		}
	}



}
bool istrue = true;
void CTileMap::Render()
{
	float camX, camY;
	CGame::GetInstance()->GetCamera(camX, camY);
	// lấy ra cột đầu và cột cuối trong Viewport ;
	int beginCol = ((int)camX) / 32;
	//+1 vì nếu vẽ vừa đủ cột cuối cùng mỗi khi render sẽ nhấp nháy
	int endCol = ((int)camX + SCREEN_WIDTH) / 32 + 1;
	int beginRow = (int)camY / 32;
	for (int i = beginRow; i < mapRow; i++)
	{
		for (int j = beginCol; j < endCol; j++)
		{
			int id = matrix[i][j];
			CSprites::GetInstance()->Get(std::to_string(id))->Draw(0, j*this->tileHeight, i*this->tileHeight + GAME_WORLD_Y);


		}
	}

}

void CTileMap::LoadObjects(const std::string& filePath)
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
	//xml_node<>* tileset = rootNode->first_node("tileset");
	LPTILEOBJECT object;
	ObjectGroup*listobject = ObjectGroup::GetInstance();
	for (xml_node<> *child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) {
		int id = std::atoi(child->first_attribute("id")->value()); // lay ID
		vector<LPTILEOBJECT> ObjectInGroup;
		object = new TileObject();
		for (xml_node<> *smailchild = child->first_node(); smailchild; smailchild = smailchild->next_sibling()) {
			int x = 0, y = 0, w = 0, h = 0;
			x = std::atoi(smailchild->first_attribute("x")->value());
			y = std::atoi(smailchild->first_attribute("y")->value());
			w = std::atoi(smailchild->first_attribute("width")->value());
			h = std::atoi(smailchild->first_attribute("height")->value());
			int scid = std::atoi(smailchild->first_attribute("id")->value()); // lay ID
			object = new TileObject(scid, x, y, w, h);
			listobject->Add(id, object);
			ObjectInGroup.push_back(listobject->GetTileObject(id));	
		}
		this->listObject.insert(std::make_pair(id, ObjectInGroup)); // 
	}
	
	/*for (const auto& entity : this->listObject) {
		DebugOut(L" ===============ID =%d \n", entity.first);
		for (const auto& child : entity.second) {
			DebugOut(L" ID =%d \n", child->GetId());
		}
	}*/

}

CTileMap::CTileMap()
{
}


CTileMap::~CTileMap()
{
}
