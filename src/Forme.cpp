#include "Forme.h"

Forme::Forme()
{
    //ctor
    this->rotation.set(0.0, 0.0, 0.0);
    this->couleur.set(1.0, 1.0, 1.0, 1.0);
    this->rendu = 3;
    this->nbRendu = 4;
    this->taille = 0.1;
    this->mesh.setMode(OF_PRIMITIVE_POINTS); // IMPORTANT doit etre raccord avec le in du geometry shader
    this->model.makeIdentityMatrix();
}

Forme::~Forme()
{
    //dtor
}


void Forme::setup(unsigned int nb)
{

    this->shader = new ofShader[5];
    this->shader[0].load("shader/render.vert", "shader/render.frag", "shader/renderPoint.geom");
    this->shader[1].load("shader/render.vert", "shader/render.frag", "shader/renderCarre.geom");
    this->shader[2].load("shader/render.vert", "shader/render.frag", "shader/renderForme.geom");
    this->shader[3].load("shader/render.vert", "shader/renderTexture.frag", "shader/renderImage.geom");
    //this->shader[4].load("shader/render.vert", "shader/render.frag", "shader/renderCrazy.geom");

    this->textureRes = nb;

    // ARROUNDI DES COORDONNES DE TEXTURES (contre pb etrange dans le shader)
    float lengthArrondi = 10.0;
    if(this->textureRes > 11){ lengthArrondi = 100.0; } else if(this->textureRes > 32){ lengthArrondi = 1000.0; }

    // CREER MESH
    this->mesh.setUsage( GL_DYNAMIC_DRAW );
    for(int y = 0; y < this->textureRes; y++)
        for(int x = 0; x < this->textureRes; x++){
        {
            this->mesh.addVertex(ofVec3f(0.0));
            float xArr = (float)x/(float)this->textureRes; xArr *= lengthArrondi; xArr = (float)ceil(xArr); xArr /= lengthArrondi; // arrondi à X decimal
            float yArr = (float)y/(float)this->textureRes; yArr *= lengthArrondi; yArr = (float)ceil(yArr); yArr /= lengthArrondi;
            this->mesh.addTexCoord(ofVec2f(xArr, yArr));
            //cout << xArr << " // " << yArr << endl;
        }
    }

    // TEXTURE DES PARTICULES
    this->textureParticule.loadImage("image/sparks.png");

}







void Forme::draw(Camera *camera, ofTexture& texPos, ofTexture& texVel)
{

    this->model.makeIdentityMatrix();
    this->model.rotate(this->rotation.x, 1.0, 0.0, 0.0);
    this->model.rotate(this->rotation.y, 0.0, 1.0, 0.0);
    this->model.rotate(this->rotation.z, 0.0, 0.0, 1.0);



        this->shader[this->rendu].begin();

            this->shader[this->rendu].setUniformTexture("posTex", texPos, 0);
            this->shader[this->rendu].setUniformTexture("velTex", texVel, 1);
            this->shader[this->rendu].setUniformTexture("particuleTex", this->textureParticule.getTextureReference(), 2);
            this->shader[this->rendu].setUniform4f("couleur", this->couleur.x, this->couleur.y, this->couleur.z, this->couleur.w);
            this->shader[this->rendu].setUniformMatrix4f("model", this->model);
            this->shader[this->rendu].setUniformMatrix4f("view", camera->getViewMatrix());
            this->shader[this->rendu].setUniformMatrix4f("projection", camera->getProjectionMatrix());
            this->shader[this->rendu].setUniform1f("tailleParticule", this->taille);
            this->shader[this->rendu].setUniform3fv("cameraPos", camera->getPosition().getPtr());

            this->mesh.draw(); // OF_MESH_WIREFRAME

        this->shader[this->rendu].end();


}







