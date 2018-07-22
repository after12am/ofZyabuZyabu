#include "testApp.h"
#include "Vehicle.h"
#include <GLUT/GLUT.h>

// http://forum.openframeworks.cc/index.php?topic=1738.0



bool isPaused = true;

//--------------------------------------------------------------
void testApp::setup()
{
	///////////////////////////////
	//	of setup
	///////////////////////////////
	//
	//ofBackground(0, 0, 0, 1);
	ofSetFrameRate(30);
	ofSetVerticalSync(false);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	//ofEnableNormalizedTexCoords();
	//ofHideCursor();
	//
	///////////////////////////////
	
	
	///////////////////////////////
	//	gui
	///////////////////////////////
	//
    guiParticle.setup("control panel test", 10, 10, 340, 340);
    guiParticle.addPanel("panel 1", 4);
    guiParticle.addSlider("rect size", "size", 100, 0, 800, false);
    guiParticle.addSlider("rotate x", "rot_x", 0, 0, 360, false);
    guiParticle.addSlider("rotate y", "rot_y", 0, 0, 360, false);
    guiParticle.addSlider("rotate z", "rot_z", 0, 0, 360, false);
	//
	///////////////////////////////
    
	
	///////////////////////////////
	//	sound
	///////////////////////////////
	//
	music.loadSound("sound/06 ときめきハッカー （EOG only）.mp3");
	music.setLoop(false);
	music.play();
	music.setPaused(true);
	//
	///////////////////////////////
	
	
	setupGL();
	
	///////////////////////////////
	//	light
	///////////////////////////////
	//
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 300.0, 200.0, 0.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };
	
	glClearColor(0.0, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	
	//
	///////////////////////////////
}

//--------------------------------------------------------------
void testApp::update()
{
	
	///////////////////////////////
	//	gui
	///////////////////////////////
	//
	guiParticle.update();
	//
	///////////////////////////////
	
	
	
	
	if (!isPaused)
	{
		particleManager.emit(2);
		particleManager.isMusicPlaying = true;
		
		///////////////////////////////
		//	particle
		///////////////////////////////
		//
		particleManager.update();
		//
		///////////////////////////////
	}
	else
	{
		particleManager.isMusicPlaying = false;
		
	}

	
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_ALPHA_TEST);
	
	
	easyCam.begin();
	glPushMatrix();
	
	///////////////////////////////
	//	particle
	///////////////////////////////
	//
	glPushMatrix();
	
	
	particleManager.draw();
	
	
	glPopMatrix();
	//
	///////////////////////////////
	
	glPopMatrix();
	easyCam.end();
	
	
	///////////////////////////////
	//	gui
	///////////////////////////////
	//
//	glDisable(GL_DEPTH_TEST);
//	guiParticle.draw();
//	ofSetColor(ofColor(255));
//	ofDrawBitmapString("[particle number] " + ofToString(particleManager.particles.size()), 10, ofGetHeight() - 10);
	//
	///////////////////////////////
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if (key == 'a')
	{
		//particleManager.emit(10);
	}
	
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
	
	if (key == 32)
	{
		isPaused = !isPaused;
		
		music.setPaused(isPaused);
	}
	
	if (key == 's')
	{
		
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
	guiParticle.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	guiParticle.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	guiParticle.mouseReleased();
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

//--------------------------------------------------------------
void testApp::setupGL()
{
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glDisable(GL_CULL_FACE);
	
	for (int i = 0; i < 100; i++)
	{
		glNewList(i, GL_COMPILE);
		glEnable(GL_DEPTH_TEST);
		glPushMatrix();
		glutSolidSphere(i, 40, 40);
		glPopMatrix();
		glDisable(GL_DEPTH_TEST);
		glEndList();
	}
}


