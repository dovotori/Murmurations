#ifndef FORME_H
#define FORME_H

#include "ofMain.h"
#include "Camera.h"



class Forme
{
    public:
        Forme();
        virtual ~Forme();
        void setup(unsigned int nb = 1);
        void draw(Camera *camera, ofTexture& texPos, ofTexture& texVel);

        inline void setRendu(unsigned int rendu) {
            this->rendu = rendu;
            switch(rendu) {
                default:
                    this->mesh.setMode(OF_PRIMITIVE_POINTS);
                    break;
            }
        };
        inline void setNoiseInfluence(float value){ this->noiseInfluence = value; };
        inline void setNoiseScale(float value){ this->noiseScale = value; };
        inline void setRotation(float x, float y, float z){ this->rotation.set(x, y, z); };
        inline void setCouleur(float x, float y, float z, float a){ this->couleur.set(x, y, z, a); };
        inline void setTaille(float valeur){ this->taille = valeur; };

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
        float cpt, noiseInfluence, noiseScale, taille;
        ofVec3f rotation;
        ofVec4f couleur;

};

#endif // FORME_H
