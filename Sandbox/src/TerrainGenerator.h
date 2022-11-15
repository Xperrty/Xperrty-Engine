#pragma once
//Generates tile based terrain with 250x250 sized tiles.
class TerrainGenerator
{
public:
	TerrainGenerator(int width,int height);
	~TerrainGenerator() {}

private:
	//Generates the terrain with width x height tiles
	void generateTerrain(int width, int height);
};
//ToDo:Implement Perlin Noise in the generation.