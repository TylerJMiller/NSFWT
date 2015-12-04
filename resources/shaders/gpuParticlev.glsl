#version 410

layout (location=0) in vec4 Position;
layout (location=1) in vec4 Velocity;
layout (location=2) in float Lifetime;
layout (location=3) in float Lifespan;

out vec4 position;
out float lifetime;
out float lifespan;

void main()
{
	position = Position;
	lifetime = Lifetime;
	lifespan = Lifespan;
}