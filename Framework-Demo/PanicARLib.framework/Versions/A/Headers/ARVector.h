//
//  ARVector.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>


/*! @class ARVector
 @brief can hold position/rotation in 3d space
 
 x,y,z position for 3d space coordinates
 */
@interface ARVector : NSObject {
    /*! @property x */
	GLfloat x;
    /*! @property y */
	GLfloat y;
    /*! @property z */
	GLfloat z;
}


@property GLfloat x; 
@property GLfloat y; 
@property GLfloat z; 


/*! init a ARVector with 0,0,0 */
- (ARVector*) init;

/*! init a ARVector with x, y, z */
- (ARVector*) initWithCoords: (GLfloat) px Y: (GLfloat) py Z: (GLfloat) pz;

/*! init a ARVector with x, y, z */
+ (ARVector*) vectorWithCoords: (GLfloat) px Y: (GLfloat) py Z: (GLfloat) pz;

@end
