//
//  ARMesh.h
//  PanicAR Framework (PanicARLib.framework)
//
//  Created by Andreas Zeitler on 13.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ARUtils.h"

@interface ARMesh : NSObject {
    NSString* _meshFile;
    Mesh _mesh;
}

- (id)initFromFile:(NSString *)file;
- (Mesh *)mesh;
- (NSString *)file;


- (NSString *)description;

#if DEBUG
- (void)printData;
#endif 

+ (ARMesh *)fromFile:(NSString *)file;

@end
