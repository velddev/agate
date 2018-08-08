#pragma once

template <typename T>
class Optional 
{
	T* value;

public:
	Optional() 
	{
		this->value = nullptr;
	}
	Optional(T value) 
	{
		this->value = &value;
	}

	T GetValueOrDefault(T defaultValue) 
	{
		if (value == nullptr) 
		{
			return defaultValue;
		}
		return *value;
	}
};