//
//  PARRadarView.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PSKMath.h"


typedef enum {
    PARRadarOff,
    PARRadarThumbnail,
    PARRadarFullscreen
} PARRadarMode;

typedef enum {
    PARRadarPositionTopLeft,
    PARRadarPositionTopRight,
    PARRadarPositionBottomLeft,
    PARRadarPositionBottomRight,
} PARRadarPosition;


@class PARController;
@class PARPoi;
@class PARViewController;
@class PARRadarView;
@class PSKDeviceAttitude;

extern PARRadarView* _activeRadarView;

/*! @class PARRadarView */
@interface PARRadarView : UIView {
	PARController* _arController;
	PARViewController* _arViewController;
    PSKDeviceAttitude *_deviceAttitude;
    UIImageView* _background;
	PSKMatrix4x4 _radarMatrix;
    
    // radar
    PARRadarMode _radarMode;
    CGRect _radarRect;
    float _radarRange;
    float _radarRadius;
    BOOL _animateRadius;
    float _radarInset;
    int _renderID;
    BOOL _rendering;
    NSTimer* _renderTimer;
    
    BOOL _canBeVisible;
}

/*! @property the PARViewController PARRadarView instance belongs to */
@property (nonatomic, retain) PARViewController* arViewController;

/*! @property used internally to keep track of rendered objects */
@property (nonatomic,readonly) int renderID;

/*! @property used internally to determine if view should be visible */
@property (nonatomic, assign) BOOL canBeVisible;


#pragma mark - Main
/*! default initialization
 creates an PARRadarView instance using the image as background image
 @param image UIImage used as background for the PARRadarView instance */
- (id)initWithImage:(UIImage *)image;

/*! starts the update behavior */
- (void)start;
/*! stops the update behavior */
- (void)stop;
/*! called each frame to render the radar content */
- (void)updateView:(NSTimer *)theTimer;

/*! @property radar orientation matrix */
- (PSKMatrix4x4*) radarMatrix;


#pragma mark - Radar

/*!  shows the radar in the last RadarMode set or in thumbnail if none was set before */
- (void)showRadar;
/*! show the PARRadarView in a specific mode
 @param theMode PARRadarMode in which the radar will be shown */
- (void)showRadarInMode:(PARRadarMode)theMode;

/*! hide the radar */
- (void)hideRadar;

/*! @property is radar visible? */
- (BOOL)isRadarVisible;

/*! @property current radar mode */
- (PARRadarMode) radarMode;


/*! make radar fullscreen */
- (void)setRadarToFullscreen;
/*! make radar fullscreen
 @param theOffset move center
 @param sizeOffset add inset */
- (void)setRadarToFullscreen:(CGPoint)theOffset withSizeOffset:(float)sizeOffset;
/*! shows the radar in Thumbnail mode */
- (void)setRadarToThumbnail;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 @param thePosition – @ref PARRadarPosition */
- (void)setRadarToThumbnail:(PARRadarPosition)thePosition;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 @param thePosition – @ref PARRadarPosition
 @param theOffset – offset from the respective borders of the screen */
- (void)setRadarToThumbnail:(PARRadarPosition)thePosition withAdditionalOffset:(CGRect)theOffset;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 @param thePosition – @ref PARRadarPosition
 @param theOffset – offset from the respective borders of the screen
 @param theSize – size of the radar on the screen */
- (void)setRadarToThumbnail:(PARRadarPosition)thePosition withAdditionalOffset:(CGRect)theOffset andSize:(float)theSize;
- (void)setRadarToThumbnail:(CGPoint)thePosition withSize:(float)theSize;

/*! set radar range in meters, objects outside range will not be displayed on radar
 @param theRange the range the radar will display markers in */
- (void)setRadarRange:(float)theRange;

/*! @property radar range in meters, objects outside range will not be displayed on radar
 @return the range
 @remarks default = 10.000 meters */
- (float)radarRange;

/*! @property range of the radar in pixel */
- (float)radarRadius;
/*! @property YES if radar radius is currently being animated
 @remarks */
- (BOOL)animatesRadius;

/*! @property inset of radar dots 
 @remarks max. distance of dot to center of radar = radius - inset */
- (float)radarInset;
/*! @property @param theInset inset of radar dots in pixels */
- (void)setRadarInset:(float)theInset;

#pragma mark - Class Methods
/*! @property set the curretly active PARRadarView
 @param theView the active PARRadarView */
+ (void)setActiveView:(PARRadarView *)theView;
/*! @property the currently active radar view */
+ (PARRadarView *)activeView;

@end
