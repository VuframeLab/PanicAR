//
//  PARMesh.h
//  PanicAR-Demo
//
//  Created by Andreas Zeitler on 14.03.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
    float Position[3];
} Vertex;

typedef struct {
    float Color[4];
} Color;

@interface PARMesh : NSObject {
    // opengl runtime
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
}

- (Vertex[])vertices;
- (GLubyte[])indices;

- (void)setup;
- (void)draw;
- (void)teardown;

@end
