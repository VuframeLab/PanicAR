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
    uint m_handle;
    BOOL m_loaded;
    UIImage* m_texture;
    uint m_width;
    uint m_height;
    NSString* m_fileId;
    BOOL m_hasAlpha;
}

- (id)initFromFile:(NSString *)file;
- (void)refresh;
- (void)freeMemory;
- (uint) handle;
- (BOOL)hasAlpha;
- (NSString *)file;


+ (ARTexture *)fromFile:(NSString *)file;

@end
