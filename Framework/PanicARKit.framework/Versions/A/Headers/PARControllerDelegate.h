//
//  PARControllerDelegate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 01.09.10.
//  copyright 2013 doPanic. All rights reserved.
//

#import "PARObjectDelegate.h"


@class PARPoiLabel;

/*!
 * @protocol PARControllerDelegate
 * @brief protocol that handles PARController callbacks
 *
 * the PARControllerDelegate enables any class implementing it
 * to receive events from the PARController instance (like the touch event of an PARPoiLabel)
 */
@protocol PARControllerDelegate

/** Object Interaction Callback
 * sent to the delegate when a object is tapped
 * @param object the object that was tapped */
- (void)arDidTapObject:(id<PARObjectDelegate>)object;

@end
