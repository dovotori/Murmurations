#ifndef CAMERA_H
#define CAMERA_H

#include "ofMain.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();
        void setup();
        void updateView();
        void updateProjection();

        inline void setPosition(float x, float y, float z){ this->position.set(x, y, z); this->updateView(); };
        inline void setNearFar(float n, float f){ this->near = n; this->far = f; this->updateProjection(); };
        inline void setTarget(float x, float y, float z){ this->target.set(x, y, z); };
        inline void setAngle(float valeur){ this->angle = valeur; this->updateProjection(); };


        inline ofMatrix4x4 getIdentityMatrix(){ return this->identity; }
        inline ofMatrix4x4 getViewMatrix(){ return this->view; }
        inline ofMatrix4x4 getProjectionMatrix(){ return this->projection; }
        inline float getAngle(){ return this->angle; };
        inline ofVec3f getPosition(){ return this->position; };
        inline float getDistanceFocale(){ return this->near; };

    protected:
    private:

        ofMatrix4x4 view, projection, identity;
        ofVec3f position, target;
        float angle, near, far;
    

};

#endif // CAMERA_H
