//
//  PARSensorManager.h
//  AR-Architect
//
//  Created by Andreas Zeitler on 28.02.12.
//  Copyright 2012 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#import "PARMath.h"
#import "PARSensorDelegate.h"
#import "PARCapabilities.h"

#define MOTION_REFRESH_RATE 30
#define MOTION_PROCESS_RATE 15
#define LOWPASS_FILTER 0.95
#define HUMAN_EYE_HEIGHT 1.620

@class PARController;
@class PARSensorManager;


//#define AF_MODE AVCaptureFocusModeLocked
#define AF_MODE AVCaptureFocusModeContinuousAutoFocus

// not needed
static const double kPARFOViPhoneHorizontal = 28.7;
static const double kPARFOViPhoneVertical = 42.3;

// calculated values -> confirmed
static const double kPARFOViPhone4Horizontal = 47.49898899;//47.5
static const double kPARFOViPhone4Vertical = 61.00390416;//60.8

// calculated values -> TODO confirm
#define IPHONE_4S_FOV_FACTOR 1.10
static const double kPARFOViPhone4sHorizontal = 43.63974349*IPHONE_4S_FOV_FACTOR;//43.2
static const double kPARFOViPhone4sVertical = 56.18943315*IPHONE_4S_FOV_FACTOR;//55.7

// calculated values -> confirmed
static const double kPARFOViPad2Horizontal = 33.34078154;//34.1
static const double kPARFOViPad2Vertical = 44.21384992;//44.5;

// calculated values -> confirmed
static const double kPARFOViPad3Horizontal = 43.00426677;//47.5
static const double kPARFOViPad3Vertical = 55.61808159;//60.8

void GetDeviceFOVs(double *hori, double *vert);

/*!
 @name Sensors
 */
@interface PARSensorManager : NSObject <CLLocationManagerDelegate> {
    // piped properties (from PARController)
    id<PARSensorDelegate> _delegate;
    BOOL _frozen;
    
    // capabilities
    PARCapabilities _capabilities;
    PARStatus _status;
    BOOL _hasCapabilities;
    
    double _cameraFovVertical, _cameraFovHorizontal;
    
    // configuration
    BOOL _continuousGPS;
    BOOL _updateHeadingFromLocationManager;
    BOOL _doesViewOrientationUpdate;
    UIInterfaceOrientation _defaultOrientation;
    BOOL _enableErrorMessages;
    
    // sensors
    CLLocationManager* _locationManager;
    BOOL _locationIsUpdating;
    CMMotionManager* _motionManager;
    NSTimer* _motionTimer;
    BOOL _isSetup;
    BOOL _useCompassAsBaseline;
    
    // sensor input
    int _userSignalQuality;
    int _gpsQuality;
    int _compassQuality;
    
    // location
    CLLocation* _userLocation;
    double _userLocationX;
    double _userLocationY;
    double _userLocationZ;
    BOOL _userLocationValid;
    float _userLocationQuality;
    float _userLocationAccuracy;
    float _userLocationAge;
    int _numberOfLocationUpdates;
    
    // heading
    double _userHeading;
    CLHeading* _userHeadingFromMagnetometer;
    double _userHeadingFromMotionRaw;
    double _userHeadingFromMotion;
    double _userLastHeading;
    float _userHeadingAccuracy;
    BOOL _userHeadingValid;
    int _stableHeadingCount;
    
    // gyro
    BOOL _gyroHeadingCalibrated;
    float _yawAtLastStableHeading;
    float _currentlyUsedYawOrigin;
    float _currentYaw;
    float _yawOffset;
    float _lastStableHeading;
    //float _yawSystemOffset;
    
    // altitude
    double _userAltitude;
    float _userAltitudeAccuracy;
    
    // accelerometer / gyro
    double _devicePitch;
    double _deviceRoll;
    double _deviceYaw;
    BOOL _hasGravityX, _hasGravityY, _hasGravityZ;
    UIAccelerationValue _deviceAccelX, _deviceAccelY, _deviceAccelZ;
    CMAttitude* _referenceAttitude;
	PARMatrix4x4 _userDeviceAngle;
	PARMatrix4x4 _userDeviceHeading;
	PARMatrix4x4 _userDeviceOrientation;
	PARMatrix4x4 _userDeviceOrientationOffset;
	PARVector3 _userDeviceGravity;
	PARVector3 _signedGravity;
    float _userDeviceRoll, _userDeviceTilt;
    
    // orientation update
    BOOL _isLandscapeView;
    float _viewOrientationAngle;
    float _deviceUpAxis;
    float _deviceSideAxis;
    UIInterfaceOrientation _arOrientation;
    UIInterfaceOrientation _arGravityOrientation;
    BOOL _orientationUpdateRunning;
    BOOL _orientationSetup;
    
    // errors
    int _lastErrorCode;
    NSError* _locationFailError;
    
@private
    
}

+(PARSensorManager*)sharedSensorManager;

#if PANICAR_FULL
@property (nonatomic, assign, readonly) id<PARSensorDelegate> delegate;
#else
@property (nonatomic, assign) id<PARSensorDelegate> delegate;
#endif
@property (nonatomic, assign, setter = setFrozen:, getter = isFrozen) BOOL isFrozen;


#ifndef RELEASE // allow to set capabilities in source code mode
-(void) setCapabilities:(PARCapabilities)capabilities;
#endif
@property (nonatomic, readonly, assign) PARCapabilities capabilities;

@property (nonatomic, readonly, assign) double cameraFovHorizontal;
@property (nonatomic, readonly, assign) double cameraFovVertical;



