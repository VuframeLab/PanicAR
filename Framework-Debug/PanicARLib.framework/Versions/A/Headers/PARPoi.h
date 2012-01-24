//
//  PARPoi.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 13.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "PARMath.h"
#import "PARObjectDelegate.h"

extern BOOL _loadsDefaultRadarGfx;
extern BOOL _alignToDeviceOrientation;
extern float _stackingAnimationSpeed;
extern float _labelBaseline;
extern float _clipObjectFarLimit;
extern float _clipObjectNearLimit;
extern BOOL _viewIsLandscape;
extern float _viewGravityX;
extern float _viewGravityY;

/*!
 @class PARPoi
 base class for all location-based Points of Interest
 implements MKAnnotation protocol
 */
@interface PARPoi : NSObject <MKAnnotation, PARObjectDelegate> {
    CLLocation* _location; // geo location of the poi
    double _distanceToCamera;
    double _distanceToUser;
    float _angleToUser;
    float _angleToCamera;
    UIView* _labelView;
    NSString* _labelViewImage;
    UIView* _radarView;
	PARVector4 _enuVector;
    double poiX, poiY, poiZ;
    CGPoint _offset;
    BOOL _useDefaultRadarGfx;
    double e,n,u;
    BOOL _hidden, _stacked;
}

@property (nonatomic, retain) UIView *labelView;
@property (nonatomic, retain) UIView *radarView;
@property (nonatomic, assign) CGPoint offset;

/*! create an empty PARPoi 
 @remarks create and assign @ref labelView before it will show up in the @ref PARView
 @remarks create and assign @ref radarView before it will show up in the @ref PARRadarView 
 @param theLocation @ref CLLocation where the Poi will show up */
- (id)initAtLocation:(CLLocation *)theLocation;

/*! create an PARPoi with the image-name (default radar will be used)
 @param imageName will load an @ref UIImage from the file with the name; uses [UIImage imageNamed]
 @remarks will create an UIImageView as @ref labelView and @ref radarView
 @param theLocation @ref CLLocation where the Poi will show up */
- (id)initWithImage:(NSString *)imageName atLocation:(CLLocation *)theLocation;

- (PARVector4 *)enuVector;

/*! @return YES if labels should be dynamically stacked so not to overlap each other */
- (BOOL)stacksInView;
/*! @return YES if the label should call @ref updateAppearance to dynamically change it's apperance, e.g. based on the distance to the user */
- (BOOL)updatesAppearance;
/*! @return the size of the label used for stacking */
- (CGSize)stackingSize;

#pragma mark - Class Methods
/*! @return YES if default radar gfx (RadarDot.png) should be loaded automatically when creating a new @ref PAR PoiLabel */
+ (BOOL)loadsDefaultRadarGfx;
/*! set to YES if default radar gfx (RadarDot.png) should be loaded automatically when creating a new @ref PAR PoiLabel
 @param theState YES to load default radar gfx*/
+ (void)setLoadsDefaultRadarGfx:(BOOL)theState;

@end
