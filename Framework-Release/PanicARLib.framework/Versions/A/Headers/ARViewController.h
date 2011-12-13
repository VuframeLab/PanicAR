//
//  ARViewController.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 14.10.11.
//  Copyright 2011 doPanic. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>


#define RADAR_POSITION_Y -2.0f
#define RADAR_BG_SIZE 1.850f
#define RADAR_MAX_RADIUS 0.90f
#define RADAR_BLIP_SIZE 0.2f
#undef RADAR_FADE_BLIPS
#define RADAR_DEFAULT_RANGE 10000.0f //10.000 meters

typedef enum {
    ARRadarOff,
    ARRadarThumbnail,
    ARRadarFullscreen
} ARRadarMode;

typedef enum {
    ARRadarPositionTopLeft,
    ARRadarPositionTopRight,
    ARRadarPositionBottomLeft,
    ARRadarPositionBottomRight,
} ARRadarPosition;


@class ARView;
@class ARController;

/*!
 @class ARViewController
 */
@interface ARViewController : UIViewController {
    
    // ar view
    ARView* _arView;
    
    // live camera feed
    UIView* cameraView;
    AVCaptureSession* session;
    AVCaptureVideoPreviewLayer* cameraPreview;
    BOOL cameraPreviewVisible;
    // camera image capture
    AVCaptureStillImageOutput* stillImageOutput;
    BOOL isCapturingImage;
    
    // radar
    BOOL radarVisible;
    ARRadarMode radarMode;
    CGRect radarRect;
    CGRect radarOriginRect;
    CGRect radarTargetRect;
    BOOL radarHidesMarkers;
    float radarRange;
    
    
    // touch interaction
    BOOL touched;
    BOOL touchMoved;
    CGPoint lastTouchPosition;
    CGPoint initialTouchPosition;
    CGPoint overallTouchDistance;
    CGPoint lastTouchDistance;
    
    UILabel* watermark;
}

#pragma mark - Config

/*! AR Objects receive touch events?
 @return YES or NO
 default: YES
 */
- (BOOL) doObjectsRespondToTouch;



#pragma mark - Radar

/*! 
 shows the radar in the last RadarMode set or in thumbnail if none was set before
 */
- (void) showRadar;

/*! 
 shows the radar in the specific mode
 @param theMode – the mode the radar will be shown in (as ARRadarMode)
 */
- (void) showRadarInMode:(ARRadarMode)theMode;

/*! 
 shows the radar in Thumbnail mode in the specific position of the AR view
 @param thePosition – @ref ARRadarPosition
 */
- (void) showRadarThumbnail:(ARRadarPosition)thePosition;

/*! 
 shows the radar in Thumbnail mode in the specific position of the AR view
 @param thePosition – @ref ARRadarPosition
 @param theOffset – offset from the respective borders of the screen
 */
- (void) showRadarThumbnail:(ARRadarPosition)thePosition withAdditionalOffset:(CGRect)theOffset;

/*!
 hide the radar
 */
- (void) hideRadar;

/*!
 is radar visible?
 */
- (BOOL) isRadarVisible;

/*! set radar range in meters, objects outside range will not be displayed on radar
 @param theRange the range the radar will display markers in
 */
- (void) setRadarRange:(float)theRange;

/*! radar range in meters, objects outside range will not be displayed on radar
 @return the range
 @remarks default = 10.000 meters
 */
- (float) radarRange;

/*!
 overwrite in sub-class
 @return YES if radar should only pop up in FaceUp orientation
 */
- (BOOL) radarVisibleInFaceUp;

/*!
 overwrite in sub-class
 @return YES if radar should only pop up in FaceUp orientation
 */
- (BOOL) radarClipsObjectsOutsideRange;



#pragma mark - Camera

- (BOOL) doesUseCameraPreview;
- (BOOL) shouldFadeInCameraView;
- (void) startCameraPreview;
- (void) stopCameraPreview;
- (void) takePicture;


#pragma mark - Touch

- (void) doTouchEvent:(CGPoint)point;
- (float) touchDragX;
- (float) touchMovedX;
- (float) touchDragY;
- (float) touchMovedY;
- (void) resetTouchDrag;
- (BOOL) tapped;

@end
