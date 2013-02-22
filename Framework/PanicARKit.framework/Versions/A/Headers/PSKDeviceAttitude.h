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

// Statuses for the GPS
typedef enum {
    PSKSignalQualityBest = 0,
    PSKSignalQualityOkay,
    PSKSignalQualityMedium,
    PSKSignalQualityBad,
    PSKSignalQualityNotUsable,
} PSKSignalQuality;
NSString* NSStringFromPSKSignalQuality(PSKSignalQuality signalQuality);

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
    PSK_PRECISION _heading;
    PSK_PRECISION _headingAccuracy;
    NSDate *_headingTimestamp;
    
    // motion
    BOOL _hasAttitude;
    BOOL _hasUpdatedAttitude;
    PSKMatrix4x4 _attitudeMatrix;
    PSKVector3 _attitudeGravity, _attitudeSignedGravity;
    BOOL _attitudeHasGravityOnX, _attitudeHasGravityOnY, _attitudeHasGravityOnZ;
    double _attitudePitch, _attitudeRoll, _attitudeYaw;
    // pulled values
    BOOL _needsToUpdateAttitudeEulerAngles;
    PSKVector3 _attitudeEulerAngles;
    
    // signal quality
    PSKSignalQuality _signalQuality;
    
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
/*!  hasLocation is a location available */
- (BOOL)hasLocation;
/*!  how old the location is in seconds */
- (float)locationAge;
/*!  the CLLocation object retrieved during the last update */
- (CLLocation*)location;
/*!  the CLLocationCoordinate2D of the last retrieved location */
- (CLLocationCoordinate2D)locationCoordinate;
/*!  user position's latitude */
- (PSK_PRECISION)locationLatitude;
/*!  user position's longitude */
- (PSK_PRECISION)locationLongitude;
/*!  user position's accuracy for latitude and longitude */
- (PSK_PRECISION)locationAccuracy;
/*!  user position's altitude */
- (PSK_PRECISION)locationAltitude;
/*!  user position's accuracy for altitude */
- (PSK_PRECISION)locationAltitudeAccuracy;
/*!  time stamp of the last retrieved location */
- (NSDate *)locationTimestamp;
// pulled values
/*!  Earth-centered, Earth-fixed coordinates */
- (PSKVector3 *)ecefCoordinates;

// heading
/*!  is heading information available */
- (BOOL)hasHeading;
/*!  age of the last heading information */
- (float)headingAge;
/*!  heading to true north pole */
- (PSK_PRECISION)heading;
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
/*!   */
- (double)attitudePitch;
/*!   */
- (double)attitudeRoll;
/*!   */
- (double)attitudeYaw;
/*!   */
- (PSKVector3 *)attitudeEulerAngles;

// signal quality
/*!   */
- (PSKSignalQuality)signalQuality;

// orientation
/*!   */
- (UIDeviceOrientation)deviceOrientation;
/*!   */
- (float)orientationSideAxis;
/*!   */
- (float)orientationUpAxis;
/*!   */
- (BOOL)orientationIsLandscape;

@end
