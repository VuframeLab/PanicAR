//
//  ARObjectDelegate.h
//  ArchiApp
//
//  Created by Andreas Zeitler on 05.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import "ARMath.h"

#define CLIP_AT_ANGLE_DEVIATION 35
#define HEAVY_SMOOTH 10
#define LIGHT_SMOOTH 5

@class ARView;
@class ARRadarView;

@protocol ARObjectDelegate

/*! unload content when ARView is unloaded */
- (void)unloadContent;
/*! load content when ARView is loaded or displayed and content is not yet loaded */
- (void)loadContent;

- (void)updateLocation;
- (void)updateContent;

- (void)renderInView:(ARView *)theView;
- (void)renderInRadar:(ARRadarView *)theRadar;
- (float)angleToCamera;
- (ARVector3)virtualPosition;
- (float)distanceToUser;

- (CLLocation*)location;
- (void)setLocation:(CLLocation *)theLocation;

- (float)latitude;
- (float)longitude;
- (float)altitude;
- (float)heading;

@end
