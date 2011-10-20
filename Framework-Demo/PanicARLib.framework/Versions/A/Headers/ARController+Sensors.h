//
//  ARController+Sensors.h
//  PanicAR Framework (PanicARLib.framework)
//
//  Created by Andreas Zeitler on 11.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#define REFRESH_RATE_MOTION 30
#define REFRESH_RATE_COREMOTION 30
#define REFRESH_RATE_ACCELEROMETER_ACTIVE 30
#define REFRESH_RATE_ACCELEROMETER_IDLE 10

@interface ARController (Sensors)

- (void)setupSensors;
- (void)setupMotionSensors;
- (void)setupLocationSensor;

/*! manually start location service update, only needed if stopped before, see: stopLocationServices */
- (BOOL)startLocationServicesIfNeccessary:(BOOL)force;
/*! manually stop location service update */
- (void)stopLocationServices:(BOOL)force;

- (void)processLocation:(CLLocation *)newLocation;
- (void)triggerLocationUpdate;


- (void)startMotionUpdate;
- (void)stopMotionUpdate;
- (BOOL)isMotionUpdateRunning;
- (void)putMotionUpdateToIdle;
- (void)motionUpdate:(NSTimer *)theTimer;

- (void)updateSignalQuality;

/*! 
 checks if location services are available/allowed for the device/user
 
 only checks if location services are turned on and the app is authorized to use them
 will not take into account if Airplane Mode is turned on
 
 use deviceSupportsAR to check if device supports camera and location services in general
 
 Returns YES if location services are available to app
 
 will always return YES if running iOS 3.x:
 ARController.locationServicesAvailable: cannot check for availability on iOS 3.x, check manually for locationManager locationServicesAvailable
 */
+ (BOOL)locationServicesAvailable;
/*! 
 checks if location services are available/allowed for the device/user
 @param raiseError: if YES a error will be dispatched to the delegate using arDidReceiveError
 @param delayError: if YES a error will be dispatched to the delegate the next time the ARView becomes visible
 
 only checks if location services are turned on and the app is authorized to use them
 will not take into account if Airplane Mode is turned on
 
 use deviceSupportsAR to check if device supports camera and location services in general
 
 Returns YES if location services are available to app
 
 will always return YES if running iOS 3.x:
 ARController.locationServicesAvailable: cannot check for availability on iOS 3.x, check manually for locationManager locationServicesAvailable
 */
+ (BOOL)locationServicesAvailable:(BOOL)raiseError delayError:(BOOL)delayError;


/*!
 calculates the direction towards a location, heads-up line isthe north
 
 pole at 0 degrees does not take into account the earth's curve and therefore 
 
 will grow more inaccurate the farther the locations are apart 
 */
+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

@end
