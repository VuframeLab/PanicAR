//
//  PARPoiAdvancedLabel.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  copyright 2013 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PARPoiLabel.h"

extern CGPoint _stackingOrigin;

#pragma mark - Interface

/*!  PARPoiAdvancedLabel
 * @brief marker object to be rendered in the PARController's view */
@interface PARPoiAdvancedLabel : PARPoiLabel {
	BOOL _inOrigin;
}

/*!  stacking origin from which new labels are faded in
 * @remarks in percent of the ARViews size
 * @remarks default = (0.5,1), i.e. x=middle,y=bottom of view */
+ (CGPoint)stackingOrigin;

/*!  stacking origin from which new labels are faded in
 * @param x relative x-axis position in view
 * @param y relative y-axis position in view
 * @remarks in percent of the ARViews size
 * @remarks default = (0.5,1), i.e. x=middle,y=bottom of view */
+ (void)setStackingOrigin:(float)x andY:(float)y;


@end
