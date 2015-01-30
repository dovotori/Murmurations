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

    this->shader.load("shader/render.vert", "shader/render.frag", "shader/render.geom");
    this->postShader.load("shader/basic.vert", "shader/postRender.frag");

    this->textureRes = (int)sqrt((float)nb);      // Definir la resolution de la texture en fonction du nombre de particules

    // CHARGER FBO
    this->fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F);
    this->fbo.begin();
        ofClear(0, 0, 0, 255);
    this->fbo.end();

    // CREER MESH
    this->mesh.setMode(OF_PRIMITIVE_POINTS); // IMPORTANT doit etre raccord avec le geometry shader
    for(int x = 0; x < this->textureRes; x++){
        for(int y = 0; y < this->textureRes; y++)
        {
            this->mesh.addVertex(ofVec3f(x,y));
            this->mesh.addTexCoord(ofVec2f(x, y));
        }
    }

    this->model.makeIdentityMatrix();
    this->cpt = 0.0;

}







void Forme::draw(Camera *camera, ofTexture& texPos)
{
    this->cpt += 0.4;
    this->model.makeIdentityMatrix();
    this->model.rotate(this->cpt, 1.0, 1.0, 0.0);

    this->fbo.begin();

      ofClear(0,0,0,0);

        this->shader.begin();

            this->shader.setUniformTexture("posTex", texPos, 0);
            this->shader.setUniform1f("resolution", (float)this->textureRes);
            this->shader.setUniform3f("screen", 40.0, 40.0, 40.0); // taille de l'espace 3D des particules
            this->shader.setUniformMatrix4f("model", this->model);
            this->shader.setUniformMatrix4f("view", camera->getViewMatrix());
            this->shader.setUniformMatrix4f("projection", camera->getProjectionMatrix());

            this->mesh.draw();

        this->shader.end();

    this->fbo.end();


    this->postShader.begin();
        this->postShader.setUniform1f("cpt", this->cpt);
        this->postShader.setUniformTexture("fboTexture", this->fbo.getTextureReference(0), 0);
        this->postShader.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight());
        this->fbo.draw(0, 0); // on dessine
    this->postShader.end();
}







