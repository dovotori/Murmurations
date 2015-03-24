#ifndef DESSIN_H
#define DESSIN_H


#include "ofMain.h"
#include "Camera.h"
#include "GpuProcess.h"
#include "Forme.h"
#include "Ligne.h"
#include "Sphere.h"
#include "Background.h"
#include "Echange.h"
#include "Noise.h"
#include "Effet.h"

#define NB 100

class Dessin
{
    public:
        Dessin();
        virtual ~Dessin();
        void setup();
        void update(Camera* camera);
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
        Sphere sphere;
        Background background;
        Echange echange;
        Noise noise;
        Ligne ligne;
        Effet effet;
};

#endif // DESSIN_H
