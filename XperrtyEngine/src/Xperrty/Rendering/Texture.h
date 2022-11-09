#pragma once
namespace Xperrty {

	class Texture
	{
	public:
		//TODO:Implement Texture manager...
		//TODO:Implement off thread loading
		Texture(const std::string& path);


		inline int getWidth() { return width; }
		inline int getHeight() { return height; }
		inline int getId() { return id; }
		inline unsigned char* getPixels() { return pixels; }
		inline unsigned int getTextureId() { return texId; }
		inline float* getUVs() { return uvs; }

		//ToDo:remove all the opengl stuff...
		void uploadToGpu();
		~Texture();
	private:
		unsigned char* pixels;
		int width;
		int height;
		int channels;
		int id;
		float uvs[8];
		unsigned int texId;
		//ToDo:remove, temporary use.
		static int globalId;
		bool isPixelMemoryFree;
		//for now it's single threaded...
		void loadTexture(const std::string& path);
	};

}
