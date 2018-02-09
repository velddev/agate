#pragma once
#include "Asset.h"
#include "Loadable.h"
#include "Utils/HashingUtils.h"
#include <unordered_map>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	int GetCacheSize();

	template<class T>
	Asset *Load(const char *filePath);
	template<class T>
	Asset *Load(char *filePath);

private:
	std::unordered_map<std::uint64_t, Asset*> assetCache;
};

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
