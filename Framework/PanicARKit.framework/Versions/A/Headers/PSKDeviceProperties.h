//
//  PSKDeviceProperties.h
//  PanicSensorKit
//
//  Created by Andreas Zeitler on 12.09.12.
//  Copyright (c) 2012 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>

// Device Type definitions
static const int kDeviceUnknown = -1;
static const int kDeviceSimulator = 0;
static const int kDeviceiPhone = 100;
static const int kDeviceiPhone3G = 110;
static const int kDeviceiPhone3Gs = 120;
static const int kDeviceiPhone4 = 130;
static const int kDeviceiPhone4s = 1040;
static const int kDeviceiPhone5 = 1050;
static const int kDeviceiPhone5c = 1051;
static const int kDeviceiPhone5s = 1052;
static const int kDeviceiPad = 150;
static const int kDeviceiPad2 = 1060;
static const int kDeviceiPadMini1 = 1061;
static const int kDeviceiPad3 = 1070;
static const int kDeviceiPad4 = 1080;
static const int kDeviceiPadAir = 1090;
static const int kDeviceiPadMini2 = 1091;
static const int kDeviceiPod = 180;
static const int kDeviceiPod4 = 190;
static const int kDeviceiPod5 = 1200;
static const int kDeviceFastGeneration = 1000;
static const int kDeviceUnkownNewDevice = 1200;

#define PSK_MINIMUM_OS_FOR_ADVANCED_SENSORS 5.0

// Statuses for the GPS
typedef enum {
    kPSKGPSAvailabilityStatusUnknown = 0,
    kPSKGPSAvailabilityStatusAvailable,
    kPSKGPSAvailabilityStatusUnavailable,
} PSKGPSAvailabilityStatus;




/*!  PSKDeviceProperties
 abstraction layer between doPanic Frameworks and iOS
 keeps track of all device and os information 
 allows for simulation of different devices on the same hardware */
@interface PSKDeviceProperties : NSObject {

 
    NSString *_deviceName;
    
    int _deviceType;
    BOOL _isPad, _isPod, _isPhone;
    BOOL _singleCoreDevice;
    
    float _osVersion;
    float _displayContentScale;
    
    BOOL _hasBackFacingCamera;
    BOOL _hasFrontFacingCamera;
    CGSize _backFacingCameraFOVs;
    CGSize _deviceMeasurements;
    CGPoint _deviceCameraOffsetFromTopRightBorder;
    CGPoint _deviceCameraOffsetFromCenter;
    
    PSKGPSAvailabilityStatus _gpsStatus;
    BOOL _hasCompass;
    BOOL _hasAccelerometer;
    BOOL _hasGyroscope;
}

+ (BOOL)simulateGPSForAllDevices;
+ (void)setSimulateGPSForAllDevices:(BOOL)doSimulateGPSForAllDevices;

/*! shared device properties instance */
+ (PSKDeviceProperties*)sharedDeviceProperties;

/*! initializes an EMPTY PSKDeviceProperties object
 @warning this is not usable */
- (id)init;
/*! get a PSKDeviceProperties object based on the properties of the actual device and the installed OS */
- (id)initFromDevice;

/*! shortcut method to get an PSKPropertiesObject based on the actual device @see initFromDevice */
+ (PSKDeviceProperties *)propertiesFromDevice;

/*!  device generation name defined by Apple
 @remarks e.g. iPhone5,1 or iPad2,3 */
- (NSString *)deviceName;

/*!  integer constant identifying the device type and generation internally */
- (int)deviceType;
/*!  YES if the device is an iPod */
- (BOOL)isPod;
/*!  YES if the device is an iPad */
- (BOOL)isPad;
/*!  YES if the device is an iPhone */
- (BOOL)isPhone;
/*!  YES if the device has a single-core CPU
 @deprecated use isSingleCoreDevice instead */
- (BOOL)isSlowDevice __attribute__((deprecated));
/*!  YES if the device has a single-core CPU */
- (BOOL)isSingleCoreDevice;

/*!  the installed OS version 
 @remarks only major and minor revision, e.g. 5.1 or 6.0 */
- (float)osVersion;
/*!  YES if the device runs at least iOS 4 */
- (BOOL)hasOS4;
/*!  YES if the device runs at least iOS 4.3 */
- (BOOL)hasOS43;
/*!  YES if the device runs at least iOS 5 */
- (BOOL)hasOS5;
/*!  YES if the device runs at least iOS 6 */
- (BOOL)hasOS6;

/*!  YES if the device runs at least iOS 7 */
- (BOOL)hasOS7;

/*!  YES if the device runs at least iOS 8 */
- (BOOL)hasOS8;

/*!  the displayContentScale of this device, 2.0f. for retina displays */
- (float)displayContentScale;
/*!  YES if this device has a retina display (@see displayContentScale) */
- (BOOL)hasRetinaScreen;

/*!  YES if the device has a back facing camera */
- (BOOL)hasBackFacingCamera;
/*!  YES if the device has a front facing camera */
- (BOOL)hasFrontFacingCamera;

- (CGSize)backFacingCameraFovs;
- (float)backFacingCameraFovPortrait;
- (float)backFacingCameraFovLandscape;
- (CGPoint)deviceCameraOffsetFromCenter;

/*!  is a real GPS sensor available on the current device
 @return only returns YES if it is absolutely sure that GPS is available (not only location services using Cell/WiFi positioning */
- (BOOL)hasGPSSensor;
/*!  availability of real GPS sensor
 @return PSKGSPAvailabilityStatus */
- (PSKGPSAvailabilityStatus)gpsAvailabilityStatus;
/*!  does device have a compass
 @remarks magnetometer = compass */
- (BOOL)hasCompass;
/*!  does device have a accelerometer
 @remarks YES for almost all devices */
- (BOOL)hasAccelerometer;
/*!  does device have a gyroscope */
- (BOOL)hasGyroscope;

/*!  device supports location services
 @remarks returns YES for almost all devices as most of them support Wifi/Cell positioning */
- (BOOL) supportsLocationServices;

/*!  device supports location-based AR
 has:
 - camera
 - compass
 - gyro
 - advanced sensor fusion
 - iOS 5+
 @return YES if location-based AR is supported
 */
- (BOOL) supportsLocationAR;
/*!  can device support visual AR features using camera processing
 @return YES if device is fast and has a back facing camera */
- (BOOL) supportsVisualAR;

@end
