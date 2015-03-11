#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
    
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE); // pour utiliser shader
    ofSetupOpenGL(800, 600, OF_WINDOW);			// <-------- setup the GL context
    
    
    // Verifie le support des cartes graphiques modernes
    if(!ofGLCheckExtension("GL_ARB_geometry_shader4")
       && !ofGLCheckExtension("GL_EXT_geometry_shader4")
       && !ofIsGLProgrammableRenderer()){
        ofLogFatalError() << "geometry shaders not supported on this graphics card";
        return 1;
    }
    

    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
