//
//  PARViewController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>



@class PARView;
@class PARRadarView;
@class PARController;

/*!
 @class PARViewController
 */
@interface PARViewController : UIViewController {
    
    // ar view
    PARView* _arView;
    
    // live camera feed
    UIView* _cameraView;
    AVCaptureSession* _session;
    AVCaptureVideoPreviewLayer* _cameraPreview;
    BOOL _cameraPreviewVisible;
#if PANICAR_3D
    // camera image capture
    AVCaptureStillImageOutput* _stillImageOutput;
    BOOL _isCapturingImage;
#endif
    
    // radar
    PARRadarView* _arRadarView;
    
    UILabel* _watermark;
    
    // touch interaction
    BOOL _touched;
    BOOL _touchMoved;
    CGPoint _lastTouchPosition;
    CGPoint _initialTouchPosition;
    CGPoint _overallTouchDistance;
    CGPoint _lastTouchDistance;
}

@property (nonatomic,retain) PARView *arView;
@property (nonatomic,retain) PARRadarView *arRadarView;
#if PANICAR_3D
@property (nonatomic,readonly) BOOL isCapturingImage;
#endif


#pragma mark - Subviews
- (void)createARView;
- (void)createARRadarView;

#pragma mark - Main Control

- (void)startAR;
- (void)stopAR;

/*! @return YES if camera feed should be displayed */
- (BOOL)usesCameraPreview;
/*! @return YES if camera feed should fade in and out */
- (BOOL)fadesInCameraPreview;
/*! @return YES if PAR functionality should start automatically */
- (BOOL)startsARAutomatically;
/*! @return YES if PARView should rotate freely with the device
 @remarks don't return YES if your ViewController already supports Landscape orientations */
- (BOOL)rotatesARView;

#pragma mark - Camera

- (void)startCameraPreview;
- (void)updateCameraPreview;
- (void)stopCameraPreview;

#if PANICAR_3D
- (void)takePicture;
#endif


#pragma mark - Touch

/*! X-distance moved since last touch position */
- (float)touchDragX;
/*! X-distance moved since initial touch position */
- (float)touchMovedX;
/*! Y-distance moved since last touch position */
- (float)touchDragY;
/*! Y-distance moved since initial touch position */
- (float)touchMovedY;

/*! reset last touch position to 0,0 */
- (void)resetTouchDrag;

/*! has the ar view been tapped
 @remarks reset to NO after processing */
- (BOOL)tapped;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;


@end
