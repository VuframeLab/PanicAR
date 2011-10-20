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
#import "ARMarker.h"
#import "ARControllerDelegate.h"

@class ARMarker;
@class ARTexture;

typedef enum {
    ARViewFixed = 0,
    ARViewDrag = 1,
    ARViewHeadingOnly = 2,
    ARViewWithTiltUpdate = 3,
    ARViewWithOrientationUpdate = 4,
    ARViewWithHorizonUpdate = 5,
} ARViewMode;

typedef enum {
    SensorNone = 0,
    SensorAccelerometer = 1,
    SensorDeviceMotion = 2,
} ARSensorMode;

#define RADAR_POSITION_Y -2
#define RADAR_BG_SIZE 100
#define RADAR_BLIP_SIZE 7
#define RADAR_FADE_BLIPS NO


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
    BOOL _userLocationValid;
    float _userLocationQuality;
    float _userLocationAccuracy;
    float _userLocationAge;
    
    // heading
    double _userNewestHeading;
    double _userNewestHeadingAccuracy;
    double _userCurrentHeading;
    double _userLastHeading;
    float _userCurrentHeadingAccuracy;
    BOOL _userHeadingValid;
    
    // altitude
    double _userAltitude;
    float _userAltitudeAccuracy;
    
    // accelerometer / gyro
    double _userDeviceAngleX;
    double _userDeviceAngleY;
    double _userDeviceAngleZ;
    UIAccelerationValue _deviceAccelX, _deviceAccelY, _deviceAccelZ;
    CMAttitude* _referenceAttitude;
    
    // updates
    NSTimer* _updateTimer;
#if DEBUG
    NSTimer* _consoleTimer;
    UITextView* _console;
#endif
    
    // orientation update
    BOOL _isLandscapeView;
    float _deviceUpAxis;
    float _deviceSideAxis;
    UIDeviceOrientation _arOrientation;
    
    // error handling
    int _lastErrorCode;
    NSError* _locationFailError;
    
    // config
    BOOL _objectsRespondToTouch;
    BOOL _radarEnabled;
    BOOL _radarAssetsLoaded;
    float _clipObjectFarLimit;
    float _clipObjectNearLimit;
    BOOL _isConsoleEnabled;
    ARViewMode _arViewMode;
    ARSensorMode _arSensorMode;
    UIColor* _arViewBackgroundTint;
    NSString* _apiKey;
    BOOL _continuousGPS;
    BOOL _doesViewOrientationUpdate;
    UIDeviceOrientation _defaultOrientation;
    
    // assets
    ARMarkerTemplate* _defaultMarkerTemplate;
    ARMesh* _defaultMarkerMesh;
    ARMesh* _radarMesh;
    ARTexture* _radarDotTexture;
    ARTexture* _radarBGTexture;
}


@property (nonatomic, assign) id<ARControllerDelegate> delegate;
@property (nonatomic, readonly, assign) float osVersion;
@property (nonatomic, readonly, assign) float contentScale;

@property (nonatomic, readonly, retain) NSMutableArray *arObjects;
@property (nonatomic, assign) BOOL objectsNeedSorting;

@property (nonatomic, readonly, retain) CLLocationManager *locationManager;
@property (nonatomic, readonly, retain) CMMotionManager *motionManager;
@property (nonatomic, retain) UITextView *console;

@property (nonatomic, readonly, assign) int userSignalQuality;
@property (nonatomic, readonly, assign, getter=isUserLocationValid) BOOL userLocationValid;
@property (nonatomic, readonly, retain) CLLocation *userLocation;
@property (nonatomic, readonly, assign) float userLocationQuality;
@property (nonatomic, readonly, assign) float userLocationAccuracy;
@property (nonatomic, readonly, assign) float userLocationAge;
@property (nonatomic, readonly, assign) double userNewestHeading;
@property (nonatomic, readonly, assign) double userNewestHeadingAccuracy;
@property (nonatomic, readonly, assign) double userCurrentHeading;
@property (nonatomic, readonly, assign) double userLastHeading;
@property (nonatomic, readonly, assign) float userCurrentHeadingAccuracy;
@property (nonatomic, readonly, assign, getter=isUserHeadingValid) BOOL userHeadingValid;
@property (nonatomic, readonly, assign) double userAltitude;
@property (nonatomic, readonly, assign) float userAltitudeAccuracy;
@property (nonatomic, readonly, assign) double userDeviceAngleX;
@property (nonatomic, readonly, assign) double userDeviceAngleY;
@property (nonatomic, readonly, assign) double userDeviceAngleZ;

@property (nonatomic, assign) int lastErrorCode;
@property (nonatomic, readonly, assign) BOOL isLandscapeView;
@property (nonatomic, readonly, assign) float deviceUpAxis;
@property (nonatomic, readonly, assign) float deviceSideAxis;
@property (nonatomic, readonly, assign) UIDeviceOrientation arOrientation;


#pragma mark - Updating

- (void)updateObjects:(NSTimer *)theTimer;
- (void)startUpdate;
- (void)stopUpdate;
- (BOOL)isUpdating;

#if DEBUG
- (void)updateConsole:(NSTimer *)theTimer;
- (void)startConsole;
- (void)stopConsole;
#endif


#pragma mark - Memory and Multitasking



/*! suspend ARController */
- (void)suspendToBackground;
/*! resume ARController */
- (void)resumeFromBackground;
/*! free as much memory as possible (mainly by releasing OGL memory occupied by ARMarker textures) */
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
 
 Returns YES if GPS, Compass and Camera are available
 i.e. if the hardware model is iPhone 3Gs or later
 
 will always return YES if running iOS 3.x: 
 cannot check for AR availability automatically, use an instance of CLLocationManager and 'headingAvailable' to check for compass availability
 */
+ (BOOL)deviceSupportsAR;

@end
