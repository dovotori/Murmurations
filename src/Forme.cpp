#include "Forme.h"

Forme::Forme()
{
    //ctor
    this->noiseInfluence = 0.0;
    this->noiseScale = 4.0;
    this->rotation.set(0.0, 0.0, 0.0);
    this->couleur.set(1.0, 1.0, 1.0, 1.0);
    this->rendu = 1;
    this->nbRendu = 4;
    this->cpt = 0.0;
    this->taille = 0.008;
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
    this->postShader.load("shader/texFbo.vert", "shader/postRender.frag");

    this->textureRes = (int)sqrt((float)nb);      // Definir la resolution de la texture en fonction du nombre de particules

    // CHARGER FBO
    this->fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F);
    this->fbo.begin(); ofClear(0, 0, 0, 255); this->fbo.end();

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
    this->textureParticule.loadImage("image/spark.png");
    
    
    // ENVOI DES VARIABLES CONSTANTES
    this->shader[3].begin(); this->shader[3].setUniformTexture("particuleTex", this->textureParticule.getTextureReference(), 2); this->shader[3].end();
    this->postShader.begin(); this->postShader.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight()); this->postShader.end();
}







void Forme::draw(Camera *camera, ofTexture& texPos, ofTexture& texVel)
{
    this->cpt += 0.4;
    this->model.makeIdentityMatrix();
    this->model.rotate(this->rotation.x, 1.0, 0.0, 0.0);
    this->model.rotate(this->rotation.y, 0.0, 1.0, 0.0);
    this->model.rotate(this->rotation.z, 0.0, 0.0, 1.0);

    this->fbo.begin();

      ofClear(0,0,0,0);

        this->shader[this->rendu].begin();

            this->shader[this->rendu].setUniformTexture("posTex", texPos, 0);
            this->shader[this->rendu].setUniformTexture("velTex", texVel, 1);
            this->shader[this->rendu].setUniform4f("couleur", this->couleur.x, this->couleur.y, this->couleur.z, this->couleur.w);
            this->shader[this->rendu].setUniformMatrix4f("model", this->model);
            this->shader[this->rendu].setUniformMatrix4f("view", camera->getViewMatrix());
            this->shader[this->rendu].setUniformMatrix4f("projection", camera->getProjectionMatrix());
            this->shader[this->rendu].setUniform1f("tailleParticule", this->taille);

            this->mesh.draw(); // OF_MESH_WIREFRAME

        this->shader[this->rendu].end();

    this->fbo.end();
    

    // noise effect
    this->postShader.begin();
        this->postShader.setUniform1f("cpt", this->cpt);
        this->postShader.setUniform1f("noiseInfluence", this->noiseInfluence); // de 0 à 1
        this->postShader.setUniform1f("noiseScale", this->noiseScale);
        this->postShader.setUniformTexture("fboTexture", this->fbo.getTextureReference(0), 0);
        this->fbo.draw(0, 0); // on dessine
    this->postShader.end();
}







