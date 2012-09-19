//
//  PARRadarView.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>

#define RADAR_DEFAULT_RANGE 10000.0f //10.000 meters
#define RENDER_RADAR_FPS 10


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

extern PARRadarView* _activeRadarView;

/*! @class PARRadarView */
@interface PARRadarView : UIView {
	PARController* _arController;
	PARViewController* _arViewController;
    UIImageView* _background;
    
    // radar
    PARRadarMode _radarMode;
    CGRect _radarRect;
    float _radarRange;
    float _radarRadius;
    float _radarInset;
    int _renderID;
    BOOL _rendering;
    NSTimer* _renderTimer;
}

@property (nonatomic, retain) PARViewController* arViewController;
@property (nonatomic, readonly) int renderID;


#pragma mark - Main
- (id)initWithImage:(UIImage *)image;

- (void)start;
- (void)stop;
- (void)updateView:(NSTimer *)theTimer;


#pragma mark - Radar Management


#pragma mark - Radar

/*!  shows the radar in the last RadarMode set or in thumbnail if none was set before */
- (void)showRadar;
- (void)showRadarInMode:(PARRadarMode)theMode;

/*! hide the radar */
- (void)hideRadar;

/*! is radar visible? */
- (BOOL)isRadarVisible;

/*! current radar mode */
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
- (void)setRadarToThumbnail:(PARRadarPosition)thePosition withAdditionalOffset:(CGRect)theOffset andSize:(float)theSize;
- (void)setRadarToThumbnail:(CGPoint)thePosition withSize:(float)theSize;

/*! set radar range in meters, objects outside range will not be displayed on radar
 @param theRange the range the radar will display markers in */
- (void)setRadarRange:(float)theRange;

/*! radar range in meters, objects outside range will not be displayed on radar
 @return the range
 @remarks default = 10.000 meters */
- (float)radarRange;

/*! range of the radar in pixel */
- (float)radarRadius;

/*! inset of radar dots 
 @remarks max. distance of dot to center of radar = radius - inset */
- (float)radarInset;
/*! @param theInset inset of radar dots in pixels */
- (void)setRadarInset:(float)theInset;

#pragma mark - Class Methods
+ (void)setActiveView:(PARRadarView *)theView;
+ (PARRadarView *)activeView;

@end
