//
//  ARController+Sensors.h
//  PanicAR Framework (PanicARLib.framework)
//
//  Created by Andreas Zeitler on 11.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#define REFRESH_RATE_COREMOTION 60
#define REFRESH_RATE_ACCELEROMETER_ACTIVE 30
#define REFRESH_RATE_ACCELEROMETER_IDLE 10

/*!
 @name Sensors
 */

@interface ARController (Sensors)

- (void)setupSensors;
- (void)setupMotionSensors;
- (void)setupLocationSensor;

/*! 
 manually start location service update, only needed if stopped before, @ref stopLocationServices 
 */
- (BOOL)startLocationServicesIfNeccessary;
/*! 
 manually stop location service update 
 */
- (void)stopLocationServices:(BOOL)force;

- (void)triggerLocationUpdate;
- (void)updateSignalQuality;

- (void)startMotionUpdate;
- (void)stopMotionUpdate;
- (BOOL)isMotionUpdateRunning;
- (void)motionUpdate:(NSTimer *)theTimer;


/*! 
 @brief checks if location services are available/allowed for the device/user
 
 @remarks only checks if location services are turned on and the app is authorized to use them
 @remarks will not take into account if Airplane Mode is turned on
 
 @remarks use deviceSupportsAR to check if device supports camera and location services in general
 
 @return YES if location services are available to app
 
 @return will always return YES if running iOS 3.x:
 @remarks ARController.locationServicesAvailable: cannot check for availability on iOS 3.x, check manually for locationManager locationServicesAvailable
 */
+ (BOOL)locationServicesAvailable;
/*! 
 @brief checks if location services are available/allowed for the device/user
 @param raiseError: if YES a error will be dispatched to the delegate using arDidReceiveError
 @param delayError: if YES a error will be dispatched to the delegate the next time the ARView becomes visible
 
 @remarks only checks if location services are turned on and the app is authorized to use them
 @remarks will not take into account if Airplane Mode is turned on
 @remarks use deviceSupportsAR to check if device supports camera and location services in general
 
 @return YES if location services are available to app
 
 @remarks will always return YES if running iOS 3.x:
 @remarks ARController.locationServicesAvailable: cannot check for availability on iOS 3.x, check manually for locationManager locationServicesAvailable
 */
+ (BOOL)locationServicesAvailable:(BOOL)raiseError delayError:(BOOL)delayError;


/*!
 @brief calculates the direction towards a location, heads-up line is the north pole at 0 degrees 
 @remarks does not take into account the earth's curve and therefore will grow more inaccurate the farther the locations are apart 
 */
+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

/*!
 @brief show default error message dialogs
 @remarks localizable
 */
+ (void)showDefaultErrorMessage:(int)forErrorCode;

@end
