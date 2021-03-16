#version 330 compatibility

// Vertex program to aid in lighting
// Nothing extra needs to be done here besides defining vST
// Credit: Mike Bailey

out vec3  vMCposition;
out float vLightIntensity;
out vec2 vST;

const vec3 LIGHTPOS   = vec3( -2., 0., 10. );

void
main( )
{
	vST = gl_MultiTexCoord0.st;

	vec3 tnorm = normalize( gl_NormalMatrix * gl_Normal );
	vec3 ECposition = vec3( gl_ModelViewMatrix * gl_Vertex );
	vLightIntensity = abs( dot( normalize(LIGHTPOS - ECposition), tnorm ) );

	vMCposition  = gl_Vertex.xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
