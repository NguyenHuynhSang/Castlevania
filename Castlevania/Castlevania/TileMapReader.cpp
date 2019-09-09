//#include "TileMapReader.h"
//#include"debug.h"
//#include <sstream>  
//#include <string>
//TileMapReader * TileMapReader::__instance = NULL;
//
//
////Đọc từng tilesheep
//std::shared_ptr<TileSheetInfo> TileMapReader::ReadTileSheet(xml_node<>* rootNode)
//{
//	TileSheetInfo tileSheetData;
//
//	// Traverse to the tile set node.
//	xml_node<>* tilesheetNode = rootNode->first_node("tileset"); 
//
//		//TODO: add error checking to ensure these values actually exist.
//		//TODO: add support for multiple tile sets.
//		//TODO: implement this.
//		int firstid = std::atoi(tilesheetNode->first_attribute("firstgid")->value());
//		string name = std::string(tilesheetNode->first_attribute("name")->value());
//	// Build the tile set data.
//	tileSheetData.tileWidth =

//		std::atoi(tilesheetNode->first_attribute("tilewidth")->value());
//
//	int sizeTest= std::atoi(tilesheetNode->first_attribute("tilewidth")->value());
//	tileSheetData.tileHeight =
//		std::atoi(tilesheetNode->first_attribute("tileheight")->value());
//	int tileCount =
//		std::atoi(tilesheetNode->first_attribute("tilecount")->value());
//	tileSheetData.columns =
//		std::atoi(tilesheetNode->first_attribute("columns")->value());
//	tileSheetData.rows = tileCount / tileSheetData.columns;
//
//	xml_node<>* imageNode = tilesheetNode->first_node("image");
//
//	/*DebugOut(L"tilewidth=%d \n", sizeTest);
//	DebugOut(L"tileheight=%d \n", tileSheetData.tileHeight);
//	DebugOut(L"tilecount=%d \n", tileCount);
//	DebugOut(L"columns=%d \n", tileSheetData.columns);
//	DebugOut(L"name=%d \n", name);*/
//	//tileSheetData.textureID =// std::string(imageNode->first_attribute("source")->value())
//		
//	//test
//
//	/*xml_node<>* layerNode = rootNode->first_node("layer");
//	xml_node<>* dataNode = layerNode->first_node("data");
//	xml_node<>* gridnode = dataNode->first_node("tile");*/
//	
//	
//
//
//	/*for (xml_node<> *child = dataNode->first_node(); child; child = child->next_sibling()) {
//		int a = std::stoi(child->first_attribute("gid")->value());
//		DebugOut(L"Grid=%d \n", a);
//	}*/
//	
//
//	//TODO: add error checking - we want to output a 
//	//message if the texture is not found.
//
//	tileSheetData.textureSize.x =
//		std::atoi(imageNode->first_attribute("width")->value());
//	tileSheetData.textureSize.y =
//		std::atoi(imageNode->first_attribute("height")->value());
//
//	return std::make_shared<TileSheetInfo>(tileSheetData);
//}
//
//std::shared_ptr<MapTiles> TileMapReader::ReadMapTiles(xml_node<>* rootNode)
//{
//	std::shared_ptr<TileSheetInfo> tileSheetInfo = ReadTileSheet(rootNode);
//
//	std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();
//
//	
//	// We loop through each layer in the XML document.
//	for (xml_node<> * node = rootNode->first_node("layer");
//		node; node = node->next_sibling())
//	{
//		std::pair<std::string, std::shared_ptr<Layer>> mapLayer=
//			ReadLayer(node, tileSheetInfo);
//
//		map->emplace(mapLayer);
//	}
//
//	return map;
//}
//
//std::pair<std::string, std::shared_ptr<Layer>> TileMapReader::ReadLayer(xml_node<>* layerNode, std::shared_ptr<TileSheetInfo> tileSheetInfo)
//{
//	TileSet tileSet;
//	std::shared_ptr<Layer> layer = std::make_shared<Layer>();
//
//	int width = std::atoi(layerNode->first_attribute("width")->value());
//	int height = std::atoi(layerNode->first_attribute("height")->value());
//
//	xml_node<>* dataNode = layerNode->first_node("data");
//	char* mapIndices = dataNode->value();
//
//	std::stringstream fileStream(mapIndices);
//
//	int count = 0;
//
//	std::string line;
//	while (fileStream.good())
//	{
//		std::string substr="1";
//		//std::getline(fileStream, substr, ',');
//
//	
//
//		int tileId = std::stoi(substr); // 3
//
//		if (tileId != 0) // 4
//		{
//			auto itr = tileSet.find(tileId); // 5
//			if (itr == tileSet.end()) // 6
//			{
//				int textureX = tileId % tileSheetInfo->columns - 1;
//				int textureY = tileId / tileSheetInfo->columns;
//
//		
//				std::shared_ptr<TileInfo> tileInfo =
//					std::make_shared<TileInfo>(
//						tileSheetInfo->textureID, tileId,
//						CRectangle(
//							textureX * tileSheetInfo->tileWidth,
//							textureY * tileSheetInfo->tileHeight,
//							tileSheetInfo->textureSize.x,
//							tileSheetInfo->textureSize.y)
//						);
//				itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
//			}
//
//			std::shared_ptr<Tile> tile = std::make_shared<Tile>();
//
//			// Bind properties of a tile from a set.
//			tile->tileProperties = itr->second; // 7
//			tile->x = count % width - 1;
//			tile->y = count / width;
//
//
//			layer->emplace_back(tile); // 8
//		}
//		count++;
//	}
//	const std::string layerName = layerNode->first_attribute("name")->value();
//	return std::make_pair(layerName, layer);
//}
//
//
//
//TileMapReader *TileMapReader::GetInstance()
//{
//	if (__instance == NULL) __instance = new TileMapReader();
//	return __instance;
//}
//
//
//
//TileMapReader::TileMapReader()
//{
//}
//
//std::vector<std::shared_ptr<TileObjects>> TileMapReader::Parse(const std::string & file,
//	D3DXVECTOR2 offset)
//{
//	char* fileLoc = new char[file.size() + 1]; // 1
//
//	   //TODO: make multi format version of string copy
//	#ifdef MACOS
//		strlcpy(fileLoc, file.c_str(), file.size() + 1);
//	#else
//		strcpy_s(fileLoc, file.size() + 1, file.c_str());
//	#endif 
//
//	//TODO: error checking - check file exists before attempting open.
//	rapidxml::file<> xmlFile(fileLoc);
//	rapidxml::xml_document<> doc;
//	doc.parse<0>(xmlFile.data());
//	xml_node<>* rootNode = doc.first_node("map");
//
//		// Loads tile layers from XML.
//		std::shared_ptr<MapTiles> tiles = ReadMapTiles(rootNode);
//
//	// We need these to calculate the tiles position in world space
//	int tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
//	int tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
//	int mapsizeX = std::atoi(rootNode->first_attribute("width")->value());
//	int mapsizeY = std::atoi(rootNode->first_attribute("height")->value());
//
//	// This will contain all of our tiles as objects.
//	std::vector<std::shared_ptr<TileObjects>> tileObjects;
//
//	// 2
//	// We iterate through each layer in the tile map
//	for (const auto& layer : *tiles)
//	{
//		// And each tile in the layer
//		for (const auto& tile : *layer.second)
//		{
//			std::shared_ptr<TileInfo> tileInfo=tile->tileProperties;
//
//			std::shared_ptr<TileObjects> tileObject = std::make_shared<TileObjects>();
//
//			//TODO: tile scale should be set at the data level.
//			const unsigned int tileScale = 3;
//
//			//// Allocate sprite.
//			//auto sprite = tileObject->AddComponent<C_Sprite>();
//			//sprite->SetTextureAllocator(&textureAllocator);
//			//sprite->Load(tileInfo->textureID);
//			//sprite->SetTextureRect(tileInfo->textureRect);
//			//sprite->SetScale(tileScale, tileScale);
//			//// Calculate world position.
//			//float x = tile->x * tileSizeX * tileScale + offset.x;
//			//float y = tile->y * tileSizeY * tileScale + offset.y;
//			//tileObject->transform->SetPosition(x, y);
//
//			// Add new tile Object to the collection.
//			tileObjects.emplace_back(tileObject);
//		}
//	}
//
//	return tileObjects;
//}
//
//void TileMapReader::TestReadXML(const std::string& file, D3DXVECTOR2 offset) {
//	
//	this->Parse(file, offset);
//}
//
//TileMapReader::~TileMapReader()
//{
//}
