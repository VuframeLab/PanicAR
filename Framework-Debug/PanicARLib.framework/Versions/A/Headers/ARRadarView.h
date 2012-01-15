//
//  ARRadarView.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>

#define RADAR_POSITION_Y -2.0f
#define RADAR_BG_SIZE 1.850f
#define RADAR_MAX_RADIUS 0.90f
#define RADAR_BLIP_SIZE 24
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


@class ARController;
@class ARPoi;
@class ARViewController;
@class ARRadarView;

extern ARRadarView* _activeRadarView;

@interface ARRadarView : UIView {
	ARController* _arController;
	ARViewController* _arViewController;
    UIImageView* _background;
    
    // radar
    ARRadarMode _radarMode;
    CGRect _radarRect;
    float _radarRange;
    float _radarRadius;
    float _radarInset;
    int _renderID;
    BOOL _rendering;
}

@property (nonatomic, retain) ARViewController* arViewController;
@property (nonatomic, readonly) int renderID;


#pragma mark - Main
- (id)initWithImage:(UIImage *)image;

- (void)start;
- (void)stop;


#pragma mark - Radar Management


#pragma mark - Radar

/*!  shows the radar in the last RadarMode set or in thumbnail if none was set before */
- (void)showRadar;
- (void)showRadarInMode:(ARRadarMode)theMode;

/*! hide the radar */
- (void)hideRadar;

/*! is radar visible? */
- (BOOL)isRadarVisible;

/*! current radar mode */
- (ARRadarMode) radarMode;


/*! make radar fullscreen */
- (void)setRadarToFullscreen;
/*! make radar fullscreen
 @param theOffset move center
 @param sizeOffset add inset */
- (void)setRadarToFullscreen:(CGPoint)theOffset withSizeOffset:(float)sizeOffset;
/*! shows the radar in Thumbnail mode in the specific position of the AR view
 @param thePosition – @ref ARRadarPosition */
- (void)setRadarToThumbnail;
/*! shows the radar in Thumbnail mode in the specific position of the AR view
 @param thePosition – @ref ARRadarPosition */
- (void)setRadarToThumbnail:(ARRadarPosition)thePosition;
/*! shows the radar in Thumbnail mode in the specific position of the AR view
 @param thePosition – @ref ARRadarPosition
 @param theOffset – offset from the respective borders of the screen */
- (void)setRadarToThumbnail:(ARRadarPosition)thePosition withAdditionalOffset:(CGRect)theOffset;
- (void)setRadarToThumbnail:(ARRadarPosition)thePosition withAdditionalOffset:(CGRect)theOffset andSize:(float)theSize;
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
/*! inset of radar dots */
- (void)setRadarInset:(float)theInset;

#pragma mark - Class Methods
+ (void)setActiveView:(ARRadarView *)theView;
+ (ARRadarView *)activeView;

@end
