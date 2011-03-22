//
//  ARMarker.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#import "ARUtils.h"
#import "ARMarker.h"
#import "ARController.h"


@class ARController;
@class ARMarkerTemplate;
@class ARView;
@class Vector;

/*! @class ARMarker
 @brief marker object to be rendered in the ARController's view
 
 a marker contains the geolocation and description (title, content, distance, image)
 a marker template will be used to render the marker
 if no special template is assigned the default infoLabel template will be used
 
 markers can be subclassed to extend their functionality
 */
@interface ARMarker : NSObject {
	
	bool enabled; // is marker updated?
	bool visible; // is marker visible?
	bool isGeoMarker;
	bool isContentMarker;
	
	NSString* title; // title of the marker's infoLabel
	NSString* content; // title of the marker's infoLabel
	UIImage* image; // image of the marker's infoLabel
	CLLocation* location; // geo location of the marker
	
	ARMarkerTemplate* markerTemplate;
	
	double distance; // distance to user's position
	double angle;
	bool jump;
	float lookAtAngle;
	
	bool suppressFirstTextureUpdate;
	
	// ogl object handles
	Mesh mesh;
    bool hasTexture;
	uint textureHandle;
	uint hitMaskHandle;
	float colorID;
	
	// ogl space transform
	Vector *position; // position
	Vector *rotation; // rotation
	Vector *size; // scale
	Vector *inputPosition; // position on screen
	float yOffset;
	float scale;
	float scaleFac;
	
	int sector;
	int yStep;
	float lastUpdateAtDistance;
	float lastUpdateAtBearing;
	
	float touchDownScale;
	float touchDownColorR;
	float touchDownColorG;
	float touchDownColorB;
	float touchDownColorA;
}

/*
 location of the marker (retained)
 **/
@property (nonatomic, retain) CLLocation *location;

/*
 title of the marker (retained)
 **/
@property (nonatomic, retain) NSString *title;

/*
 content (description) of the marker (retained)
 **/
@property (nonatomic, retain) NSString *content;

/*
 image of the marker (retained)
 depending on the size of the template this can be a icon or thumbnail
 but also a full-sized image
 **/
@property (nonatomic, retain) UIImage *image;

@property int sector;
@property int yStep;
@property double distance;
@property double angle;
@property bool jump;
@property bool enabled;
@property bool isGeoMarker;
@property float scale;
@property float colorID;
@property float touchDownScale;
@property float touchDownColorR;
@property float touchDownColorG;
@property float touchDownColorB;
@property float touchDownColorA;

- (id) initWithTitle:(NSString*)pTitle;
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent;
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage;
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage templateOrNil:(ARMarkerTemplate*)pTemplate;
- (id) initAs3DObject:(NSString*)meshFile texture:(NSString*)textureFile scale:(float)pScale;

- (void) updateGeoInfo;
- (void) updateTexture;
- (void) freeMemory;

- (void) transform;
- (void) draw:(float)dt;
- (void) drawAsLabel:(float)dt;
- (void) drawAsObject:(float)dt;
- (void) drawBounds;
- (void) drawOnRadar;

+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

@end