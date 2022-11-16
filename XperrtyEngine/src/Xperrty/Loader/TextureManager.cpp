#include "xppch.h"
#include "TextureManager.h"
#include <filesystem>
namespace Xperrty {
	/*void TextureManager::getTexture(int id, std::function<void(Texture* texture)> onTextureLoaded) {
		if (textureMap.contains(id)) {
			onTextureLoaded(textureMap[id]);
			return;
		}
		//ToDo:make this multithreaded.
		Texture* t = new Texture(texturePathMap[id]);
		textureMap.add(id, t);
		t->uploadToGpu();
		onTextureLoaded(textureMap[id]);
		//XP_INFO("Loaded texture with id{0} and ptr{1}", id, long int(t));
	}*/
	void TextureManager::freeTexturePtr(Texture* texture) {
		texturePool.deleteObject(texture);
	}
	Texture* TextureManager::getTexture(int id) {
		if (textureMap.contains(id)) {
			Texture* existingTexture = textureMap[id];
			unsigned int gpuId = existingTexture->getTextureId();
			//ToDo: remove this after texture atlases are done.
			Texture* t = texturePool.newObject();
			t->texId = gpuId;
			t->id = existingTexture->id;
			t->width = existingTexture->width;
			t->height = existingTexture->height;
			return t;
		}
		//ToDo:make this multithreaded.
		Texture* t = texturePool.newObject(texturePathMap[id]);
		textureMap.add(id, t);
		//XP_INFO("Loaded texture with id{0} and ptr{1}", id, long int(t));
		t->uploadToGpu();
		//We do this to get a new pointer to the freshly created texture (freeTexturePtr will break all textures if it's called with the main pointer)...
		//ToDo:Fix this, it's not ok. 
		return getTexture(id);
	}



	void TextureManager::addTexturePath(int id, const std::string& path) {
		texturePathMap.add(id,path);
	}

	void TextureManager::init() {
		//ToDo: remove this... only quick demo code.
		std::string path = std::filesystem::current_path().string() + "\\..\\";
		addTexturePath(0, path + "Sandbox\\assets\\images\\archer.png");
		addTexturePath(1, path + "Sandbox\\assets\\images\\tile_1.png");
		addTexturePath(2, path + "Sandbox\\assets\\images\\tile_2.png");
		addTexturePath(3, path + "Sandbox\\assets\\images\\tile_3.png");
		addTexturePath(4, path + "Sandbox\\assets\\images\\tile_4.png");
		addTexturePath(5, path + "Sandbox\\assets\\images\\cpu.png");
		addTexturePath(6, path + "Sandbox\\assets\\images\\arrow.png");
		addTexturePath(7, path + "Sandbox\\assets\\images\\character.png");
		addTexturePath(8, path + "Sandbox\\assets\\images\\zombie.png");
	}

	Dictionary<int, Texture*> TextureManager::textureMap;
	Dictionary<int, std::string> TextureManager::texturePathMap;
	ObjectPool<Texture> TextureManager::texturePool = ObjectPool<Texture>(200);
}