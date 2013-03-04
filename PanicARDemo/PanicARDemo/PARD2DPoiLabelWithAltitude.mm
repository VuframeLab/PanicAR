//
//  PARD2DPoiLabelWithAltitude.mm
//  PanicARDemo
//
//  An Extension of the PARPoiLabel that also includes altitude information
//
//  Created by Andreas Zeitler on 26.02.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

#import "PARD2DPoiLabelWithAltitude.h"

@implementation PARD2DPoiLabelWithAltitude

// turn off auto-layout and stacking
- (BOOL)stacksInView {
    return NO;
}

// calculate the altitude of the label on screen
- (void)updateLocation {
    [super updateLocation]; // super will calculate label position
	_worldPosition.z = -(self.altitude - [[PSKSensorManager sharedSensorManager] deviceAttitude].locationAltitude); // we add altitude here
}

// add height above sea level to displayed content
- (void)updateContent {
    [super updateContent];
    const float distance = floorf(self.distanceToUser / LARGE_DISTANCE_INTERVAL);
    _distance = [NSString stringWithFormat:@"%1.f km at %.1f m", distance, self.altitude];
    _labelTemplate.distance.text = _distance;
}

@end
