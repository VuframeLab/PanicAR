//
//  ARControllerDelegate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 01.09.10.
//  Copyright 2010 doPanic. All rights reserved.
//



@class ARMarker;

/*! 
 @protocol ARControllerDelegate
 @brief protocol that handles ARController callbacks
 
 the ARControllerDelegate enables any class implementing it
 to receive events from the ARController instance (like the touch event of an ARMarker)
 */
@protocol ARControllerDelegate


/** Marker Interaction Callback 
 sent to the delegate when a marker is tapped
 */
- (void) arDidTapMarker:(ARMarker*)marker;


/** AR System Error Callback 
 sent to the delegate when an error occured
 this will most likely be caused by an error in the locationManager
 
 error types:
 kCLErrorLocationUnknown
 kCLErrorDenied
 kCLErrorNetwork
 */
- (void) arDidReceiveErrorCode:(int)code;


/** Info Update Callback
 sent to delegate when location or heading changes
 use this to change the output in the infoLabel or to perform other output functions
 */
- (void) arDidUpdateLocation;

/** Device Orientation Changed Callback
 sent to delegate when arOrientation changed, use it to adjust AR views (like radar)
 */
- (void) arDidChangeOrientation:(UIDeviceOrientation)orientation radarOrientation:(UIDeviceOrientation)radarOrientation;

@end
