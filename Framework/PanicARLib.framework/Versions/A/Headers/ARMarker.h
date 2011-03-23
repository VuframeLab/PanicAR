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
@class ARVector;

/*! @class ARMarker
 @brief marker object to be rendered in the ARController's view
 
 a marker contains the geolocation and description (title, content, distance, image)
 a marker template will be used to render the marker
 if no special template is assigned the default infoLabel template will be used
 
 markers can be subclassed to extend their functionality
 */
@interface ARMarker : NSObject {
	
	BOOL enabled; // is marker updated?
	BOOL visible; // is marker visible?
	BOOL isGeoMarker;
	BOOL isContentMarker;
	
	NSString* title; // title of the marker's infoLabel
	NSString* content; // title of the marker's infoLabel
	UIImage* image; // image of the marker's infoLabel
	CLLocation* location; // geo location of the marker
	
	ARMarkerTemplate* markerTemplate;
	
	double distance; // distance to user's position
	double angle;
	BOOL jump;
	float lookAtAngle;
	
	BOOL suppressFirstTextureUpdate;
	
	// ogl object handles
	Mesh mesh;
    BOOL hasTexture;
	uint textureHandle;
	uint hitMaskHandle;
	float colorID;
	
	// ogl space transform
	ARVector *position; // position
	ARVector *rotation; // rotation
	ARVector *size; // scale
	ARVector *inputPosition; // position on screen
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
@property BOOL jump;
@property BOOL enabled;
@property BOOL isGeoMarker;
@property float scale;
@property float colorID;
@property float touchDownScale;
@property float touchDownColorR;
@property float touchDownColorG;
@property float touchDownColorB;
@property float touchDownColorA;

/** create ARMarker with Title
 */
- (id) initWithTitle:(NSString*)pTitle;
/** create ARMarker with Title and Description (content)
 */
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent;
/** create ARMarker with Title, Description (content) and Image, Title is a mandatory parameter.
 */
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage;
/** create ARMarker at Geolocation with Title, Description (content) and Image, Title is a mandatory parameter. Optional: use a custom template for this marker.
 */
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage templateOrNil:(ARMarkerTemplate*)pTemplate;
- (id) initAs3DObject:(NSString*)meshFile texture:(NSString*)textureFile position:(ARVector*)position rotation:(ARVector*)rotation size:(ARVector*)pSize scale:(float)pScale;

- (void) updateGeoInfo;
- (void) updateTexture;
- (void) freeMemory;

- (void) transform;
- (void) draw:(float)dt;
- (void) drawAsLabel:(float)dt;
- (void) drawAsObject:(float)dt;
- (void) drawBounds;
- (void) drawOnRadar;

/* calculates the direction towards a location, heads-up line isthe north
 pole at 0 degrees does not take into account the earth's curve and therefore 
 will grow more inaccurate the farther the locations are apart */
+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

@end