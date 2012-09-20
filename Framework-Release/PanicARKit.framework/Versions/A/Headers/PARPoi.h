//
//  PARPoi.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 13.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "PSKMath.h"
#import "PARObjectDelegate.h"

extern BOOL _loadsDefaultRadarGfx;
extern float _stackingAnimationSpeed;
extern float _labelBaseline;
extern float _clipObjectFarLimit;
extern float _clipObjectNearLimit;
extern BOOL _viewIsLandscape;
extern float _viewGravityX;
extern float _viewGravityY;
extern PSKVector3 _deviceGravity;

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
    PSKMatrix4x4 _toUserRotation;
    
    float _angleToCamera;
    UIView* _labelView;
    NSString* _labelViewImage;
    UIView* _radarView;
	PSKVector4 _enuVector;
    PSKVector4 _worldToScreenSpace;
    PSKVector3 _worldToRadarSpace;
    
    double poiX, poiY, poiZ;
    CGPoint _relativeScreenPosition;
    CGPoint _center;
    BOOL _useDefaultRadarGfx;
    double _enuVectorE, _enuVectorN, _enuVectorU;
    
    BOOL _hidden;
    BOOL _stacked;
    BOOL _clippedByDistance;
    BOOL _clippedByViewport;
    BOOL _addedToView;
    BOOL _addedToRadar;
}

/*! create an empty PARPoi 
 @remarks create and assign @ref labelView before it will show up in the @ref PARView
 @remarks create and assign @ref radarView before it will show up in the @ref PARRadarView 
 @param theLocation @ref CLLocation where the Poi will show up */
- (id)initAtLocation:(CLLocation *)theLocation;

/*! create an PARPoi with the image-name (default radar will be used)
 @param imageName will load an @ref UIImage from the file with the name; uses UIImage +imageNamed
 @remarks will create an UIImageView as @ref labelView and @ref radarView
 @param theLocation @ref CLLocation where the Poi will show up */
- (id)initWithImage:(NSString *)imageName atLocation:(CLLocation *)theLocation;


#pragma mark - Properties
@property (nonatomic, retain) UIView *labelView;

@property (nonatomic, retain) UIView *radarView;

@property (nonatomic, assign) CGPoint offset;

- (void)setHidden:(BOOL)hidden;

- (PSKVector4 *)enuVector;

- (BOOL)clippedByDistance;


#pragma mark - Setting Methods
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
