#include "Texture.h"
#include "stb_image.h"
#include <spdlog/spdlog.h>
#include <iostream>

Texture::Texture(const char* file) {
	
	unsigned char* rgb = stbi_load(file, &width, &height, &bpp, 4);

	if(!rgb) {
		spdlog::critical("Failed loading texture {}", file);

		std::cin.get();
		exit(1);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,  rgb);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(rgb);
	spdlog::info("Loaded texture {0} {1}", file, textureID);

}

void Texture::destroy() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureID);
	spdlog::info("Destroyed texture {}", textureID);

}
