// Working Code Base for Nested function by Pamela Liou
//based on code from Patrick Hebron, Art of Graphics Programming ITP

#include "Resources.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/ObjLoader.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class MatrixTransformNestedApp : public AppNative {
public:
	void setup();
	void mouseDown(MouseEvent event);
	void keyUp(KeyEvent event);
	void update();
	void draw();
    void nested(int i);
    TriMesh weave;
    
	CameraPersp mCam;
};

void MatrixTransformNestedApp::setup()
{
    ObjLoader loader( loadResource("ambient_working?.obj" ));
	loader.load( &weave );
    
	//mVBO = gl::VboMesh( mMesh );
	
    
	// Enable alpha blending:
	gl::enableAlphaBlending();
	
	// Enable depth buffer read/write:
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	// Setup camera:
	mCam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
    gl::translate(100.0, 100.9, 0);
    
}

void MatrixTransformNestedApp::mouseDown( MouseEvent event )
{
}

void MatrixTransformNestedApp::keyUp(KeyEvent event)
{
}

void MatrixTransformNestedApp::update()
{
}


void MatrixTransformNestedApp::nested(int i){
    gl::drawCoordinateFrame();
    int scalar = 50;
    
    Vec3f tInnerCubeDimension   = Vec3f( 1.0, 1.0, 1.0 )* scalar;
	Vec3f tInnerCubeTranslation = Vec3f( 0.0, 0.0, 0.0 )* (scalar/5) ;
	Vec3f tInnerCubeRotation    = Vec3f( getElapsedSeconds() * 180.0, 0.0, 0.0 );
	Vec3f tInnerCubeAnchor	    = Vec3f( 5.0, 5.0, 0.0 )*(scalar/3);
    i++;
    if (i < 100){
        gl::pushMatrices();
        // Set color:
        gl::color( Color( 0.0, 1.0, 1.0 ) );
        // Push inner matrix:
        // gl::pushMatrices();
        
        // Set color:
        gl::color( Color( 0.0, 1.0, 1.0 ) );
        // Apply translation:
        gl::translate( tInnerCubeTranslation);
        
        // Apply rotation:
        gl::rotate( tInnerCubeRotation );
        
        // Apply scaling:
        gl::scale( Vec3f( 0.9, 0.9, 0.9 ));
        
        // Apply anchor translation:
        gl::translate( tInnerCubeAnchor );
        
        
        
        
        // Draw cube:
        
        // VBO MESH
        gl::draw( weave );
        
        // gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
        
        nested(i);
        
        // Pop inner matrix:
        // gl::popMatrices();
        
        gl::popMatrices();
    }
}


void MatrixTransformNestedApp::draw()
{
    
    gl::clear();
    gl::pushMatrices();
    gl::translate( getWindowCenter() );
    
    nested(1);
    gl::pushMatrices();
    gl::rotate(Vec3f(-180, 0, 0));
    nested(1);
    
    gl::popMatrices();
    
    gl::popMatrices();
    
    
}