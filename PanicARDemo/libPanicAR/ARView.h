#ifndef st_ARView_h_
#define st_ARView_h_


#include "FrameBuffer.h"
#include "GlErrors.h"
#include <QuartzCore/QuartzCore.h>
#include <OpenGLES/EAGL.h>
#include <OpenGLES/EAGLDrawable.h>
#include <OpenGLES/ES1/glext.h>
#import <UIKit/UIKit.h>

#import "ARView.h"
#import "ARMarker.h"
#import "HardwareClock.h"
#import "ARController.h"
#import "Queue.h"
#import "RenderUtils.h"
#import <math.h>
#import "Lerp.h"
#import "Mesh.h"
#import "ARController.h"


@class EAGLContext;
@class ARController;
@class ARMarker;

@interface ARView : UIView 
{
	FrameBuffer m_frameBuffer;
	
	//infra
	ARController* m_ARController;
	ARMarker* currentMarker;
	
	EAGLContext* m_oglContext;
	
	st::HardwareClock m_clock;
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
	
	st::QueueStorage< float, 200 > m_dtHistory;
	
	bool m_touched;
	bool m_touchMoved;
	
	CGPoint initialTouchPosition;
	CGPoint touchDistance;
}

@property CGPoint touchDistance;
@property (assign) float cameraAngleX;
@property (assign) float cameraTargetAngleX;
@property (assign) float cameraTargetAngleY;
@property (assign) float cameraTargetY;
@property (assign) float cameraRoll;
@property (assign) int cameraSector;
@property (nonatomic, retain) ARController	*m_ARController;


- (void)initialize:(EAGLContext*)oglContext;
- (void)updateRotation;
- (void)bind;
- (bool)popTouch;


- (id)initWithARController:(ARController*)controller;
- (void)hide;
- (void)show;
- (void)drawView:(NSTimer*)theTimer;
- (void)drawRadar;
- (void)setupView;
- (void)setupTouchView;


@end


#endif
