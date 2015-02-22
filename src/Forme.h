#ifndef FORME_H
#define FORME_H

#include "ofMain.h"
#include "Camera.h"


/*
 RENDU
 0 FORME A PARTIR D'UN POINT
 1 LIGNES
 2 POINTS
 */

class Forme
{
    public:
        Forme();
        virtual ~Forme();
        void setup(unsigned int nb = 1);
        void draw(Camera *camera, ofTexture& texPos);
    
        inline void setRendu(unsigned int rendu) {
            this->rendu = rendu;
            switch(rendu) {
                case 1:
                    this->mesh.setMode(OF_PRIMITIVE_LINES);
                    break;
                default:
                    this->mesh.setMode(OF_PRIMITIVE_POINTS);
                    break;
            }
        };
        inline void setNoiseInfluence(float value){ this->noiseInfluence = value; };
        inline void setNoiseScale(float value){ this->noiseScale = value; };
        inline void setRotation(float x, float y, float z){ this->rotation.set(x, y, z); };
        inline void setEspace(float x, float y, float z){ this->espace.set(x, y, z); };
        inline void setCouleur(float x, float y, float z){ this->couleur.set(x, y, z); };
    
        inline float getNoiseInfluence(){ return this->noiseInfluence; };
    
    
    protected:
    private:

        ofMatrix4x4 model;
        ofShader *shader;
        ofShader postShader;
        ofVboMesh mesh;
        ofFbo fbo;
        ofImage textureParticule;


        unsigned int textureRes;
        unsigned int rendu;
        float cpt;
        float noiseInfluence, noiseScale;
        ofVec3f rotation, espace, couleur;

};

#endif // FORME_H
