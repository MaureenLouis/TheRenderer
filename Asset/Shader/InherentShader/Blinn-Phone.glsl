#type vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBiTangent;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

varying vec3 normalInterp;
varying vec3 vertPos;

void main()
{

	vec4 vertPos4 = v * m * vec4(aPos, 1.0);
	vertPos = vec3(vertPos4) / vertPos4.w;
	normalInterp = mat3(transpose(inverse(m))) * aNormal;

	gl_Position = p * v * m * vec4(aPos, 1.0);
}

#type fragment

in vec3 normalInterp;
in vec3 vertPos;

uniform vec4 diffuseColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float glossiness;
uniform vec4  specularColor;
uniform float specularLevel;
uniform float lightPower;
const   vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec4 ambientColor;
uniform float ambientLevel;

void main()
{
	vec3 normal = normalize(normalInterp);
	vec3 lightDir = lightPos - vertPos;
	
	float distance = length(lightDir);
	distance = distance * distance;
	lightDir = normalize(lightDir);

	float lambertian = max(dot(lightDir, normal) , 0.0);
	float specular = 0.0;

	if (lambertian > 0.0)
	{
		vec3 viewDir = normalize(-vertPos);

		vec3 halfDir = normalize(lightDir + viewDir);

		float specAngle = max(dot(halfDir, normal) ,0.0);
		specular = pow(specAngle, glossiness);
	}

	vec3 colorLinear = ambientLevel * ambientColor.xyz + diffuseColor.xyz * lambertian * lightPower * lightColor / distance
		+ specularColor.xyz * specularLevel * specular * lightColor * lightColor * lightPower / distance;

	gl_FragColor = vec4(colorLinear, 1.0);
}