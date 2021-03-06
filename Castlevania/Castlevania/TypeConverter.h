#include <unordered_map>
#include <string>

const enum ObjectID
{
	OPlayer,
	OWall,
	OGround,
	OMoneyBagTrigger,
	OTorch,
	ONextmap,
	OEntrance,
	OMoneyBag,
	OCastle,
	OCam,
	OSpawner,
	OStair,
	OBirck,
	OCandle,
	ODoor,
	OBoss,
	OBossBorder,
	OBossTrigger,
	OWater,
};

const auto string2EntityType = std::unordered_map<std::string, ObjectID>
{
	{ "Player", ObjectID::OPlayer },
	{ "Wall", ObjectID::OWall },
	{ "Ground", ObjectID::OGround },
	{ "MoneyBagTrigger", ObjectID::OMoneyBagTrigger },
	{ "Cam", ObjectID::OCam},
	{ "Torch", ObjectID::OTorch },
	{ "Nextmap", ObjectID::ONextmap },
	{ "Entrance", ObjectID::OEntrance },
	{ "MoneyBag", ObjectID::OMoneyBag },
	{ "Castle", ObjectID::OCastle },
	{ "BossTrigger", ObjectID::OBossTrigger },
	{ "BossBorder", ObjectID::OBossBorder },
	{ "BOSS", ObjectID::OBoss },
	{ "Door", ObjectID::ODoor },
	{ "Brick", ObjectID::OBirck },
	{ "Spawner", ObjectID::OSpawner },
	{ "Stair", ObjectID::OStair },
	{ "Candle", ObjectID::OCandle },
	{ "Water", ObjectID::OWater },
};

