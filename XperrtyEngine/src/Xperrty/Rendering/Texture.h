#pragma once
namespace Xperrty {

	class Texture
	{
	public:
		Texture(const std::string& path);
		Texture();


		inline int getWidth() { return width; }
		inline int getHeight() { return height; }
		inline int getId() { return id; }
		inline unsigned char* getPixels() { return pixels; }
		inline unsigned int getTextureId() { return texId; }
		inline float* getUVs() { return uvs; }

		//ToDo: remove and replace with bounds for texture atlases.
		inline void setUVs(float* newUvs) { memcpy(uvs, newUvs, 8 * sizeof(float)); }

		//ToDo:remove all the opengl stuff...
		void uploadToGpu();
		//Frees the texture memory on the gpu.
		void freeGpuTexture();
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
		friend class TextureManager;
	};

}
