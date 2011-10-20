//
//  ARFreeObject.h
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
@class ARView;
@class ARVector;
@class ARMesh;
@class ARTexture;

/*! @class ARFreeObject
 @brief marker object to be rendered in the ARController's view
 
 a marker contains the geom_location and description (title, content, distance, image)
 a marker template will be used to render the marker
 if no special template is assigned the default infoLabel template will be used
 
 arObjects can be subclassed to extend their functionality
 */
@interface ARFreeObject : ARObject {
	
	// ogl object handles
	ARMesh* _mesh;
    ARTexture* _texture;
}



- (id)initWithParams:(ARMesh *)pMesh texture:(ARTexture *)pTexture position:(ARVector *)pPosition rotation:(ARVector *)pRotation size:(ARVector *)pSize scale:(float)pScale;


- (BOOL)hasTexture;

@end