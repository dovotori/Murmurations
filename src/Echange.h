#ifndef ECHANGE_H
#define ECHANGE_H

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 12000
#define NB_VAR_MAX 10

class Echange
{
    public:
        Echange();
        virtual ~Echange();
        void setup();
        void update();
        void draw();
        float* getVar();
        inline bool getClick(){ return this->click; }
        inline bool getDraw(int index){ return this->isDraw[index]; }

    protected:
    private:
        ofxOscReceiver receiver;
        float variables[NB_VAR_MAX];
        unsigned int nbVariables;

        bool click;
        bool isDraw[NB_VAR_MAX];
};

#endif // ECHANGE_H
