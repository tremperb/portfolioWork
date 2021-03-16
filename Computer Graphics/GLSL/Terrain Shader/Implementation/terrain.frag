#version 330 compatibility

in float vLightIntensity;
in vec2 vST;

in vec3 vMc;
in vec3 vNs;
in vec3 vEs;
in vec3 vLs;

uniform float uKa, uKd;


// Coloring
uniform float uTol;
uniform float uNoiseAmp;
uniform float uNoiseFreq;
uniform sampler2D uHgtUnit;
uniform sampler3D nMap;

uniform float uWaterMax;
uniform float uSandMax;
uniform float uGrassMax;
uniform float uForestMax;
uniform float uDirtMax;
uniform float uLevels;
uniform bool uUseLevels;

// water, sand, grass, forest, dirt, snow
const vec3 WATER = vec3( (212. / 255.), (241. / 255.), (249. / 255.));
const vec3 SAND = vec3( 214. / 255., 208. / 255., 185. / 255.);
const vec3 GRASS = vec3( 91. / 255., 162. / 255., 131. / 255.);
const vec3 FOREST = vec3(  65. / 255., 82. / 255., 65. / 255.);
const vec3 DIRT = vec3(  155. / 255., 118. / 255., 83. / 255.);
const vec3 SNOW = vec3( 1.0, 1.0, 1.0 );//vec3(  224. / 255., 220. / 255., 219. / 255.);



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

void
main() {

  vec3 Normal = vNs;
  vec3 Eye = normalize(vEs);

  // Similarily from before this part is relatively just to set up lighting
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
  // if using levels we are going to rounud the value out
  if(uUseLevels) {
		here = round(here * uLevels) / uLevels;
	}


  // Base case is water
  vec3 color = WATER;

  // Based on levels via height
  // as in each level builds off the previous
  if(here > uWaterMax) {
    float t = smoothstep(uWaterMax - uTol, uWaterMax + uTol, here);
    color = mix(WATER, SAND, t);
  }
  if(here > (uWaterMax + uSandMax)) {
    float t = smoothstep(uSandMax - uTol, uSandMax + uTol, here);
    color = mix(SAND, GRASS, t);
  }
  if(here > (uWaterMax + uSandMax + uGrassMax)) {
    float t = smoothstep(uGrassMax - uTol, uGrassMax + uTol, here);
    color = mix(GRASS, FOREST, t);
  }
  if(here > (uWaterMax + uSandMax + uGrassMax + uForestMax)) {
    float t = smoothstep(uGrassMax - uTol, uGrassMax + uTol, here);
    color = mix(FOREST, DIRT, t);
  }
  if(here > (uWaterMax + uSandMax + uGrassMax + uForestMax + uDirtMax)) {
    float t = smoothstep(uDirtMax - uTol, uDirtMax + uTol, here);
    color = mix(DIRT, SNOW, t);
  }

  // That does it for height coloring
  // Now finish it off with lighting

  // Just went ahead and did ambient and diffuse
  vec3 ambientColor = uKa * color;

  float diffuseIntensity = dot(Normal, L);
  vec3 diffuseColor = uKd * diffuseIntensity * color;


  gl_FragColor = vec4(ambientColor.rgb + diffuseColor.rgb, 1.);
}
