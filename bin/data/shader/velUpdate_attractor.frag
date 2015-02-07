#version 330

in vec2 fragTexture;

uniform sampler2D prevVelData;   // vitesse precedente
uniform sampler2D posData;      // position
uniform int resolution;

out vec4 outputColor;



vec3 attract(vec3 pos, vec3 vel)
{
	float radious = 0.5;
	float strength = 1.0;
	float ramp = 1.0;

	vec3 positionAttractor = vec3(0.5, 0.5, 0.0);
	vec3 d = positionAttractor - pos;
    float distance = length(d);

    if(distance > 0 && distance < radious)
    {
        float s = distance / radious;
        float force = 1.0 / pow(s, (0.5 * ramp)) - 1.0;
        force = strength * force / radious;

        return vel + (d * force);
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
    nextVel = limiter(nextVel, 1.0);

    outputColor = vec4(nextVel, 1.0);
}






