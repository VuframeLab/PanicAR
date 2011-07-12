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

#import "ARController.h"
#import "ARObjectDelegate.h"
#import "ARUtils.h"


@class EAGLContext;
@class ARController;
@class ARMarker;



@interface ARView : UIView 
{
@private
	ARUtils::FrameBuffer m_frameBuffer;
	
    float dt;
    
	//infra
	ARController* m_ARController;
	id<ARObjectDelegate> currentMarker;
	
	EAGLContext* m_oglContext;
	
	struct ARUtils::ARHardwareTimer m_clock;
	NSTimer* m_timer;
    
	//x and y current angle of camera
	float cameraAngleX;
	float cameraAngleY;
	float cameraRoll;
	float currentCameraRoll;
	float cameraY;
	//x and y target angle of camera
	float cameraTargetAngleX;
	float cameraTargetAngleY;
	float cameraTargetY;
	int cameraSector;
	
	BOOL isSetup;
	BOOL hasTimer;
	
	BOOL m_touched;
	BOOL m_touchMoved;
	
	CGPoint initialTouchPosition;
	CGPoint touchDistance;
	
	float viewWidth;
	float viewHeight;
	float viewX;
	float viewY;
}

@property CGPoint touchDistance;
@property (assign) float cameraAngleX;
@property (assign) float cameraTargetAngleX;
@property (assign) float cameraTargetAngleY;
@property (assign) float cameraTargetY;
@property (assign) float cameraRoll;
@property (assign) int cameraSector;
@property (nonatomic, retain) ARController	*m_ARController;


- (void)initializeOGL:(EAGLContext*)oglContext getOGLContext:(BOOL)getOGL;
- (void)releaseOGL;
- (void)updateRotation;
- (void)bind;
- (BOOL)popTouch;


- (id)initWithARController:(ARController*)controller;
- (void)stopUpdate;
- (void)startUpdate;
- (void)drawView:(NSTimer*)theTimer;
- (void)drawRadar;
- (void)setupView;
- (void)setupTouchView;


@end
