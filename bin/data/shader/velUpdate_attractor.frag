#version 330

in vec2 fragTexture;

uniform sampler2D prevVelData;   // vitesse precedente
uniform sampler2D posData;      // position
uniform int resolution;
uniform float maxSpeed;

uniform float ramp;
uniform float radious;
uniform float strength;
uniform vec3 positionAttractor;

out vec4 outputColor;



vec3 attract(vec3 pos, vec3 vel)
{

	vec3 dif = positionAttractor - pos;
    float distance = length(dif);

    if(distance > 0 && distance < radious && radious > 0.0)
    {
        float t = pow((distance/radious), ramp);
        float force = (1.0 / t) - 1.0;
        return vel + (dif * force);
    } else {
    	return vel;
    }

}


vec3 limiter(vec3 v, float max)
{
    vec3 resultat = v;
    float longueurCarre = (resultat.x * resultat.x) + (resultat.y * resultat.y) + (resultat.z * resultat.z);

    if( ( longueurCarre > max * max ) && ( longueurCarre > 0 ) )
    {
        float ratio = max / sqrt( longueurCarre );
        resultat.x *= ratio;
        resultat.y *= ratio;
        resultat.z *= ratio;
    }
    return resultat;
}



void main(void)
{
    vec2 st = fragTexture * resolution;    	  // recupere la particule

    vec3 pos = texture(posData, st).xyz;      // sa position
    vec3 vel = texture(prevVelData, st).xyz;  // sa precedente vitesse

    vec3 nextVel = attract(pos, vel);
    nextVel = limiter(nextVel, maxSpeed);

    outputColor = vec4(nextVel, 1.0);
}






