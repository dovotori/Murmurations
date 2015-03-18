#include "Background.h"

Background::Background()
{
    //ctor
    this->alpha = 1.0;
    this->nbImages = 0;
    this->currentImage = 0;
}


Background::~Background()
{
    //dtor
}


void Background::setup()
{

    this->shader.load("shader/textureFlat");

    this->screen.setMode(OF_PRIMITIVE_TRIANGLES);

    this->screen.addVertex(ofVec3f(-1.0, 1.0, 0.0));
    this->screen.addVertex(ofVec3f(-1.0, -1.0, 0.0));
    this->screen.addVertex(ofVec3f(1.0, 1.0, 0.0));

    this->screen.addVertex(ofVec3f(-1.0, -1.0, 0.0));
    this->screen.addVertex(ofVec3f(1.0, 1.0, 0.0));
    this->screen.addVertex(ofVec3f(1.0, -1.0, 0.0));

    this->screen.addTexCoord(ofVec2f(0.0, 0.0));
    this->screen.addTexCoord(ofVec2f(0.0, 1.0));
    this->screen.addTexCoord(ofVec2f(1.0, 0.0));

    this->screen.addTexCoord(ofVec2f(0.0, 1.0));
    this->screen.addTexCoord(ofVec2f(1.0, 0.0));
    this->screen.addTexCoord(ofVec2f(1.0, 1.0));


    // SCAN DOSSIER
    this->dossier.listDir("image/background/");
	this->dossier.sort();
	this->nbImages = this->dossier.size();

    // CHARGER IMAGES
    this->image = new ofImage[this->nbImages];
    for(int i = 0; i < this->nbImages; i++)
    {
        //stringstream ss;
        //ss << "image/background/background_" << i << ".jpg";
        this->image[i].loadImage(this->dossier.getPath(i));
        //cout << this->dossier.getPath(i) << endl;
    }
}


void Background::update()
{
}


void Background::draw()
{

    this->shader.begin();
        this->shader.setUniform1f("alpha", this->alpha);
        this->shader.setUniformTexture("tex", this->image[this->currentImage].getTextureReference(), 0);
        this->shader.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight());
        this->screen.draw();
    this->shader.end();

    //this->fbo.draw(0, 0);
}

