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
#import "PARCapabilities.h"
#import "PARSensorDelegate.h"

#define OBJECT_REFRESH_RATE 60
#define CONSOLE_REFRESH_RATE 2

@class PARViewController;
@class PARSensorManager;

/*!
 @class PARController
 @brief singleton class that manages PAR data used by PARViewController subclasses
 */
@interface PARController : NSObject <PARSensorDelegate> {
    BOOL _started;
    
    PARSensorManager *_sensorManager;
    // piped properties (to PARSensorManager)
    id<PARSensorDelegate> _sensorDelegate;
    BOOL _frozen;
    PARStatus _status;
    
    // ar object collection
    NSMutableArray *_arObjects;
    BOOL _objectsNeedSorting;
    
    PARViewController* _activeViewController;
    
    // updates
    NSTimer* _updateTimer;
#if DEBUG
    NSTimer* _consoleTimer;
    UITextView* _console;
#endif
    
    
    // config
    float _clipObjectFarLimit;
    float _clipObjectNearLimit;
    BOOL _isConsoleEnabled;
}

@property (nonatomic, assign) id<PARControllerDelegate> delegate;
@property (nonatomic, assign, getter = isFrozen, setter = setFrozen:) BOOL isFrozen;
@property (nonatomic, readonly, assign) PARStatus status;

@property (nonatomic, readonly, assign) BOOL isStarted;

@property (nonatomic, readonly, retain) NSMutableArray *arObjects;
@property (nonatomic, assign) BOOL objectsNeedSorting;
@property (assign) PARViewController *activeViewController;
@property (nonatomic, retain) UITextView *console;



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


#pragma mark - Memory and Multitasking
/*! suspend PARController */
- (void)suspendToBackground;
/*! resume PARController */
- (void)resumeFromBackground;
/*! free as much memory as possible (mainly by releasing OGL memory occupied by PARPoiLabel textures) */
- (void)freeMemory;





#pragma mark - Capabilities
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
