#ifndef DESSIN_H
#define DESSIN_H


#include "ofMain.h"
#include "Camera.h"
#include "GpuProcess.h"
#include "Forme.h"
#include "Background.h"




class Dessin
{
    public:
        Dessin();
        virtual ~Dessin();
        void setup();
        void update();
        void draw(Camera* camera);

        void keyReleased(int key);
        void keyPressed(int key);
        void mouseDragged(int x, int y);
        void mousePressed();
        void mouseReleased();

    protected:
    private:

        GpuProcess process;
        Forme forme;
        Background background;


};

#endif // DESSIN_H
