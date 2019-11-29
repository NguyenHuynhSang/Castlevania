#include "MapManager.h"


MapManager* MapManager::_instance = NULL;
void MapManager::AddMap(string MapID,const std::string& filePath, LPDIRECT3DTEXTURE9 texTileSet)
{
	CTileMap* map = new CTileMap();
	map->LoadGameData(filePath,texTileSet,MapID);
	this->tileMaps.insert(std::make_pair(MapID, map));

}
MapManager* MapManager::GetInstance()
{
	if (_instance == NULL) _instance = new MapManager();
	return _instance;
}
