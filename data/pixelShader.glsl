#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3
/*in uint id;
out vec4 frag_colour;
void main () {
	frag_colour = vec4 (0.0, 0.0, 1.0, 1.0);
	if (id == 1) frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);
	if (id == 2) frag_colour = vec4 (1.0, 0.0, 1.0, 1.0);
}*/

in vec2 texture_coord;
uniform sampler2D basic_texture;
out vec4 frag_colour;
void main () {
	vec4 texel = texture2D (basic_texture, texture_coord);
	frag_colour = texel;
}