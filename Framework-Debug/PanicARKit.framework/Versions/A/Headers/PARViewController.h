//
//  PARViewController.h
//  PanicARKit
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
@class PARViewController;

extern PARViewController* _activeViewController;

/*!
  PARViewController
 */
@interface PARViewController : UIViewController <PSKSensorDelegate> {
    // references
    PSKSensorManager *_sensorManager;
    PSKDeviceAttitude *_deviceAttitude;
    
    // ar view
    PARView* _arView;
    PARRadarView* _arRadarView;
    
    // live camera feed
    UIView* _cameraView;
    AVCaptureSession* _session;
    AVCaptureVideoPreviewLayer* _cameraPreview;
    BOOL _cameraPreviewVisible;
    
    // other
    BOOL _notificationVisible;
    
    // touch interaction
    BOOL _touched;
    BOOL _touchMoved;
}

/*! the arView of this PARViewController */
@property (nonatomic,retain) PARView *arView;
/*! the arRadarView of this PARViewController */
@property (nonatomic,retain) PARRadarView *arRadarView;
/*! reference to the PSKSensorManager:sharedSensorManager 
 @remarks for convenience */
@property (nonatomic,readonly) PSKSensorManager *sensorManager;

/*! @return YES if notificationView is visible */
- (BOOL)notificationVisible;



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
 override to deactivate default behavior 
 @param inFaceUp YES if orientation just switched to UIDeviceOrientationFaceUp */
- (void)switchFaceUp:(BOOL)inFaceUp;
/*! called when deviceOrientation switches to or from FaceDown 
 default behavior: show notification and hide PARView and PARRadarView
 @param inFaceDown YES if orientation just switched to UIDeviceOrientationFaceDown */
- (void)switchFaceDown:(BOOL)inFaceDown;

/*! show a string in the notification overlay window of the PARViewController
 @param notification NSString used for the notification
 @remarks while notifications are visible the PARView and PARRadarView are hidden */
- (void)setNotification:(NSString *)notification;

/*!  for internal use only */
- (float)orientationOffsetAngle;



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


/*!  pause all updates in the PARViewController's views */
- (BOOL)paused;
/*!  pause all updates in the PARViewController's views
 @param paused YES to pause, NO to unpause */
- (void)setPaused:(BOOL)paused;


#pragma mark - Class Methods
/*!  set the curretly active PARViewController
 @param theViewController the active PARViewController */
+ (void)setActiveViewController:(PARViewController *)theViewController;
/*!  the currently active PARViewController */
+ (PARViewController *)activeViewController;
@end

#pragma mark - C Helper
float OrientationOffsetAngleFromUIInterfaceOrientation(UIInterfaceOrientation orientation);
