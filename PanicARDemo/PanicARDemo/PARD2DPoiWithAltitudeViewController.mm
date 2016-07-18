//
//  PARD2DPoiViewController.m
//  PanicARDemo
//
// Basic example of UIKit-driven rendering of Points of Interest
// uses real altitude (no stacking/layout)
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 Vuframe Lab GmbH. All rights reserved.
//

#import "PARD2DPoiWithAltitudeViewController.h"
#import "PARD2DPoiLabelWithAltitude.h"

@implementation PARD2DPoiWithAltitudeViewController {
    BOOL _createdInitialObjects;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        _createdInitialObjects = NO;
    }
    return self;
}

- (void)didUpdateLocation:(CLLocation *)newLocation {
    [super didUpdateLocation:newLocation];
    if (newLocation) {
        if (!_hasARPoiObjects && ! _createdInitialObjects) {
            [self createARPoiObjects];
            _createdInitialObjects = YES;
            _hasARPoiObjects =YES;
        }
    }
}

// override: create a few test poi objects usin PARPoiFactory
- (void)createARPoiObjects {
    // first clear old objects
    [[PARController sharedARController] clearObjects];
    
    // check if user location is already determined
    CLLocation* userLocation = [[[PSKSensorManager sharedSensorManager] deviceAttitude] location];
    if (!userLocation || userLocation.coordinate.latitude == 0 || userLocation.coordinate.longitude == 0) {
        return; // exit if user location is not yet determined
        // we only do this because we later call [PARPoiFactory createRandom:32] which uses the user's position to scatter the generated POIs
    }
    
    // now create new ones
    Class poiLabelClass = [PARD2DPoiLabelWithAltitude class];
    
    [PARPoiFactory setPoiClass:poiLabelClass];
    [PARPoiFactory createRandom:32];
    for (PARD2DPoiLabelWithAltitude * poi in [[PARController sharedARController] arObjects]) {
        poi.altitude = randomRangef(0, 13000); // random altitude between 0 and 40.000 feet (specified in meters)
        NSLog(@"POI at %f", poi.altitude);
    }
    
    NSLog(@"PAR Objects Created: %d", [[PARController sharedARController] numberOfObjects]);
    _hasARPoiObjects = YES;
}

- (BOOL)showARViewInOrientation:(UIDeviceOrientation)orientation {
    return orientation != UIDeviceOrientationFaceUp;
}

- (void)switchFaceDown:(BOOL)inFaceDown {
    // make sure this is an empty call; otherwise the PARViewController will display a HUD text once the device goes into UIDeviceOrientationFaceDown (which it will when the user looks up)
}

@end
