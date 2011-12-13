//
//  ARPoi.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 13.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "ARPoi.h"
#import "ARObject.h"

/*!
 @class ARPoi
 base class for all location-based Points of Interest
 implements MKAnnotation protocol
 */
@interface ARPoi : ARObject <MKAnnotation> {
    CLLocationCoordinate2D coordinate;
}

@end
