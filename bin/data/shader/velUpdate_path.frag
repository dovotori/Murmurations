#version 330

in vec2 fragTexture;

uniform sampler2D prevVelData;   // vitesse precedente
uniform sampler2D posData;      // position
uniform int resolution;

out vec4 outputColor;





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



vec3 seek(vec3 position, vec3 cible, float vitesseMax)
{
  // ATTIRER PAR LA CIBLE
  vec3 direction = cible - position;
  direction *= vitesseMax;
  direction = normalize(direction);
  return direction;
}





vec3 getPathTarget(vec3 predictionPos, vec3 origine, vec3 destination)
{
    vec3 pathDir = destination - origine;
    vec3 originToPos = predictionPos - origine;

    vec3 distanceSurPath = normalize(pathDir);
    distanceSurPath *= dot(originToPos, normalize(pathDir)); // raccourci pour la longueur de l'adjacent

    return origine + distanceSurPath;
}




vec3 followPath(vec3 pos, vec3 vel)
{

    vec3 predictionPos = pos; 

    vec3 pointsPath[4];
    pointsPath[0] = vec3(0.0, 0.5, 0.5);
    pointsPath[1] = vec3(0.3, 0.2, 0.5);
    pointsPath[2] = vec3(0.7, 0.8, 0.5);
    pointsPath[3] = vec3(1.0, 0.5, 0.5);

    float distancePlusProche = 100000.0;
    vec3 destination = vec3(0.0);

    
    int i;
    for(i = 0; i < pointsPath.length()-1; i++)
    {
        vec3 a = pointsPath[i];
        vec3 b = pointsPath[i+1];
        
        vec3 normalPoint = getPathTarget(predictionPos, a, b);

        if (normalPoint.x < a.x || normalPoint.x > b.x) { // hors du path
            normalPoint = b;
        }

        float distance = length(predictionPos - normalPoint);

        if (distance < distancePlusProche) {
            distancePlusProche = distance;
            destination = normalPoint;
        }
    }
    



    float vitesseMax = 1.0;
    return seek(pos, destination, vitesseMax);
}




void main(void)
{
    vec2 st = fragTexture * resolution;    	  // recupere la particule

    vec3 pos = texture(posData, st).xyz;      // sa position
    vec3 vel = texture(prevVelData, st).xyz;  // sa precedente vitesse

    vec3 nextVel = followPath(pos, vel);

    outputColor = vec4(nextVel, 1.0);
}






