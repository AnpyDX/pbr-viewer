@shader: Gaussian-Blur for GUI

[ vertex ]
#version 430 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main() {
    gl_Position = vec4(aPosition, 1.0);
    texCoord = aTexCoord;
}

[ fragment ]
#version 430 core
out vec4 fragColor;
in vec2 texCoord;

uniform sampler2D frame_texture;
uniform bool is_horizontal;

/**
* Gaussian Kernal:
* 
*   w[4] w[3] w[2] w[1]  w[0]  w[1] w[2] w[3] w[4]
*  
*/
const float kernal_weight[5] = {
    0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216
};

void main() {
    vec2 texture_offset = 1.0 / textureSize(frame_texture, 0);
    vec4 raw_color = texture(frame_texture, texCoord); // FIXME
    vec3 result = raw_color.rgb * kernal_weight[0];

    if (is_horizontal) {
        for (int i = 1; i < 5; i++) {
            result += texture(frame_texture, texCoord + vec2(texture_offset.x * i, 0.0)).rgb * kernal_weight[i];
            result += texture(frame_texture, texCoord - vec2(texture_offset.x * i, 0.0)).rgb * kernal_weight[i];
        }
    }
    else {
        for (int i = 1; i < 5; i++) {
            result += texture(frame_texture, texCoord + vec2(0.0, texture_offset.y * i)).rgb * kernal_weight[i];
            result += texture(frame_texture, texCoord - vec2(0.0, texture_offset.y * i)).rgb * kernal_weight[i];
        }
    }

    fragColor = vec4(result, raw_color.a); // FIXME
}