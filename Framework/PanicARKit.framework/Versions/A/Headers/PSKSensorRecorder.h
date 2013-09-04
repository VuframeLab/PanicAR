//
//  PSKSensorRecorder.h
//  PanicSensorKit
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PSKMath.h"
#import "PSKSensorManager.h"
#import "PSKSensorDelegate.h"

typedef enum {
    PSKSensorRecorderRecordAttitude,
    PSKSensorRecorderRecordLocation,
    PSKSensorRecorderRecordLocationAndAttitude
} PSKSensorRecorderRecordMode;

@interface PSKSensorRecorder : NSObject <PSKSensorDelegate, CLLocationManagerDelegate> {
  
}

@property (nonatomic,assign) PSKSensorRecorderRecordMode recordMode;

/*! shared attitude recorder instance */
+ (PSKSensorRecorder *)sharedAttitudeRecorder;

- (void)startRecordingwithSamplingRate:(float)samplingRate;
- (void)stopRecording;
- (void)saveRecord;
- (void)resetRecord;
- (void)recordSample:(NSTimer*)timer;


@end
