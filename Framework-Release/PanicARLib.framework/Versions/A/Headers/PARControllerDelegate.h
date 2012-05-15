//
//  PARControllerDelegate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 01.09.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import "PARObjectDelegate.h"


@class PARPoiLabel;

/*! 
 @protocol PARControllerDelegate
 @brief protocol that handles PARController callbacks
 
 the PARControllerDelegate enables any class implementing it
 to receive events from the PARController instance (like the touch event of an PARPoiLabel)
 */
@protocol PARControllerDelegate


/** Object Interaction Callback 
 sent to the delegate when a object is tapped
 @param object the object that was tapped */
- (void)arDidTapObject:(id<PARObjectDelegate>)object;

@optional
- (void)arPreRenderPass;
- (void)arPostRenderPass;

- (void)arBeganToTakePicture;
- (void)arDidTakePicture:(UIImage *)image;

@end
