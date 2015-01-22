#ifndef DESSIN_H
#define DESSIN_H


#include "ofMain.h"
#include "Camera.h"
#include "GpuProcess.h"




class Dessin
{
    public:
        Dessin();
        virtual ~Dessin();
        void setup();
        void update();
        void draw(Camera* camera);

        void mouseDragged(int x, int y);
        void mousePressed();
        void mouseReleased();

    protected:
    private:
    
        GpuProcess process;
    
        ofFbo fbo1, fbo2;
        ofShader shader;

};

#endif // DESSIN_H
