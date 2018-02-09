#pragma once
#include <type_traits>
#include "Loadable.h"
#include <cstdint>

class Asset
{
public:
	Asset(std::uint64_t hash) : hash(hash)
	{}
	
	~Asset() {}

	void SetResource(Loadable *resource);

	template<class T>
	T *Get();

	std::uint64_t GetHash();

private:
	std::uint64_t hash;
	Loadable *resource;
};

template<class T>
inline T *Asset::Get()
{
	return (T*)resource;
}
