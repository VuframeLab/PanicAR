//
//  ARBillboard.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "ARFreeObject.h"


@class ARController;
@class ARMarkerTemplate;
@class ARView;
@class ARMesh;
@class ARTexture;
@class ARVector;

/*! @class ARMarker
 @brief marker object to be rendered in the ARController's view
 
 a marker contains the geolocation and description (title, content, distance, image)
 a marker template will be used to render the marker
 if no special template is assigned the default infoLabel template will be used
 
 arObjects can be subclassed to extend their functionality
 */
@interface ARBillboard : ARFreeObject {
	CLLocation* _location; // geo location of the marker
	
	double _distance; // distance to user's position
	double _angle;
	float _lookAtAngle;
}

- (id)init:(ARMesh *)withMesh andTexture:(ARTexture *)theTexture atHeight:(float)theHeight withSize:(ARVector *)theSize andScale:(float)theScale;
- (void)setLocation:(CLLocation *)theLocation;
- (void)setAngle:(float)theAngle;




@end