#version 430

uniform vec4 PointColor = vec4(0.9, 0.1, 0.1, 1.0);

void main()
{
    gl_FragColor = PointColor;
}