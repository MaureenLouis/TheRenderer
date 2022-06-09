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
	void loadHeightMap();
	void normalizeHeightMap();
	void shutdownHeightMap();

private:
	unsigned int _width;              
	unsigned int _height;

	Unique<VertexArray> _array;              /* Vertex array */
	Ref<VertexBuffer>   _vertices;           /* vertices */
	Ref<IndexBuffer>    _indices;            /* indices */
	Ref<ShaderProgram>  _shader;             /* Shader */
	Ref<TrackBall>      _trackBall;          /* Camera */
	static const char* _vertexShader;        /* vertex shader souces */
	static const char* _fragmentShader;      /* fragment shader souces */

	std::vector<glm::vec3> _gridVertices;    /* Grid vertex data */
	std::vector<glm::uvec3> _gridIndices;    /* Grid index data */
	Byte*           _heightMapData;
};