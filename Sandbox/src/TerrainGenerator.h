#pragma once
//Generates tile based terrain with 250x250 sized tiles.
class TerrainGenerator
{
public:
	//ToDo:Implement Perlin Noise in the generation.
	//Creates a tilemap width x height using 4 types of tiles. At the moment each row is one tile type.
	TerrainGenerator(int width, int height);
	~TerrainGenerator() {}

private:
	//Generates the terrain with width x height tiles
	void generateTerrain(int width, int height);
};