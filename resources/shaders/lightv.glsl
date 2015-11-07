#version 410
layout(location = 0) in vec4 Position;
layout(location = 3) in vec2 TexCoord;

out vec2 vTexCoord;
out vec4 vDirection;

uniform mat4 View;
uniform vec4 Direction;



void main() 
{
	vTexCoord = TexCoord;
	gl_Position = Position;
		
	vDirection = View * Direction;
}