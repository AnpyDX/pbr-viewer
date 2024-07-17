@shader: PBRV Universal Soild Shader

[ vertex ]
#version 430 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 PBRV_Transform_Model;
uniform mat4 PBRV_Transform_View;
uniform mat4 PBRV_Transform_Projection;

out vec2 PBRV_TexCoord;
out vec3 PBRV_Normal;

void main() {
    gl_Position = PBRV_Transform_Projection * PBRV_Transform_View * PBRV_Transform_Model * vec4(aPosition, 1.0);
    PBRV_TexCoord = aTexCoord;
    PBRV_Normal = (PBRV_Transform_View * PBRV_Transform_Model * vec4(aNormal, 0.0)).xyz;
}


[ fragment ]
#version 430 core
out vec4 fragColor;

in vec2 PBRV_TexCoord;
in vec3 PBRV_Normal;

uniform sampler2D PBRV_Texture0;
uniform sampler2D PBRV_Texture1;
uniform sampler2D PBRV_Texture2;
uniform sampler2D PBRV_Texture3;
uniform sampler2D PBRV_Texture4;

void main() {
    fragColor = texture(PBRV_Texture0, PBRV_TexCoord);
}