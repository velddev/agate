#pragma once
#include "Graphics\Transform.h"

class Model
{
public:
	Model();
	~Model();

	static Model *FromOBJ(char *filePath);

private:
	Transform *transform = new Transform();
};

