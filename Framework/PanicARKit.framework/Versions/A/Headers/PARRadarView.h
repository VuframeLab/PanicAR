//
//  PARRadarView.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PSKMath.h"


typedef enum
{
	PARRadarOff,
	PARRadarThumbnail,
	PARRadarFullscreen
} PARRadarMode;

typedef enum
{
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

extern PARRadarView *_activeRadarView;

/*!  PARRadarView */
@interface PARRadarView : UIView {
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
	NSTimer *_renderTimer;

	BOOL _canBeVisible;
}

/*!  the container view which is rotated */
@property (nonatomic, strong, readonly) UIView *containerView;

/*!  the background image container */
@property (nonatomic, strong, readonly) UIImageView *backgroundImageView;

/*!  the PARViewController PARRadarView instance belongs to */
@property (nonatomic, strong) PARViewController *arViewController;

/*!  used internally to keep track of rendered objects */
@property (nonatomic, readonly) int renderID;

/*!  used internally to determine if view should be visible */
@property (nonatomic, assign) BOOL canBeVisible;


#pragma mark - Main
/*! default initialization
 * creates an PARRadarView instance using the image as background image
 * @param image UIImage used as background for the PARRadarView instance */
- (id)initWithImage:(UIImage *)image;

/*!  radar orientation matrix */
- (PSKMatrix4x4 *)radarMatrix;


#pragma mark - Radar

/*!  shows the radar in the last RadarMode set or in thumbnail if none was set before */
- (void)showRadar;
/*! show the PARRadarView in a specific mode
 * @param theMode PARRadarMode in which the radar will be shown */
- (void)showRadarInMode:(PARRadarMode)theMode;

/*! hide the radar */
- (void)hideRadar;

/*!  is radar visible? */
- (BOOL)isRadarVisible;

/*!  current radar mode */
- (PARRadarMode)radarMode;


/*! make radar fullscreen */
- (void)setRadarToFullscreen;
/*! make radar fullscreen
 * @param theOffset move center
 * @param sizeOffset add inset */
- (void)setRadarToFullscreen:(CGPoint) theOffset withSizeOffset:(float)sizeOffset;
/*! shows the radar in Thumbnail mode */
- (void)setRadarToThumbnail;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 * @param thePosition – @ref PARRadarPosition */
- (void)setRadarToThumbnail:(PARRadarPosition)thePosition;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 * @param thePosition – @ref PARRadarPosition
 * @param theOffset – offset from the respective borders of the screen */
- (void)setRadarToThumbnail:(PARRadarPosition) thePosition withAdditionalOffset:(CGRect)theOffset;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 * @param thePosition – @ref PARRadarPosition
 * @param theOffset – offset from the respective borders of the screen
 * @param theSize – size of the radar on the screen */
- (void)setRadarToThumbnail:(PARRadarPosition) thePosition withAdditionalOffset:(CGRect) theOffset andSize:(float)theSize;
/*! shows the radar in Thumbnail mode in the specific position of the PAR view
 * @param thePosition – set position directly using a @ref CGPoint
 * @param theSize – size of the radar on the screen */
- (void)setRadarToThumbnail:(CGPoint) thePosition withSize:(float)theSize;

/*! set radar range in meters, objects outside range will not be displayed on radar
 * @param theRange the range the radar will display markers in */
- (void)setRadarRange:(float)theRange;

/*!  radar range in meters, objects outside range will not be displayed on radar
 * @return the range
 * @remarks default = 10.000 meters */
- (float)radarRange;

/*!  range of the radar in pixel */
- (float)radarRadius;
/*!  YES if radar radius is currently being animated
 * @remarks */
- (BOOL)animatesRadius;

/*!  inset of radar dots
 * @remarks max. distance of dot to center of radar = radius - inset */
- (float)radarInset;
/*!  @param theInset inset of radar dots in pixels */
- (void)setRadarInset:(float)theInset;

#pragma mark - Class Methods
/*!  the currently active radar view
 @deprecated don't use this any more, it will be removed from future revisions */
+ (PARRadarView *)activeView  __attribute__ ((deprecated));

@end
