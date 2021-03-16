#version 330 compatibility

out vec2 vST; // just using to get our st coordinates

void
main( )
{
	// Just a picture so no lighting just want to grab our s and t values really
	vST = gl_MultiTexCoord0.st;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
