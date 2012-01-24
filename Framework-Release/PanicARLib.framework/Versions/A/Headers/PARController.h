//
//  PARController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#ifndef PanicARLib_ARController_h
#define PanicARLib_ARController_h

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CoreMotion.h>
#import "PARControllerDelegate.h"
#import "PARMath.h"

#define OBJECT_REFRESH_RATE 60
#define CONSOLE_REFRESH_RATE 2

@class PARViewController;

typedef enum {
    kARStatusNotDetermined = 0,
    kARStatusLocationUnavailble,
    kARStatusHeadingUnavailable,
    kARStatusSensorsUnavailable,
    kARStatusLocationRestricted,
    kARStatusLocationDenied,
    kARStatusReady,
} PARStatus;

typedef struct {
    float osVersion;
    float displayContentScale;
    BOOL hasRetinaDisplay;
    BOOL hasOS4;
    BOOL hasOS5;
    
    BOOL hasSensors;
    BOOL hasAccelerometer;
    BOOL hasGyroscope;
    BOOL hasAttitudeReference;
    
    CLAuthorizationStatus locationAuthStatus;
    BOOL hasCamera;
    BOOL hasGPS;
    BOOL allowsGPS;
    BOOL hasCompass;
    BOOL deniesGPS;
    BOOL restrictsGPS;
    
    BOOL useSemiAutoAttitude;
    BOOL useAutoAttitude;
} PARCapabilities;

/*!
 @class PARController
 @brief singleton class that manages PAR data used by PARViewController subclasses
 */
@interface PARController : NSObject <CLLocationManagerDelegate> {
    PARCapabilities _capabilities;
    PARStatus _status;
    BOOL _hasCapabilities;
    BOOL _started;
    
    // delegate object
    id<PARControllerDelegate> _delegate;
    
    // ar object collection
    NSMutableArray *_arObjects;
    BOOL _objectsNeedSorting;
    
    // sensors
    CLLocationManager* _locationManager;
    BOOL _locationIsUpdating;
    CMMotionManager* _motionManager;
    PARViewController* _activeViewController;
    
    // motion update
    NSTimer* _motionTimer;
    
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
    double _finalHeading;
    double _userLastHeading;
    float _userHeadingAccuracy;
    BOOL _userHeadingValid;
    int _stableHeadingCount;
    
    
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
    double _userDeviceAngleX;
    double _userDeviceAngleY;
    double _userDeviceAngleZ;
    BOOL _hasGravityX, _hasGravityY, _hasGravityZ;
    UIAccelerationValue _deviceAccelX, _deviceAccelY, _deviceAccelZ;
    CMAttitude* _referenceAttitude;
	PARMatrix4x4 _userDeviceAngle;
	PARMatrix4x4 _userDeviceHeading;
	PARVector3 _userDeviceGravity;
	PARVector3 _signedGravity;
    float _userDeviceRoll, _userDeviceTilt;
    
    // updates
    NSTimer* _updateTimer;
#if DEBUG
    NSTimer* _consoleTimer;
    UITextView* _console;
#endif
    
    BOOL _frozen;
    
    // orientation update
    BOOL _isLandscapeView;
    float _viewOrientationAngle;
    float _deviceUpAxis;
    float _deviceSideAxis;
    UIInterfaceOrientation _arOrientation;
    UIInterfaceOrientation _arGravityOrientation;
    BOOL _orientationUpdateRunning;
    BOOL _orientationSetup;
    
    // error handling
    int lastErrorCode;
    NSError* _locationFailError;
    
    // config
    float _clipObjectFarLimit;
    float _clipObjectNearLimit;
    BOOL _isConsoleEnabled;
    NSString* _apiKey;
    BOOL _hasValidApiKey;
    BOOL _continuousGPS;
    BOOL _doesViewOrientationUpdate;
    UIInterfaceOrientation _defaultOrientation;
    BOOL _enableErrorMessages;
}

#ifndef RELEASE // allow to set capabilities in source code mode
-(void) setCapabilities:(PARCapabilities)capabilities;
#endif
@property (nonatomic, readonly, assign) PARCapabilities capabilities;
@property (nonatomic, readonly, assign) BOOL isStarted;
@property (nonatomic, assign) id<PARControllerDelegate> delegate;

