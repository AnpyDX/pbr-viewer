@shader: Physical Based Rendering

[ vertex ]
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragPos;
out vec3 fragNorm;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normal_transform;

void main() {
    fragPos = (model * vec4(aPos, 1.0)).xyz;
    fragNorm = normal_transform * normal_transform;
    texCoord = aTexCoord;

    gl_Position = proj * view * model * vec4(aPos, 1.0);
}

[ fragment ]
#version 430 core
out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNorm;
in vec2 texCoord;

@include(data_define)
@include(math_collection)

uniform vec3 camera_pos;
uniform LightInfo light;
uniform PBRMaterial material;


void main() {
    // essential info
    vec3 N = normalize(fragNorm);
    vec3 V = normalize(camera_pos - fragPos);
    vec3 L = normalize(light.position - fragPos);
    vec3 H = normalize(V + L);

    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0);

    /* Cook-Torrance BRDF */
    float f_D = D_GGX_TR(NdotH, material.roughness);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, material.albedo, material.metallic);
    vec3 f_F = FresnelSchlick(NdotV, F0);

    float f_G = GeometrySmith(NdotV, NdotL, material.roughness);

    vec3 kS = f_F;
    vec3 kD = vec3(1.0) - kS; // obey energy conservation
    kD *= 1.0 - material.metallic; // metel doesn't have diffuse reflect

    vec3 diffuse = kD * (material.albedo / PI);
    vec3 specular = kS * (f_D * f_F * f_G) / (4.0 * NdotV * NdotL, 0.0) + 0.0001);
    vec3 BRDF_result = diffuse + specular;

    /* Radiance */
    float LF_distance = length(light.position, fragPos);
    float attenuation = 1.0 / (LF_distance * LF_distance);
    vec3 radiance = light.color * attenuation;

    /* output result */
    vec3 Lo = BRDF_result * radiance * NdotL; // direct lighting
    vec3 ambient = vec3(0.03) * material.albedo * material.ao; // indirect lighting

    // gamma correction
    vec3 color = Lo + ambient;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0, 2.2));

    fragColor = vec4(color, 1.0);
}


[ data_define ]
struct LightInfo {
    vec3 position;
    vec3 color;
};

struct PBRMaterial {
    vec3 albedo;
    float metallic;
    float roughness;
    float ao;
};


[ math_collection ]
const float PI = 3.1415926535;

/**
* Normal Distribution Function
*   vec3 N : fragment's normal
*   vec3 H : fragment's halfway vector
*   float a : roughness argument
*/
float D_GGX_TR(float NdotH, float a) {
    float a_square = a * a;
    float NdotH_square = NdotH * NdotH;

    float denom = NdotH_square * (a_square - 1.0) + 1.0;
    denom = denom * denom;
    return a_square / (PI * denom);
}

/**
* Geometry Function (func <GeometrySmith>)
*   vec3 N : fragment's normal
*   vec3 V : view direction
*   vec3 L : light direction
*   float a : roughness argument
*/
float GeometrySchlickGGX(float NdotX, float a) {
    float k = pow(a + 1.0, 2) / 8.0;
    return NdotX / (NdotX * (1.0 - k) + k);
}

float GeometrySmith(float NdotV, float NdotL, float a) {
    return GeometrySchlickGGX(NdotV, a) * GeometrySchlickGGX(NdotL, a);
}

/**
* Fresnel Rquation
*   vec3 H : fragment's halfway vector
*   vec3 V : view direction
*   vec3 F0 : base reflectivity
*/
vec3 FresnelSchlick(float HdotV, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - HdotV, 0.0, 1.0), 5);
}