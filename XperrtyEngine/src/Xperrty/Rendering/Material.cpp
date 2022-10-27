#include "xppch.h"
#include "Material.h"
#include "Xperrty/World/GameObject.h"
namespace Xperrty {
	Material::Material(Shader* shader,Texture* texture):shader(shader),texture(texture), memLocation(nullptr)
	{
	}
	void Material::setVerticesMemLocation(float* location)
	{
		memLocation = location;
	}
	void Material::updateVertices(GameObject* gameObject)
	{
        TransformMatrix2D& wt = gameObject->getWorldTransformMatrix();
        /*var texture = this.texture;
        var wt = object.worldTransform;
        var uvs = texture.uvs;
        var aX = object.anchor.x;
        var aY = object.anchor.y;
        var w0, w1, h0, h1;
        w0 = (object.forcedWidth || (texture.width)) * (1 - aX);
        w1 = (object.forcedWidth || (texture.width)) * -aX;
        h0 = (object.forcedHeight || texture.height) * (1 - aY);
        h1 = (object.forcedHeight || texture.height) * -aY;
        var i = vertexI;
        var a = wt.a;
        var b = wt.b;
        var c = wt.c;
        var d = wt.d;
        var tx = wt.tx;
        var ty = wt.ty;
        var positions = vertexBuffer;
        var color = this.color;
        var texId = Quack.Shaders.MultiTextureShader.textureArray.indexOf(this.texture.baseTexture);
        if (texId == -1)
            this.shader.setTexture(this.texture);
        texId = Quack.Shaders.MultiTextureShader.textureArray.indexOf(this.texture.baseTexture);
        positions[i + 0] = a * w1 + c * h0 + tx;
        positions[i + 1] = d * h0 + b * w1 + ty;
        positions[i + 2] = uvs[0];
        positions[i + 3] = uvs[1];
        positions[i + 4] = object.worldAlpha;
        positions[i + 5] = color ? color.r / 255 : 1;
        positions[i + 6] = color ? color.g / 255 : 1;
        positions[i + 7] = color ? color.b / 255 : 1;
        positions[i + 8] = color ? color.a : 1;
        positions[i + 9] = texId;
        positions[i + 10] = a * w1 + c * h1 + tx;
        positions[i + 11] = d * h1 + b * w1 + ty;
        positions[i + 12] = uvs[2];
        positions[i + 13] = uvs[3];
        positions[i + 14] = object.worldAlpha;
        positions[i + 15] = color ? color.r / 255 : 1;
        positions[i + 16] = color ? color.g / 255 : 1;
        positions[i + 17] = color ? color.b / 255 : 1;
        positions[i + 18] = color ? color.a : 1;
        positions[i + 19] = texId;
        positions[i + 20] = a * w0 + c * h1 + tx;
        positions[i + 21] = d * h1 + b * w0 + ty;
        positions[i + 22] = uvs[4];
        positions[i + 23] = uvs[5];
        positions[i + 24] = object.worldAlpha;
        positions[i + 25] = color ? color.r / 255 : 1;
        positions[i + 26] = color ? color.g / 255 : 1;
        positions[i + 27] = color ? color.b / 255 : 1;
        positions[i + 28] = color ? color.a : 1;
        positions[i + 29] = texId;
        positions[i + 30] = a * w0 + c * h0 + tx;
        positions[i + 31] = d * h0 + b * w0 + ty;
        positions[i + 32] = uvs[6];
        positions[i + 33] = uvs[7];
        positions[i + 34] = object.worldAlpha;
        positions[i + 35] = color ? color.r / 255 : 1;
        positions[i + 36] = color ? color.g / 255 : 1;
        positions[i + 37] = color ? color.b / 255 : 1;
        positions[i + 38] = color ? color.a : 1;
        positions[i + 39] = texId;
        this.shader.game.renderer.dataAddedInShader(this.shader.getStride());*/
	}
}