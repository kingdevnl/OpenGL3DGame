#pragma once
#include <gl/glew.h>

class Texture
{
public:
	GLuint textureID;
	int width, height, bpp;

	Texture(const char* file);
	void destroy();
	
};

