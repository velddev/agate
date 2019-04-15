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
	Asset *AddNew(T* newAsset);

	template<class T>
	Asset *Load(const char* filePath);
	template<class T>
	Asset *Load(char* filePath);
	template<class T>
	Asset* Load(std::vector<char*> filePaths);

private:
	template<class T, typename Arg>
	Asset* LoadInternal(std::uint64_t hash, Arg& a);

	std::unordered_map<std::uint64_t, Asset*> assetCache;
};

template<class T>
inline Asset* AssetManager::AddNew(T *newAsset)
{
	char *generatedName = (char*)(std::string(typeid(newAsset).name()) 
		+ std::to_string(time(0))).c_str();
	std::uint64_t hash = HashingUtils::Djb2(generatedName);

	TAsset<T>* asset = new TAsset<T>(hash, newAsset);

	assetCache.insert({
		hash,
		(Asset*)asset
	});
	
	return (Asset*)asset;
}

template<class T>
inline Asset* AssetManager::Load(const char *filePath)
{
	return Load<T>((char*)filePath);
}

template<class T>
inline Asset* AssetManager::Load(char* filePath)
{
	std::uint64_t hash = HashingUtils::Djb2(filePath);
	return LoadInternal<T, char*>(hash, filePath);
}

template<class T>
inline Asset* AssetManager::Load(std::vector<char*> filePath)
{
	std::uint64_t hash = HashingUtils::Djb2(filePath);
	return LoadInternal<T, std::vector<char*>>(hash, filePath);
}

template<class T, typename Args>
inline Asset* AssetManager::LoadInternal(std::uint64_t hash, Args& arg)
{
	auto search = assetCache.find(hash);
	if (search == assetCache.end())
	{
		T* value = T::FromFile(arg);
		if (value == nullptr)
		{
			// Asset failed loading.
			value = new T();
		}

		Asset* asset = new TAsset<T>(hash, value);

		assetCache.insert({
			asset->GetHash(),
			asset
		});
	}
	return assetCache[hash];
}