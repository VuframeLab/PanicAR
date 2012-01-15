//
//  ARController+Config.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 18.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "ARController.h"

/*!
 @name Config
 */
@interface ARController (Config)

/*! resets the default config
 @remarks: see individual settings for defaults
 */
- (void)setDefaultConfig;

/*! can AR Objects receive touch events?
 @param state: YES to enable touch events on ARObjects
 @remarks ARObject sub-class has to implement touch events
 default: YES
 */






#pragma mark -
#pragma mark Debugging

- (void)enableConsole;
- (void)disableConsole;
- (BOOL)isConsoleEnabled;

- (void)enableErrorMessages;
- (void)disableErrorMessages;


#pragma mark -
#pragma mark Radar

- (void)enableContinuousGPS;
- (void)disableContinuousGPS;
- (BOOL)isContinuousGPSEnabled;

- (float)clipObjectsNearLimit;
- (float)clipObjectsFarLimit;
- (void)clipObjectsNearerThan:(float)theNearLimit fartherThan:(float)theFarLimit;


- (void)enableOrientationUpdate;
- (void)disableOrientationUpdate;
- (BOOL)isOrientationUpdateEnabled;
- (UIDeviceOrientation)defaultOrientation;
- (void)setDefaultOrientation:(UIDeviceOrientation)theOrientation;


#pragma mark - ARView Mode
/*!
 
 default: ARViewWithOrientationUpdate
 */
- (ARViewMode) arViewMode;

/*! 
 CONFIGURATION: sets the mode of the ar view
 @param theMode - View Modes:
 ARViewFixed: the view will not change orientation
 ARViewHeadingOnly: the view will only update heading
 ARViewWithTiltUpdate: the view will update on the vertical axis
 ARViewWithOrientationUpdate: the view will snap to all supported UIViewOrientations (Portrait, LandscapeLeft/Right, etc.)
 ARViewWithHorizonUpdate: the view will dynamically rotate with the device
 
 default: ARViewWithOrientationUpdate
 */
- (void)setARViewMode:(ARViewMode)theMode;




@end
