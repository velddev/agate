#include "Engine/Resources/Asset.h"

void Asset::SetResource(Loadable * resource)
{
	this->resource = resource;
}

std::uint64_t Asset::GetHash()
{
	return hash;
}
