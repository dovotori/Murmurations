
#include "Sphere.h"


Sphere::Sphere()
{
    this->cpt = 0.0;
    this->nbPoints = 0;
    this->textureRes = 0;
    this->texScreen.allocate(100, 100, GL_RGBA);
}

Sphere::~Sphere()
{
    //dtor
}


void Sphere::setup()
{

    this->model.makeIdentityMatrix();
    this->shader.load("shader/basic");
    this->mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    //this->setupClassic();
    this->setupGeodesic(1);
    this->generateTexture();

    this->nbPoints = this->mesh.getNumVertices();

    cout << "textureRes: " << this->textureRes << " // nbPoints: " << this->nbPoints << endl;
}




void Sphere::draw(Camera *camera)
{
    this->cpt += 1.0;

    this->model.makeIdentityMatrix();
    this->model.rotate(90.0, 1.0, 0.0, 0.0);
    this->model.rotate(this->cpt, 0.0, 1.0, 1.0);

    this->shader.begin();

    this->shader.setUniformMatrix4f("model", this->model);
    this->shader.setUniformMatrix4f("view", camera->getViewMatrix());
    this->shader.setUniformMatrix4f("projection", camera->getProjectionMatrix());

    this->mesh.draw();

    this->shader.end();
    
    this->texScreen.loadScreenData(0,0,100,100);
}




void Sphere::generateTexture()
{

    this->textureRes = (int)sqrt((float)this->mesh.getNumVertices());      // Definir la resolution de la texture en fonction du nombre de points

    float * pos = new float[this->textureRes*this->textureRes*3];
    for(int i = 0; i < this->textureRes*this->textureRes; i++)
    {
        if(i < this->mesh.getNumVertices()){
            ofVec3f tmp = this->mesh.getVertex(i);
            pos[i*3 + 0] = tmp.x;
            pos[i*3 + 1] = tmp.y;
            pos[i*3 + 2] = tmp.z;
        } else {
            pos[i*3 + 0] = 0.0;
            pos[i*3 + 1] = 0.0;
            pos[i*3 + 2] = 0.0;
        }

    }
    this->fbo.allocate(this->textureRes, this->textureRes, GL_RGB);
    this->fbo.getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);

    delete [] pos;

}




void Sphere::setupClassic()
{

    float * pos = new float[10*3];

    double r = 10.0;
    int lats = 10; int longs = 10;

    int i, j;
    for (i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for (j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double)(j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            this->mesh.addVertex(ofVec3f(x * zr0, y * zr0, z0));
            this->mesh.addVertex(ofVec3f(x * zr1, y * zr1, z1));
        }
    }

    delete [] pos;
}











void Sphere::setupGeodesic(const unsigned int depth)
{
    const double X = 0.525731112119133606;
    const double Z = 0.850650808352039932;
    ofVec3f vdata[12] = {
        ofVec3f(-X, 0.0, Z), ofVec3f(X, 0.0, Z), ofVec3f(-X, 0.0, -Z), ofVec3f(X, 0.0, -Z),
        ofVec3f(0.0, Z, X), ofVec3f(0.0, Z, -X), ofVec3f(0.0, -Z, X), ofVec3f(0.0, -Z, -X),
        ofVec3f(Z, X, 0.0), ofVec3f(-Z, X, 0.0), ofVec3f(Z, -X, 0.0), ofVec3f(-Z, -X, 0.0)
    };
    int tindices[20][3] = {
        {0, 4, 1}, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 }, { 4, 8, 1 },
        { 8, 10, 1 }, { 8, 3, 10 }, { 5, 3, 8 }, { 5, 2, 3 }, { 2, 7, 3 },
        { 7, 10, 3 }, { 7, 6, 10 }, { 7, 11, 6 }, { 11, 0, 6 }, { 0, 1, 6 },
        { 6, 1, 10 }, { 9, 0, 11 }, { 9, 11, 2 }, { 9, 2, 5 }, { 7, 2, 11 }
    };
    for(int i = 0; i < 20; i++)
    {
        subdivide(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], depth);
    }

    cout << this->mesh.getNumVertices() << endl;
}




void Sphere::subdivide(ofVec3f &v1, ofVec3f  &v2, ofVec3f  &v3, const unsigned int depth)
{
    if(depth == 0) {
        this->mesh.addVertex(v1);
        this->mesh.addVertex(v2);
        this->mesh.addVertex(v3);
        return;
    }
    ofVec3f  v12 = (v1 + v2).normalize();
    ofVec3f  v23 = (v2 + v3).normalize();
    ofVec3f  v31 = (v3 + v1).normalize();
    this->subdivide(v1, v12, v31, depth - 1);
    this->subdivide(v2, v23, v12, depth - 1);
    this->subdivide(v3, v31, v23, depth - 1);
    this->subdivide(v12, v23, v31, depth - 1);
}




