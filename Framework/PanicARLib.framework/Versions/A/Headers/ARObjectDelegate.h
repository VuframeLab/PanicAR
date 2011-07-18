//
//  ARObjectDelegate.h
//  ArchiApp
//
//  Created by Andreas Zeitler on 05.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>


@protocol ARObjectDelegate

- (BOOL) enabled;

- (float) distance;
- (int) colorID;
- (void) setColorID:(int)color;

/** refresh the AR marker (after changing content)
 @param immediately: use to force immediate update, if NO marker will be updated the next time it is rendered
 */
- (void) refresh:(BOOL)immediately;

- (void) updateInfo;
- (void) updateTexture;
- (void) freeMemory;

- (void) transform;
- (void) draw:(float)dt;
- (void) drawBounds;
- (void) drawOnRadar;

@end
