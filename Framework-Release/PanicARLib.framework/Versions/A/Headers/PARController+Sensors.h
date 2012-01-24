//
//  PARController+Sensors.h
//  PanicAR Framework (PanicARLib.framework)
//
//  Created by Andreas Zeitler on 11.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#define MOTION_REFRESH_RATE 30
#define MOTION_PROCESS_RATE 15
#define LOWPASS_FILTER 0.95

/*!
 @name Sensors
 */

@interface PARController (Sensors)

- (void)setupSensors;
- (CMMotionManager*)motionManager;

#pragma mark - Orientation Update
- (void)setViewOrientation;

#pragma mark - Motion
- (void)setupMotionSensors;
- (void)startMotionUpdate;
- (void)stopMotionUpdate;
- (BOOL)isMotionUpdateRunning;

- (void)motionUpdateAutoAttitude:(NSTimer *)theTimer;

- (void)motionUpdateSemiAutoAttitude:(NSTimer *)theTimer;
- (void)calibrateHeading;

- (void)motionUpdateManualAttitude:(NSTimer *)theTimer;

- (void)processMotionUpdate;


#pragma mark - Location
- (void)setupLocationSensor;

/*! manually start location service update, only needed if stopped before, @ref stopLocationServices */
- (void)startLocationServices;
/*! manually stop location service update 
 @param forSuspendOrResume YES indicates that the method was called automatically on suspending the app */
- (void)stopLocationServices:(BOOL)forSuspendOrResume;

- (void)triggerLocationUpdate;
- (void)delayedLocationFail;
- (void)updateSignalQuality;


#pragma mark - Class Methods

/*! @brief calculates the direction towards a location, heads-up line is the north pole at 0 degrees 
 @remarks does not take into account the earth's curve and therefore will grow more inaccurate the farther the locations are apart 
 @param fromLocation location of center point
 @param towardsLocation location of look-at point */
+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

/*! @brief show default error message dialogs
 @param forErrorCode the error code for which a message needs to be displayed
 @remarks localizable */
+ (void)showDefaultErrorMessage:(int)forErrorCode;


/*! @brief checks if location services are available/allowed for the device/user
 @remarks only checks if location services are turned on and the app is authorized to use them
 @remarks will not take into account if Airplane Mode is turned on
 @remarks use deviceSupportsAR to check if device supports camera and location services in general
 @return YES if location services are available to app
 @return will always return YES if running iOS 3.x:
 @remarks PARController.locationServicesAvailable: cannot check for availability on iOS 3.x, check manually for locationManager locationServicesAvailable
 @deprecated use @ref deviceSupportsAR and @ref PARCapabilities instead */
+ (BOOL)locationServicesAvailable  __attribute__ ((deprecated));
/*! @brief checks if location services are available/allowed for the device/user
 @param raiseError if YES a error will be dispatched to the delegate using arDidReceiveError
 @param delayError if YES a error will be dispatched to the delegate the next time the PARView becomes visible
 @remarks only checks if location services are turned on and the app is authorized to use them
 @remarks will not take into account if Airplane Mode is turned on
 @remarks use deviceSupportsAR to check if device supports camera and location services in general
 @return YES if location services are available to app
 @remarks will always return YES if running iOS 3.x:
 @remarks PARController.locationServicesAvailable: cannot check for availability on iOS 3.x, check manually for locationManager locationServicesAvailable 
 @deprecated use @ref deviceSupportsAR and @ref PARCapabilities instead */
+ (BOOL)locationServicesAvailable:(BOOL)raiseError delayError:(BOOL)delayError  __attribute__ ((deprecated));

@end
