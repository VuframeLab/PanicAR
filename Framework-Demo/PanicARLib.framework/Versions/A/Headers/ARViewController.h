//
//  ARViewController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

typedef enum {
    VisibleInFaceUp,
    AlwaysVisible,
} ARRadarMode;

@class ARView;
@class ARController;

@interface ARViewController : UIViewController {
    
    // ar view
    ARView* _arView;
    
    // live camera feed
    UIView* _cameraView;
    AVCaptureSession* _session;
    AVCaptureVideoPreviewLayer *_cameraPreview;
    BOOL _cameraPreviewVisible;
    // camera image capture
    AVCaptureStillImageOutput* _stillImageOutput;
    BOOL _isCapturingImage;
    
    // radar
    CGRect _radarRect;
    CGRect _radarOriginRect;
    CGRect _radarTargetRect;
    BOOL _radarIsFullscreen;
    BOOL _radarHidesMarkers;
    
    
    // touch interaction
    BOOL _touched;
    BOOL _touchMoved;
    CGPoint _lastTouchPosition;
    CGPoint _initialTouchPosition;
    CGPoint _overallTouchDistance;
    CGPoint _lastTouchDistance;
    
    UILabel* _watermark;
}

/*!
 show the radar view full screen while hiding the other markers
 */
//- (void)showRadar;
/*!
 show the radar view full screen while optionally hiding the other markers
 */
//- (void)showRadar:(BOOL)hideMarkers;
/*!
 show the radar view within the rect while optionally hiding the other markers 
 */
//- (void)showRadar:(BOOL)hideMarkers inRectangle:(CGRect)theRect;
/*!
 hide the radar view
 */
//- (void)hideRadar;




#pragma mark - Camera

- (BOOL)doesUseCameraPreview;
- (BOOL)shouldFadeInCameraView;
- (void)startCameraPreview;
- (void)stopCameraPreview;
- (void)takePicture;


#pragma mark - Touch

- (void)doTouchEvent:(CGPoint)point;
- (float)touchDragX;
- (float)touchMovedX;
- (float)touchDragY;
- (float)touchMovedY;
- (void)resetTouchDrag;
- (BOOL)tapped;

@end
