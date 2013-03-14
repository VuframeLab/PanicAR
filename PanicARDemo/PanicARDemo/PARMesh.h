//
//  PARMesh.h
//  PanicAR-Demo
//
//  Created by Andreas Zeitler on 14.03.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

struct vertexDataTextured
{
	GLKVector3		vertex;
	GLKVector3		normal;
	GLKVector2      texCoord;
};
typedef struct vertexDataTextured vertexDataTextured;
typedef vertexDataTextured* vertexDataTexturedPtr;



@interface PARMesh : NSObject {
    GLuint vertexArray;
    GLuint vertexBuffer;
}
@property (strong, nonatomic) GLKTextureInfo *texture;
@property (strong, nonatomic, readonly) GLKBaseEffect *effect;

- (id)initWithEffect:(GLKBaseEffect *)effect andMeshData:(vertexDataTextured[])meshData andMeshLength:(int)meshLength andTextureAtPath:(NSString *)texturePath;
- (void)draw;
- (void)teardown;

@end
