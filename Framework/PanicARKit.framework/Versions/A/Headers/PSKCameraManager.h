//
//  PSKCameraManager.h
//  Pods
//
//  Created by Andreas Zeitler on 30.04.13.
//
//

#import <AVFoundation/AVFoundation.h>

@protocol PSKCameraManagerDelegate
- (void)cameraManagerDidCaptureImage:(UIImage *)image;
@end

@interface PSKCameraManager : NSObject {
    AVCaptureDeviceInput *_input;
}

- (id)initWithView:(UIView *)cameraView;
@property (nonatomic, weak, readonly) UIView *cameraView;
@property (nonatomic, strong, readonly) AVCaptureSession *session;
@property (nonatomic, assign, readonly) BOOL cameraPreviewPaused;
@property (nonatomic, assign, readonly) BOOL cameraPreviewStarted;
@property (nonatomic, strong) NSString *sessionPreset;
@property (nonatomic, weak) id<PSKCameraManagerDelegate> delegate;

- (void)startCameraPreview;
- (void)stopCameraPreview:(BOOL)animated;
- (void)toggleCameraPreviewPause;
- (void)unpauseCameraPreview;
- (void)captureImage;
- (void)captureImageWithSize:(CGSize)size;

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;

@end
