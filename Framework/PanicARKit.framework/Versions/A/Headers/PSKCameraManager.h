//
//  PSKCameraManager.h
//  Pods
//
//  Created by Andreas Zeitler on 30.04.13.
//
//

#import <AVFoundation/AVFoundation.h>

@interface PSKCameraManager : NSObject {
    AVCaptureDeviceInput *_input;
}

- (id)initWithView:(UIView *)cameraView;
@property (nonatomic, strong, readonly) UIView *cameraView;
@property (nonatomic, strong, readonly) AVCaptureSession *session;
@property (nonatomic, assign, readonly) BOOL cameraPreviewPaused;
@property (nonatomic, assign, readonly) BOOL cameraPreviewStarted;
@property (nonatomic, strong) NSString *sessionPreset;

- (void)startCameraPreview;
- (void)stopCameraPreview:(BOOL)animated;
- (void)toggleCameraPreviewPause;
- (void)unpauseCameraPreview;

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;

@end
