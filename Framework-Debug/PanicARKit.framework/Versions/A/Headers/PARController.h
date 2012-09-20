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
#import "PSKMath.h"
#import "PSKSensorDelegate.h"


// Statuses for PARController
typedef enum {
    kPARStatusNotDetermined = 0,
    kPARStatusUnavailable,
    kPARStatusRestricted,
    kPARStatusDenied,
    kPARStatusReady,
} PARAvailability;


@class PARViewController;
@class PSKSensorManager;
@class PSKDeviceAttitude;

/*!
 @class PARController
 @brief singleton class that manages PAR data used by PARViewController subclasses
 */
@interface PARController : NSObject <PSKSensorDelegate> {
    BOOL _started;
    
    PSKSensorManager *_sensorManager;
    PSKDeviceAttitude *_deviceAttitude;
    // piped properties (to PSKSensorManager)
    id<PSKSensorDelegate> _sensorDelegate;
    BOOL _frozen;
    
    // ar object collection
    NSMutableArray *_arObjects;
    BOOL _objectsNeedSorting;
    
    PARViewController* _activeViewController;
    
    // updates
    NSTimer* _updateTimer;
    BOOL _shouldUpdateObjects;
    
    // config
    float _clipObjectFarLimit;
    float _clipObjectNearLimit;
}

@property (nonatomic, assign) id<PARControllerDelegate> delegate;
@property (nonatomic, assign) id<PSKSensorDelegate> sensorDelegate;


@property (nonatomic, readonly, assign) BOOL isStarted;

@property (nonatomic, readonly, retain) NSMutableArray *arObjects;
@property (nonatomic, assign) BOOL objectsNeedSorting;
@property (assign) PARViewController *activeViewController;


- (PARAvailability)availability;

#pragma mark - Api Key
- (void)setApiKey:(NSString *)theKey;
- (BOOL)hasValidApiKey;


#pragma mark - Updating
/*! will be called in PARViewController:viewDidAppear */
- (void)start;
/*! will be called in PARViewController:viewWillDisappear */
- (void)stop;
- (void)updateObjects:(NSTimer *)theTimer;
- (void)startObjectUpdate;
- (void)stopObjectUpdate;
- (BOOL)isUpdatingObjects;


#pragma mark - Memory and Multitasking
/*! suspend PARController */
- (void)suspendToBackground;
/*! resume PARController */
- (void)resumeFromBackground;
/*! free as much memory as possible (mainly by releasing OGL memory occupied by PARPoiLabel textures) */
- (void)freeMemory;



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
