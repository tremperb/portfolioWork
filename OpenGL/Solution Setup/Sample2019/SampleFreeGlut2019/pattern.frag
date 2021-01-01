#version 330 compatibility

uniform float	uTime;		// "Time", from Animate( )
uniform bool uAnimateF;
// LightSTuff
uniform float   uKa, uKd;		// coefficients of each type of lighting
uniform vec3  uColor;			// object color



in vec2  	vST;		// texture coords
// Light Stuff
in  vec3  vN;			// normal vector
in  vec3  vL;			// vector from point to light
in  vec3  vE;			// vector from point to eye


const float PI = 	3.14159265;
const float AMP = 	1.0;		// amplitude
const float W = 	2.;		// frequency

float animTime;

void
main( )
{

	animTime = uTime;

	if(!uAnimateF) {
		animTime = 0.75;
	}
	


	// Light Stuff
	vec3 Normal = normalize(vN);
	vec3 Light     = normalize(vL);
	vec3 Eye        = normalize(vE);

	vec3 myColor = uColor;

	
	float wavesSin = sin(animTime * PI);
	float wavesCos = cos(animTime * PI);
	
	if(vST.s < sin((vST.t * wavesSin * 2) * W))
		myColor = vec3(1., animTime, 0.);
	else if(vST.s < cos((vST.t * wavesCos * 2) * W))
		myColor = vec3(animTime, 0., 1.);
	else 
		myColor =  vec3( uColor.x, uColor.y, animTime);


	
	vec3 ambient = uKa * myColor;

	float d = max( dot(Normal,Light), 0. );       // only do diffuse if the light can see the point
	vec3 diffuse = uKd * d * myColor;

	
	
	gl_FragColor = vec4( ambient + diffuse,  1. );
}