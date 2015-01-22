

#ifndef __MurmurationsGPU__GpuProcess__
#define __MurmurationsGPU__GpuProcess__

#include "ofMain.h"
#include "Camera.h"

struct pingPongBuffer {
public:
    void allocate( int _width, int _height, int _internalformat = GL_RGBA, float _dissipation = 1.0f){
        // Allocate
        for(int i = 0; i < 2; i++){
            FBOs[i].allocate(_width,_height, _internalformat );
            FBOs[i].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        }
        
        // Clean
        clear();
        
        // Set everything to 0
        flag = 0;
        swap();
        flag = 0;
    }
    
    void swap(){
        src = &(FBOs[(flag)%2]);
        dst = &(FBOs[++(flag)%2]);
    }
    
    void clear(){
        for(int i = 0; i < 2; i++){
            FBOs[i].begin();
            ofClear(0,255);
            FBOs[i].end();
        }
    }
    
    ofFbo& operator[]( int n ){ return FBOs[n];}
    
    ofFbo   *src;       // Source       ->  Ping
    ofFbo   *dst;       // Destination  ->  Pong
private:
    ofFbo   FBOs[2];    // Real addresses of ping/pong FBOs
    int     flag;       // Integer for making a quick swap
};


/* //////////////////////// */


class GpuProcess
{
public:
    GpuProcess();
    virtual ~GpuProcess();
    void setup(unsigned int nb = 1);
    void update();
    void draw(Camera* camera);
    
protected:
private:
    ofShader    updatePos;
    ofShader    updateVel;
    ofShader    updateRender;
    
    pingPongBuffer posPingPong;
    pingPongBuffer velPingPong;
    
    ofFbo   renderFBO;
    
    ofImage sparkImg;
    
    float   timeStep;
    float   particleSize;
    
    int     width, height;
    int     imgWidth, imgHeight;
    int     numParticles;
    int     textureRes;
    
    ofVboMesh mesh;
    
    
    void setupRender();
    void setupPosition();
    void setupVelocity();
    
    void computeGpuPosition();
    void computeGpuVelocity();
    void renderTextureScene(Camera* camera);
    
    float cpt;
    ofMatrix4x4 model;
};

#endif
