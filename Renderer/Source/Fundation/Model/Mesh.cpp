#include "stdafx.h"
#include "Mesh.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Scene/Scene.h"
#include "Renderer/Components/BasicComponent.h"


Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, Ref<Material>& material)
{
	_vertices = std::move(vertices);
	_indices = std::move(indices);
	_material = std::move(material);

	BufferLayout layout =
	{
		{ BufferElement::BufferElementType::Float3, "aPos" },
		{ BufferElement::BufferElementType::Float3, "aNormal"},
		{ BufferElement::BufferElementType::Float2, "aTexCoords"},
	    { BufferElement::BufferElementType::Float3, "aTangent"},
		{ BufferElement::BufferElementType::Float3, "aBiTangent"}
	};

	_vertexArray = std::make_unique<VertexArray>();
	_vertexArray->bind();

	_vertexBuffer = std::make_shared<VertexBuffer>((float*)&_vertices[0], sizeof(Vertex) * _vertices.size());
	_vertexBuffer->setLayout(layout);
	_vertexArray->addVertexBuffer(_vertexBuffer);

	_indexBuffer = std::make_shared<IndexBuffer>((int*)&_indices[0],  _indices.size());
	_vertexArray->setIndexBuffer(_indexBuffer);

	_program = std::make_unique<ShaderProgram>("D:\\Projects\\TheRenderer\\Asset\\Shader\\InherentShader\\BlinnPhongWithNormal.fx");
}

void Mesh::draw(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p)
{
	glm::vec4 diffuseColor = _material->_diffuseColor;

	_program->use();
	_program->setUniform("m", m);
	_program->setUniform("v", v);
	_program->setUniform("p", p);
	_program->setUniform("diffuseColor", diffuseColor);

    float glossiness = _material->_glossiness;
    _program->setUniform("glossiness", glossiness);

    float specularLevel = _material->_specularLevel;
    _program->setUniform("specularLevel", specularLevel);

    glm::vec4 specularColor = _material->_specularColor;
    _program->setUniform("specularColor", specularColor);

    glm::vec4 ambientColor = _material->_ambientColor;
    _program->setUniform("ambientColor", ambientColor);

    float ambientLevel = _material->_ambientLevel;
    _program->setUniform("ambientLevel", ambientLevel);

	Ref<LightComponent> defaultLight = Scene::get().defaultLight();

	Ref<TrackBall> trackBall = Scene::get().trackBall();
	_program->setUniform("viewPos", trackBall->cameraPosition());

    _program->setUniform("displacementFactor", _material->_displacementFactor);

    // Texture

    auto tex = _material->_textureSet._normalMaps[0];
    if (tex)
    {
		glActiveTexture(GL_TEXTURE0);
		tex->bind();
		_program->setUniform("normalMap", 0);
    }
    
	tex = _material->_textureSet._diffuseMaps[0];
    if (tex)
    {
        glActiveTexture(GL_TEXTURE1);
        tex->bind();
        _program->setUniform("diffuseMap", 1);
    }

    tex = _material->_textureSet._displacementMaps[0];
    if (tex)
    {
        glActiveTexture(GL_TEXTURE2);
        tex->bind();
        _program->setUniform("displacementMap", 2);
    }

	_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, _indexBuffer->count(), GL_UNSIGNED_INT, 0);
}
