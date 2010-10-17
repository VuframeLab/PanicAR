//
//  ARLabelTemplate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 18.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include "ARMarker.h"

@class ARMarker;

@interface ARLabelTemplate : UIView {
	
	IBOutlet UILabel* title;
	IBOutlet UILabel* content;
	IBOutlet UILabel* distance;
	IBOutlet UIImageView* hitMask;
	IBOutlet UIImageView* image;
	uint hitMaskHandle;
	UIImage* hitMaskTexture;
	float sizeAspect;
}

@property (nonatomic ,assign) IBOutlet UILabel *title;
@property (nonatomic ,assign) IBOutlet UILabel *content;
@property (nonatomic ,assign) IBOutlet UILabel *distance;
@property (nonatomic ,assign) IBOutlet UIImageView *hitMask;
@property (nonatomic ,assign) IBOutlet UIImageView *image;
@property (nonatomic, retain) UIImage *hitMaskTexture;
@property (assign) uint hitMaskHandle;
@property (assign) float sizeAspect;


-(UIImage*) drawLabel:(ARMarker*)marker;
-(void) initHitMask;

+ (ARLabelTemplate*) loadLabelTemplate:(NSString*)xibFilename;
+ (ARLabelTemplate*) loadLabelTemplate:(NSString*)xibFilename aspect:(float)pAspect;

@end
