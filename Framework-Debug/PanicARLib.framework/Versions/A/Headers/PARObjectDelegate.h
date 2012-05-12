//
//  PARObjectDelegate.h
//  ArchiApp
//
//  Created by Andreas Zeitler on 05.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import "PARMath.h"

#define CLIP_AT_ANGLE_DEVIATION 35
#define HEAVY_SMOOTH 10
#define LIGHT_SMOOTH 5

@class PARView;
@class PARRadarView;

/*! @protocol PARObjectDelegate */
@protocol PARObjectDelegate

- (void)addedToARController;
- (void)removedFromARController;

- (BOOL)enabled;

/*! unload content when PARView is unloaded */
- (void)unloadContent;
/*! load content when PARView is loaded or displayed and content is not yet loaded */
- (void)loadContent;

- (void)updateLocation;
- (void)updateContent;
- (void)updateAppearance;

- (void)renderInView:(PARView *)theView;
- (void)renderInRadar:(PARRadarView *)theRadar;
- (float)angleToCamera;
- (PARVector3)virtualPosition;
- (float)distanceToUser;

- (CLLocation*)location;
- (void)setLocation:(CLLocation *)theLocation;

- (float)latitude;
- (float)longitude;
- (float)altitude;
- (float)heading;

@end
