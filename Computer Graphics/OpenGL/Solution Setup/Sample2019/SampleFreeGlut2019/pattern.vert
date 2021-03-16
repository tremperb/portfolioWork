#version 330 compatibility

uniform float	uTime;		// "Time", from Animate( )
uniform bool uAnimateV; //

out vec2  	vST;		// texture coords
// Lighting stuff
out  vec3  vN;		// normal vector
out  vec3  vL;		// vector from point to light
out  vec3  vE;		// vector from point to eye


const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency
// Light
vec3 LightPosition = vec3(  5., 5., -5. );

void
main( )
{ 

	vST = gl_MultiTexCoord0.st;

	vec3 vert = gl_Vertex.xyz;
	if(uAnimateV) {
		vert.x *= cos(2 * PI * uTime); //something fun of your own design
		vert.y *= sin(2 * PI * W * uTime); // something fun of your own design
		vert.z *= cos(tan(2 * PI * uTime) * AMP); //something fun of your own design
	}
	

	//Lighting Stuff
	vec4 ECposition = gl_ModelViewMatrix * vec4( vert, 1. );
	vN = normalize( gl_NormalMatrix * gl_Normal );	// normal vector
	vL = LightPosition - ECposition.xyz;			// vector from the point
													// to the light position
	vE = vec3( 0., 0., 0. ) - ECposition.xyz;		// vector from the point
													// to the eye position 
	gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );


}
