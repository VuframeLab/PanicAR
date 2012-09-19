//
//  PARController+Config.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 18.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "PARController.h"

#define DEFAULT_OBJECT_NEAR_DISTANCE 10
#define DEFAULT_OBJECT_FAR_DISTANCE 10*1000*1000 // 10.000 km

/*!
 @name Config
 */
@interface PARController (Config)

/*! resets the default config
 @remarks: see individual settings for defaults */
- (void)setDefaultConfig;






- (float)clipObjectsNearLimit;
- (float)clipObjectsFarLimit;
- (void)clipObjectsNearerThan:(float)theNearLimit fartherThan:(float)theFarLimit;





@end
