
precision highp float;

out vec4 frag_color;

uniform float time;
uniform vec2 resolution;

void main() {

	vec4 color = vec4(0.5, 0.7, 1.0, 1.0);

	int total = 15;
	float diameter = 0.35f;

	vec2 center = vec2(0.5f);

	vec2 uv = gl_FragCoord.xy / resolution.xy;
	uv.y *= resolution.x / resolution.y;

	vec2 offset = uv - center + time;

	vec2 repeat = vec2(

		fract(offset.x * float(total)),

		fract(offset.y * float(total)) 

	);

	if(length(repeat - center) < diameter)

		color = vec4(0.0);

	frag_color = color;

}
