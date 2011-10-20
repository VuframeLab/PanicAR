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
#import "ARObject.h"


@class ARController;
@class ARMarkerTemplate;
@class ARView;
@class ARMesh;
@class ARVector;


#pragma mark - CONSTANTS

#define NUMBER_OF_STACKINGSECTORS 36 
#define NUMBER_OF_SLOTS_PER_STACKINGSECTOR 100
#define STACKINGSECTOR_WIDTH_IN_DEGREES()(360.0/NUMBER_OF_STACKINGSECTORS)
#define ARMARKER_DEFAULT_SIZE 50
#define DISABLE_AT_ANGLE_DEVIATION 50

#define ARMARKER_DEFAULT_HEIGHT_FOR_STACKING 1.6
#define ARMARKER_DEFAULT_BASELINE_Y -2


#pragma mark - Interface

/*! @class ARMarker
 @brief marker object to be rendered in the ARController's view
 
 a marker contains the geolocation and description (title, content, distance, image)
 a marker template will be used to render the marker
 if no special template is assigned the default infoLabel template will be used
 
 arObjects can be subclassed to extend their functionality
 */
@interface ARMarker : ARObject {	
	NSString* _title; // title of the marker's infoLabel
	NSString* _content; // title of the marker's infoLabel
	UIImage* _image; // image of the marker's infoLabel
	CLLocation* _location; // geo location of the marker
	
	ARMarkerTemplate* _markerTemplate;
	
	double _distance; // distance to user's position
	double _angle;
	float _lookAtAngle;
	
	BOOL _suppressFirstTextureUpdate;
	BOOL _forceTextureUpdate;
	
	// ogl object handles
	uint _hitMaskHandle;
	float _lowerMeshBounds;
	
	int _stackingSectorID;
	int _stackingSlotID;
	float _lastUpdateAtDistance;
	float _lastUpdateAtBearing;
	
	// ogl object handles
	ARMesh* _mesh;
    BOOL _hasTexture;
	uint _textureHandle;
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

@property int stackingSectorID;
@property int stackingSlotID;


/** create ARMarker with Title
 @param Title: title of the marker (may not be nil)
 */
- (id)initWithTitle:(NSString *)pTitle atLocation:(CLLocation *)theLocation;


/** create ARMarker with Title and Description (content)
 @param Title: title of the marker (may not be nil)
 @param contentOrNil: description/content of the marker (may be nil)
 */
- (id)initWithTitle:(NSString *)pTitle contentOrNil:(NSString *)pContent atLocation:(CLLocation *)theLocation;


/** create ARMarker with Title, Description (content) and Image, Title is a mandatory parameter.
 @param Title: title of the marker (may not be nil)
 @param contentOrNil: description/content of the marker (may be nil)
 @param imageOrNil: image to be rendered as specified in marker template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 */
- (id)initWithTitle:(NSString *)pTitle contentOrNil:(NSString *)pContent imageOrNil:(UIImage *)pImage atLocation:(CLLocation *)theLocation;


/** create ARMarker at Geolocation with Title, Description (content) and Image, Title is a mandatory parameter. Optional: use a custom template for this marker.
 @param Title: title of the marker (may not be nil)
 @param contentOrNil: description/content of the marker (may be nil)
 @param imageOrNil: image to be rendered as specified in marker template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 @param templateOrNil: template that will be used to render the marker (may be nil); if nil: default template will be used
 */
- (id)initWithTitle:(NSString *)pTitle contentOrNil:(NSString *)pContent imageOrNil:(UIImage *)pImage templateOrNil:(ARMarkerTemplate *)pTemplate atLocation:(CLLocation *)theLocation;


+ (void)updateStacking;



@end