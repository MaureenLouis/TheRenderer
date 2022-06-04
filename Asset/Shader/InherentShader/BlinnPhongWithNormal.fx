#type vertex

#version 410 core
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
    
    vec3 T = normalize(mat3(m) * aTangent);
    vec3 B = normalize(mat3(m) * aBiTangent);
    vec3 N = normalize(mat3(m) * aNormal);
    mat3 TBN = transpose(mat3(T, B, N));

    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}

#type fragment
#version 410 core
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
uniform sampler2D displacementMap;
uniform float displacementFactor;
uniform vec4 diffuseColor;
uniform vec4  specularColor;
uniform float glossiness;
uniform vec4 ambientColor;
uniform float ambientLevel;
uniform float lightPower;
uniform float specularLevel;
const   vec3 lightColor = vec3(1.0, 1.0, 1.0);

/* Parallax mapping */
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
	
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
	
    // depth of current layer
    float currentLayerDepth = 0.0;
	
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * displacementFactor; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(displacementMap, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(displacementMap, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(displacementMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}


void main()
{
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 texCoords = fs_in.TexCoords;
	
	
	    texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
	    if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0) discard;
	

	/* range [-1, 1] */
	vec3 normal = texture(normalMap, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
	
	/* ambient color */
	vec3 ambient = ambientColor.xyz * ambientLevel;

	/* light direction */
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float lightDistance = length(fs_in.TangentLightPos - fs_in.TangentFragPos);

	/* diffuse color */
	float lambertia = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = lambertia * texture(diffuseMap, texCoords).rgb * lightColor;
	

	/* specular color */
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