#pragma once
#include <type_traits>
#include "Loadable.h"
#include <cstdint>

class Asset
{
public:
	virtual ~Asset() = default;

	template<class T>
	T *Get();

	std::uint64_t GetHash();

protected:
	Asset(std::uint64_t hash)
		: hash(hash)
	{}

	std::uint64_t hash;

private:
	Asset() = default;
};

template<class T>
class TAsset : public Asset
{
public:
	TAsset(std::uint64_t hash)
		: Asset(hash)
	{}
	TAsset(std::uint64_t hash, T* resource)
		: Asset(hash), resource(resource)
	{}

	~TAsset() 
	{
		delete resource;
	}

	T* resource;
};

template<class T>
inline T* Asset::Get()
{
	TAsset<T>* deepAsset = dynamic_cast<TAsset<T>*>(this);
	if (deepAsset == nullptr)
	{
		return nullptr;
	}
	return deepAsset->resource;
}
