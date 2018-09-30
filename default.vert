#version 430

in vec4 Vertex;
uniform double PointSize = 1;

void main()
{
    gl_Position = Vertex;
}