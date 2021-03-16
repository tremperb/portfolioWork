// samplerCube doesnt want to work
uniform sampler2D uTexUnit;


void
main( )
{
	vec3 newcolor = texture2D( uTexUnit, gl_TexCoord[0].st ).rgb;
	gl_FragColor = vec4( newcolor.rgb, 1. );
}
