//
//  PSKDeviceAttitude.h
//  PanicSensorKit
//
//  Created by Andreas Zeitler on 13.09.12.
//  Copyright (c) 2012 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PSKMath.h"
#import "PSKSensorDelegate.h"

NSString* NSStringFromPSKSignalQuality(PSKSignalQuality signalQuality);
BOOL PSKSignalQualityIsUsable(PSKSignalQuality signalQuality);
UIDeviceOrientation PSKGetUIDeviceOrientationFromGravity(float x, float y, float z);

/*!  stores all sensor information retrieved from the OS */
@interface PSKDeviceAttitude : NSObject {
    // location
    BOOL _hasLocation;
    CLLocation *_location;
    float _locationAge;
    PSK_PRECISION _locationLatitude;
    PSK_PRECISION _locationLongitude;
    PSK_PRECISION _locationAccuracy;
    PSK_PRECISION _locationAltitude;
    PSK_PRECISION _locationAltitudeAccuracy;
    NSDate *_locationTimestamp;
    // pulled values
    BOOL _needsToUpdateEcef;
    double _ecefCoordinatesX, _ecefCoordinatesY, _ecefCoordinatesZ;
    PSKVector3 _ecefCoordinates;
    
    // heading
    BOOL _hasHeading;
    float _headingAge;
    BOOL _hasUpdatedHeading;
    PSK_PRECISION _headingTrue;
    
    // Magnetic Heading is for legacy code only, do not use in new code
    PSK_PRECISION _headingMagnetic;
    
    PSK_PRECISION _headingAccuracy;
    NSDate *_headingTimestamp;
    
    // motion
    BOOL _hasAttitude;
    CLAuthorizationStatus _authorizationStatus;
    BOOL _hasUpdatedAttitude;
    PSKMatrix4x4 _attitudeMatrix;
    PSKVector3 _attitudeGravity, _attitudeSignedGravity;
    BOOL _attitudeHasGravityOnX, _attitudeHasGravityOnY, _attitudeHasGravityOnZ;
    double _attitudePitch, _attitudeRoll, _attitudeYaw;
    double _motionPitch, _motionRoll, _motionYaw;
    // pulled values
    BOOL _needsToUpdateAttitudeEulerAngles;
    PSKVector3 _attitudeEulerAngles;
    BOOL _needsToUpdateMotionEulerAngles;
    PSKVector3 _motionEulerAngles;
    PSK_PRECISION _attitudeHeading;
    PSK_PRECISION _attitudeTilting;
    PSKMatrix4x4 _headingMatrix;
    
    // signal quality
    PSKSignalQuality _signalQuality;
    PSKSignalQuality _locationSignalQuality;
    PSKSignalQuality _headingSignalQuality;
    
    // orientation
    UIDeviceOrientation _deviceOrientation;
    UIDeviceOrientation _previousDeviceOrientation;
    float _orientationSideAxis;
    float _orientationUpAxis;
    BOOL _orientationIsLandscape;
    float _deviceOffsetToPortraitAngle;
    PSKMatrix4x4 _deviceOffsetToPortraitMatrix;
}

/*! shared device attitude instance */
+ (PSKDeviceAttitude *)sharedDeviceAttitude;

// location
/*! hasLocation is a location available */
- (BOOL)hasLocation;
/*! @abstract authorization for location manager
 @brief wraps @ref [CLLocationManager authorizationStatus] and allows simulation using @ref PSKSimulator */
- (CLAuthorizationStatus)locationAuthorizationStatus;
/*! how old the location is in seconds */
- (float)locationAge;
/*! the CLLocation object retrieved during the last update
 @return nil if the location is invalid or the @ref locationCoordinate is 0,0 */
- (CLLocation*)location;
/*! the CLLocationCoordinate2D of the last retrieved location */
- (CLLocationCoordinate2D)locationCoordinate;
/*! user position's latitude */
- (PSK_PRECISION)locationLatitude;
/*! user position's longitude */
- (PSK_PRECISION)locationLongitude;
/*! user position's accuracy for latitude and longitude */
- (PSK_PRECISION)locationAccuracy;
/*! user position's altitude */
- (PSK_PRECISION)locationAltitude;
/*! user position's accuracy for altitude */
- (PSK_PRECISION)locationAltitudeAccuracy;
/*! time stamp of the last retrieved location */
- (NSDate *)locationTimestamp;
// pulled values
/*! Earth-centered, Earth-fixed coordinates */
- (PSKVector3 *)ecefCoordinates;

// heading
/*!  is heading information available */
- (BOOL)hasHeading;
/*!  age of the last heading information */
- (float)headingAge;
/*!  heading to true north pole */
- (PSK_PRECISION)heading;
/*!  heading to magnetic north pole - LEGACY CODE ONLY*/
- (PSK_PRECISION)magneticHeading;
/*!  accuracy of heading */
- (PSK_PRECISION)headingAccuracy;
/*!  time stamp of last heading update */
- (NSDate *)headingTimestamp;

// motion
/*!   */
- (BOOL)hasAttitude;
/*!   */
- (PSKMatrix4x4 *)attitudeMatrix;
/*!   */
- (PSKVector3 *)attitudeGravity;
/*! the pitch of the device calculated from gravity */
- (double)attitudePitch;
/*! the roll of the device calculated from gravity */
- (double)attitudeRoll;
/*! the yaw of the device calculated from magnetometer  */
- (double)attitudeYaw;
/*! the heading extracted from the CMMotion-based attitude  */
- (float)attitudeHeading;
/*! the tilting extracted from the CMMotion-based attitude  */
- (float)attitudeTilting;
/*! roll, pitch, yaw calculated manually and put into an PSKVector3  */
- (PSKVector3 *)attitudeEulerAngles;
/*! pitch component from the latest motion update */
- (double)motionPitch;
/*! roll component from the latest motion update */
- (double)motionRoll;
/*! yaw component from the latest motion update */
- (double)motionYaw;
/*! roll, pitch, yaw as returned by CMMotionManager  */
- (PSKVector3 *)motionEulerAngles;
/*!   */
- (PSKMatrix4x4 *)headingMatrix;

// signal quality
/*!   */
- (PSKSignalQuality)signalQuality;
- (PSKSignalQuality)locationSignalQuality;
- (PSKSignalQuality)headingSignalQuality;

// orientation
/*!   */
- (UIDeviceOrientation)deviceOrientation;
/*!   */
- (float)orientationSideAxis;
/*!   */
- (float)orientationUpAxis;
/*!   */
- (BOOL)orientationIsLandscape;


/*! @return string describing all heading parameters */
- (NSString *)descriptionForHeading;
/*! @return string describing all motion parameters */
- (NSString *)descriptionForMotion;

@end
