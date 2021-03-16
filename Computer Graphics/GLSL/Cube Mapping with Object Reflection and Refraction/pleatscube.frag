#version 330 compatibility

uniform sampler3D	Noise3;
uniform float 		uNoiseAmp;
uniform float 		uNoiseFreq;
uniform float		uEta;
uniform float 		uMix;
uniform samplerCube uReflectUnit;
uniform samplerCube uRefractUnit;

in vec3	vMC;
in vec3	vNs;
in vec3	vEs;

const vec4  WHITE = vec4( 1.,1.,1.,1. );


vec3
RotateNormal( float angx, float angy, vec3 n )
{
	float cx = cos( angx );
	float sx = sin( angx );
	float cy = cos( angy );
	float sy = sin( angy );

	// rotate about x:
	float yp =  n.y*cx - n.z*sx;	// y'
	n.z      =  n.y*sx + n.z*cx;	// z'
	n.y      =  yp;
	// n.x      =  n.x;

	// rotate about y:
	float xp =  n.x*cy + n.z*sy;	// x'
	n.z      = -n.x*sy + n.z*cy;	// z'
	n.x      =  xp;
	// n.y      =  n.y;

	return normalize( n );
}


void
main( )
{
	vec3 Normal = vNs; //?????	// remember to unitize this
	vec3 Eye =    normalize(vEs); //?????	// remember to unitize this

  //vec3 pNorm = normalize(gl_NormalMatrix * gl_Normal);
  //vec3 pEye = normalize(ECposition - vec3(0.,0.,0.));

	vec4 nvx = texture( Noise3, uNoiseFreq*vMC );
	vec4 nvy = texture( Noise3, uNoiseFreq*vec3(vMC.xy,vMC.z+0.5) );

	float angx = nvx.r + nvx.g + nvx.b + nvx.a;	//  1. -> 3.
	angx = angx - 2.;				// -1. -> 1.
	angx *= uNoiseAmp;

	float angy = nvy.r + nvy.g + nvy.b + nvy.a;	//  1. -> 3.
	angy = angy - 2.;				// -1. -> 1.
	angy *= uNoiseAmp;

	Normal = RotateNormal( angx, angy, Normal );
	Normal = normalize( gl_NormalMatrix * Normal );

	vec3 reflectVector = reflect(Eye, Normal);
	vec4 reflectColor = textureCube(uReflectUnit, reflectVector);

	vec3 refractVector = refract(Eye, Normal, uEta);

	vec4 refractColor = textureCube(uRefractUnit, refractVector);
	if( all( equal( refractVector, vec3(0.,0.,0.) ) ) )
	{
		refractColor = reflectColor;
	}
	else
	{
		refractColor = texture( uRefractUnit, refractVector );
		refractColor = mix( refractColor, WHITE, 0.30 );
	}
	gl_FragColor = vec4( mix(refractColor, reflectColor, uMix).rgb, 1.);
}
