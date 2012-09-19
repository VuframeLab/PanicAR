//
//  PARController+Objects.h
//  PanicAR Framework (PanicARLib.framework)
//
//  Created by Andreas Zeitler on 07.08.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PARObjectDelegate.h"

@class PARPoiLabel; 

/*!
 @name Object Management
 */

@interface PARController (Objects)


#pragma mark - Management

/*!  adds an object to the controller
 @param anObject the object to add (implements @ref PARObjectDelegate)
 */
- (void)addObject:(id<PARObjectDelegate>)anObject;

/*!  adds an array of PARObjectDelegate-type Objects to the controller
 Objects need to have locations assign, markers without will be omitted! 
 @param anArray the collection of objects to be added
 */
- (void)addObjects:(NSArray *)anArray;

/*!  remove an PARObjectDelegate object 
 @param anObject the object to add (implements @ref PARObjectDelegate) */
- (void)removeObject:(id<PARObjectDelegate>)anObject;

/*!  remove all objects from the controller */
- (void)clearObjects;

/*! @return the number of objects currently added to the Controller */
- (int) numberOfObjects;



#pragma mark - Sorting
- (void)updateAfterLocationChange;
- (void)sortMarkersByDistance;




#ifdef PANICAR_LEGACY
#pragma mark - Deprecated  Methods

/*! adds an PARPoiLabel to the controller Marker needs to have location! */
- (PARPoiLabel *)addMarker:(PARPoiLabel *)marker  __attribute__ ((deprecated));
/*!  adds the PARPoiLabel at the given location
 @param atLocation: set this location to the marker and add it to the controller
 */
- (PARPoiLabel *)addMarkerAtLocation:(PARPoiLabel *)marker atLocation:(CLLocation *)_location  __attribute__ ((deprecated));
/*! adds an array of PARPoiLabel-type Objects to the controller Markers need to have locations assign, markers without will be omitted! */
- (void)addMarkers:(NSArray *)array  __attribute__ ((deprecated));
/*!  remove a PARPoiLabel object */
- (void)removeMarker:(PARPoiLabel *)object  __attribute__ ((deprecated));
/*!  remove all PARPoiLabels from the controller */
- (void)clearMarkers  __attribute__ ((deprecated));
/*!  @return  the number of PARPoiLabels currently added to the Controller */
- (int) numberOfMarkers  __attribute__ ((deprecated));
#endif 

@end