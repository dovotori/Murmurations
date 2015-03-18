#ifndef LIGNE_H
#define LIGNE_H


#include "ofMain.h"
#include "Camera.h"

class Ligne
{
    public:
        Ligne();
        virtual ~Ligne();
        void setup(unsigned int nb);
        void update(ofTexture& texPos);
        void draw(Camera *camera);

        inline void setDistance(float value){ this->distance = value; }

    protected:
    private:
        ofShader shader;
        ofVbo mesh;
        unsigned int nbPoints, nbPointsMax;
        float distance;
};

#endif // LIGNE_H
