//
//  PSKNativeCameraManager.h
//  Pods
//
//  Created by Andreas Zeitler on 30.04.13.
//
//

#import <Foundation/Foundation.h>
#import "PSKCameraManager.h"


@interface PSKNativeCameraManager : PSKCameraManager<AVCaptureVideoDataOutputSampleBufferDelegate>{
    AVCaptureSession *_session;
    AVCaptureVideoPreviewLayer *_cameraPreviewLayer;
}

@property (nonatomic, assign) CGSize previewScale;
@property (nonatomic, strong) NSString* sessionPreset;
@property (nonatomic, assign) NSString* videoGravity;
@property (nonatomic, strong, readwrite) NSMutableArray* supportedPresets;
@property (nonatomic, strong, readwrite) NSArray* videoGravities;
@property (nonatomic, assign) CGSize previewSize;
@end
