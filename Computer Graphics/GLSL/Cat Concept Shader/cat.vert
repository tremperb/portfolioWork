#version 330 compatibility

uniform float uLightX, uLightY, uLightZ;


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

	vNs = tnorm;

	// Set up per frag lighting
	vec4 ECposition = gl_ModelViewMatrix * gl_Vertex;

	vLs = eyeLightPosition - ECposition.xyz;

	vEs = vec3(0., 0., 0.) - ECposition.xyz;

	vMc = gl_Vertex.xyz;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
