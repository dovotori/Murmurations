#version 330

in vec2 fragTexture;

uniform sampler2D prevVelData;   // recive the previus velocity texture
uniform sampler2D posData;      // recive the position texture
uniform int resolution;
uniform vec4 rapportForces;

out vec4 outputColor;


/*////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// UTILS //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////*/


vec3 limiter(vec3 v, float max)
{
    float longueurCarre = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    if( ( longueurCarre > max * max ) && ( longueurCarre > 0 ) )
    {
        float ratio = max / sqrt( longueurCarre );
        v *= ratio;
    }
    return v;
}



vec3 seek(vec3 position, vec3 cible, float vitesseMax)
{
  // ATTIRER PAR LA CIBLE
  vec3 direction = cible - position;
  direction *= vitesseMax;
  direction = normalize(direction);
  return direction;
}



vec3 seekSteering(vec3 position, vec3 cible, vec3 vitesse, float vitesseMax, float forceMax, float masse)
{
  // ATTIRER PAR LA CIBLE AVEC UN SMOOTH DE TRAJECTOIRE
  vec3 directionDesiree = seek(position, cible, vitesseMax);
  vec3 direction = directionDesiree - vitesse;
  direction = limiter(direction, forceMax);
  direction /= masse; // la masse influe le temps pour changer de direction, plus grand plus long
  direction += vitesse;
  direction = limiter(direction, vitesseMax);
  return direction;
}




/*////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// FLOCKING //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////*/

uniform float masse;
uniform float forceMax;

uniform vec3 flockDistance;
uniform vec3 flockAmplitude;


vec3 flocking(vec3 pos, vec3 vel) {

    // SEPARATION ecarte les oiseaux
    vec3 forceSeparation = vec3(0.0);
    int cptSeparation = 0;

    // ALIGNEMENT dirige vers une direction commune
    vec3 forceAlignement = vec3(0.0);
    int cptAlignement = 0;

    // COHESION crée un groupe uni d'oiseaux
    vec3 forceCohesion = vec3(0.0);
    int cptCohesion = 0;

    int x = 0, y = 0;
    for(y = 0; y < resolution; y++)
    {
        for(x = 0; x < resolution; x++)
        {
            vec3 posVoisin = texture(posData, vec2(float(x) / float(resolution), y / float(resolution) ) ).xyz;
            vec3 velVoisin = texture(prevVelData, vec2(float(x) / float(resolution), float(y) / float(resolution ) ) ).xyz;

            float distance = length(posVoisin - pos);

            if(distance > 0.0) // exclue soit meme
            {

                // SEPARATION
                if(distance < flockDistance.x)
                {
                    forceSeparation += (pos - posVoisin) / distance;
                    cptSeparation++;
                }

                // ALIGNEMENT
                if(distance < flockDistance.y)
                {
                    forceAlignement += velVoisin;
                    cptAlignement++;
                }

                // COHESION
                if(distance < flockDistance.z)
                {
                    forceCohesion += posVoisin;
                    cptCohesion++;
                }

            }
        }
    }


    /////////////////////// DEFINITION DES FORCES ///////////////////////

    // SEPARATION
    if(cptSeparation > 0) {
        forceSeparation /= float(cptSeparation); // divise par le nombre de voisin
    
        if(length(forceSeparation) > 0.0)
        {
            forceSeparation = normalize(forceSeparation);

            // steer
            forceSeparation -= vel;
            forceSeparation = limiter(forceSeparation, forceMax);
        } 
    }

    // ALIGNEMENT
    if(cptAlignement > 0) {
        forceAlignement /= cptAlignement; // divise par le nombre de voisin
        forceAlignement = normalize(forceAlignement);

        // steer
        forceAlignement -= vel;
        forceAlignement = limiter(forceAlignement, forceMax);
    }

    // COHESION
    if(cptCohesion > 0) {
        forceCohesion /= cptCohesion;
        forceCohesion = seek(pos, forceCohesion, 1.0);
        forceCohesion = limiter(forceCohesion, forceMax);
    }

    /////////////////////// TOTAL FLOCKING ///////////////////////
    vec3 forces = forceSeparation * flockAmplitude.x;
    forces += forceAlignement * flockAmplitude.y;
    forces += forceCohesion * flockAmplitude.z;
    forces /= masse;
    

    /////////////////////// ON SORT DU CERCLE ///////////////////////
    //*
    vec3 centreHive = vec3(0.5);
    float rayonHive = 0.3;
    float distanceHive = length(centreHive - pos);
    if(distanceHive > rayonHive){
        float dif = ( distanceHive - rayonHive ) * 4.0;
        vec3 forceHive = seekSteering(pos, centreHive, forces, 1.0, forceMax, masse);
        forces = forceHive * dif;
    }
    //*/
    /*
    vec3 centreHive = vec3(0.5);
    float distanceHive = length(centreHive - pos);
    vec3 forceHive = seekSteering(pos, centreHive, forces, 1.0, forceMax, masse);
    forces = forces + ( forceHive * distanceHive * distanceHive );
    */
    /////////////////////// ON APPLIQUE ///////////////////////
    vel += forces;
    vel = limiter(vel, 1.0);
    return vel;

}






