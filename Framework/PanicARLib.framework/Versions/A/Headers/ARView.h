//
//  ARView.h
//  PanicAR
//
//  Created by Andreas Zeitler on 17.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#include <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/glext.h>
#import <UIKit/UIKit.h>
#import <math.h>

#import "ARController.h"
#import "ARUtils.h"


@class EAGLContext;
@class ARController;
@class ARMarker;



@interface ARView : UIView 
{
	ARUtils::FrameBuffer m_frameBuffer;
	
	//infra
	ARController* m_ARController;
	ARMarker* currentMarker;
	
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
	
	bool isSetup;
	bool hasTimer;
	
	bool m_touched;
	bool m_touchMoved;
	
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


- (void)initializeOGL:(EAGLContext*)oglContext getOGLContext:(bool)getOGL;
- (void)releaseOGL;
- (void)updateRotation;
- (void)bind;
- (bool)popTouch;


- (id)initWithARController:(ARController*)controller;
- (void)stopUpdate;
- (void)startUpdate;
- (void)drawView:(NSTimer*)theTimer;
- (void)drawRadar;
- (void)setupView;
- (void)setupTouchView;


@end
