#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : require
//#version 150
//#extension GL_ARB_texture_rectangle : enable

vec3 rotateVectorByQuaternion( vec3 v, vec4 q ) {
	
	vec3 dest = vec3( 0.0 );
	
	float x = v.x, y  = v.y, z  = v.z;
	float qx = q.x, qy = q.y, qz = q.z, qw = q.w;
	
	// calculate quaternion * vector
	float ix =  qw * x + qy * z - qz * y,
	iy =  qw * y + qz * x - qx * z,
	iz =  qw * z + qx * y - qy * x,
	iw = -qx * x - qy * y - qz * z;
	
	// calculate result * inverse quaternion
	dest.x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
	dest.y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
	dest.z = iz * qw + iw * -qz + ix * -qy - iy * -qx;
	
	return dest;
}

vec3 qtransform( vec4 q, vec3 v ){
	return v + 2.0*cross(cross(v, q.xyz ) + q.w*v, q.xyz);
}
float lengthSquared(vec3 v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

vec4 makeRotate( vec3 sourceVector, vec3 targetVector )
{
	vec4 _v;

	float fromLen2 = lengthSquared(sourceVector);
	float fromLen;
	// normalize only when necessary, epsilon test
	if ((fromLen2 < 1.0 - 1e-7) || (fromLen2 > 1.0 + 1e-7)) {
		fromLen = sqrt(fromLen2);
		sourceVector /= fromLen;
	} else fromLen = 1.0;

	float toLen2 = lengthSquared(targetVector);
	// normalize only when necessary, epsilon test
	if ((toLen2 < 1.0 - 1e-7) || (toLen2 > 1.0 + 1e-7)) {
		float toLen;
		// re-use fromLen for case of mapping 2 vectors of the same length
		if ((toLen2 > fromLen2 - 1e-7) && (toLen2 < fromLen2 + 1e-7)) {
			toLen = fromLen;
		} else toLen = sqrt(toLen2);
		targetVector /= toLen;
	}
	
	
	// Now let's get into the real stuff
	// Use "dot product plus one" as test as it can be re-used later on
	float dotProdPlus1 = 1.0 + dot(sourceVector, targetVector);

	if (dotProdPlus1 < 1e-7)
	{
		if (abs(sourceVector.x) < 0.6) {
			float norm = sqrt(1.0 - sourceVector.x * sourceVector.x);
			_v.x = 0.0;
			_v.y = sourceVector.z / norm;
			_v.z = -sourceVector.y / norm;
			_v.w = 0.0;
		} else if (abs(sourceVector.y) < 0.6) {
			float norm = sqrt(1.0 - sourceVector.y * sourceVector.y);
			_v.x = -sourceVector.z / norm;
			_v.y = 0.0;
			_v.z = sourceVector.x / norm;
			_v.w = 0.0;
		} else {
			float norm = sqrt(1.0 - sourceVector.z * sourceVector.z);
			_v.x = sourceVector.y / norm;
			_v.y = -sourceVector.x / norm;
			_v.z = 0.0;
			_v.w = 0.0;
		}
	}
	
	else {
		// Find the shortest angle quaternion that transforms normalized vectors
		// into one other. Formula is still valid when vectors are colinear
		float s = sqrt(0.5 * dotProdPlus1);
		vec3 tmp = cross(sourceVector, targetVector) / (2.0 * s);
		_v.x = tmp.x;
		_v.y = tmp.y;
		_v.z = tmp.z;
		_v.w = s;
	}
	
	return _v;
}


uniform sampler2DRect posTexture;
uniform sampler2DRect velTexture;
uniform sampler2DRect quatTexture;
uniform sampler2DRect colTexture;

uniform vec3 camPos;

uniform float dim;
uniform float dimX;
uniform float dimY;

varying vec4 color;

varying vec3 norm;
varying vec4 vPos;
varying vec3 ePos;
varying vec2 uv;

varying float fogMix;



void main()
{
	uv = gl_MultiTexCoord0.xy;
	
//	float scl = 10.;
	vec4 v = gl_Vertex;// * vec4(scl,scl,scl, 1.);
	
//	float s = mod(float(gl_InstanceID), dimY);
//	float t = floor(float(gl_InstanceID) / dimY);
	
	vec2 st = vec2(mod(float(gl_InstanceID), dimY), floor(float(gl_InstanceID) / dimY));
	
	color = texture2DRect( colTexture, st );
	vec4 q = texture2DRect( quatTexture, st );
	vec3 pos = texture2DRect( posTexture, st ).xyz;
	vec3 velDir = (texture2DRect( velTexture, st ).xyz);
	
	norm = gl_NormalMatrix * qtransform(q, gl_Normal);
	v.xyz = qtransform(q, v.xyz);
	
	norm = gl_NormalMatrix * gl_Normal;

	v.xyz += pos;
	
	vPos = v;
	
	vec4 ecPosition = gl_ModelViewMatrix * v;
	ePos = normalize(ecPosition.xyz/ecPosition.w);
	gl_Position = gl_ProjectionMatrix * ecPosition;
	
	fogMix = 1. - pow(abs(vPos.y) / dim, 10.);
	
	fogMix *= clamp(1. - pow(distance(camPos, vPos.xyz) / 1000., 3.), 0., 1.);
}

