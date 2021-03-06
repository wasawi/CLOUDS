
#version 120

uniform sampler2DRect position;
uniform sampler2DRect velocity;

uniform float t;
uniform float dt;

vec4 getPosition() {
	return texture2DRect(position, floor(gl_TexCoord[0].xy) + vec2(.5,.5));
}

vec4 getVelocity() {
	return texture2DRect(velocity, gl_TexCoord[0].xy);
}

//this function is a force and returns velocity
void main() {
	vec4 position = getPosition();
	vec4 velocity = getVelocity();
	
	if (position.y < 0.0)
		velocity.y = abs(velocity.y);
	gl_FragColor = velocity;
}