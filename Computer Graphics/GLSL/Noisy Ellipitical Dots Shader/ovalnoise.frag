#version 330 compatibility

in float vLightIntensity;
in vec2 vST;
in vec3 vMCposition;

uniform float uAd;
uniform float uBd;
uniform float uTol;
uniform float uNoiseAmp;
uniform float uNoiseFreq;
uniform float uAlpha;
uniform sampler3D Noise3;

const vec3 WHITE = vec3(1., 1., 1.);
// Going to do beaver ORANGE
// RGB: 215-63-9
const vec3 ORANGE = vec3((215. / 255.), (63. / 255.), (9. / 255.));

void
main() {

  // Want to key off st values
  // Dont have to redefine but it is easier to visualize with equation
  float s = vST.s;
  float t = vST.t;

  // Now get Ar and Br which is the raidus of the a and b diameter
  float Ar = uAd / 2.;
  float Br = uBd / 2.;

  // Now we need to find the ellipse centers
  // Get the location in order to calculate the center
  // Note since float we need to cast as int
  int num_in_s = int(s / uAd);
  int num_in_t = int(t / uBd);

  // so now find the actual center
  // num in * diameter + radius
  // Idea credit to dots lecture notes
  float sc = num_in_s * uAd + Ar;
  float tc = num_in_t * uBd + Br;

  // Now plug in all that to get elispse equation results
  // isolate s and t
  float d_s = ((s - sc) / (Ar)) * ((s - sc) / (Ar));
  float d_t = ((t - tc) / (Br)) * ((t - tc) / (Br));

  //so our final result of both s and t
  float d = d_s + d_t;

  // Everything else from last assignment
  // Now Start Noise

  vec4 nv  = texture3D( Noise3, uNoiseFreq*vMCposition );

  // give the noise a range of [-1.,+1.]:

  float n = nv.r + nv.g + nv.b + nv.a;    //  1. -> 3.
  n = n - 2.;                             // -1. -> 1.
  n *= uNoiseAmp;

  // determine the color based on the noise-modified (s,t):

  float sc_n = float(num_in_s) * uAd  +  Ar;
  float ds = s - sc_n;                   // wrt ellipse center
  float tc_n = float(num_in_t) * uBd  +  Br;
  float dt = t - tc_n;                   // wrt ellipse center

  float oldDist = sqrt( ds*ds + dt*dt );
  // Newdist? old plus n
  float newDist = oldDist + n;
  float scale = newDist / oldDist;        // this could be < 1., = 1., or > 1.

  ds *= scale;
  ds /= Ar;
  dt *= scale;
  dt /= Br;

  float d_noise = ds * ds + dt * dt;
  //


  float t_smooth = smoothstep( 1. - uTol, 1. + uTol, d_noise );
  vec3 color = mix(ORANGE, WHITE, t_smooth);

  // Now do transparency last of vec4 is ualpha
  // but only want to edit when color is WHITE
  // if zero then just get rid of it.
  if(color == WHITE) {
    color = uAlpha * WHITE + (1-uAlpha) * color;
    if(uAlpha == 0.)
      discard;
    // good now set it unless it was simply discarded
    gl_FragColor = vec4(vLightIntensity * color, uAlpha);
  }
  else {
    // good now set it
    gl_FragColor = vec4(vLightIntensity * color, 1);
  }


}
