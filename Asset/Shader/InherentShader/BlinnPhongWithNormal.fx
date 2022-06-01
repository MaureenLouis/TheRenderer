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
uniform vec3 lightPos;
uniform vec3 viewPos;

out VS_OUT
{
	vec3 FragPos;
    vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vs_out;

void main()
{
	gl_Position = p * v * m * vec4(aPos, 1.f);

	vs_out.FragPos = vec3(m * vec4(aPos, 1.0));
	vs_out.TexCoords = aTexCoords;

	/* Normal interp */
	mat3 normalMatrix = transpose(inverse(mat3(m)));

	/* TBN matrix.  */
	/*
	vec3 T = normalize(normalMatrix * aTangent);
	vec3 B = normalize(normalMatrix * aBiTangent);
	vec3 N = normalize(normalMatrix * aNormal);
	*/

	vec3 T = normalize(vec3(m * vec4(aTangent, 0.0)));
	vec3 N = normalize(vec3(m * vec4(aNormal, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(T, N);

	/* Transfer world space into TBN space */
	/* mat3 TBN = transpose(mat3(T, B, N)); */
	mat3 TBN = mat3(T, B, N);

	vs_out.TangentLightPos = TBN * lightPos;
	vs_out.TangentViewPos  = TBN * viewPos;
	vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}

#type fragment
#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fs_in;

uniform sampler2D normalMap;
uniform sampler2D diffuseMap;
uniform vec4 diffuseColor;
uniform vec4  specularColor;
uniform float glossiness;
uniform vec4 ambientColor;
uniform float ambientLevel;
uniform float lightPower;
uniform float specularLevel;
const   vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main()
{
	/* range [0, 1] */
	vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;

	/* range [-1, 1] */
	normal = normalize(normal * 2.0 - 1.0);
	
	/* ambient color */
	vec3 ambient = ambientColor.xyz * ambientLevel;

	/* light direction */
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float lightDistance = length(lightDir);

	/* diffuse color */
	float lambertia = max(dot(lightDir, normal), 0.0);
	/*vec3 diffuse = lambertia * diffuseColor.xyz * lightColor;*/
	vec3 diffuse = lambertia * texture(diffuseMap, fs_in.TexCoords).rgb * lightColor;
	

	/* specular color */
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), glossiness);
	vec3 specular = specularColor.xyz * spec * lightColor * specularLevel;

	FragColor = vec4(ambient + diffuse /** lightPower / lightDistance*/ + specular /** lightPower / lightDistance*/, 1.f);
}