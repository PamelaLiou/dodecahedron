// Working Code Base for Nested function by Pamela Liou
//based on code from Patrick Hebron, Art of Graphics Programming ITP

#include "Resources.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cubie.h"
#include "cinder/ObjLoader.h"
#include "cinder/gl/Texture.h"


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
    gl::Texture		mTexture;
    gl::Texture		bTexture;
    bool	mPaused;
    
    size_t	mIndex, mMinIndex, mMaxIndex;
    gl::Texture      mTexture2;
    
    gl::Texture      mTexture3;
    
    gl::Texture      mTexture4;



	CameraPersp mCam;
};

void MatrixTransformNestedApp::setup()
{
    mMinIndex =  0;
    
    mMaxIndex = 3;
    
    mIndex    = mMinIndex;
    
    mPaused   = false;
    setFullScreen( true );


    ObjLoader loader( loadResource("ambient_working?.obj" ));
    gl::enableDepthRead();
    gl::enableDepthWrite();
    mTexture = gl::Texture( loadImage( loadResource( "baked_test2.tif" ) ) );
        bTexture = gl::Texture( loadImage( loadResource( "BackgroundCinder1.png" ) ) );
    
    mTexture2 = gl::Texture(loadImage (loadResource ("BackgroundCinder2.png")));
    
    mTexture3 = gl::Texture(loadImage (loadResource ("BackgroundCinder3.png")));
    
    mTexture4 = gl::Texture(loadImage (loadResource ("BackgroundCinder4.png")));

	loader.load( &weave );
    
	//mVBO = gl::VboMesh( mMesh );
	

	// Enable alpha blending:
	gl::enableAlphaBlending();
	
	// Enable depth buffer read/write:
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	// Setup camera:
	mCam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
    gl::translate(200.0, 200.9, 0);

}

void MatrixTransformNestedApp::mouseDown( MouseEvent event )
{
}

void MatrixTransformNestedApp::keyUp(KeyEvent event)
{
    
  
        
        switch( event.getChar() ) {
                
            case ' ': {
                
                mPaused = !mPaused;
                
                break;
                
            }
                
            default: { break; }
                
        
        
    }
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
    gl::color( Color(  sin(getElapsedSeconds())/2 + 0.5, cos(getElapsedSeconds())/2 + 0.5,1 ) );
    // Push inner matrix:
   // gl::pushMatrices();
    
        // Set color:
//        gl::color( Color( 0.0, 1.0, 1.0 ) );
        // Apply translation:
        gl::translate( tInnerCubeTranslation);
        
        // Apply rotation:
        gl::rotate( tInnerCubeRotation );
        
        // Apply scaling:
        gl::scale( Vec3f( 0.9, 0.9, 0.9 ));
        
        // Apply anchor translation:
        gl::translate( tInnerCubeAnchor );
        
   
        // VBO MESH
        gl::pushMatrices();
        gl::scale(Vec3f(5.0,5.0,5.0));
        glEnable(GL_TEXTURE_2D);
        mTexture.bind();
        gl::draw( weave );
        mTexture.unbind();
        
        glDisable(GL_TEXTURE_2D);


        gl::popMatrices();
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
    gl::disableDepthRead();
    gl::disableDepthWrite();
    gl::color(1,1,1);
    //gl::draw( bTexture, getWindowBounds() );
    
    
    switch ( mIndex ) {
            
        case 0: {
            
            gl::draw( bTexture, getWindowBounds() );
            
            break;
            
        }
            
        case 1: {
            
            gl::draw( mTexture2, getWindowBounds() );
            
            break;
            
        }
            
        case 2: {
            
            gl::draw( mTexture3, getWindowBounds() );
            
            break;
            
        }
            
        case 3: {
            
            gl::draw( mTexture4, getWindowBounds() );
            
            break;
            
        }
            
        default: { break; }
            
    }
    
    
    
    // Update index:
    
    if( !mPaused && getElapsedFrames() % 100 == 0 ) {
        
        mIndex++;
        
        if( mIndex > mMaxIndex ) {
            
            mIndex = mMinIndex;
            
        }
        
    }
    

    
    
    //1
    gl::pushMatrices();
    gl::translate( getWindowCenter() );
    gl::pushMatrices();
    nested(1);
    gl::pushMatrices();
    gl::translate(getWindowCenter());
    gl::rotate(Vec3f(0, -180, 0));
    nested(1);
    gl::popMatrices();
    gl::popMatrices();
    
    gl::popMatrices();
    
    //2
    gl::pushMatrices();
    gl::translate( getWindowWidth()/2, getWindowHeight()/2-200 );
    gl::pushMatrices();
    nested(1);
    gl::pushMatrices();
    gl::translate(getWindowWidth()/2, getWindowHeight()/2-200 );
    gl::rotate(Vec3f(0, -180, 0));
    nested(1);
    gl::popMatrices();
    gl::popMatrices();
    
    gl::popMatrices();
    
    //3
    gl::pushMatrices();
    gl::translate( getWindowWidth()/2, getWindowHeight()/2+200 );
    gl::pushMatrices();
    nested(1);
    gl::pushMatrices();
    gl::translate(getWindowWidth()/2, getWindowHeight()/2+200 );
    gl::rotate(Vec3f(0, -180, 0));
    nested(1);
    gl::popMatrices();
    gl::popMatrices();
    
    gl::popMatrices();

    
}

