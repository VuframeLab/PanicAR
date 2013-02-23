//
//  PARController+Config.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 18.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "PARController.h"

#define DEFAULT_OBJECT_NEAR_DISTANCE 10
#define DEFAULT_OBJECT_FAR_DISTANCE	 10 * 1000 * 1000                                             // 10.000 km

/*!
 * @name Config
 */
@interface PARController (Config)

/*! resets the default config
 * @remarks: see individual settings for defaults */
- (void)setDefaultConfig;

/*! near clip limit
 * @remarks objects closer than this distance will not be rendered */
- (float)clipObjectsNearLimit;
/*! far clip limit
 * @remarks objects farther away than this distance will not be rendered */
- (float)clipObjectsFarLimit;
/*! @param theNearLimit objects closer than this distance will not be rendered
 * @param theFarLimit objects farther away than this distance will not be rendered */
- (void)clipObjectsNearerThan:(float)theNearLimit fartherThan:(float)theFarLimit;


/*!  status of the PARController
 * @return YES if @ref availability is kPARStatusReady;
 * @ref availability */
- (BOOL)isReady  __attribute__ ((deprecated));


/*!  pause all updates in the PARViewController's views
 * @ref PARViewController:paused */
- (BOOL)isFrozen  __attribute__ ((deprecated));
/*!  pause all updates in the PARViewController's views
 * @param frozen YES to pause, NO to unpause
 * @ref PARViewController:setPaused */
- (void)setFrozen:(BOOL)frozen  __attribute__ ((deprecated));


@end
