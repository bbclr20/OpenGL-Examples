#version 410

in vec2 coord;
out vec4 color; 
uniform sampler2D tex;

void main(void) {
	float alpha = texture(tex, coord).a;
	if (alpha < 0.1) {
		discard;
	}

	// draw leaf
	color = texture(tex, coord);

	// filter and add offset
	vec4 red = vec4(1, 0, 0, 1);
	color = texture(tex, coord) * red;
	color = texture(tex, coord) + red;
	
	// // swap channel
	// color.rb = color.br;
}