#pragma once
#include "Renderer/InherientObject/RenderObject.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Camera/TrackBall.h"


class TerrainBase : public RenderObject
{
	SELF(TerrainBase);
	SUPER(RenderObject);

public:
	TerrainBase(unsigned int width, unsigned int height, Ref<TrackBall>& trackBall);

	virtual void initialize() override;
	virtual void draw() override;

private:
	unsigned int _width;              
	unsigned int _height;

	Unique<VertexArray> _array;       /* Vertex array */
	Ref<VertexBuffer>   _vertices;    /* vertices */
	Ref<IndexBuffer>    _indices;     /* indices */
	Ref<ShaderProgram>  _shader;    
	Ref<TrackBall>      _trackBall;
	static const char* _vertexShader;
	static const char* _fragmentShader;

	std::vector<glm::vec3> _gridVertices;

	std::vector<glm::uvec3> _gridIndices;

};