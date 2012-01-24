//
//  PARPoiAdvancedLabel.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PARPoiLabel.h"

extern CGPoint _stackingOrigin;

#pragma mark - Interface

/*! @class PARPoiAdvancedLabel
 @brief marker object to be rendered in the PARController's view */
@interface PARPoiAdvancedLabel : PARPoiLabel {
    BOOL _inOrigin;
}

/*! @property stacking origin from which new labels are faded in
 @remarks in percent of the ARViews size
 @remarks default = (0.5,1), i.e. x=middle,y=bottom of view */
+ (CGPoint)stackingOrigin;
+ (void)setStackingOrigin:(float)x andY:(float)y;


@end