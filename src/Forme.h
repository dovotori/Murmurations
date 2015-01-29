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
        void draw(Camera *camera, ofTexture& texPos);

    protected:
    private:

        ofMatrix4x4 model;
        ofShader shader, postShader;
        ofVboMesh mesh;
        ofFbo fbo;

        int textureRes;
        float cpt;

};

#endif // FORME_H
