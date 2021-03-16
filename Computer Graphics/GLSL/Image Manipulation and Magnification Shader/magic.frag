#version 330 compatibility

uniform float uSc;
uniform float uTc;
uniform float uRadius; // The radius of circle
uniform float uDs; // switch to circle dont need anymore
uniform float uDt;
uniform float uMagFactor;
uniform float uRotAngle;
uniform float uSharpFactor;
uniform sampler2D uImageUnit;
uniform bool uUseCircle;

in vec2 vST;

//const vec3 WHITE = vec3(1., 1., 1.); // just for testing the boundaries
// did indeed turn white when tested and could move/scale

void
main( )
{
	// (x-h)^2 + (y-k)^2 = r^2
	float sCen = pow(uSc - vST.s, 2);
	float tCen = pow(uTc - vST.t, 2);
	float circleCondition = sqrt(sCen + tCen);

	// Start rectangle
	bool inRectangle = false;
	if(vST.s < (uSc + uDs) && vST.s > (uSc - uDs) && vST.t < (uTc + uDt) && vST.t > (uTc - uDt))
		inRectangle = true;


	// okay now lets compare to our bounds
	// Start with quad first if everything goes good we can move to circle
	if((uUseCircle && circleCondition <= uRadius) || (!uUseCircle && inRectangle)) {
		vec2 magST = vST;

		// Translate by center
		magST.s -= uSc;
		magST.t -= uTc;

		// Magnify
		magST.s /= uMagFactor; // divide multiplying makes us go the opposite
		magST.t /= uMagFactor;

		// Rotate
		float s = magST.s;
		float t = magST.t;
		float theta = uRotAngle;

		// Want the inverse and respect to center
		magST.s = s * cos(theta) + t * sin(theta) + uSc;
		magST.t = -s * sin(theta) + t * cos(theta) + uTc;


		// Sharpening from notes
		ivec2 ires = textureSize( uImageUnit, 0);
		float ResS = float( ires.s );
		float ResT = float( ires.t );

		vec2 stp0 = vec2(1./ResS, 0. );
		vec2 st0p = vec2(0. , 1./ResT);
		vec2 stpp = vec2(1./ResS, 1./ResT);
		vec2 stpm = vec2(1./ResS, -1./ResT);
		vec3 i00 = texture2D( uImageUnit, magST ).rgb;
		vec3 im1m1 = texture2D( uImageUnit, magST-stpp ).rgb;
		vec3 ip1p1 = texture2D( uImageUnit, magST+stpp ).rgb;
		vec3 im1p1 = texture2D( uImageUnit, magST-stpm ).rgb;
		vec3 ip1m1 = texture2D( uImageUnit, magST+stpm ).rgb;
		vec3 im10 = texture2D( uImageUnit, magST-stp0 ).rgb;
		vec3 ip10 = texture2D( uImageUnit, magST+stp0 ).rgb;
		vec3 i0m1 = texture2D( uImageUnit, magST-st0p ).rgb;
		vec3 i0p1 = texture2D( uImageUnit, magST+st0p ).rgb;
		vec3 target = vec3(0.,0.,0.);
		target += 1.*(im1m1+ip1m1+ip1p1+im1p1);
		target += 2.*(im10+ip10+i0m1+i0p1);
		target += 4.*(i00);
		target /= 16.;

		// end sharpening

		// mix based on our sharpening, and new magnified s and t vector for our image
		gl_FragColor = vec4(mix(target, texture(uImageUnit, magST).rgb, uSharpFactor ), 1.); // tested with white and works
	}
	else {
		gl_FragColor = vec4(texture2D(uImageUnit, vST).rgb, 1.);
	}
}
