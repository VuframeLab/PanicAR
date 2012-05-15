//
//  PARView.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PARObjectDelegate.h"
#import "PARMath.h"


#define RENDER_FPS 15
#define RENDER_PLANE_NEAR 0.25
#define RENDER_PLANE_FAR 100000
#define DEFAULT_STACKING_ANIMATION_SPEED_IPAD 0.25
#define DEFAULT_STACKING_ANIMATION_SPEED_IPHONE 0.5
#define DEFAULT_LABEL_BASELINE 0.5
#define DEFAULT_LABEL_ALIGN_TO_DEVICE YES

#define MAX_NUMBER_OF_STACKINGSECTORS 80 
#define HALF_NUMBER_OF_STACKINGSECTORS (MAX_NUMBER_OF_STACKINGSECTORS/2)

@class PARController;
@class PARSensorManager;
@class PARPoi;
@class PARViewController;

#ifdef DEBUG
    #ifndef PANIC_FRAMEWORK
        #undef VISUALIZE_STACKING // use define to activate
    #else
        #undef VISUALIZE_STACKING
    #endif
#else
    #undef VISUALIZE_STACKING
#endif

extern PARView* _activeView;



/*! @class PARView 
 handles interface for rendering AR objects
 provides functionality for non-3d rendering and stacking of labels
 */
@interface PARView : UIView {
	PARController* _arController;
	PARSensorManager* _arSensorManager;
	PARViewController* _arViewController;
	id<PARObjectDelegate> _currentObject;
    
    double _fov, _verticalFov;
	PARMatrix4x4 _perspectiveMatrix;
	PARMatrix4x4 _perspectiveCameraMatrix;
    
    // object sorting
    float _heightInStackingSector[MAX_NUMBER_OF_STACKINGSECTORS];
    int _numberOfStackingSectors;
#ifdef VISUALIZE_STACKING
    UIView* _heightBars[MAX_NUMBER_OF_STACKINGSECTORS];
#endif
    float _widthOfStackingSector;
    float _firstSectorX, _lastSectorX;
    float _stackingAnimationSpeed;
    float _labelBaseline;
    BOOL _alignLabelsToDeviceOrientation;
    NSTimer *_renderTimer;
}


@property (nonatomic, retain) PARViewController* arViewController;
/*! @property stacking animation speed
 @remarks speed of label's movement to new position when stacking is enabled*/
@property (nonatomic, assign,setter = setStackingAnimationSpeed:) float stackingAnimationSpeed;

/*! @property base line at which label's y-position is calculated
 @remarks default = 0.5, i.e. middle of view */
- (float) labelBaseline;
- (void) setLabelBaseline:(float)percentage;

- (PARMatrix4x4*) perspectiveCameraMatrix;


#pragma mark - Main
- (void)start;
- (void)stop;
- (void)updateView:(NSTimer *)theTimer;

- (void)setupProjectionMatrix;

#pragma mark - Utilities
- (UIImage *)renderToImageWithSize:(float)theWidth Height:(float)theHeight;

#pragma mark - Class Methods
+ (void)setActiveView:(PARView *)theView;
+ (PARView *)activeView;

@end
