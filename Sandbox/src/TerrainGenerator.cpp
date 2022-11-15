#include "xppch.h"
#include "TerrainGenerator.h"
#include "Xperrty/World/SceneManager.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Loader/TextureManager.h"
#include "Xperrty/Rendering/Shader.h"
#include <filesystem>
TerrainGenerator::TerrainGenerator(int width, int height) {
	generateTerrain(width, height);
}

void TerrainGenerator::generateTerrain(int width, int height) {
	std::string path = std::filesystem::current_path().string() + "\\..\\";
	Xperrty::Texture* tile2 = Xperrty::TextureManager::getTexture(2);
	Xperrty::Texture* tile3 = Xperrty::TextureManager::getTexture(3);
	Xperrty::Texture* tile1 = Xperrty::TextureManager::getTexture(1);
	Xperrty::Texture* tile4 = Xperrty::TextureManager::getTexture(4);
	Xperrty::Texture* tiles[]{ tile2,tile3,tile1, tile4 };
	Xperrty::Shader* shader = Xperrty::Shader::getShader(path + "XperrtyEngine\\src\\Xperrty\\Rendering\\Shaders\\MultiTextureShader.glsl");
	float startX = -width / 2 * 250;
	for (int i = 0; i < width; i++)
	{
		float startY = -height / 2 * 250;
		for (int j = 0; j < height; j++) {
			Xperrty::GameObject* go = Xperrty::SceneManager::instance()->createObject();
			go->setMaterial(new Xperrty::Material(shader, tiles[i % 4], go));
			Xperrty::SceneManager::instance()->addObject(go);
			go->setX(startX);
			go->setY(startY);
			go->setWidth(250);
			go->setHeight(250);
			go->updateTransform();
			go->setIsStatic(true);
			startY += 250;
		}
		startX += 250;
	}
}