@property (nonatomic, readonly, retain) NSMutableArray *arObjects;
@property (nonatomic, assign) BOOL objectsNeedSorting;

@property (nonatomic, readonly, retain) CLLocationManager *locationManager;
@property (nonatomic, readonly, retain, getter=motionManager) CMMotionManager *motionManager;
@property (assign) PARViewController *activeViewController;
@property (nonatomic, retain) UITextView *console;

@property (nonatomic, readonly, assign) int userSignalQuality;
@property (nonatomic, readonly, assign, getter=isUserLocationValid) BOOL userLocationValid;
@property (nonatomic, readonly, retain) CLLocation *userLocation;
@property (nonatomic, readonly, assign) double userLocationX;
@property (nonatomic, readonly, assign) double userLocationY;
@property (nonatomic, readonly, assign) double userLocationZ;
@property (nonatomic, readonly, assign) float userLocationQuality;
@property (nonatomic, readonly, assign) float userLocationAccuracy;
@property (nonatomic, readonly, assign) float userLocationAge;
/*! @property heading (retrieved from compass) */
@property (nonatomic, readonly, assign) double heading;
@property (nonatomic, readonly, assign) double userLastHeading;
@property (nonatomic, readonly, assign) float userHeadingAccuracy;
@property (nonatomic, readonly, assign, getter=isUserHeadingValid) BOOL userHeadingValid;
@property (nonatomic, readonly, assign) double userAltitude;
@property (nonatomic, readonly, assign) float userAltitudeAccuracy;
@property (nonatomic, readonly, assign) double userDeviceAngleX;
@property (nonatomic, readonly, assign) double userDeviceAngleY;
@property (nonatomic, readonly, assign) double userDeviceAngleZ;
@property (nonatomic, readonly, assign) float userDeviceRoll;
- (PARMatrix4x4*)userDeviceAngle;
- (PARVector3*)userDeviceGravity;

@property (nonatomic, assign) int lastErrorCode;
@property (nonatomic, readonly, assign) BOOL isLandscapeView;
@property (nonatomic, readonly, assign) float viewOrientationAngle;
@property (nonatomic, readonly, assign) float deviceUpAxis;
@property (nonatomic, readonly, assign) float deviceSideAxis;
@property (nonatomic, readonly, assign) UIInterfaceOrientation arOrientation;
@property (nonatomic, readonly, assign) UIInterfaceOrientation arGravityOrientation;


#pragma mark - Api Key
- (void)setApiKey:(NSString *)theKey;
- (BOOL) hasValidApiKey;


#pragma mark - Updating
/*! will be called in PARViewController:viewDidAppear */
- (void)start;
/*! will be called in PARViewController:viewWillDisappear */
- (void)stop;
- (void)updateObjects:(NSTimer *)theTimer;
- (void)startObjectUpdate;
- (void)stopObjectUpdate;
- (BOOL) isUpdatingObjects;
#if DEBUG
- (void)updateConsole:(NSTimer *)theTimer;
- (void)startConsole;
- (void)stopConsole;
#endif

- (void)freeze;
- (void)unfreeze;
- (BOOL)isFrozen;


#pragma mark - Memory and Multitasking
/*! suspend PARController */
- (void)suspendToBackground;
/*! resume PARController */
- (void)resumeFromBackground;
/*! free as much memory as possible (mainly by releasing OGL memory occupied by PARPoiLabel textures) */
- (void)freeMemory;


#pragma mark - Utils
- (void)failWithErrorCodeImmediately:(int)code;
- (void)failWithErrorCodeDelayed:(int)code;



#pragma mark - Capabilities
- (void)getCapabilities;
- (void)updateCapabilities;
- (PARStatus)getStatus;
- (BOOL)isReady;

#pragma mark - Class Methods
/*! shared PARController */
+ (PARController *)sharedARController;


/*! checks if the device supports Augmented Reality functionality
 @return YES if PAR functionality is supported by the device's sensors 
 @remarks returns also YES on devices without a camera */
+ (BOOL)deviceSupportsAR;
+ (BOOL)deviceSupportsAR:(BOOL)showErrors;

+ (void)showAlert:(NSString *)title withMessage:(NSString *)message andDismissButton:(NSString *)dismissButtonTitle;

@end

#endif
