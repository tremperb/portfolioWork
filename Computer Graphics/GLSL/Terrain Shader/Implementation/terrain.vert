#version 330 compatibility

uniform sampler2D uHgtUnit;

uniform float uNoiseAmp;
uniform float uNoiseFreq;
uniform float uWaterMax; // this will be our min value
uniform float uLevels;
uniform bool uUseLevels;

uniform float uLightX, uLightY, uLightZ;

out float vLightIntensity;

out vec3  vMc;

out vec2 vST;
out vec3 vNs;
out vec3 vEs;
out vec3 vLs;

vec3 eyeLightPosition = vec3 (uLightX, uLightY, uLightZ);


void
main( )
{
	vST = gl_MultiTexCoord0.st;

	vec3 tnorm = normalize( gl_NormalMatrix * gl_Normal );


	vec4 newVert = gl_Vertex;

	float loc = texture2D(uHgtUnit, vST * uNoiseFreq).r;
	loc *= uNoiseAmp;
	if(uUseLevels) {
		loc = round((loc*2) * uLevels) / uLevels;
		loc /= 2.;

	}

	if(loc <= uWaterMax) {
		newVert = vec4(gl_Vertex.x, ((uWaterMax) - uNoiseAmp / 2) * 3, gl_Vertex.z, gl_Vertex.w);
	}
	else {
		newVert = vec4(gl_Vertex.x, ((loc) - uNoiseAmp / 2) * 3, gl_Vertex.z, gl_Vertex.w);
	}

	vNs = tnorm;

	// Set up per frag lighting
	vec4 ECposition = gl_ModelViewMatrix * newVert;

	vLs = eyeLightPosition - ECposition.xyz;

	vEs = vec3(0., 0., 0.) - ECposition.xyz;

	vMc = newVert.xyz;

	gl_Position = gl_ModelViewProjectionMatrix * newVert;
}
