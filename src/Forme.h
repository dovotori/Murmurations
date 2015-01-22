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
        void update();
        void draw(Camera *camera);

    protected:
    private:

        ofMatrix4x4 model;
        ofShader shader;
        ofVbo mesh;
    
        unsigned int nbPoints;


};

#endif // FORME_H
