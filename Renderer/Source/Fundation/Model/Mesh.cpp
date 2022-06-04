#include "stdafx.h"
#include "Mesh.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Scene/Scene.h"

const char* Mesh::_vertexShaderSource =R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoords;
layout(location=3) in vec3 aTangent;
layout(location=4) in vec3 aBiTangent;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p; 

out vec3 normal;
out vec3 fragPos;

void main()
{    
    gl_Position = p * v * m * vec4(aPos, 1.0);
    // Normal matrix
    normal = mat3(transpose(inverse(m))) * aNormal;
    fragPos = vec3(m * vec4(aPos, 0.0));
}
)";

const char* Mesh::_fragmentShaderSource = R"(
#version 330 core
layout(location=0) out vec4 outColor;

in vec3 normal;
in vec3 fragPos;

uniform vec4 diffuseColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
// Specular Highlights
uniform float glossiness;
uniform vec4  specularColor;
uniform float specularLevel;

vec3 calculateAmbient()
{
    float ambientStrength = 1.f;
    vec3 ambient = ambientStrength * diffuseColor.xyz;

    vec3 result = ambient * diffuseColor.xyz;
    return result;
}

vec3 calculateSpeculate()
{    

    vec3 viewDir = normalize(lightPos - fragPos);
    vec3 lightDir = normalize(fragPos - lightPos);
    vec3 norm = normalize(normal);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), glossiness);
    return specularLevel * spec * lightColor * specularColor.xyz;
}

vec3 calculateDiffuse()
{
    // Global normal
    vec3 norm = normalize(normal);
    
    // Light direction
    vec3 lightDir = normalize(fragPos - lightPos);
    
    // Diffuse quantity
    float diff = max(dot(lightDir, norm), 0.0);

    // Diffuse color
    vec3 diffuse = diff * lightColor;

    return diffuse;
}

void main()
{
    // Diffuse
    vec3 diffuse = calculateDiffuse();

    // Ambient
    vec3 ambient = calculateAmbient();

    // Specular color
    vec3 specular = calculateSpeculate();

    // Result
    vec3 result = (diffuse + ambient + specular) * diffuseColor.xyz;
 
    outColor = vec4(result, 1.0);
}
)";

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
	_program->setUniform("lightColor",defaultLight->color());
	_program->setUniform("lightPos", defaultLight->position());
    _program->setUniform("lightPower", defaultLight->lightPower());

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
