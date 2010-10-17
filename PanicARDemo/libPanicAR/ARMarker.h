#ifndef st_ARMarker_h_
#define st_ARMarker_h_
//
//  ARMarker.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//


#import "ARView.h"
#import "Mesh.h"
#import "Vector.h"
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "ARController.h"
#import "ARMarkerDelegate.h"
#import "ARLabelTemplate.h"
#import "GlErrors.h"
#import <OpenGLES/ES1/glext.h>
#import "TextureUtils.h"
#import "Lerp.h"
#import "RenderUtils.h"

@class ARController;
@class ARView;

@interface ARMarker : NSObject {
	
	bool enabled; // is marker updated?
	bool visible; // is marker visible?
	bool isGeoMarker;
	bool isContentLabel;
	
	id<ARMarkerDelegate> delegate;
	
	NSString* title; // title of the marker's label
	NSString* content; // title of the marker's label
	UIImage* image; // image of the marker's label
	CLLocation* location; // geo location of the marker
	
	ARLabelTemplate* labelTemplate;
	
	double distance; // distance to user's position
	double angle;
	bool jump;
	float lookAtAngle;
	
	bool suppressFirstTextureUpdate;
	
	// ogl object handles
	Mesh mesh;
	uint textureHandle;
	uint hitMaskHandle;
	float colorID;
	
	// UIKit references
	ARView* view;
	ARController* controller;
	
	// ogl space transform
	Vector *position; // position
	Vector *rotation; // rotation
	Vector *size; // scale
	Vector *inputPosition; // position on screen
	float yOffset;
	float scale;
	
	int sector;
	int yStep;
	float lastUpdateAtDistance;
	float lastUpdateAtBearing;
}

@property (nonatomic, retain) CLLocation *location;
@property (nonatomic, retain) NSString *title;
@property (nonatomic, retain) NSString *content;
@property (nonatomic, retain) UIImage *image;
@property (assign) id<ARMarkerDelegate> delegate;
@property (assign) ARView *view;
@property (assign) ARController *controller;

@property int sector;
@property int yStep;
@property double distance;
@property double angle;
@property bool jump;
@property bool enabled;
@property bool isGeoMarker;
@property float scale;
@property float colorID;

- (id) init:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage;
- (id) init:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage templateOrNil:(ARLabelTemplate*)pTemplate;
- (id) init:(NSString*)pTitle locationOrNil:(CLLocation*)pLocation contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage templateOrNil:(ARLabelTemplate*)pTemplate;
- (id) init:(NSString*)meshFile texture:(NSString*)textureFile scale:(float)pScale;

- (void) updateGeoInfo;
- (void) updateTexture;

- (void) transform;
- (void) draw:(float)dt;
- (void) drawAsLabel:(float)dt;
- (void) drawAsObject:(float)dt;
- (void) drawBounds;
- (void) drawOnRadar;

+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

@end

#endif