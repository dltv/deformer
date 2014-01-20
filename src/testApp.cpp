#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	cam.initGrabber(640, 480);
    ofSetVerticalSync(false);
	ofEnableAlphaBlending();
    
	//we load a font and tell OF to make outlines so we can draw it as GL shapes rather than textures
	font.loadFont("type/verdana.ttf", 100, true, false, true, 0.4, 72);
//#ifdef TARGET_OPENGLES

//shader.load("shaders/instanced_120.vert","shaders/instanced_120.frag");

    
//#else
//	if(ofGetGLProgrammableRenderer()){
//shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
//	}else{
	shader.load("shaders/noise.vert", "shaders/noise.frag");
//	}
//#endif
//    
doShader = false;


	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	stepSize = 4;
	ySteps = cam.getHeight() / stepSize;
	xSteps = cam.getWidth() / stepSize;
	for(int y = 0; y < ySteps; y++) {
		for(int x = 0; x < xSteps; x++) {
			mesh.addVertex(ofVec2f(x * stepSize, y * stepSize));
			mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
		}
	}
	for(int y = 0; y + 1 < ySteps; y++) {
		for(int x = 0; x + 1 < xSteps; x++) {
			int nw = y * xSteps + x;
			int ne = nw + 1;
			int sw = nw + xSteps;
			int se = sw + 1;
			mesh.addIndex(nw);
			mesh.addIndex(ne);
			mesh.addIndex(se);
			mesh.addIndex(nw);
			mesh.addIndex(se);
			mesh.addIndex(sw);
		}
	}
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		flow.setWindowSize(8);
		flow.calcOpticalFlow(cam);
		int i = 0;
		float distortionStrength = 10;
		for(int y = 1; y + 1 < ySteps; y++) {
			for(int x = 1; x + 1 < xSteps; x++) {
				int i = y * xSteps + x;
				ofVec2f position(x * stepSize, y * stepSize);
				ofRectangle area(position - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
				ofVec2f offset = flow.getAverageFlowInRegion(area);
				mesh.setVertex(i, position + distortionStrength * offset);
                i++;
            }
		}
	}
}

void testApp::draw() {
	ofBackground(0);
	ofScale(2, 2);

  
    shader.begin();
    
    shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
    shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
    
    //we also pass in the mouse position
    //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
   
    shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
        cam.getTextureReference().bind();
    
        mesh.draw();
        cam.getTextureReference().unbind();
//        if(ofGetMousePressed()) {
//            mesh.drawWireframe();
//        }
            shader.end();
   
  
        
   
        
        //we also pass in the mouse position
        //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
//        shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
        

	
    //finally draw our text
  
	

		
	}







//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if( key == 's' ){
		doShader = !doShader;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}

