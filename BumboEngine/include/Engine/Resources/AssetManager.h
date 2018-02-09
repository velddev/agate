#pragma once
#include "Asset.h"
#include "Loadable.h"
#include "Utils/HashingUtils.h"

#include <unordered_map>
#include <time.h>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	int GetCacheSize();

	template<class T>
	Asset *AddNew(T *newAsset);

	template<class T>
	Asset *Load(const char *filePath);
	template<class T>
	Asset *Load(char *filePath);

private:
	std::unordered_map<std::uint64_t, Asset*> assetCache;
};

template<class T>
inline Asset *AssetManager::AddNew(T *newAsset)
{
	char *generatedName = (char*)(std::string(typeid(newAsset).name()) + std::to_string(time(0))).c_str();
	std::uint64_t hash = HashingUtils::Djb2(generatedName);

	Asset *asset = new Asset(hash);
	asset->SetResource((Loadable*)newAsset);

	assetCache.insert({
		hash,
		asset
	});
	
	return asset;
}

template<class T>
inline Asset *AssetManager::Load(const char *filePath)
{
	return Load<T>((char*)filePath);
}

template<class T>
inline Asset *AssetManager::Load(char *filePath)
{
	std::uint64_t hash = HashingUtils::Djb2(filePath);

	auto search = assetCache.find(hash);
	if (search == assetCache.end()) {
		Asset *asset = new Asset(hash);

		T *t = new T();
		((Loadable*)t)->Load(filePath);

		asset->SetResource((Loadable*)t);

		assetCache.insert({
			asset->GetHash(),
			asset
		});
	}
	return assetCache[hash];
}
