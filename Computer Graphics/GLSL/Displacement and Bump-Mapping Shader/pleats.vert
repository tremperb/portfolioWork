#version 330 compatibility

#define A_PI 3.14159265
// Define approximate pi value

uniform float uLightX, uLightY, uLightZ;
uniform float uK, uP;

out vec3 vNf;
		 out vec3 vNs;
out vec3 vLf;
		 out vec3 vLs;
out vec3 vEf;
		 out vec3 vEs;
		 out vec3 vMc;


vec3 eyeLightPosition = vec3( uLightX, uLightY, uLightZ );

void
main( )
{
	// Just manually setting this. could change it but this works
	float uY0 = 1.;
	// Need per fragment lighting
	// sin way calculate new vertex
	float z = uK * (uY0 - gl_Vertex.y) * sin(2. * A_PI * gl_Vertex.x / uP);
	vec4 newVert = vec4(gl_Vertex.x, gl_Vertex.y, z, gl_Vertex.w);
	vec4 ECposition = gl_ModelViewMatrix * newVert;


	// Find tangents
	float dzdx = uK * (uY0 - gl_Vertex.y) * (2. * A_PI/uP) * cos(2. * A_PI * gl_Vertex.x / uP);     //K * (Y0-y) * (2.*PI/P) * cos( 2.*PI*x/P )
	float dzdy = -uK * sin(2. * A_PI * gl_Vertex.x / uP);			//-K * sin( 2.*PI*x/P )
	vec3 Tx = vec3(1., 0., dzdx );
	vec3 Ty = vec3(0., 1., dzdy );
	vec3 newNormal = cross(Tx, Ty);

	// Set up per fragment lighting just like lecture notes
	vNf = normalize( gl_NormalMatrix * newNormal ); // surface normal vector
	vNs = vNf;

	vLf = eyeLightPosition - ECposition.xyz; // vector from the point
	vLs = vLf; // to the light position

	vEf = vec3( 0., 0., 0. ) - ECposition.xyz; // vector from the point
	vEs = vEf ; // to the eye position

	vMc = newVert.xyz;

	gl_Position = gl_ModelViewProjectionMatrix * newVert;

}
