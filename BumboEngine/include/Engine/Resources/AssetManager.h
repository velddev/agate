#pragma once
#include "Asset.h"
#include "Loadable.h"
#include "Utils/HashingUtils.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	template<class T>
	static Asset *Load(char *filePath);
};

template<class T>
inline Asset *AssetManager::Load(char *filePath)
{
	Asset *asset = new Asset();

	T t = new T();
	((Loadable*)t)->Load(filePath);

	asset->resource = t;
	asset->hash = HashingUtils::Djb2(filePath);

	return resource;
}
