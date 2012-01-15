//
//  ARController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CoreMotion.h>
#import "ARPoiLabel.h"
#import "ARControllerDelegate.h"
#import "ARViewController.h"

#define OBJECT_REFRESH_RATE 60
#define CONSOLE_REFRESH_RATE 2

#define NUMBER_OF_STACKINGSECTORS 36 
#define NUMBER_OF_SLOTS_PER_STACKINGSECTOR 100
#define STACKINGSECTOR_WIDTH_IN_DEGREES()(360.0/NUMBER_OF_STACKINGSECTORS)
#define ARPoiLabel_DEFAULT_SIZE_IPHONE 50
#define ARPoiLabel_DEFAULT_SIZE_IPAD 25
#define DISABLE_AT_ANGLE_DEVIATION 50

#define ARPoiLabel_DEFAULT_HEIGHT_FOR_STACKING 1.6
#define ARPoiLabel_DEFAULT_BASELINE_Y -2

@class ARPoiLabel;
@class ARTexture;

typedef enum {
    ARViewFixed = 0,
    ARViewDrag = 1,
    ARViewHeadingOnly = 2,
    ARViewWithTiltUpdate = 3,
    ARViewWithOrientationUpdate = 4,
    ARViewWithHorizonUpdate = 5,
} ARViewMode;

/*!
 @class ARController
 @brief singleton class that manages AR data used by ARViewController subclasses
 */
@interface ARController : NSObject <CLLocationManagerDelegate> {
@private
    // delegate object
    id<ARControllerDelegate> _delegate;
    
    // system info
    float _contentScale;
    float _osVersion;
    
    // ar object collection
    NSMutableArray *_arObjects;
    
    // object sorting
    BOOL _objectStackingSlots[NUMBER_OF_STACKINGSECTORS][NUMBER_OF_SLOTS_PER_STACKINGSECTOR];
    int _objectsInStackingSector[NUMBER_OF_STACKINGSECTORS];
    BOOL _objectsNeedSorting;
    
    // sensors
    CLLocationManager* _locationManager;
    CMMotionManager* _motionManager;
    ARViewController* _activeViewController;
    
    // motion update
    NSTimer* _motionTimer;
    
    // filtering
    float _motionFreq;
    double _motionDT;
    double _motionRC;
    double _motionFilterConstant;
    
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
    double _userLastHeading;
    float _userHeadingAccuracy;
    BOOL _userHeadingValid;
    
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
	ARMatrix4x4 _userDeviceAngle;
	ARVector3 _userDeviceGravity;
    BOOL _useGyroForMotion;
    BOOL _useGyroForMotion5;
    float _userDeviceRoll;
    
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
    UIDeviceOrientation _arOrientation;
    
    // error handling
    int lastErrorCode;
    NSError* _locationFailError;
    
    // config
    float _clipObjectFarLimit;
    float _clipObjectNearLimit;
    BOOL _isConsoleEnabled;
    ARViewMode _arViewMode;
    UIColor* _arViewBackgroundTint;
    NSString* _apiKey;
    BOOL _hasValidApiKey;
    BOOL _continuousGPS;
    BOOL _doesViewOrientationUpdate;
    UIDeviceOrientation _defaultOrientation;
    BOOL _enableErrorMessages;
}


@property (nonatomic, assign) id<ARControllerDelegate> delegate;
@property (nonatomic, readonly, assign) float osVersion;
@property (nonatomic, readonly, assign) float contentScale;

@property (nonatomic, readonly, retain) NSMutableArray *arObjects;
@property (nonatomic, assign) BOOL objectsNeedSorting;

@property (nonatomic, readonly, retain) CLLocationManager *locationManager;
@property (nonatomic, readonly, retain) CMMotionManager *motionManager;
@property (assign) ARViewController *activeViewController;
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
@property (nonatomic, readonly, assign) double userHeading;
@property (nonatomic, readonly, assign) double userLastHeading;
@property (nonatomic, readonly, assign) float userHeadingAccuracy;
@property (nonatomic, readonly, assign, getter=isUserHeadingValid) BOOL userHeadingValid;
@property (nonatomic, readonly, assign) double userAltitude;
@property (nonatomic, readonly, assign) float userAltitudeAccuracy;
@property (nonatomic, readonly, assign) double userDeviceAngleX;
@property (nonatomic, readonly, assign) double userDeviceAngleY;
@property (nonatomic, readonly, assign) double userDeviceAngleZ;
@property (nonatomic, readonly, assign) float userDeviceRoll;
- (ARMatrix4x4*)userDeviceAngle;
- (ARVector3*)userDeviceGravity;

@property (nonatomic, assign) int lastErrorCode;
@property (nonatomic, readonly, assign) BOOL isLandscapeView;
@property (nonatomic, readonly, assign) float viewOrientationAngle;
@property (nonatomic, readonly, assign) float deviceUpAxis;
@property (nonatomic, readonly, assign) float deviceSideAxis;
@property (nonatomic, readonly, assign) UIDeviceOrientation arOrientation;


#pragma mark - Api Key
- (void)setApiKey:(NSString *)theKey;
- (BOOL) hasValidApiKey;


#pragma mark - Updating
- (void)start;
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
/*! suspend ARController */
- (void)suspendToBackground;
/*! resume ARController */
- (void)resumeFromBackground;
/*! free as much memory as possible (mainly by releasing OGL memory occupied by ARPoiLabel textures) */
- (void)freeMemory;


#pragma mark - Utils
- (void)failWithErrorCodeImmediately:(int)code;
- (void)failWithErrorCodeDelayed:(int)code;

#pragma mark - Viewport
- (void)deviceOrientationChanged:(NSNotification *)notification;
- (void)setViewOrientation;
- (void)delayedLocationFail;

#pragma mark - Class Methods

/*!
 shared ARController
 */
+ (ARController *)sharedARController;


/*! 
 checks if the device supports Augmented Reality functionality
 
 @return YES if GPS, Compass and Camera are available
 i.e. if the hardware model is iPhone 3Gs or later
 
 will always return YES if running iOS 3.x: 
 cannot check for AR availability automatically, use an instance of CLLocationManager and 'headingAvailable' to check for compass availability
 */
+ (BOOL)deviceSupportsAR;

@end
