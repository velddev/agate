#include "Engine/Resources/AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

int AssetManager::GetCacheSize()
{
	return assetCache.size();
}