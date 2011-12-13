//
//  ARView+Util.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <PanicARLib/PanicARLib.h>

@interface ARView (Util)

- (UIImage *)getScreenshot;
- (void)saveScreenshotToFile:(NSString *)theFilename;

@end
