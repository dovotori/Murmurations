#include "Camera.h"

Camera::Camera()
{
    //ctor
    this->position.set(0, 0, 10);
    this->target.set(0, 0, 0);
    this->angle = 50.0;
    this->near = 1.0;
    this->far = 100.0;
    
    this->anglesRotation.set(0.0, 0.0);
    this->zoomRotation = 2.0;
}

Camera::~Camera()
{
    //dtor
}


void Camera::setup()
{
    this->identity.makeIdentityMatrix();
    this->updateView();
    this->updateProjection();

}


void Camera::updateView(){

    this->view.makeLookAtViewMatrix(this->position, this->target, ofVec3f(0, 1, 0));
}

void Camera::updateProjection(){
    this->projection.makePerspectiveMatrix(this->angle, ofGetWindowWidth()/ofGetWindowHeight(), this->near, this->far);
}



void Camera::updateRotation()
{
    //this->anglesRotation *= 360.0;
    float x = this->zoomRotation * sin( this->anglesRotation.x * M_PI / 360.0 ) * cos( this->anglesRotation.y * M_PI / 360.0 );
    float y = this->zoomRotation * sin( this->anglesRotation.y * M_PI / 360.0 );
    float z = this->zoomRotation * cos( this->anglesRotation.x * M_PI / 360.0 ) * cos( this->anglesRotation.y * M_PI / 360.0 );

    this->position.set(x, y, z);
    this->updateView();

}

