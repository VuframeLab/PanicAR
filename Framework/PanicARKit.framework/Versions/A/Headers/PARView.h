//
//  PARView.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PARObjectDelegate.h"
#import "PSKMath.h"


#define RENDER_FPS								15
#define RENDER_PLANE_NEAR						0.25
#define RENDER_PLANE_FAR						100000
#define DEFAULT_STACKING_ANIMATION_SPEED_IPAD	0.25
#define DEFAULT_STACKING_ANIMATION_SPEED_IPHONE 0.5
#define DEFAULT_LABEL_BASELINE					0.5
#define DEFAULT_LABEL_ALIGN_TO_DEVICE			YES

#define MAX_NUMBER_OF_STACKINGSECTORS			80
#define HALF_NUMBER_OF_STACKINGSECTORS			(MAX_NUMBER_OF_STACKINGSECTORS / 2)

@class PARController;
@class PSKSensorManager;
@class PSKDeviceAttitude;
@class PARPoi;
@class PARViewController;

extern PARView *_activeView;



/*!  PARView
 * handles interface for rendering AR objects
 * provides functionality for non-3d rendering and stacking of labels
 */
@interface PARView : UIView {
	id<PARObjectDelegate> _currentObject;

	CGSize _viewport;
	float _fov, _verticalFov;
	PSKMatrix4x4 _perspectiveMatrix;
	PSKMatrix4x4 _perspectiveCameraMatrix;

	// object sorting
	float _heightInStackingSector[MAX_NUMBER_OF_STACKINGSECTORS];
	int _numberOfStackingSectors;
	float _widthOfStackingSector;
	float _firstSectorX, _lastSectorX;
	float _stackingAnimationSpeed;
	float _labelBaseline;
	BOOL _alignLabelsToDeviceOrientation;
	NSTimer *_renderTimer;
	float _viewRotationOffset;
}

/*!  the PARViewController PARView instance belongs to */
@property (nonatomic, strong) PARViewController *arViewController;
/*!  stacking animation speed
 * @remarks speed of label's movement to new position when stacking is enabled*/
@property (nonatomic, assign, setter = setStackingAnimationSpeed :) float stackingAnimationSpeed;

/*!  base line at which label's y-position is calculated
 * @remarks default = 0.5, i.e. middle of view */
- (float)labelBaseline;

/*!  base line at which label's y-position is calculated
 * @remarks default = 0.5, i.e. middle of view
 * this is how the POI position on screen is calculated:
    _relativeScreenPosition.x = (p.x + 1.f) * .5f;
    _relativeScreenPosition.y = (p.y + 1.f) * .5f + (_labelBaseline - 0.5);
 * @param percentage relative y-position of label baseline, 0.0 for bottom margin of screen, 1.0 for top margin of screen */
- (void)setLabelBaseline:(float)percentage;

/*! the rotated projection matrix of the camera
 * @remarks for internal use */
- (PSKMatrix4x4 *)perspectiveCameraMatrix;

/*! the size of the viewport */
- (CGSize)viewport;


#pragma mark - Class Methods
/*! returns the currently activeView
 @deprecated don't use this any more, it will be removed from future revisions
 */
+ (PARView *)activeView  __attribute__ ((deprecated));;

@end
