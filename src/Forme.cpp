#include "Forme.h"

Forme::Forme()
{
    //ctor
    this->noiseInfluence = 0.5;
    this->rotation = 0.0;
    this->rendu = 3;
    this->mesh.setMode(OF_PRIMITIVE_POINTS); // IMPORTANT doit etre raccord avec le geometry shader
}

Forme::~Forme()
{
    //dtor
}


void Forme::setup(unsigned int nb)
{

    this->shader = new ofShader[5];
    this->shader[0].load("shader/render.vert", "shader/render.frag", "shader/renderForme.geom");
    this->shader[1].load("shader/render.vert", "shader/render.frag", "shader/renderLigne.geom");
    this->shader[2].load("shader/render.vert", "shader/render.frag", "shader/renderPoint.geom");
    this->shader[3].load("shader/render.vert", "shader/render.frag", "shader/renderCrazy.geom");
    this->shader[4].load("shader/render.vert", "shader/render.frag", "shader/renderImage.geom");
    this->postShader.load("shader/basic.vert", "shader/postRender.frag");

    this->textureRes = (int)sqrt((float)nb);      // Definir la resolution de la texture en fonction du nombre de particules

    // CHARGER FBO
    this->fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F);
    this->fbo.begin();
        ofClear(0, 0, 0, 255);
    this->fbo.end();

    // CREER MESH
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
    this->model.rotate(this->rotation, 1.0, 1.0, 0.0);

    this->fbo.begin();

      ofClear(0,0,0,0);

        this->shader[this->rendu].begin();

            this->shader[this->rendu].setUniformTexture("posTex", texPos, 0);
            this->shader[this->rendu].setUniform1f("resolution", (float)this->textureRes);
            this->shader[this->rendu].setUniform3f("screen", 40.0, 40.0, 40.0); // taille de l'espace 3D des particules
            this->shader[this->rendu].setUniformMatrix4f("model", this->model);
            this->shader[this->rendu].setUniformMatrix4f("view", camera->getViewMatrix());
            this->shader[this->rendu].setUniformMatrix4f("projection", camera->getProjectionMatrix());

            this->mesh.draw();

        this->shader[this->rendu].end();

    this->fbo.end();


    // noise effect
    this->postShader.begin();
        this->postShader.setUniform1f("cpt", this->cpt);
        this->postShader.setUniform1f("noiseInfluence", this->noiseInfluence); // de 0 à 1
        this->postShader.setUniformTexture("fboTexture", this->fbo.getTextureReference(0), 0);
        this->postShader.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight());
        this->fbo.draw(0, 0); // on dessine
    this->postShader.end();
}







