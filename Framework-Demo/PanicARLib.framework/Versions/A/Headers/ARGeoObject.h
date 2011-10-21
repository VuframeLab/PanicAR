//
//  ARGeoObject.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#import "ARObject.h"


@class ARObjectDelegate;
@class ARController;
@class ARView;
@class ARVector;
@class ARMesh;
@class ARTexture;

/*! @class ARGeoObject
 @brief marker object to be rendered in the ARController's view
 
 a marker contains the geom_location and description (title, content, distance, image)
 a marker template will be used to render the marker
 if no special template is assigned the default infoLabel template will be used
 
 arObjects can be subclassed to extend their functionality
 */
@interface ARGeoObject : ARObject {
	
    // geo space
	ARVector*_geoPosition; // position: latitude, longitude, altitude
	float _geoRotation; // rotation
    
	CLLocation* _location; // geo location of the marker
	float _distance;
	float _angle;
    
	// general variables
	// ogl object handles
	ARMesh* _mesh;
    ARTexture* _texture;
}


/*! constructor
 creates an ARGeoObject at the specific geo location, with the heading (direction to face) and scale
 will generate a virtual space for the GeoObject at the specified location
 geo location and heading are read only after creation
 model can only be modified in virtual space (position, rotation, size)
 */
- (id)initWithParams:(ARMesh *)pMesh texture:(ARTexture *)pTexture latitude:(double)latitude longitude:(double)longitude altitude:(float)altitude heading:(float)heading scale:(float)scale;

- (id)initWithParams:(NSString *)meshFile textureFile:(NSString *)textureFile latitude:(double)latitude longitude:(double)longitude altitude:(float)altitude heading:(float)heading scale:(float)scale __attribute__((deprecated));

- (id)initWithParams:(NSString *)meshFile textureFile:(NSString *)textureFile location:(CLLocation *)pLocation heading:(double)pHeading size:(ARVector *)pSize scale:(float)pScale __attribute__((deprecated));


- (float)heading;

- (BOOL)hasTexture;

@end