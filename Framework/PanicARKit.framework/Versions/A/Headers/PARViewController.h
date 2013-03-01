//
//  PARViewController.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 14.10.11.
//  copyright 2013 doPanic. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

#import "PSKSensorDelegate.h"
#import "PARViewControllerDelegate.h"

@class PARView;
@class PARRadarView;
@class PARController;
@class PSKSensorManager;
@class PARViewController;

extern id<PARViewControllerDelegate> _activeViewController;

/*!
 * PARViewController
 */
@interface PARViewController : UIViewController <PSKSensorDelegate, PARViewControllerDelegate>

/*! the arView of this PARViewController */
@property (nonatomic, strong, readonly) PARView *arView;
/*! the arRadarView of this PARViewController */
@property (nonatomic, strong, readonly) PARRadarView *arRadarView;

/*! the camera view of this PARViewController (if camera is used) */
@property (nonatomic, strong, readonly) UIView *cameraView;
@property (nonatomic, strong, readonly) AVCaptureSession *cameraAvCaptureSession;
@property (nonatomic, strong, readonly) AVCaptureVideoPreviewLayer *cameraAvCaptureVideoPreviewLayer;
@property (nonatomic, assign, readonly) BOOL cameraPreviewVisible;

@property (nonatomic, assign, readonly) BOOL touched;
@property (nonatomic, assign, readonly) BOOL touchMoved;

/*! reference to the PSKSensorManager:sharedSensorManager
 * @remarks for convenience */
- (PSKSensorManager *)sensorManager;
/*! reference to the PSKSensorManager:sharedSensorManager:deviceAttitude
 * @remarks for convenience */
- (PSKDeviceAttitude *)deviceAttitude;


/*! show a string in the notification overlay window of the PARViewController
 * @param notification NSString used for the notification
 * @remarks while notifications are visible the PARView and PARRadarView are hidden */
- (void)setNotification:(NSString *)notification;

/*! @return YES if notificationView is visible */
@property (nonatomic, assign, readonly) BOOL notificationVisible;

/*! @abstract the current offset of the view from portrait orientation, in degres
 @remarks for internal use only */
@property (nonatomic, assign, readonly) float orientationOffsetAngle;




/*!  pause all updates in the PARViewController's views */
- (BOOL)paused;
/*!  pause all updates in the PARViewController's views
 * @param paused YES to pause, NO to unpause */
- (void)setPaused:(BOOL)paused;


#pragma mark - Class Methods
/*!  set the curretly active PARViewController
 * @param theViewController the active PARViewController */
+ (void)setActiveViewController:(PARViewController *)theViewController;
/*!  the currently active PARViewController */
+ (PARViewController *)activeViewController;





#pragma mark - DEPRECATIONS

/*! X-distance moved since last touch position
 @deprecated don't use this any more, it will be removed from future revisions */
- (float)touchDragX  __attribute__ ((deprecated));
/*! X-distance moved since initial touch position
 @deprecated don't use this any more, it will be removed from future revisions */
- (float)touchMovedX  __attribute__ ((deprecated));
/*! Y-distance moved since last touch position
 @deprecated don't use this any more, it will be removed from future revisions */
- (float)touchDragY  __attribute__ ((deprecated));
/*! Y-distance moved since initial touch position
 @deprecated don't use this any more, it will be removed from future revisions */
- (float)touchMovedY  __attribute__ ((deprecated));

/*! reset last touch position to 0,0
 @deprecated don't use this any more, it will be removed from future revisions */
- (void)resetTouchDrag  __attribute__ ((deprecated));

/*! has the ar view been tapped
 * @remarks reset to NO after processing
 @deprecated don't use this any more, it will be removed from future revisions */
- (BOOL)tapped  __attribute__ ((deprecated));

@end

#pragma mark - C Helper
float PAROrientationOffsetAngleFromUIInterfaceOrientation(UIInterfaceOrientation orientation);
BOOL PARDisablesViewForUIDeviceOrientation(UIDeviceOrientation orientation);
