//
//  ARController+Config.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 18.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <PanicARLib/PanicARLib.h>



/*!
 @name Config
 */

@interface ARController (Config)

- (void)setDefaultConfig;

- (void)objectsRespondToTouch:(BOOL)state;
- (BOOL)doObjectsRespondToTouch;

- (void)enableRadar;
- (void)disableRadar;
- (BOOL)isRadarEnabled;
/*! set radar range in meters, objects outside range will not be displayed on radar
 @param theRange the range the radar will display markers in
 */
- (void)setRadarRange:(float)theRange;
/*! radar range in meters, objects outside range will not be displayed on radar
 @return the range
 @remarks default = 10.000 meters
 */
- (float)radarRange;
- (void)setRadarClipping:(BOOL)theState;
- (BOOL)radarClipsObjects;

- (void)enableConsole;
- (void)disableConsole;
- (BOOL)isConsoleEnabled;

- (void)enableErrorMessages;
- (void)disableErrorMessages;

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
- (ARViewMode) arViewMode;
/*! 
 CONFIGURATION: sets the mode of the ar view
 @param mode
 
 View Modes:
 ARViewFixed: the view will not change orientation
 ARViewHeadingOnly: the view will only update heading
 ARViewWithTiltUpdate: the view will update on the vertical axis
 ARViewWithOrientationUpdate: the view will snap to all supported UIViewOrientations (Portrait, LandscapeLeft/Right, etc.)
 ARViewWithHorizonUpdate: the view will dynamically rotate with the device
 
 default: (0,0)
 */
- (void)setARViewMode:(ARViewMode)theMode;




@end
