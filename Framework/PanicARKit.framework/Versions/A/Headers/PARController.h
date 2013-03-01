//
//  PARController.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 14.10.11.
//  copyright 2013 doPanic. All rights reserved.
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
typedef enum
{
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
 * PARController
 * @brief singleton class that manages PAR data used by PARViewController subclasses
 */
@interface PARController : NSObject <PSKSensorDelegate> {
	BOOL _objectsNeedSorting;
}

/*! PARControllerDelegate delegate object receiving updates from the PARController */
@property (nonatomic, assign) id<PARControllerDelegate> delegate;
/*! PSKSensorDelegate delegate object receiving updates from the PSKSensorManager */
@property (nonatomic, assign) id<PSKSensorDelegate> sensorDelegate;


/*! @return YES if PARController is running updates */
@property (nonatomic, readonly, assign, getter = isStarted) BOOL started;

/*! @return NSArray containing all PARObjectDelegate-objects in the PARController */
@property (nonatomic, readonly, strong) NSMutableArray *arObjects;
/*! internal use only */
@property (nonatomic, assign) BOOL objectsNeedSorting;

/*! status of PARController functionality */
- (PARAvailability)availability;

#pragma mark - Api Key
/*! @param theKey the api key to disable the watermarks */
- (void)setApiKey:(NSString *)theKey;
/*! @return YES if valid API key is set */
- (BOOL)hasValidApiKey;


#pragma mark - Updating
/*! will be called in PARViewController:viewDidAppear */
- (void)start;
/*! will be called in PARViewController:viewWillDisappear */
- (void)stop;
/*! @return YES if object update is running
 * @remarks internal use only */
- (BOOL)isUpdatingObjects;

#pragma mark - Memory and Multitasking
/*! suspend PARController
 * @remarks Call this from applicationDidEnterBackground in the delegate
 */
- (void)suspendToBackground;

/*! resume PARController
 * @remarks Call this from applicationWillEnterForeground in the delegate
 */
- (void)resumeFromBackground;
/*! free as much memory as possible (mainly by releasing OGL memory occupied by PARPoiLabel textures) */
- (void)freeMemory;



#pragma mark - Class Methods
/*! shared PARController */
+ (PARController *)sharedARController;
/*! @abstract the NSBundle holding all framework resources */
+ (NSBundle *)frameworkBundle;

/*! checks if the device supports Augmented Reality functionality
 * @return YES if AR functionality is supported by the device's sensors
 * @remarks Call this OR (BOOL)deviceSupportsAR:(BOOL)showErrors in applicationWillEnterForeground in the delegate 
 * to react to changes in the settings app */
+ (BOOL)deviceSupportsAR;

/*! checks if the device supports Augmented Reality functionality
 * @return YES if AR functionality is supported by the device's sensors
 * @param showErrors YES will rais UIAlertView's with default messages defined in PanicARKit.strings
 * @remarks Call this OR (BOOL)deviceSupportsAR in applicationWillEnterForeground in the delegate
 * to react to changes in the settings app */
+ (BOOL)deviceSupportsAR:(BOOL)showErrors;

/*! shortcut method to show an UIAlertView with the passed parameters
 * @param title title of the alert
 * @param message mesage of the alert
 * @param dismissButtonTitle button title of the alert */
+ (void)showAlert:(NSString *)title withMessage:(NSString *)message andDismissButton:(NSString *)dismissButtonTitle;

@end

#endif // ifndef PanicARLib_ARController_h
