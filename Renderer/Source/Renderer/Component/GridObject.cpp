#include "stdafx.h"
#include "GridObject.h"


const char* GridObject::_vertexShaderSource = R"(
#version 330 core
layout(location=0) in vec3 aPos;

out vec3 nearPoint;
out vec3 farPoint;
out mat4 view, proj;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection)
{
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);

    vec4 unprojectedPoint = viewInv * projInv * vec4(x, y, z, 1.0);

    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
    nearPoint = unprojectPoint(aPos.x, aPos.y, 0.0, v, p);
    farPoint  = unprojectPoint(aPos.x, aPos.y, 1.0, v, p);
    
    gl_Position = vec4(aPos, 1.0);
    view = v;
    proj = p;
}
)";

const char* GridObject::_fragmentShaderSource = R"(
#version 330 core
layout(location=0) out vec4 outColor;

in vec3 nearPoint;
in vec3 farPoint;
in mat4 fragView;
in mat4 fragProj;
float near = 0.01;
float far = 100.0;

vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
    // z axis
    if(fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
        color.z = 1.0;
    // x axis
    if(fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
        color.x = 1.0;
    return color;
}

float computeDepth(vec3 pos) {
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    return (clip_space_pos.z / clip_space_pos.w);
}

float computeLinearDepth(vec3 pos) {
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    float clip_space_depth = (clip_space_pos.z / clip_space_pos.w) * 2.0 - 1.0; // put back between -1 and 1
    float linearDepth = (2.0 * near * far) / (far + near - clip_space_depth * (far - near)); // get linear value between 0.01 and 100
    return linearDepth / far; // normalize
}


void main()
{
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);
    
    gl_FragDepth = computeDepth(fragPos3D);

    float linearDepth = computeLinearDepth(fragPos3D);
    float fading = max(0, (0.5 - linearDepth));

    outColor = (grid(fragPos3D, 10, true) + grid(fragPos3D, 1, true))* float(t > 0); // adding multiple resolution for the grid
    outColor.a *= fading;
  
}
)";

GridObject::GridObject()
{
	float vertices[] = {
		 1.f, 1.f,  0.f,
		 1.f, -1.f, 0.f,
		-1.f, -1.f, 0.f,
		-1.f, 1.f,  0.f,
	};

	int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	BufferLayout layout =
	{
		{ BufferElement::BufferElementType::Float3, "aPos" },
	};

	_vertexArray = std::make_unique<VertexArray>();
	_vertexArray->bind();

	_vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	_vertexBuffer->setLayout(layout);
	_vertexArray->addVertexBuffer(_vertexBuffer);

	_indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));
	_vertexArray->setIndexBuffer(_indexBuffer);

	_program = std::make_unique<ShaderProgram>(_vertexShaderSource, _fragmentShaderSource);
}

void GridObject::draw()
{
    _program->use();

	_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, _indexBuffer->count(), GL_UNSIGNED_INT, 0);

}
