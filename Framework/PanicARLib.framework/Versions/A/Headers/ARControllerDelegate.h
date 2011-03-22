//
//  ARControllerDelegate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 01.09.10.
//  Copyright 2010 doPanic. All rights reserved.
//



@class ARMarker;

/*! @class ARControllerDelegate
 @brief protocol that handles ARController callbacks
 
 the ARControllerDelegate enables any class implementing it
 to receive events from the ARController instance (like the touch event of an ARMarker)
 */
@protocol ARControllerDelegate
- (void) markerTapped:(ARMarker*)marker;
@end
