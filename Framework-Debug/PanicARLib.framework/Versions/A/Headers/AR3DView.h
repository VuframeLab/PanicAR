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
#import "ARViewController.h"
#import "ARUtils.h"

#define FADE_SPEED 5.0f

@class EAGLContext;
@class ARController;
@class ARPoiLabel;
@class ARObject;
@class ARVector;
@class ARViewController;


extern ARView* _active;

/*!
 @class ARView
 @brief ARView controlled by ARViewController, derived from UIView
 @remarks should not be manipulated directly
 */
@interface AR3DView : UIView 
{
@private
	ARUtils::FrameBuffer _frameBuffer;
	
    float _dt;
    
	//infra
	ARController* _arController;
	ARViewController* _arViewController;
	ARObject* _currentObject;
	
	EAGLContext* _oglContext;
	
	ARUtils::ARHardwareTimer _clock;
	NSTimer* renderingTimer;
    
    // the target position and rotation
    ARVector* _CameraPosition;
    ARVector* _CameraRotation;
    // the interpolated positions and rotation
    ARVector* _FinalCameraRotation;
    ARVector* _FinalCameraPosition;
    
    ARVector* _dragOffset;
    float _baselineOffset;
    
	int _cameraRotationSector;
	
	BOOL _isSetup;
    
	float _viewWidth;
	float _viewHeight;
	float _viewX;
	float _viewY;
    
    float _baseAlpha;
    float _targetBaseAlpha;
    
    BOOL _cameraLocked;
    
    BOOL _shouldBeRenderingObjects;
}

@property (nonatomic, assign) int cameraRotationSector;
@property (nonatomic, assign) BOOL cameraLocked;


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

- (UIImage *)renderToImageWithSize:(float)_width Height:(float)_height;
- (void)renderToBuffer;

- (void)updateCamera;


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

- (void)jumpToTarget;


- (void)setupProjection;
- (void)switchToOrtho;
- (void)switchBackToFrustum;


- (void)hideObjects:(BOOL)animated;
- (void)showObjects:(BOOL)animated;
- (BOOL)areObjectsVisible;

- (NSString *)description;


+ (void)setActiveView:(ARView *)theView;
+ (ARView *)activeView;


@end
