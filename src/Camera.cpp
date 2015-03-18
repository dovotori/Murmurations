#include "Camera.h"

Camera::Camera()
{
    //ctor
    this->position.set(0, 0, 10);
    this->target.set(0, 0, 0);
    this->angle = 50.0;
    this->near = 1.0;
    this->far = 100.0;
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



void Camera::rotation(ofVec2f angle, float zoom)
{

    angle *= 360.0;
    float x = zoom * sin( angle.x * M_PI / 360.0 ) * cos( angle.y * M_PI / 360.0 );
    float y = zoom * sin( angle.y * M_PI / 360.0 );
    float z = zoom * cos( angle.x * M_PI / 360.0 ) * cos( angle.y * M_PI / 360.0 );

    this->position.set(x, y, z);
    this->updateView();

}

