#version 330 core
in vec2 texCoord;
in vec3 color;
out vec4 FragColor;
uniform sampler2D Tex;
void main()
{
	FragColor = texture(Tex, texCoord);
}

