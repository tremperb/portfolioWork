#version 330 compatibility


in vec2 vST;

in vec3 vMc;
in vec3 vNs;
in vec3 vEs;
in vec3 vLs;

//Lighting
uniform float uKa, uKd;


// Coloring
uniform float uTol;
uniform float uNoiseAmp;
uniform float uNoiseFreq;
uniform sampler2D uHgtUnit;
uniform sampler3D nMap;
uniform float Timer;
uniform float uSpeed;

const float Level1 = 0.25;
const float level2 = 0.40;
const float Level3 = 0.50;
const float Level4 = 0.60;


vec3
RotateNormal( float angx, float angy, vec3 n )
{

        float cx = cos( angx );
        float sx = sin( angx );
        float cy = cos( angy );
        float sy = sin( angy );

        // rotate about x:
        float yp =  n.y*cx - n.z*sx;    // y'
        n.z      =  n.y*sx + n.z*cx;    // z'
        n.y      =  yp;
        // n.x      =  n.x;

        // rotate about y:
        float xp =  n.x*cy + n.z*sy;    // x'
        n.z      = -n.x*sy + n.z*cy;    // z'
        n.x      =  xp;
        // n.y      =  n.y;

        return normalize( n );
}

vec3
HeightColor( float t )
{
	t = clamp( t, 0., 1. );

	vec3 rgb = vec3(1., .6, 0.);
	if(t < Level1) { // If we are less lets go ahead and create a sub level
		// this will only really happen when our timer resets
			if( t >= Level1/4.)
			{
				rgb.r = 1.;
				rgb.g = 1. - 4. * ( t - Level1 );
				rgb.b = 0.;
			}

			if( t >= level2/4. )
			{
				rgb.r = 4. * ( t - level2 );
				rgb.g = 4. * ( t - level2 );
				rgb.b = 4. * ( t - level2 );
			}

			if( t >= Level3/4. )
			{
				rgb.r = 1.;
				rgb.g = 1. - 4. * ( t - Level3 );
				rgb.b = 4. * ( t - Level3 );
			}

			if( t >= Level4/4. )
			{
				rgb.r = 1. - 4. * ( t - Level4 );
				rgb.g = 1.;
				rgb.b = 1.;
			}
	}

	if( t >= Level1)
	{
		rgb.r = 1.;
		rgb.g = 1. - 4. * ( t - Level1 );
		rgb.b = 0.;
	}

	if( t >= level2 )
	{
		rgb.r = 4. * ( t - level2 );
		rgb.g = 4. * ( t - level2 );
		rgb.b = 4. * ( t - level2 );
	}

	if( t >= Level3 )
	{
		rgb.r = 1.;
		rgb.g = 1. - 4. * ( t - Level3 );
		rgb.b = 4. * ( t - Level3 );
	}

	if( t >= Level4 )
	{
		rgb.r = 1. - 4. * ( t - Level4 );
		rgb.g = 1.;
		rgb.b = 1.;
	}

	return rgb;
}

void
main() {

  vec3 Normal = vNs;
  vec3 Eye = normalize(vEs);

  vec4 nvx = texture( nMap, uNoiseFreq * vMc );
	vec4 nvy = texture( nMap, uNoiseFreq * vec3(vMc.xy,vMc.z+0.5) );

  float angx = nvx.r + nvx.g + nvx.b + nvx.a;	//  1. -> 3.
	angx = angx - 2.;				// -1. -> 1.
	angx *= uNoiseAmp;

	float angy = nvy.r + nvy.g + nvy.b + nvy.a;	//  1. -> 3.
	angy = angy - 2.;				// -1. -> 1.
	angy *= uNoiseAmp;


  Normal = RotateNormal( angx, angy, Normal );
	Normal = normalize( gl_NormalMatrix * Normal );

  vec3 L = normalize(vLs);
  vec3 E = normalize(vEs);

    // Start height coloring

  // water, sand, grass, forest, dirt, snow
  float here = texture2D(uHgtUnit, vST * uNoiseFreq).r;
	here = here * Timer;

	vec3 color = HeightColor(here);


  vec3 ambientColor = uKa * color;

  float diffuseIntensity = dot(Normal, L);
  vec3 diffuseColor = uKd * diffuseIntensity * color;




  gl_FragColor = vec4(ambientColor.rgb + diffuseColor.rgb, 1.);



}
