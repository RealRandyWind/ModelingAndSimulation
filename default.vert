#version 430

in vec4 Vertex;
out vec3 World;
uniform mat4 Model;
uniform mat4 MVP;

void main()
{
    World = vec3(Model * vec4(Vertex.xyz, 1.0));
    gl_Position = MVP * vec4(World, 1.0);
}