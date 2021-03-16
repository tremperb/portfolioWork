#version 330 compatibility

in vec3 vNs;
in vec3 vLs;
in vec3 vEs;
in vec3 vMc;

uniform float uNoiseAmp;
uniform float uNoiseFreq;

uniform float uShininess;
uniform vec4 uColor;
uniform vec4 uSpecularColor;

uniform float uKa, uKd, uKs;

uniform sampler3D Noise3;


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

        vec4 nvx = texture( Noise3, uNoiseFreq*vMc );
        float angx = nvx.r + nvx.g + nvx.b + nvx.a  -  2.;
        angx *= uNoiseAmp;

        vec4 nvy = texture( Noise3, uNoiseFreq*vec3(vMc.xy,vMc.z+0.5) );
        float angy = nvy.r + nvy.g + nvy.b + nvy.a  -  2.;
        angy *= uNoiseAmp;

        vec3 rNormal = RotateNormal(angx, angy, vNs);

        vec3 L = normalize(vLs);

        vec3 E = normalize(vEs);

        vec4 ambientColor = uKa * uColor;

        float diffuseIntensity = dot(rNormal, L);
        vec4 diffuseColor = uKd * diffuseIntensity * uColor;

        float specularIntensity = 0.;
        if( dot(rNormal, L) > 0. ) // only do specular if the light can see the point
        {
            vec3 ref = normalize( 2. * rNormal * dot(rNormal, L) - L );
            specularIntensity = pow( max( dot(E,ref),0. ), uShininess );
        }


        vec4 specularColor = uKs * specularIntensity * uSpecularColor;

        gl_FragColor = vec4(ambientColor.rgb + diffuseColor.rgb + specularColor.rgb, 1.);

}
