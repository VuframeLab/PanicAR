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
#import "ARController.h"
#import "ARObjectDelegate.h"


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
@interface ARMarker : NSObject <ARObjectDelegate> {	
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
	BOOL forceTextureUpdate;
	
	// ogl object handles
	uint hitMaskHandle;
	ARVector *inputPosition; // position on screen
	float yOffset;
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
	
	
	// general variables
	BOOL enabled; // is marker updated?
	BOOL visible; // is marker visible?
	float colorID; // color id for touch handling
	// ogl object handles
	Mesh mesh;
    BOOL hasTexture;
	uint textureHandle;
	// ogl space transform
	ARVector *position; // position
	ARVector *rotation; // rotation
	ARVector *size; // scale
	float scale;
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
@property double angle;
@property BOOL jump;
@property float scale;
@property float touchDownScale;
@property float touchDownColorR;
@property float touchDownColorG;
@property float touchDownColorB;
@property float touchDownColorA;


/** create ARMarker with Title
 @param Title: title of the marker (may not be nil)
 */
- (id) initWithTitle:(NSString*)pTitle;


/** create ARMarker with Title and Description (content)
 @param Title: title of the marker (may not be nil)
 @param contentOrNil: description/content of the marker (may be nil)
 */
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent;


/** create ARMarker with Title, Description (content) and Image, Title is a mandatory parameter.
 @param Title: title of the marker (may not be nil)
 @param contentOrNil: description/content of the marker (may be nil)
 @param imageOrNil: image to be rendered as specified in marker template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 */
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage;


/** create ARMarker at Geolocation with Title, Description (content) and Image, Title is a mandatory parameter. Optional: use a custom template for this marker.
 @param Title: title of the marker (may not be nil)
 @param contentOrNil: description/content of the marker (may be nil)
 @param imageOrNil: image to be rendered as specified in marker template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 @param templateOrNil: template that will be used to render the marker (may be nil); if nil: default template will be used
 */
- (id) initWithTitle:(NSString*)pTitle contentOrNil:(NSString*)pContent imageOrNil:(UIImage*)pImage templateOrNil:(ARMarkerTemplate*)pTemplate;



@end