//
//  PARController+Objects.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 07.08.11.
//  copyright 2013 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PARObjectDelegate.h"

@class PARPoiLabel;

/*!
 * @name Object Management
 */

@interface PARController (Objects)


#pragma mark - Management

/*!  adds an object to the controller
 * @param anObject the object to add (implements @ref PARObjectDelegate)
 */
- (void)addObject:(id<PARObjectDelegate>)anObject;

/*!  adds an array of PARObjectDelegate-type Objects to the controller
 * Objects need to have locations assign, markers without will be omitted!
 * @param anArray the collection of objects to be added
 */
- (void)addObjects:(NSArray *)anArray;

/*!  remove an PARObjectDelegate object
 * @param anObject the object to add (implements @ref PARObjectDelegate) */
- (void)removeObject:(id<PARObjectDelegate>)anObject;

/*!  remove all objects from the controller */
- (void)clearObjects;

/*! @return the number of objects currently added to the Controller */
- (int)numberOfObjects;






#ifdef PANICAR_LEGACY
#pragma mark - Deprecated  Methods

/*! adds an PARPoiLabel to the controller Marker needs to have location!
 * @param marker the marker to be added */
- (PARPoiLabel *)addMarker:(PARPoiLabel *)marker  __attribute__ ((deprecated));
/*!  adds the PARPoiLabel at the given location
 * @param marker the marker to be added
 * @param _location the CLLocation
 * @ref addObject
 */
- (PARPoiLabel *)addMarkerAtLocation:(PARPoiLabel *)marker atLocation:(CLLocation *)_location  __attribute__ ((deprecated));
/*! adds an array of PARPoiLabel-type Objects to the controller Markers need to have locations assign, markers without will be omitted!
 * @param array the array of markers to be added
 * @ref addObjects */
- (void)addMarkers:(NSArray *)array  __attribute__ ((deprecated));
/*!  remove a PARPoiLabel object
 * @param object the marker to be added
 * @ref removeObject */
- (void)removeMarker:(PARPoiLabel *)object  __attribute__ ((deprecated));
/*!  remove all PARPoiLabels from the controller
 * @ref clearObjects */
- (void)clearMarkers  __attribute__ ((deprecated));
/*!  @return  the number of PARPoiLabels currently added to the Controller
 * @ref numberOfObjects */
- (int)numberOfMarkers  __attribute__ ((deprecated));
#endif

@end