//	// Clear window:
//	gl::clear( Color( 0, 0, 0 ) );
//
//	// Update camera position:
//	mCam.lookAt( Vec3f( 1.0, 1.0, 5.0), Vec3f::zero() );
//
//	// Set matrix from camera:
//	gl::setMatrices( mCam );
//	
//	// Set color:
//	gl::color( Color( 1.0, 1.0, 1.0 ) );
//	
//	// Set line width:
//	gl::lineWidth( 1.0 );
//	
//	// Draw origin:
//	gl::drawCoordinateFrame();
//	
//	// Prepare matrix transformation settings:
//	Vec3f tOuterCubeDimension   = Vec3f( 1.0, 2.0, 2.0 );
//	Vec3f tOuterCubeTranslation = Vec3f( 1.5, 0.0, 0.0 );
//	Vec3f tOuterCubeScale       = Vec3f( 0.5, 0.5, 0.5 );
//	Vec3f tOuterCubeRotation    = Vec3f( getElapsedSeconds() * 90.0, 0.0, 0.0 );
//	Vec3f tOuterCubeAnchor	    = Vec3f( 0.0, 0.0, 0.0 );
//	
//	Vec3f tInnerCubeDimension   = Vec3f( 3.0, 3.0, 3.0 );
//	Vec3f tInnerCubeTranslation = Vec3f( 0.0, 0.0, 0.0 );
//	Vec3f tInnerCubeScale       = Vec3f( 0.25, 0.25, 0.25 );
//	Vec3f tInnerCubeRotation    = Vec3f( getElapsedSeconds() * 180.0, 0.0, 0.0 );
//	Vec3f tInnerCubeAnchor	    = Vec3f( 2.0, 5.0, 0.0 );
//
//	// Draw 3D geometry (that HAS been pre-centered about the origin):
//	{
//		// Set color:
//		gl::color( Color( 0.0, 1.0, 0.0 ) );
//		
//		// Push outer matrix:
//		gl::pushMatrices();
//		
//		// Apply translation:
//		gl::translate( tOuterCubeTranslation );
//		
//		// Apply rotation:
//		gl::rotate( tOuterCubeRotation );
//		
//		// Apply scaling:
//		gl::scale( tOuterCubeScale );
//		
//		// Apply anchor translation:
//		gl::translate( tOuterCubeAnchor );
//		
//		// Draw cube:
//		gl::drawStrokedCube( Vec3f::zero(), tOuterCubeDimension );
//		
//		{
//			// Set color:
//			gl::color( Color( 0.0, 1.0, 1.0 ) );
//			
//			// Push inner matrix:
//			gl::pushMatrices();
//			
//			// Apply translation:
//			gl::translate( tInnerCubeTranslation );
//			
//			// Apply rotation:
//			gl::rotate( tInnerCubeRotation );
//			
//			// Apply scaling:
//			gl::scale( tInnerCubeScale );
//			
//			// Apply anchor translation:
//			gl::translate( tInnerCubeAnchor );
//			
//			// Draw cube:
//			gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
//            
//            {
//            	// Set color:
//                gl::color( Color( 0.0, 1.0, 1.0 ) );
//                
//                // Push inner matrix:
//                gl::pushMatrices();
//                
//                // Apply translation:
//                gl::translate( tInnerCubeTranslation);
//                
//                // Apply rotation:
//                gl::rotate( tInnerCubeRotation );
//                
//                // Apply scaling:
//                gl::scale( Vec3f( 0.75, 0.75, 0.75 ));
//                
//                // Apply anchor translation:
//                gl::translate( tInnerCubeAnchor );
//                
//                // Draw cube:
//                gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
//                
//                {
//                    // Set color:
//                    gl::color( Color( 0.0, 1.0, 1.0 ) );
//                    
//                    // Push inner matrix:
//                    gl::pushMatrices();
//                    
//                    // Apply translation:
//                    gl::translate( tInnerCubeTranslation);
//                    
//                    // Apply rotation:
//                    gl::rotate( tInnerCubeRotation );
//                    
//                    // Apply scaling:
//                    gl::scale( Vec3f( 0.75, 0.75, 0.75 ));
//                    
//                    // Apply anchor translation:
//                    gl::translate( tInnerCubeAnchor );
//                    
//                    // Draw cube:
//                    gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
//                    {
//                        // Set color:
//                        gl::color( Color( 0.0, 1.0, 1.0 ) );
//                        
//                        // Push inner matrix:
//                        gl::pushMatrices();
//                        
//                        // Apply translation:
//                        gl::translate( tInnerCubeTranslation);
//                        
//                        // Apply rotation:
//                        gl::rotate( tInnerCubeRotation );
//                        
//                        // Apply scaling:
//                        gl::scale( Vec3f( 0.75, 0.75, 0.75 ));
//                        
//                        // Apply anchor translation:
//                        gl::translate( tInnerCubeAnchor );
//                        
//                        // Draw cube:
//                        gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
//                        
//                        {
//                            // Set color:
//                            gl::color( Color( 0.0, 1.0, 1.0 ) );
//                            
//                            // Push inner matrix:
//                            gl::pushMatrices();
//                            
//                            // Apply translation:
//                            gl::translate( tInnerCubeTranslation);
//                            
//                            // Apply rotation:
//                            gl::rotate( tInnerCubeRotation );
//                            
//                            // Apply scaling:
//                            gl::scale( Vec3f( 0.75, 0.75, 0.75 ));
//                            
//                            // Apply anchor translation:
//                            gl::translate( tInnerCubeAnchor );
//                            
//                            // Draw cube:
//                            gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
//                            {
//                                // Set color:
//                                gl::color( Color( 0.0, 1.0, 1.0 ) );
//                                
//                                // Push inner matrix:
//                                gl::pushMatrices();
//                                
//                                // Apply translation:
//                                gl::translate( tInnerCubeTranslation);
//                                
//                                // Apply rotation:
//                                gl::rotate( tInnerCubeRotation );
//                                
//                                // Apply scaling:
//                                gl::scale( Vec3f( 0.75, 0.75, 0.75 ));
//                                
//                                // Apply anchor translation:
//                                gl::translate( tInnerCubeAnchor );
//                                
//                                // Draw cube:
//                                gl::drawStrokedCube( Vec3f::zero(), tInnerCubeDimension );
//                                
//                                
//                                // Pop inner matrix:
//                                gl::popMatrices();
//                                
//                            }
//
//                            
//                            // Pop inner matrix:
//                            gl::popMatrices();
//                            
//                        }
//
//                        // Pop inner matrix:
//                        gl::popMatrices();
//                        
//                    }
//
//                    
//                    // Pop inner matrix:
//                    gl::popMatrices();
//                    
//                }
//
//			// Pop inner matrix:
//			gl::popMatrices();
//            
//            }
//			
//			// Pop inner matrix:
//			gl::popMatrices();
//		}
//		
//		// Pop outer matrix:
//		gl::popMatrices();
//	}


CINDER_APP_NATIVE( MatrixTransformNestedApp, RendererGl )