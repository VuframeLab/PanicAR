//
//  PARCapabilities.h
//  AR-Architect
//
//  Created by Andreas Zeitler on 29.02.12.
//  Copyright (c) 2012 doPanic GmbH. All rights reserved.
//

static const int kDeviceSimulator = 0;
static const int kDeviceiPhone = 10;
static const int kDeviceiPhone3G = 11;
static const int kDeviceiPhone3Gs = 12;
static const int kDeviceiPhone4 = 103;
static const int kDeviceiPhone4s = 104;
static const int kDeviceiPad = 15;
static const int kDeviceiPad2 = 106;
static const int kDeviceiPad3 = 107;
static const int kDeviceiPod = 18;
static const int kDeviceiPod4 = 109;
static const int kDeviceNewGeneration = 100;

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
    int deviceType;
    float osVersion;
    float displayContentScale;
    BOOL hasRetinaDisplay;
    BOOL hasOS4;
    BOOL hasOS43;
    BOOL hasOS5;
    
    BOOL isSlow;
    BOOL isPod, isPad, isPhone;
    
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
