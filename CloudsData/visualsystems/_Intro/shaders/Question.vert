#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect image;

uniform float minPointSize;
uniform float maxPointSize;
uniform float minDistance;
uniform float maxDistance;

float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) 
{
	return ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
}

const float epsilon = 1e-6;

void main(void)
{
	// passes the  texture coordinates along to the fragment shader
	//gl_TexCoord[0] = gl_MultiTexCoord0;
	
							 //snoise(vec4(gl_Vertex.zxy / noiseDensity, noisePosition)));
	
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	

	//gl_PointSize = clamp(map(pow(gl_Position.z,1.5), maxDistance, minDistance, minPointSize, maxPointSize),
	//						minPointSize, maxPointSize);
	gl_PointSize = 2.5;
	
	//pass color info along
	gl_FrontColor = gl_Color * clamp(map(gl_Position.z, minDistance, maxDistance, 1.0, 0.0), 0.0, 1.0);
}
