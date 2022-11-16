#pragma once
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/Performance/ObjectPool.h"
//#include <functional>
namespace Xperrty {
	class TextureManager
	{
	public:
		~TextureManager() {};

		//Returns a texture. If this is the first time the texture is created, it will be uploaded to the gpu.
		static Texture* getTexture(int id);
		//Frees the cpu pointer for this texture.
		static void freeTexturePtr(Texture* texture);
		//Initializes the texture manager.
		static void init();

		//Destroys the texture manager and frees all the textures from gpu memory.
		static void destroy();
	private:
		TextureManager();
		static Dictionary<int, Texture*> textureMap;
		static Dictionary<int, std::string> texturePathMap;
		static ObjectPool<Texture> texturePool;

		static void addTexturePath(int id, const std::string& path);

		friend class ResourceManager;
	};
}