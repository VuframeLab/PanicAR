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



#pragma mark - Debugging

/*! enable console (will show console display if possible)
 @remarks DEBUG only */
- (void)enableConsole;
/*! show console display
 @remarks DEBUG only */
- (void)showConsole;
/*! hide console display
 @remarks DEBUG only */
- (void)hideConsole;
/*! disable console
 @remarks DEBUG only */
- (void)disableConsole;
/*! check if console is enabled
 @return YES if console is enabled
 @remarks DEBUG only */
- (BOOL)isConsoleEnabled;



- (float)clipObjectsNearLimit;
- (float)clipObjectsFarLimit;
- (void)clipObjectsNearerThan:(float)theNearLimit fartherThan:(float)theFarLimit;





@end
