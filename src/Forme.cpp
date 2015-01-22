#include "Forme.h"

Forme::Forme()
{
    //ctor
}

Forme::~Forme()
{
    //dtor
}




void Forme::setup(unsigned int nb)
{
    this->shader.load("shader/basic");
    
    this->nbPoints = nb;
    
    vector<ofVec3f> vert(this->nbPoints);
    for(unsigned int i = 0; i < this->nbPoints; i++){ vert[i].set(0.0, 0.0, 0.0); }
    this->mesh.setVertexData( &vert[0], this->nbPoints, GL_STREAM_DRAW );
    
    this->model.makeIdentityMatrix();
    
}




void Forme::update()
{

}




void Forme::draw(Camera *camera)
{
    
    this->shader.begin();
    this->shader.setUniformMatrix4f("model", this->model);
    this->shader.setUniformMatrix4f("view", camera->getViewMatrix());
    this->shader.setUniformMatrix4f("projection", camera->getProjectionMatrix());
    this->mesh.draw(GL_POINTS, 0, this->nbPoints);
    this->shader.end();
    

}







