//
//  PARMesh.m
//  PanicAR-Demo
//
//  Created by Andreas Zeitler on 14.03.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

#import "PARMesh.h"
#import <GLKit/GLKit.h>

const Vertex Vertices[] = {
    {1, -1, 0},
    {1, 1, 0},
    {-1, 1, 0},
    {-1, -1, 0}
};

const Color Colors[] = {
    {1, 0, 0, 1},
    {0, 1, 0, 1},
    {0, 0, 1, 1},
    {0, 0, 0, 1}
};

const GLubyte Indices[] = {
    0, 1, 2,
    2, 3, 0
};

@implementation PARMesh

- (Vertex[])vertices {
    //return k_Vertices;
}
- (GLubyte[])indices {
    //return k_Indices;
}

- (int)vertexCount {
    return 6;
}

- (void)setup {
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}
- (void)draw {
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    // vertex positions
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    // vertex colors
    glEnableVertexAttribArray(GLKVertexAttribColor);
    glVertexAttribPointer(GLKVertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Color), Colors);
    
    glDrawElements(GL_TRIANGLES, [self vertexCount], GL_UNSIGNED_BYTE, 0);
}

- (void)teardown {
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);
}

@end
