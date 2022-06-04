#type vertex
#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBiTangent;

uniform vec3 viewPos;

out VS_OUT
{
    vec3 WorldPos_CS_in;
    vec2 TexCoord_CS_in;
    vec3 Normal_CS_in;
	vec3 Tangent_CS_in;
	vec3 BiTangent_CS_in;
    vec3 WorldViewPos_CS_in;
} vs_out;

void main()
{
    vs_out.WorldPos_CS_in     = aPos;
	vs_out.TexCoord_CS_in     = aTexCoords;
	vs_out.Normal_CS_in       = aNormal;
	vs_out.Tangent_CS_in      = aTangent;
	vs_out.BiTangent_CS_in    = aBiTangent;
	vs_out.WorldViewPos_CS_in = viewPos;   
}

#type tc
#version 410 core
in VS_OUT
{
    vec3 WorldPos_CS_in[];
    vec2 TexCoord_CS_in[];
    vec3 Normal_CS_in[];
	vec3 Tangent_CS_in[];
	vec3 BiTangent_CS_in[];
    vec3 WorldViewPos_CS_in;
} vs_out;

out CS_OUT
{
    vec3 WorldPos_ES_in[];
    vec2 TexCoord_ES_in[];
    vec3 Normal_ES_in[];
	vec3 Tangent_ES_in[];
	vec3 BiTangent_ES_in[];
	vec3 WorldViewPos_ES_in;
} cs_out;





float GetTessLevel(float Distance0, float Distance1)
{
	float avgDistance = (Distance0+ Distance1) / 2.0;

	if (avgDistance <= 2.0)      return 10.0;
	else if (avgDistance < -5.0) return 7.0;
	else                         return 3.0;
}

void main()
{
    cs_out.TexCoord_ES_in [gl_InvocationID]  = vs_out.TexCoord_CS_in[gl_InvocationID];
    cs_out.Normal_ES_in   [gl_InvocationID]  = vs_out.Normal_CS_in[gl_InvocationID];
    cs_out.WorldPos_ES_in [gl_InvocationID]  = vs_out.WorldPos_CS_in[gl_InvocationID];
    cs_out.Tangent_ES_in  [gl_InvocationID]  = vs_out.Tangent_CS_in[gl_InvocationID];
    cs_out.BiTangent_ES_in[gl_InvocationID]  = vs_out.BiTangent_CS_in[gl_InvocationID];
	cs_out.WorldViewPos_ES_in = vs_out.WorldViewPos_CS_in;
    
    // Calculate the distance from the camera and three control points
    float eyeToVertexDistance0 = distance(vs_out.WorldViewPos_CS_in, vs_out.WorldPos_CS_in[0]);
    float eyeToVertexDistance1 = distance(vs_out.WorldViewPos_CS_in, vs_out.WorldPos_CS_in[1]);
    float eyeToVertexDistance2 = distance(vs_out.WorldViewPos_CS_in, vs_out.WorldPos_CS_in[2]);
    
    // Calculation the tessellation levels
    gl_TessLevelOuter[0] = GetTessLevel(eyeToVertexDistance1, eyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(eyeToVertexDistance2, eyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(eyeToVertexDistance0, eyeToVertexDistance1);
    gl_TessLevelOuter[0] = gl_TessLevelOuter[2];
    
}


#type te
#version 410 core
in CS_OUT
{
    vec3 WorldPos_ES_in[];
    vec2 TexCoord_ES_in[];
    vec3 Normal_ES_in[];
	vec3 Tangent_ES_in[];
	vec3 BiTangent_ES_in[];
	vec3 WorldViewPos_ES_in;
} cs_out;

out ES_OUT
{
    vec3 FragPos;
    vec2 TexCoord;
    vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fs_in;

uniform sampler2D displacementMap;
uniform float displacementFactor;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec3 lightPos;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main()
{
    // Texture coord
    fs_in.TexCoord = interpolate2D(cs_out.TexCoord_ES_in[0], cs_out.TexCoord_ES_in[1], cs_out.TexCoord_ES_in[2]);
    
	// Normal
	vec3 normal = interpolate3D(cs_out.Normal_ES_in[0],cs_out.Normal_ES_in[1], cs_out.Normal_ES_in[2]);
    vec3 N = normalize(vec3(m * vec4(normal, 0.0)));
	
	vec3 tangent = interpolate3D(cs_out.Tangent_ES_in[0],cs_out.Tangent_ES_in[1], cs_out.Tangent_ES_in[2]);
	vec3 T = normalize(vec3(m * vec4(tangent, 0.0)));
	T = normalize(T - dot(T, N) * N);
	
	vec3 B = cross(T, N);
	
	mat3 TBN = mat3(T, B, N);
	
    // Displaced vertex
	float displacement = texture(displacementMap, fs_in.TexCoord.xy).x;
	fs_in.FragPos += vec3(m * vec4(N * displacement * displacementFactor, 1.0));
	
	fs_in.TangentLightPos = TBN * lightPos;
	fs_in.TangentViewPos = TBN * cs_out.WorldViewPos_ES_in;
	fs_in.TangentFragPos = TBN * fs_in.FragPos;
}

#type fragment
#version 410 core

in ES_OUT
{
    vec3 FragPos;
    vec2 TexCoord;
    vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fs_in;

out vec4 FragColor;

uniform sampler2D normalMap;
uniform sampler2D diffuseMap;
uniform sampler2D displacementMap;
uniform sampler2D displacementFactor;

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
	vec3 normal = texture(normalMap, fs_in.TexCoord).rgb;

	/* range [-1, 1] */
	normal = normalize(normal * 2.0 - 1.0);
	
	/* ambient color */
	vec3 ambient = ambientColor.xyz * ambientLevel;

	/* light direction */
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float lightDistance = length(fs_in.TangentLightPos - fs_in.TangentFragPos);

	/* diffuse color */
	float lambertia = max(dot(lightDir, normal), 0.0);
	/*vec3 diffuse = lambertia * diffuseColor.xyz * lightColor;*/
	vec3 diffuse = lambertia * texture(diffuseMap, fs_in.TexCoord).rgb * lightColor;
	

	/* specular color */
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), glossiness);
	vec3 specular = specularColor.xyz * spec * lightColor * specularLevel;


	/* attenuation */
	float attenuation = lightPower / (lightDistance * lightDistance);

	vec3 outputColor = ambient + diffuse * attenuation + specular * attenuation;
	
	/*
	    float gamma = 2.2;
	    FragColor = vec4(pow(outputColor, vec3(1.0 / gamma)), 1.0);
	*/
	FragColor = vec4(outputColor, 1.0);
}