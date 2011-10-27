precision lowp float;
attribute vec4 a_vertices;
attribute vec4 a_colors;
attribute vec2 a_uv;
uniform mat4 u_mvpMatrix;

varying vec4 v_colors;
varying vec2 v_uv;

void main()
{
	v_uv = a_uv;
	v_colors = a_colors;
	gl_Position = u_mvpMatrix * a_vertices;
}