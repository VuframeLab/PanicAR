//
//  ARController+Config.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 18.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <PanicARLib/PanicARLib.h>




@interface ARController (Config)

- (void)setDefaultConfig;

- (void)objectsRespondToTouch:(BOOL)state;
- (BOOL)doObjectsRespondToTouch;

- (void)enableRadar;
- (void)disableRadar;
- (BOOL)isRadarEnabled;

- (void)enableConsole;
- (void)disableConsole;
- (BOOL)isConsoleEnabled;

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

- (void)setAPIKey:(NSString *)theKey;
- (NSString *)APIKey;


#pragma mark - Sensor Mode
- (ARSensorMode) sensorMode;
/*! 
 CONFIGURATION: the sensor type used for determening the device orientation in 3d space
 @param theMode
 */
- (void)setSensorMode:(ARSensorMode)theMode;


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
