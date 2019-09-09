//#pragma once
//#include"TileSheet.h"
//#include"Textures.h"
//#include<memory>
//#include"TileObjects.h"
//#include<Windows.h>
//class TileMapReader
//{
//private:
//	std::shared_ptr<TileSheetInfo> ReadTileSheet(xml_node<>* rootNode);
//	std::shared_ptr<MapTiles> ReadMapTiles(xml_node<>* rootNode);
//	std::pair<std::string, std::shared_ptr<Layer>> 
//		ReadLayer(
//			xml_node<>* layerNode, std::shared_ptr<TileSheetInfo> tileSheetInfo
//		);
//	static TileMapReader * __instance;
//public:
//	TileMapReader(CTextures * textures);
//	TileMapReader();
//	std::vector<std::shared_ptr<TileObjects>>
//		Parse(const std::string& file, D3DXVECTOR2 offset);
//	void TestReadXML(const std::string& file, D3DXVECTOR2 offset);
//	~TileMapReader();
//	static TileMapReader * GetInstance();
//};
//
