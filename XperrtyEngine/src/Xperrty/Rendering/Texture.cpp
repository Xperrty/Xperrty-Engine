#include "xppch.h"
#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"
//0,1-------1,1
// |		 |
// |   UVs	 |
// |		 |
//0,0-------1,0
namespace Xperrty {
	Texture::Texture(const std::string& path) :pixels(nullptr), width(0), height(0), channels(0), uvs{ 0,0,1,0,1,1,0,1 }, isPixelMemoryFree(true)
	{
		loadTexture(path);
	}
	void Texture::uploadToGpu()
	{
		unsigned int texId;
		glGenTextures(1, &texId);

		glBindTexture(GL_TEXTURE_2D, texId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		//ToDo: free texture after uploading to gpu;

	}
	Texture::~Texture()
	{
		if (!isPixelMemoryFree) free(pixels);
	}
	void Texture::loadTexture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);
		isPixelMemoryFree = false;
	}
}