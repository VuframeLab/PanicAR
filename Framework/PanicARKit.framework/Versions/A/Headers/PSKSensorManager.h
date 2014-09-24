//
//  PSKSensorManager.h
//  PanicSensorKit
//
//  Created by Andreas Zeitler on 28.02.12.
//  copyright 2013 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#import "PSKMath.h"
#import "PSKSensorDelegate.h"

//#define AF_MODE AVCaptureFocusModeLocked
#define AF_MODE AVCaptureFocusModeContinuousAutoFocus



static const int kPSKErrorRestricted = 10024;
static const int kPSKErrorCompassCalibrationDisabled = 16770;
static const float kPSKHumanEyeHeight = 1.620;


@class PSKSensorManager;
@class PSKDeviceProperties;
@class PSKDeviceAttitude;
@protocol PSKSensorDelegate;


// Type definition to use a block as property, see http://stackoverflow.com/questions/3935574/can-i-use-objective-c-blocks-as-properties
typedef void (^PSKVoidBlock)();


/*!
 @class PSKSensorManager
 @abstract singleton class to handle all sensor input and act as an abstraction layer between doPanic Frameworks and OS sensor output
 */
@interface PSKSensorManager : NSObject <CLLocationManagerDelegate>

#pragma mark -
/*! shared sensor manager instance */
+ (PSKSensorManager *)sharedSensorManager;
/*! PSKSensorDelegate delegate object receiving updates from the PSKSensorManager */
@property (nonatomic, weak) id<PSKSensorDelegate> delegate;

/*! PSKDeviceProperties reflecting the properties of the currently active device */
@property (nonatomic, strong, readonly) PSKDeviceProperties *deviceProperties;

/*! CLLocationManager instance */
@property (nonatomic, strong, readonly) CLLocationManager *locationManager;

/*! CMMotionManager instance */
@property (nonatomic, strong, readonly) CMMotionManager *motionManager;

/*! PSKDeviceAttitude instance that reflects the sensor output from the device */
@property (nonatomic, strong, readonly) PSKDeviceAttitude *deviceAttitude;

/*! status - reflects the sensor availability */
@property (nonatomic, assign, readonly) PSKSensorManagerStatus status;


/*! number of location updates */
@property (nonatomic, assign, readonly) int numberOfLocationUpdates;

/*! block that is run when manager resumed */
@property (nonatomic, copy, readonly) PSKVoidBlock willSuspendEvent;

/*! block that is run before manager will suspend */
@property (nonatomic, copy, readonly) PSKVoidBlock didResumeEvent;

- (void)setDidResumeEvent:(PSKVoidBlock)didResumeEvent;
- (void)setWillSuspendEvent:(PSKVoidBlock)willSuspendEvent;


/*! freeze the motion data as is */
@property (nonatomic, assign) BOOL freezeMotion;

/*! freeze the motion data as is */
@property (nonatomic, assign) BOOL freezeLocationAndHeading;

/*! use the fake location */
@property (nonatomic, assign) BOOL useFakeLocation;

/*! the fake location to use */
@property (nonatomic, strong) CLLocation *fakeLocation;

/*! by default PanicAR requires GPS to run
 set this to @ref YES to enable Wifi only positioning */
@property (nonatomic, assign) BOOL allowWifiOnlyPositioning;

/*! @property if YES then @ref CLLocationManager setHeadingOrientation is called when the device orientation changes */
@property (nonatomic, assign) BOOL respectOrientationForHeading;

#pragma mark - setup, start, stop
/*! @property YES if location should be updated 
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign,getter = shouldUpdateLocation, setter = setShouldUpdateLocation:) BOOL shouldUpdateLocation;

/*! @property YES if heading should be updated
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign,getter = shouldUpdateHeading, setter = setShouldUpdateHeading:) BOOL shouldUpdateHeading;

/*! @property YES if heading should be updated
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign,getter = shouldUpdateMotion, setter = setShouldUpdateMotion:) BOOL shouldUpdateMotion;

/*! @property set the CMAttitudeReferenceFrame that should be used for the motion update
 @remarks only change this if you know what your doing and when you want to use @ref start instead of @ref startForLocationBasedPoiAR */
@property (nonatomic,assign) CMAttitudeReferenceFrame motionRefrenceFrame;

/*! @property sensorUpdateMode
    @abstract set the components for which updates should be performed see @ref PSKSensorManagerUpdateMode */
@property (nonatomic,assign) PSKSensorManagerUpdateMode sensorUpdateMode;

/*! @return YES if heading is update by the CMMotionManager */
- (BOOL)motionUpdateIncludesHeading;

/*! shortcut method to set @ref motionReferenceFrame
 will use CMAttitudeReferenceFrameXArbitraryCorrectedZVertical if NO, CMAttitudeReferenceFrameXTrueNorthZVertical if YES */
- (void)setUseCompassAsBaseline:(BOOL)useCompass;

/*! starts the sensor update with custom settings
 @return YES if all routines could be started successfully, NO if an error occured, check @ref status in that case to get details on the error */
- (BOOL)start;

/*! starts the sensor update for a standard Location-based AR application */
- (BOOL)startForLocationBasedPoiAR;

/*! stops the sensor update */
- (void)stop;

/*! @return wrapped call to [CLLocationManager authorizationStatus] */
- (CLAuthorizationStatus)locationAuthorizationStatus;
/*! @return check the localization Authorization and on iOS 8 request it when it's not available */
- (CLAuthorizationStatus)checkAndEnsureLocationAuthorization;
- (BOOL)isUpdatingLocation;
- (BOOL)isUpdatingHeading;
- (BOOL)isUpdatingMotion;
- (BOOL)isCompassCalibrationEnabled;

#pragma mark - helper methods
NSString* NSStringFromPSKSensorManagerStatus(PSKSensorManagerStatus status);
NSString* NSStringFromUIInterfaceOrientation(UIInterfaceOrientation orientation);
NSString* NSStringFromUIDeviceOrientation(UIDeviceOrientation orientation);
NSString* NSStringFromPSKSensorManagerUpdateMode(PSKSensorManagerUpdateMode sensorUpdateMode);
NSString* NSStringFromCMAttitudeReferenceFrame(CMAttitudeReferenceFrame attitudeReferenceFrame);
float PSKOrientationAngleFromUIInterfaceOrientation(UIInterfaceOrientation UIDeviceOrientation);
float PSKOrientationAngleFromUIDeviceOrientation(UIDeviceOrientation orientation);

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
