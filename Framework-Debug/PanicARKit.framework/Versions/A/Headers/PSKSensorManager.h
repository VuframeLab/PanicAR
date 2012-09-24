//
//  PSKSensorManager.h
//  PanicSensorKit
//
//  Created by Andreas Zeitler on 28.02.12.
//  Copyright 2012 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#import "PSKMath.h"

//#define AF_MODE AVCaptureFocusModeLocked
#define AF_MODE AVCaptureFocusModeContinuousAutoFocus

static const int kPSKErrorRestricted = 10024;

typedef enum {
    kPSKSensorManagerUnavailable = 0,
    kPSKSensorManagerIdle,
    kPSKSensorManagerRestricted,
    kPSKSensorManagerDenied,
    kPSKSensorManagerRunning,
    kPSKSensorManagerWarning,
    kPSKSensorManagerPaused,
} PSKSensorManagerStatus;




@class PSKSensorManager;
@class PSKDeviceProperties;
@class PSKDeviceAttitude;
@protocol PSKSensorDelegate;

/*!
  PSKSensorManager
 singleton class to handle all sensor input and act as an abstraction layer between doPanic Frameworks and OS sensor output
 */
@interface PSKSensorManager : NSObject <CLLocationManagerDelegate> {
    id<PSKSensorDelegate> __weak _delegate; // receives all events
    CMMotionManager* _motionManager; // CoreMotion interface
    CLLocationManager* _locationManager; // CoreLocation interface
    PSKDeviceProperties *_deviceProperties; // device properties abstraction layer
    PSKDeviceAttitude *_deviceAttitude;

    PSKSensorManagerStatus _status; // current status
    
    // setup, start, stop
    BOOL _shouldUpdateLocation; // should PSK start location updates using CLLocationManager
    BOOL _shouldUpdateHeading; // should PSK start heading updates using CLLocationManager
    BOOL _shouldUpdateMotion;
    CMAttitudeReferenceFrame _motionRefrenceFrame; // the reference frame the motionManager uses
    
    // runtime
    int _numberOfLocationUpdates;
}

#pragma mark -
/*! shared sensor manager instance */
+(PSKSensorManager*)sharedSensorManager;
/*! PSKSensorDelegate delegate object receiving updates from the PSKSensorManager */
@property (nonatomic, weak) id<PSKSensorDelegate> delegate;
/*! PSKDeviceProperties reflecting the properties of the currently active device */
- (PSKDeviceProperties *)deviceProperties;
/*! CLLocationManager instance */
- (CLLocationManager *)locationManager;
/*! CMMotionManager instance */
- (CMMotionManager *)motionManager;
/*! PSKDeviceAttitude instance that reflects the sensor output from the device */
- (PSKDeviceAttitude *)deviceAttitude;
/*! status - reflects the sensor availability */
- (PSKSensorManagerStatus)status;

#pragma mark - setup, start, stop
/*! @property YES if location should be updated 
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign) BOOL shouldUpdateLocation;
/*! @property YES if heading should be updated
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign) BOOL shouldUpdateHeading;
/*! @property YES if heading should be updated
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign) BOOL shouldUpdateMotion;
/*! @property set the CMAttitudeReferenceFrame that should be used for the motion update
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign) CMAttitudeReferenceFrame motionRefrenceFrame;
/*! @return YES if heading is update by the CMMotionManager */
- (BOOL)motionUpdateIncludesHeading;

/*! starts the sensor update with custom settings */
- (void)start;
/*! starts the sensor update for a standard Location-based AR application */
- (void)startForLocationBasedPoiAR;

/*! stops the sensor update */
- (void)stop;



#pragma mark - helper methods
NSString* NSStringFromUIInterfaceOrientation(UIInterfaceOrientation orientation);
NSString* NSStringFromUIDeviceOrientation(UIDeviceOrientation orientation);
/*! @brief calculates the direction towards a location, heads-up line is the north pole at 0 degrees 
 @remarks does not take into account the earth's curve and therefore will grow more inaccurate the farther the locations are apart 
 @param fromLocation location of center point
 @param towardsLocation location of look-at point */
+ (double)bearingTowardsLocation:(CLLocation *)fromLocation to:(CLLocation *)towardsLocation;

/*! @brief show default error message dialogs
 @param forErrorCode the error code for which a message needs to be displayed
 @remarks localizable */
+ (void)showDefaultErrorMessage:(int)forErrorCode;

@end
