//
//  PSKBufferedCameraManager.h
//  Pods
//
//  Created by Andreas Zeitler on 30.04.13.
//
//

#import "PSKCameraManager.h"

@interface PSKBufferedCameraManager : PSKCameraManager <AVCaptureVideoDataOutputSampleBufferDelegate> {
    
    AVCaptureVideoDataOutput *_dataOutput;
    AVCaptureConnection *_videoConnection;
    CALayer *_cameraPreviewLayer;
    CGSize _cameraPreviewImageSize;
    
    BOOL _cameraPreviewNeedsResize;
    BOOL _cameraPreviewHadFirstFrame;
    BOOL _videoConnectionSupportsVideoOrientation;
}

@end
