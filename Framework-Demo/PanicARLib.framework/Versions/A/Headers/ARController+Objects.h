//
//  ARController+Objects.h
//  PanicAR Framework (PanicARLib.framework)
//
//  Created by Andreas Zeitler on 07.08.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@class ARMarker; 
@class ARObject; 

@interface ARController (Objects)


#pragma mark - Management

/*!  adds an ARObject to the controller */
- (void)addObject:(ARObject *)anObject;

/*!  adds an array of ARObject-type Objects to the controller
 Objects need to have locations assign, markers without will be omitted! */
- (void)addObjects:(NSArray *)anArray;

/*!  remove a ARObject object */
- (void)removeObject:(ARObject *)anObject;

/*!  remove all ARObjects from the controller */
- (void)clearObjects;

/*!  returns the number of ARObjects currently added to the Controller */
- (int) numberOfObjects;



#pragma mark - Sorting

- (BOOL)isStackingSlotOccupied:(int)atSlotID inStackingSector:(int)theSectorID;
- (int)getTopmostSlotInStackingSector:(int)theSectorID;
- (void)occupyStackingSlot:(int)slotID inStackingSector:(int)theSectorID;
- (void)sortMarkersByDistance;




#pragma mark - Deprecated  Methods

/*!  adds an ARMarker to the controller Marker needs to have location! */
- (ARMarker *)addMarker:(ARMarker *)marker DEPRECATED_ATTRIBUTE;
/*!  adds the ARMarker at the given location
 @param atLocation: set this location to the marker and add it to the controller
 */
- (ARMarker *)addMarkerAtLocation:(ARMarker *)marker atLocation:(CLLocation *)_location DEPRECATED_ATTRIBUTE;
/*!  adds an array of ARMarker-type Objects to the controller Markers need to have locations assign, markers without will be omitted! */
- (void)addMarkers:(NSArray *)array DEPRECATED_ATTRIBUTE;
/*!  remove a ARMarker object */
- (void)removeMarker:(ARMarker *)object DEPRECATED_ATTRIBUTE;
/*!  remove all ARMarkers from the controller */
- (void)clearMarkers DEPRECATED_ATTRIBUTE;
/*!  returns the number of ARMarkers currently added to the Controller */
- (int) numberOfMarkers DEPRECATED_ATTRIBUTE;

@end