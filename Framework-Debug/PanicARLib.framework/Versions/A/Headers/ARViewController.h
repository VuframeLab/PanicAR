//
//  ARViewController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "ARRadarView.h"



@class ARView;
@class ARController;

/*!
 @class ARViewController
 */
@interface ARViewController : UIViewController {
    
    // ar view
    ARView* _arView;
    
    // live camera feed
    UIView* _cameraView;
    AVCaptureSession* _session;
    AVCaptureVideoPreviewLayer* _cameraPreview;
    BOOL _cameraPreviewVisible;
    // camera image capture
    AVCaptureStillImageOutput* _stillImageOutput;
    BOOL _isCapturingImage;
    
    // radar
    ARRadarView* _arRadarView;
    
    UILabel* _watermark;
    
    // touch interaction
    BOOL _touched;
    BOOL _touchMoved;
    CGPoint _lastTouchPosition;
    CGPoint _initialTouchPosition;
    CGPoint _overallTouchDistance;
    CGPoint _lastTouchDistance;
}

@property (nonatomic,retain) ARView *arView;
@property (nonatomic,retain) ARRadarView *arRadarView;

#pragma mark - Subviews
- (void)createARView;
- (void)createARRadarView;

#pragma mark - Camera
- (BOOL)usesCameraPreview;
- (BOOL)shouldFadeInCameraPreview;
- (void)startCameraPreview;
- (void)updateCameraPreview;
- (void)stopCameraPreview;
- (void)takePicture;



#pragma mark - Touch
/*! AR Objects receive touch events?
 @return YES or NO
 default: YES */
- (BOOL)doObjectsRespondToTouch;
- (float)touchDragX;
- (float)touchMovedX;
- (float)touchDragY;
- (float)touchMovedY;
- (void)resetTouchDrag;
- (BOOL)tapped;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;


@end