/*////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// ATTRACTOR //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////*/

uniform float ramp;
uniform float radious;
uniform float strength;
uniform vec3 positionAttractor;



vec3 attract(vec3 pos, vec3 vel)
{

    vec3 dif = positionAttractor - pos;
    float distance = length(dif);
    vec3 nextVel;

    if(distance > 0 && distance < radious && radious > 0.0)
    {
        float t = pow((distance/radious), ramp);
        float force = (1.0 / t) - 1.0;
        nextVel = vel + (dif * force /* strength*/);
    } else {
        nextVel = vel;
    }
    return limiter(nextVel, 1.0);
}



/*////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// PATH ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////*/

uniform float rayonPath;
uniform int path;


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
    switch(path)
    {
        case 0: // croissement
            pointsPath[0] = vec3(0.3, 0.5, 0.3);
            pointsPath[1] = vec3(0.4, 0.3, 0.8);
            pointsPath[2] = vec3(0.6, 0.7, 0.7);
            pointsPath[3] = vec3(0.7, 0.5, 0.2);
            break;
        case 1: // cube
            pointsPath[0] = vec3(0.3, 0.3, 0.3);
            pointsPath[1] = vec3(0.4, 0.3, 0.5);
            pointsPath[2] = vec3(0.6, 0.7, 0.7);
            pointsPath[3] = vec3(0.7, 0.5, 0.3);
            break;
    }

    float distancePlusProche = 100000.0;
    vec3 destination = vec3(0.0);

    
    int i;
    for(i = 0; i < pointsPath.length(); i++)
    {
        vec3 a = pointsPath[i];
        vec3 b = pointsPath[(i+1)%pointsPath.length()];
        
        vec3 normalPoint = getPathTarget(predictionPos, a, b);

        vec3 dir = b - a;
        if (normalPoint.x < min(a.x,b.x) || normalPoint.x > max(a.x,b.x) 
        || normalPoint.y < min(a.y,b.y) || normalPoint.y > max(a.y,b.y)
        || normalPoint.z < min(a.z,b.z) || normalPoint.z > max(a.z,b.z)) {
            
            normalPoint = b;
            // hors du segment, on prend le suivant
            a = pointsPath[(i+1)%pointsPath.length()];
            b = pointsPath[(i+2)%pointsPath.length()];
            dir = b - a;
        }

        float distance = length(predictionPos - normalPoint);

        if (distance < distancePlusProche) {
            distancePlusProche = distance;
            
            destination = normalPoint;
            
            vec3 decalageAvant = normalize(dir) * 2.0; 
            destination += decalageAvant;
        }
    }

    if (distancePlusProche > rayonPath) {
      return seekSteering(pos, destination, vel, 1.0, forceMax, masse);
    } 
    else {
      return vel;
    }
}



/*////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// NOISE //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////*/

uniform sampler2D texNoise;
uniform float noiseMagnitude;

vec3 noiseProcess(vec3 pos)
{
    vec2 st = pos.xy / noiseMagnitude;
    vec3 noise = texture(texNoise, st).xyz; // st doit etre entre 0 et 1
    return noise;
}




/*////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// MAIN ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////*/

void main(void)
{

    vec2 st = fragTexture * resolution;    // gets the position of the pixel that it´s dealing with...
    vec3 pos = texture(posData, st).xyz;      // ... for getting the position data
    vec3 vel = texture(prevVelData, st).xyz;  // and the velocity

    vec3 nextVel = flocking(pos, vel) * (rapportForces.x+0.0001); // peut pas etre à zero car ne repartira pas
    nextVel += followPath(pos, vel) * (rapportForces.y+0.0001);
    nextVel += noiseProcess(pos) * rapportForces.z;
    nextVel += attract(pos, vel) * rapportForces.w;

    outputColor = vec4(nextVel, 1.0);

}

