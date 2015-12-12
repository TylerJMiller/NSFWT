#version 410
layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 aNormal;
layout (location = 3) in vec2 TexCoord;

out vec4 vNormal;
out vec4 vPosition;
out vec2 vTexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	
	vTexCoord = TexCoord;
	
	vNormal     = normalize(View * Model * aNormal);
	vPosition   = View * Model * Position;
	gl_Position = Projection * View * Model * Position;
}