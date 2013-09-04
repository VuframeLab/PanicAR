//
//  PSKSensorDelegate.h
//  PanicSensorKit
//
//  Created by Andreas Zeitler on 29.02.12.
//  Copyright (c) 2012 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/*! status of the PSKSensorManager update routine
 see also: @ref start @ref stop */
typedef enum {
    PSKSensorManagerUnavailable = 0,
    PSKSensorManagerIdle,
    PSKSensorManagerRestricted,
    PSKSensorManagerDenied,
    PSKSensorManagerRunning
} PSKSensorManagerStatus;

typedef NS_OPTIONS(NSUInteger, PSKSensorManagerUpdateMode) {
    PSKSensorManagerUpdateNone              = 0,
    PSKSensorManagerUpdateLocation          = 1 << 0,
    PSKSensorManagerUpdateHeading           = 1 << 1,
    PSKSensorManagerUpdateMotion            = 1 << 2
};

// Statuses for the GPS
typedef enum {
    PSKSignalQualityBest = 0,
    PSKSignalQualityOkay,
    PSKSignalQualityMedium,
    PSKSignalQualityBad,
    PSKSignalQualityNotUsable,
} PSKSignalQuality;

/*! @protocol PSKSensorDelegate */
@protocol PSKSensorDelegate <NSObject>

/*! called when statis of PSKSensorManager changed
 @remarks use this to update UI 
 @param newStatus the new PSKSensorManagerStatus */
- (void)didChangeStatus:(PSKSensorManagerStatus)newStatus;

/*! called when an error was encountered
 @param code the error code */
- (void)didReceiveErrorCode:(int)code;

/*! called when status of PSKSensorManager.sensorUpdateMode changed
 @param newUpdateMode the new PSKSensorManagerUpdateMode
 @param oldUpdateMode the old PSKSensorManagerUpdateMode */
- (void)didChangeSensorUpdateMode:(PSKSensorManagerUpdateMode)newUpdateMode fromMode:(PSKSensorManagerUpdateMode)oldUpdateMode motionIncludesHeading:(BOOL)includeHeading;

/*! called when a location update was made */
- (void)didUpdateLocation:(CLLocation *)newLocation;

/*! called when a heading update was made */
- (void)didUpdateHeading:(CLHeading *)newHeading;

/*! called when the signal quality changed 
 @param newSignalQuality new signal quality*/
- (void)didChangeSignalQuality:(PSKSignalQuality)newSignalQuality;

/*! called when the device orientation changed 
 @param orientation the new device orientation */
- (void)didChangeDeviceOrientation:(UIDeviceOrientation)orientation;

/*! called when authorization status changed (location services enabled/disabled, etc.)
 @param status the new authorization status */
- (void)didChangeAuthorizationStatus:(CLAuthorizationStatus)status;

@end
