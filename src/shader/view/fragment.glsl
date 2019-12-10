
precision highp float;

in vec2 texture_;

out vec4 color;

uniform sampler2D texture_sample;

void main() {

	color = texture(texture_sample, texture_);

}
