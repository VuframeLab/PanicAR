//
//  PARSensorDelegate.h
//  AR-Architect
//
//  Created by Andreas Zeitler on 29.02.12.
//  Copyright (c) 2012 doPanic GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol PARSensorDelegate <NSObject>


/** PAR System Error Callback 
 sent to the delegate when an error occured
 this will most likely be caused by an error in the locationManager
 @param code constant of the error code
 error types:
 kCLErrorLocationUnknown
 kCLErrorDenied
 kCLErrorNetwork
 */
- (void)arDidReceiveErrorCode:(int)code;


/** Info Update Callback
 sent to delegate when location or heading changes
 use this to change the output in the infoLabel or to perform other output functions
 */
- (void)arDidUpdateLocation;
- (void)arDidUpdateHeading;

/** Device Orientation Changed Callback
 sent to delegate when arOrientation changed, use it to adjust PAR views (like radar)
 @param orientation the new orientation */
- (void)arDidChangeOrientation:(UIInterfaceOrientation)orientation;

- (void)arSignalQualityChanged;

@end
