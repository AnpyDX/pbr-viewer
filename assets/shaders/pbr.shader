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

uniform vec3 camera_pos;
uniform float mat_albedo;
uniform float mat_metallic;
uniform float mat_roughness;
uniform float mat_AO;

