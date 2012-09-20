//
//  PARViewController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

#import "PSKSensorDelegate.h"

@class PARView;
@class PARRadarView;
@class PARController;
@class PSKSensorManager;

/*!
 @class PARViewController
 */
@interface PARViewController : UIViewController <PSKSensorDelegate> {
    
@public
    // ar view
    PARView* _arView;
    PSKSensorManager *_sensorManager;
    PSKDeviceAttitude *_deviceAttitude;
    
    // live camera feed
    UIView* _cameraView;
    AVCaptureSession* _session;
    AVCaptureVideoPreviewLayer* _cameraPreview;
    BOOL _cameraPreviewVisible;
    BOOL _notificationVisible;
    
    // radar
    PARRadarView* _arRadarView;
    
    // touch interaction
    BOOL _touched;
    BOOL _touchMoved;
    CGPoint _lastTouchPosition;
    CGPoint _initialTouchPosition;
    CGPoint _overallTouchDistance;
    CGPoint _lastTouchDistance;
    
    // orientation
    float _orientationOffsetAngle;
}

@property (nonatomic,retain) PARView *arView;
@property (nonatomic,retain) PARRadarView *arRadarView;
@property (nonatomic,readonly) PSKSensorManager *sensorManager;
- (BOOL)notificationVisible;


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
/*! @return size for the notification overlay view, default: ipad=256, iphone=128 */
- (float)sizeOfNotification;

/*! called when deviceOrientation switches to or from FaceUp
 default behavior: show radar in full screen mode, go back to thumbnail when no longer in face up
 override to deactivate default behavior */
- (void)switchFaceUp:(BOOL)inFaceUp;
/*! called when deviceOrientation switches to or from FaceDown 
 default behavior: */
- (void)switchFaceDown:(BOOL)inFaceDown;

- (void)setNotification:(NSString *)notification;

- (float)orientationOffsetAngle;

#pragma mark - Camera

- (void)startCameraPreview;
- (void)updateCameraPreview;
- (void)stopCameraPreview;


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

#pragma mark - C Helper
float OrientationOffsetAngleFromUIInterfaceOrientation(UIInterfaceOrientation orientation);
