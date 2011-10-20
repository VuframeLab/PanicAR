//
//  ARView.h
//  PanicAR
//
//  Created by Andreas Zeitler on 17.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/glext.h>
#import <UIKit/UIKit.h>
#import <math.h>

#import "ARUtils.h"

#define FADE_SPEED 1.0f//5.0f

@class EAGLContext;
@class ARController;
@class ARMarker;
@class ARObject;
@class ARVector;
@class ARView;
@class ARViewController;


extern ARView* _active;


@interface ARView : UIView 
{
@private
	ARUtils::FrameBuffer _frameBuffer;
	
    float _dt;
    
	//infra
	ARController* _arController;
	ARViewController* _arViewController;
	ARObject* _currentObject;
	
	EAGLContext* _oglContext;
	
	struct ARUtils::ARHardwareTimer _clock;
	NSTimer* _renderingTimer;
    
    // the target position and rotation
    ARVector* _CameraPosition;
    ARVector* _CameraRotation;
    // the interpolated positions and rotation
    ARVector* _FinalCameraRotation;
    ARVector* _FinalCameraPosition;
    
    ARVector* _dragOffset;
    float _baselineOffset;
    
	int _cameraRotationSector;
    float _orientation;
	
	BOOL _isSetup;
    
	float _viewWidth;
	float _viewHeight;
	float _viewX;
	float _viewY;
    
    float _baseAlpha;
    float _targetBaseAlpha;
    
    BOOL _enableDragging;
    float _focusDistance;
    
    BOOL _shouldBeRenderingObjects;
    
    BOOL _radarVisible;
    CGRect _radarRect;
    //CGRect _targetRadarRect;
    //BOOL _radarRectNeedsAnimation;
    BOOL _radarHidesObjects;
    float _radarAlpha;
}

@property (nonatomic, assign) int cameraRotationSector;
@property (nonatomic, retain) ARViewController* arViewController;


- (void)initializeOGL:(EAGLContext *)oglContext getOGLContext:(BOOL)getOGL;
- (void)releaseOGL;
- (void)updateRotation;
- (void)setBuffer;
- (void)setBuffer:(ARUtils::FrameBuffer)buffer;

- (void)stopRendering:(BOOL)clear;
- (void)startRendering;
- (BOOL)isRendering;
- (void)drawView:(NSTimer *)theTimer;
- (void)drawRadar;

- (void)setupRenderPipeline;

- (UIImage *)renderWithSize:(float)_width Height:(float)_height;
- (void)renderToBuffer;

- (void)updateCamera;
- (void)orientate:(float)newOrientation;

- (void)enableDragging:(BOOL)_state;
- (void)setPosition: (float) px Y: (float) py Z: (float) pz;
- (ARVector *)position;
- (void)setRotation: (float) px Y: (float) py Z: (float) pz;
- (ARVector *)rotation;
- (float)baselineOffset;

- (float)heading;
- (float)tilt;
- (float)roll;

- (void)setBaseAlpha:(double)theAlpha;
- (double)baseAlpha;

- (void)setFocusDistance:(float)theDistance;

- (void)jumpToTarget;


- (void)setupProjection;
- (void)switchToOrtho;
- (void)switchBackToFrustum;


- (void)hideObjects:(BOOL)animated;
- (void)showObjects:(BOOL)animated;
- (BOOL)areObjectsVisible;

- (void)setRadarToFullscreen;
- (void)setRadarToThumbnail;
- (void)setRadarToThumbnail:(CGPoint)thePosition withSize:(float)theSize;
- (void)showRadar;
- (void)hideRadar;

- (NSString *)description;


+ (void)setActiveARView:(ARView *)theView;
+ (ARView *)activeARView;


@end
