//
//  ARTexture.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 10.08.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ARUtils.h"

@interface ARTexture : NSObject {
    uint _handle;
    BOOL _loaded;
    UIImage* _texture;
    uint _width;
    uint _height;
    NSString* _fileId;
    BOOL _hasAlpha;
}

- (id)initFromFile:(NSString *)file;
- (void)refresh;
- (void)freeMemory;
- (uint) handle;
- (BOOL)hasAlpha;
- (NSString *)file;


+ (ARTexture *)fromFile:(NSString *)file;

@end
