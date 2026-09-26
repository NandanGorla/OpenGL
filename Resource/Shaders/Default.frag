#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 texcoord;

uniform sampler2D tex0;

void main()
{
    fragColor = texture(tex0,texcoord);
}