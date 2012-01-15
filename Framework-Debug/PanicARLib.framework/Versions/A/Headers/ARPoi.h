//
//  ARPoi.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 13.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "ARMath.h"
#import "ARPoi.h"
#import "ARObjectDelegate.h"

/*!
 @class ARPoi
 base class for all location-based Points of Interest
 implements MKAnnotation protocol
 */
@interface ARPoi : NSObject <MKAnnotation, ARObjectDelegate> {
    CLLocation* _location; // geo location of the poi
    double _distanceToCamera;
    double _distanceToUser;
    float _angleToUser;
    float _angleToCamera;
    UIView* _labelView;
    NSString* _labelViewImage;
    UIView* _radarView;
	ARVector4 _enuVector;
    double poiX, poiY, poiZ;
    CGPoint _offset;
    BOOL _useDefaultRadarGfx;
}

@property (nonatomic, retain) UIView *labelView;
@property (nonatomic, retain) UIView *radarView;
@property (nonatomic, assign) CGPoint offset;

/*! create an empty ARPoi 
 @remarks create and assign @ref labelView before it will show up in the @ref ARView
 @remarks create and assign @ref radarView before it will show up in the @ref ARRadarView 
 @param theLocation @ref CLLocation where the Poi will show up */
- (id)initAtLocation:(CLLocation *)theLocation;

/*! create an ARPoi with the image-name (default radar will be used)
 @param imageNamed will load an @ref UIImage from the file with the name; uses [UIImage imageNamed..]
 @remarks will create an UIImageView as @ref labelView and @ref radarView
 @param theLocation @ref CLLocation where the Poi will show up */
- (id)initWithImage:(NSString *)imageName atLocation:(CLLocation *)theLocation;

- (ARVector4 *)enuVector;

/*! return YES if label should rotate dynamically to all orientation changes */
- (BOOL)rotateInView;

@end
