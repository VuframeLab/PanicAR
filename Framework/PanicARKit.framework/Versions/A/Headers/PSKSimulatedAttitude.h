//
//  PSKSimulatedAttitude.h
//  Pods
//
//  Created by Andreas Zeitler on 28.01.13.
//
//

#import "PSKDeviceAttitude.h"
#import <UIKit/UIKit.h>

@interface PSKSimulatedAttitude : PSKDeviceAttitude

/*! shared simulated attitude instance */
+ (PSKSimulatedAttitude *)sharedAttitude;

@property (nonatomic,assign) BOOL simulateLocation;
@property (nonatomic,assign) CLLocationCoordinate2D simulatedCenter;
@property (nonatomic,assign) float simulatedDistance;
@property (nonatomic,assign) float simulatedDirection;

@property (nonatomic,assign) BOOL simulateHeading;
@property (nonatomic,assign) float simulatedHeading;

- (void)makeDirty;
- (BOOL)overridesAnything;

@end
