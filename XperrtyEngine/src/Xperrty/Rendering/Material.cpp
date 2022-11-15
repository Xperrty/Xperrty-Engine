#include "xppch.h"
#include "Material.h"
#include "Xperrty/World/GameObject.h"
#include "Window.h"
#include "Cameras/RtsCamera.h"
namespace Xperrty {
	Material::Material(Shader* shader, Texture* texture, GameObject* object) :shader(shader), texture(texture), gameObject(object), memLocation(nullptr), bl(nullptr), br(nullptr), tr(nullptr), tl(nullptr)
	{
	}

	void Material::setVerticesMemLocation(MaterialVertexData* location)
	{
		memLocation = location;
		createVertices();
	}

	void Material::uploadUniforms() {
		//auto resolutionLocation = shader->getUniformLocation("uResolution");
		auto projectionLocation = shader->getUniformLocation("uProjectionVector");
		auto cameraPositionLocation = shader->getUniformLocation("uCameraPosition");
		Window* window = Window::instance;
		Camera* camera = Camera::getActiveCamera();
		//shader->setUniform2f(resolutionLocation, window->getWidth(), window->getHeight());
		shader->setUniform2f(projectionLocation, static_cast<float>(window->getWidth()) / 2, -static_cast<float>(window->getHeight()) / 2);
		shader->setUniform3f(cameraPositionLocation, camera->getBounds().getX(), camera->getBounds().getY(), camera->getScale());
	}

	void Material::createVertices()
	{
		TransformMatrix2D& wt = gameObject->getWorldTransformMatrix();
		float* uvs = texture->getUVs();
		float aX = gameObject->getAnchorX();
		float aY = gameObject->getAnchorY();
		//ToDo: Add forced width and height for objects.
		//float w0 = (gameObject.forcedWidth || (texture.width)) * (1 - aX);
		//float w1 = (gameObject.forcedWidth || (texture.width)) * -aX;
		//float h0 = (gameObject.forcedHeight || texture.height) * (1 - aY);
		//float h1 = (gameObject.forcedHeight || texture.height) * -aY;
		float w0 = gameObject->getWidth() * (1 - aX);
		float w1 = gameObject->getWidth() * -aX;
		float h0 = gameObject->getHeight() * (1 - aY);
		float h1 = gameObject->getHeight() * -aY;

		int i = 0;
		float a = wt.getA();
		float b = wt.getB();
		float c = wt.getC();
		float d = wt.getD();
		float tx = wt.getTx();
		float ty = wt.getTy();
		int texId = texture->getId();
		//XP_INFO("Should have texId:{0}", texId);

		//ToDo: Instantiate the data
		bl = new(memLocation + 0) MaterialVertexData(a * w1 + c * h0 + tx, d * h0 + b * w1 + ty, uvs[0], uvs[1], gameObject->getWorldAlpha(), texId);
		br = new(memLocation + 1) MaterialVertexData(a * w0 + c * h0 + tx, d * h0 + b * w0 + ty, uvs[2], uvs[3], gameObject->getWorldAlpha(), texId);
		tr = new(memLocation + 2) MaterialVertexData(a * w0 + c * h1 + tx, d * h1 + b * w0 + ty, uvs[4], uvs[5], gameObject->getWorldAlpha(), texId);
		tl = new(memLocation + 3) MaterialVertexData(a * w1 + c * h1 + tx, d * h1 + b * w1 + ty, uvs[6], uvs[7], gameObject->getWorldAlpha(), texId);

	}

	void Material::updateVertices() {
		TransformMatrix2D& wt = gameObject->getWorldTransformMatrix();
		float* uvs = texture->getUVs();
		float aX = gameObject->getAnchorX();
		float aY = gameObject->getAnchorY();
		//ToDo: Add forced width and height for objects.
		//float w0 = (gameObject.forcedWidth || (texture.width)) * (1 - aX);
		//float w1 = (gameObject.forcedWidth || (texture.width)) * -aX;
		//float h0 = (gameObject.forcedHeight || texture.height) * (1 - aY);
		//float h1 = (gameObject.forcedHeight || texture.height) * -aY;
		float w0 = texture->getWidth() * (1 - aX);
		float w1 = texture->getWidth() * -aX;
		float h0 = texture->getHeight() * (1 - aY);
		float h1 = texture->getHeight() * -aY;

		int i = 0;
		float a = wt.getA();
		float b = wt.getB();
		float c = wt.getC();
		float d = wt.getD();
		float tx = wt.getTx();
		float ty = wt.getTy();
		int texId = texture->getId();
		//texId = 1;
		//bl
		bl->position[0] = a * w1 + c * h0 + tx;
		bl->position[1] = d * h0 + b * w1 + ty;
		bl->UV[0] = uvs[0];
		bl->UV[1] = uvs[1];
		bl->textureId = texId;
		bl->alpha = gameObject->getWorldAlpha();
		//br
		br->position[0] = a * w0 + c * h0 + tx;
		br->position[1] = d * h0 + b * w0 + ty;
		br->UV[0] = uvs[2];
		br->UV[1] = uvs[3];
		br->textureId = texId;
		br->alpha = gameObject->getWorldAlpha();
		//tr
		tr->position[0] = a * w0 + c * h1 + tx;
		tr->position[1] = d * h1 + b * w0 + ty;
		tr->UV[0] = uvs[4];
		tr->UV[1] = uvs[5];
		tr->textureId = texId;
		tr->alpha = gameObject->getWorldAlpha();
		//tl
		tl->position[0] = a * w1 + c * h1 + tx;
		tl->position[1] = d * h1 + b * w1 + ty;
		tl->UV[0] = uvs[6];
		tl->UV[1] = uvs[7];
		tl->textureId = texId;
		tl->alpha = gameObject->getWorldAlpha();
	}

}