@property (nonatomic, readonly, retain) CLLocationManager *locationManager;
@property (nonatomic, readonly, retain, getter=motionManager) CMMotionManager *motionManager;

/*! use compass as baseline for gyroscope
 if NO: gyroscope does not adjust baseline drift -> use for VR applications */
@property (nonatomic, assign) BOOL useCompassAsBaseline;

/*! current average signal quality of all sensors (location and compass)
 ranges from -1 (not available), 0 (best) to 4 (worst) */
@property (nonatomic, readonly, assign) int userSignalQuality;

/*! is the user's location set? will return YES after the first location update */
@property (nonatomic, readonly, assign, getter=isUserLocationValid) BOOL userLocationValid;

/*! @property user location (retrieved from CLLocationManager) */
@property (nonatomic, readonly, retain) CLLocation *userLocation;

/*! @property user location x position in ECEF reference frame */
@property (nonatomic, readonly, assign) double userLocationX;

/*! @property user location Y position in ECEF reference frame */
@property (nonatomic, readonly, assign) double userLocationY;

/*! @property user location Z position in ECEF reference frame */
@property (nonatomic, readonly, assign) double userLocationZ;

/*! @property quality of the location signal (calculated based on accuracy and age) */
@property (nonatomic, readonly, assign) float userLocationQuality;

/*! @property accuracy of the location signal, measured in meters */
@property (nonatomic, readonly, assign) float userLocationAccuracy;

/*! @property age of the location signal (time passed in seconds since last update of location) */
@property (nonatomic, readonly, assign) float userLocationAge;

/*! @property heading (retrieved from compass) */
@property (nonatomic, readonly, assign) CLHeading *userHeadingFromMagnetometer;

@property (nonatomic, readonly, assign) double userHeadingFromMotion;
@property (nonatomic, readonly, assign) double userHeading;
@property (nonatomic, readonly, assign) double userLastHeading;
@property (nonatomic, readonly, assign) float userHeadingAccuracy;
@property (nonatomic, readonly, assign, getter=isUserHeadingValid) BOOL userHeadingValid;
@property (nonatomic, readonly, assign) double userAltitude;
@property (nonatomic, readonly, assign) float userAltitudeAccuracy;
@property (nonatomic, readonly, assign) double devicePitch;
@property (nonatomic, readonly, assign) double deviceRoll;
@property (nonatomic, readonly, assign) double deviceYaw;
@property (nonatomic, readonly, assign) float userDeviceRoll;

- (PARMatrix4x4*)userDeviceAngle;
- (PARMatrix4x4*)userDeviceOrientation;
- (PARVector3*)userDeviceGravity;

@property (nonatomic, readonly, assign) BOOL isLandscapeView;
@property (nonatomic, readonly, assign) float viewOrientationAngle;
@property (nonatomic, readonly, assign) float deviceUpAxis;
@property (nonatomic, readonly, assign) float deviceSideAxis;
@property (nonatomic, readonly, assign) UIInterfaceOrientation arOrientation;
@property (nonatomic, readonly, assign) UIInterfaceOrientation arGravityOrientation;

@property (nonatomic, assign) int lastErrorCode;

#pragma mark Base Functionality

- (void)retrieveCapabilities;
- (void)retrieveCapabilities:(BOOL)fromOS;
- (void)updateCapabilities;
- (PARStatus)getStatus;

/*! starts the sensor update for the AR */
- (void)start;

/*! starts location-only update 
 @warning only use when you need to run location updates while the PARViewController is hidden */
- (void)startLocationOnly;

/*! starts motion-only update 
 @warning only use when you want to update the device attitude to use outside PanicAR */
- (void)startMotionOnly;

/*! stops the sensor update */
- (void)stop;

/*! stops the motion update */
- (void)startMotionUpdate;

/*! stops the motion update */
- (void)stopMotionUpdate;

- (void)suspendToBackground;
- (void)resumeFromBackground;

- (void)setupSensors;
- (void)setDefaultConfig;
- (CMMotionManager*)motionManager;



#pragma mark - Configuration
/*! enable continuous gps
 @remarks use this if your app needs to retrieve the user's location outside the PAR functionality, this allows to use the locationManager the PARController has started to access location data; you don't need to do it a second time in your own code 
 @attention may drain battery */
- (void)enableContinuousGPS;
/*! disable continuous gps */
- (void)disableContinuousGPS;
/*! @return YES if location manager is not stopped when exiting the PAR view */
- (BOOL)isContinuousGPSEnabled;




/*! show alert box for any error that occurs (lost GPS signal, etc) */
- (void)enableErrorMessages;
/*! do not show alert box for errors */
- (void)disableErrorMessages;
- (BOOL)areErrorMessagesEnabled;


-(void)enableUpdateHeadingFromLocationManager;
-(void)disableUpdateHeadingFromLocationManager;
-(BOOL)updatesHeadingFromLocationManager;

- (void)disableOrientationUpdate;
- (void)enableOrientationUpdate;
- (void)disableOrientationUpdate;
- (BOOL)isOrientationUpdateEnabled;
- (UIInterfaceOrientation)defaultOrientation;
- (void)setDefaultOrientation:(UIInterfaceOrientation)theOrientation;

#pragma mark - Orientation Update
- (void)setViewOrientation:(UIInterfaceOrientation)orientation;
- (void)setViewOrientation;

#pragma mark - Motion
- (BOOL)isMotionUpdateRunning;



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

+ (NSString *)deviceType;

@end
