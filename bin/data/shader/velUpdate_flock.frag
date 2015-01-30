#version 330

in vec2 fragTexture;

uniform sampler2D prevVelData;   // recive the previus velocity texture
uniform sampler2D posData;      // recive the position texture
uniform float timestep;
uniform int resolution;

uniform float distanceSeparation;
uniform float distanceAlignement;
uniform float distanceCohesion;

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





void main(void)
{

    vec2 st = fragTexture * resolution;    // gets the position of the pixel that it´s dealing with...

    vec3 pos = texture(posData, st).xyz;      // ... for getting the position data
    vec3 vel = texture(prevVelData, st).xyz;  // and the velocity

    float vitesseMax = 1.0;
    float forceMax = 0.1;
    float masse = 1.0;

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
            vec3 posVoisin = texture(posData, vec2(x, y)).xyz;
            vec3 velVoisin = texture(prevVelData, vec2(x, y)).xyz;

            float distance = length(posVoisin - pos);

            if(distance > 0) // exclue soit meme
            {
                // SEPARATION
                if(distance < distanceSeparation)
                {
                    vec3 ajoutForce = pos - posVoisin;
                    ajoutForce = normalize(ajoutForce);
                    ajoutForce /= distance; // plus le voisin est loin moins la force est importante
                    forceSeparation += ajoutForce;
                    cptSeparation++;
                }

                // ALIGNEMENT
                if(distance < distanceAlignement)
                {
                    forceAlignement += velVoisin;
                    cptAlignement++;
                }

                // COHESION
                if(distance < distanceCohesion)
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
        forceSeparation /= cptSeparation; // divise par le nombre de voisin
    }


    if(length(forceSeparation) > 0)
    {
        forceSeparation = normalize(forceSeparation);
        forceSeparation *= vitesseMax;

        // steer
        forceSeparation -= vel;
        forceSeparation = limiter(forceSeparation, forceMax);
    }


    // ALIGNEMENT
    if(cptAlignement > 0) {
        forceAlignement /= cptAlignement; // divise par le nombre de voisin
        forceAlignement = normalize(forceAlignement);
        forceAlignement *= vitesseMax;

        // steer
        forceAlignement -= vel;
        forceAlignement = limiter(forceAlignement, forceMax);
    }

    // COHESION
    if(cptCohesion > 0) {
        forceCohesion /= cptCohesion;
        forceCohesion = seekSteering(pos, forceCohesion, vel, vitesseMax, forceMax, masse);
    }



    /////////////////////// ON APPLIQUE ///////////////////////


    // gerer les influences arbitrairement
    forceSeparation *= 1.5;

    // appliquer la masse
    vec3 forces = forceSeparation;
    forces += forceAlignement;
    forces += forceCohesion;
    forces /= masse;

    // on forme la nouvelle vitesse
    vel += forces;
    vel = limiter(vel, vitesseMax);


    outputColor = vec4(vel, 1.0);

}

