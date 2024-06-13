@shader: hello_triangle

[ vertex ]
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}

[ fragment ]
#version 430 core
out vec4 fragColor;
in vec2 texCoord;

uniform sampler2D tex1;

void main() {
    fragColor = texture(tex1, texCoord);
}