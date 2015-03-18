#include "Ligne.h"

Ligne::Ligne()
{
    //ctor
    this->nbPoints = 0;
    this->nbPointsMax = 0;
    this->distance = 0.05;
}

Ligne::~Ligne()
{
    //dtor
}


void Ligne::setup(unsigned int nb)
{
    this->shader.load("shader/ligne");

    this->nbPointsMax = nb*nb*nb*nb;

    vector<ofVec3f> vertices(this->nbPointsMax);
    vector<ofFloatColor> couleurs(this->nbPointsMax);

    this->mesh.setVertexData( &vertices[0], this->nbPointsMax, GL_STREAM_DRAW );
    this->mesh.setColorData( &couleurs[0], this->nbPointsMax, GL_STREAM_DRAW );
}



void Ligne::update(ofTexture& texPos)
{

    ofPixels pix;
    texPos.readToPixels(pix);

    vector<ofFloatColor> couleurs;
    vector<ofVec3f> vertices;

    for(int i = 0; i < pix.size(); i+=3)
    {
        ofVec3f pos(pix[i] / 255.0, pix[i+1] / 255.0, pix[i+2] / 255.0);
        pos -= 0.5;
        //cout << pos.x << " / " << pos.y << " / " << pos.z << endl;

        for(int j = 0; j < pix.size(); j+=3)
        {
            if(i != j)
            {
                ofVec3f posVoisin(pix[j] / 255.0, pix[j+1] / 255.0, pix[j+2] / 255.0);
                posVoisin -= 0.5;

                float distance = pos.distance(posVoisin);
                //cout << distance << endl;
                if(distance < this->distance) {

                    vertices.push_back(pos);
                    couleurs.push_back(ofFloatColor(pos.z+0.5));
                    vertices.push_back(posVoisin);
                    couleurs.push_back(ofFloatColor(pos.z+0.5));
                }
            }
        }
    }

    this->nbPoints = vertices.size();
    //cout << " // " << this->nbPoints << endl;
    this->mesh.clearVertices();
    this->mesh.clearColors();
    this->mesh.setVertexData(&vertices[0], this->nbPoints,GL_STATIC_DRAW);
    this->mesh.setColorData(&couleurs[0], this->nbPoints,GL_STATIC_DRAW);


}



void Ligne::draw(Camera *camera)
{
    this->shader.begin();

        this->shader.setUniformMatrix4f("model", camera->getIdentityMatrix());
        this->shader.setUniformMatrix4f("view", camera->getViewMatrix());
        this->shader.setUniformMatrix4f("projection", camera->getProjectionMatrix());

        this->mesh.draw(GL_LINES, 0, this->nbPoints);

    this->shader.end();
}

