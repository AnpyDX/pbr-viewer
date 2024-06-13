@shader: frame_present

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

void main() {
    fragColor = texture(frame_texture, texCoord);
}