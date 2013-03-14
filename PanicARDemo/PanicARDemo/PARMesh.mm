//
//  PARMesh.m
//  PanicAR-Demo
//
//  Created by Andreas Zeitler on 14.03.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

#import "PARMesh.h"

@interface PARMesh ()
@property (strong, nonatomic, readwrite) GLKBaseEffect *effect;
@end

@implementation PARMesh {
    int _lengthOfMesh;
}

- (id)initWithEffect:(GLKBaseEffect *)effect andMeshData:(vertexDataTextured[])meshData andMeshLength:(int)meshLength andTextureAtPath:(NSString *)texturePath {
    if (self = [super init]) {
        self.effect = effect;
        [self loadMesh:meshData andMeshLength:meshLength];
        [self loadTexture:texturePath];
    }
    return self;
}

- (void)loadMesh:(vertexDataTextured[])meshVertexData andMeshLength:(int)meshLength {
    glGenVertexArraysOES(1, &vertexArray);
    glBindVertexArrayOES(vertexArray);
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    _lengthOfMesh = meshLength;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexDataTextured)*_lengthOfMesh, meshVertexData, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(vertexDataTextured), 0);
    glEnableVertexAttribArray(GLKVertexAttribNormal);
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE,  sizeof(vertexDataTextured), (char *)12);
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(vertexDataTextured), (char *)24);
    glBindVertexArrayOES(0);
}

- (void)loadTexture:(NSString *)texturePath {
    glActiveTexture(GL_TEXTURE0);
    
    NSError *error = nil;
    self.texture = [GLKTextureLoader textureWithContentsOfFile:texturePath
                                                       options:@{ GLKTextureLoaderOriginBottomLeft : @(YES) }
                                                         error:&error];
    if (self.texture == nil) {
        NSLog(@"Error loading texture: %@", [error localizedDescription]);
    }
    
    GLKEffectPropertyTexture *tex = [[GLKEffectPropertyTexture alloc] init];
    tex.enabled = YES;
    tex.envMode = GLKTextureEnvModeDecal;
    tex.name = self.texture.name;
    
    _effect.texture2d0.name = tex.name;
}

- (void)draw {
    glBindVertexArrayOES(vertexArray);
    [_effect prepareToDraw];
    glDrawArrays(GL_TRIANGLES, 0, _lengthOfMesh); // sizeof(MeshVertexData) / sizeof(vertexDataTextured)
}

- (void)teardown {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArraysOES(1, &vertexArray);
}

@end
