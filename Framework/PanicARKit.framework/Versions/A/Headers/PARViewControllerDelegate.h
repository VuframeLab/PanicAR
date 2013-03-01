//
//  PARViewControllerDelegate.h
//  Pods
//
//  Created by Andreas Zeitler on 24.02.13.
//
//

#import <Foundation/Foundation.h>

@protocol PARViewControllerDelegate <NSObject>

@required
/*! @return YES if camera feed should be displayed */
- (BOOL)usesCameraPreview;
/*! @return YES if camera feed should fade in and out */
- (BOOL)fadesInCameraPreview;
/*! @return YES if PAR functionality should start automatically */
- (BOOL)startsARAutomatically;
/*! @return YES for all orientations the AR view should be visible in */
- (BOOL)showARViewInOrientation:(UIDeviceOrientation)orientation;
/*! @return YES if PARView should rotate freely with the device
 * @remarks don't return YES if your ViewController already supports Landscape orientations */
- (BOOL)rotatesARView;
/*! @return size for the notification overlay view, default: ipad=256, iphone=128 */
- (float)sizeOfNotification;

/*! called when deviceOrientation switches to or from FaceUp
 * default behavior: show radar in full screen mode, go back to thumbnail when no longer in face up
 * override to deactivate default behavior
 * @param inFaceUp YES if orientation just switched to UIDeviceOrientationFaceUp */
- (void)switchFaceUp:(BOOL)inFaceUp;
/*! called when deviceOrientation switches to or from FaceDown
 * default behavior: show notification and hide PARView and PARRadarView
 * @param inFaceDown YES if orientation just switched to UIDeviceOrientationFaceDown */
- (void)switchFaceDown:(BOOL)inFaceDown;

@end
