#pragma once
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/Performance/ObjectPool.h"
//#include <functional>
namespace Xperrty {
	class TextureManager
	{
	public:
		~TextureManager() {};

		static Texture* getTexture(int id);
		static void freeTexturePtr(Texture* texture);
		static void init();
	private:
		TextureManager();
		static Dictionary<int, Texture*> textureMap;
		static Dictionary<int, std::string> texturePathMap;
		static ObjectPool<Texture> texturePool;

		static void addTexturePath(int id, const std::string& path);

		friend class ResourceManager;
	};
}