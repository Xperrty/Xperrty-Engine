#pragma once

class TerrainGenerator
{
public:
	TerrainGenerator(int width,int height);
	~TerrainGenerator() {}

private:
	void generateTerrain(int width, int height);
};
