//
//  PARPoiFactory.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 12.09.12.
//  Copyright (c) 2012 doPanic. All rights reserved.
//

#import "PSKDeviceProperties.h"
#import "PSKSensorManager.h"

/*! 
 @class PARPoiFactory
 @abstract provides methods to create POI objects for testing purposes
 */
@interface PARPoiFactory : NSObject
+ (void)setPoiClass:(Class)poiClass;
+ (void)createAtHeading:(float)theHeading withDistance:(float)theDistance;
+ (void)createAroundUser:(int)count;
+ (void)createAroundUser:(double)angleBetweenLabels atDistanceIntervals:(double)distanceInterval inRows:(int)numberOfRows;
+ (void)createAroundUser:(double)angleBetweenLabels andOffsetAngle:(double)angleOffset atDistance:(double)distance;
+ (void)createRandom:(int)count;
+ (void)createCitiesAroundUser:(int)count;
@end
