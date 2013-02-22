//
//  PSKDeviceProperties+Simulator.h
//  PanicSensorKit
//
//  Created by Andreas Zeitler on 12.09.12.
//  Copyright (c) 2012 doPanic. All rights reserved.
//

#import "PSKDeviceProperties.h"
#import "PSKSensorManager.h"

#define PSK_DEVICE_MIN_OS_PHONE_3G 3.2
#define PSK_DEVICE_MAX_OS_PHONE_3G 4.2
#define PSK_DEVICE_MIN_OS_PHONE_3GS 3.2
#define PSK_DEVICE_MIN_OS_PHONE_4 4.0
#define PSK_DEVICE_MIN_OS_PHONE_4S 5.0
#define PSK_DEVICE_MIN_OS_PHONE_5 6.0

#define PSK_DEVICE_MIN_OS_POD_4 4.1
#define PSK_DEVICE_MIN_OS_POD_5 6.0

#define PSK_DEVICE_MIN_OS_PAD_1 3.2
#define PSK_DEVICE_MAX_OS_PAD_1 5.1
#define PSK_DEVICE_MIN_OS_PAD_2 4.2
#define PSK_DEVICE_MIN_OS_PAD_MINI_1 6.0
#define PSK_DEVICE_MIN_OS_PAD_3 5.1
#define PSK_DEVICE_MIN_OS_PAD_4 6.0

#define PSK_SIMULATOR_DEFAULT_OS_VERSION 5.1

@interface PSKDeviceProperties (Simulator)
- (id)initForPhone3GWithOS:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone3G:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone3G;

- (id)initForPhone3GsWithOS:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone3Gs:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone3Gs;

- (id)initForPhone4WithOS:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone4:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone4;

- (id)initForPhone4sWithOS:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone4s:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone4s;

- (id)initForPhone5WithOS:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone5:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPhone5;

- (id)initForPad1WithOS:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad1:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad1;

- (id)initForPad2WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad2WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad2_Wifi:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad2_3G:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad2_CDMA:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad2_WifiNew:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad2_Wifi;
+ (PSKDeviceProperties *)devicePropertiesForPad2_3G;
+ (PSKDeviceProperties *)devicePropertiesForPad2_CDMA;
+ (PSKDeviceProperties *)devicePropertiesForPad2_WifiNew;

- (id)initForPadMini1WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1_Wifi:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1_3G:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1_CDMA:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1_Wifi;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1_3G;
+ (PSKDeviceProperties *)devicePropertiesForPadMini1_CDMA;

- (id)initForPad3WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad3WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad3_Wifi:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad3_4G:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad3_Wifi;
+ (PSKDeviceProperties *)devicePropertiesForPad3_4G;

- (id)initForPad4WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad4WithName:(NSString *)theName andOsVersion:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad4_Wifi:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad4_4G:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPad4_Wifi;
+ (PSKDeviceProperties *)devicePropertiesForPad4_4G;

- (id)initForPod4thGeneration:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPod4thGeneration:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPod4thGeneration;

- (id)initForPod5thGeneration:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPod5thGeneration:(float)theOsVersion;
+ (PSKDeviceProperties *)devicePropertiesForPod5thGeneration;
@end


@interface PSKSensorManager (Simulator)
- (void)clearDeviceProperties;
@end

@interface PSKSimulator : NSObject
+ (void)simulate:(PSKDeviceProperties *)deviceProperties;
@end
