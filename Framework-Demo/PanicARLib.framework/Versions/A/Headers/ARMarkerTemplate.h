//
//  ARMarkerTemplate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 18.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class ARMarker;

/*! @class ARMarkerTemplate
 @brief template for how a marker is styled and rendered
 
 1. use ARMarkerTemplate as base class for a view in Interface Builder
 2. use Interface Builder to design how your arObjects should look
 3. make all necessary reference connections
 4. save to a *.xib file and load it as a ARMarkerTemplate
 5. pass loaded template to any ARMarker you create
 */
@interface ARMarkerTemplate : UIView {
	
	IBOutlet UILabel* title;
	IBOutlet UILabel* content;
	IBOutlet UILabel* distance;
	IBOutlet UIImageView* hitMask;
	IBOutlet UIImageView* image;
	uint hitMaskHandle;
	UIImage* hitMaskTexture;
	float _aspectRatio;
    float _size;
}

@property (nonatomic ,assign) IBOutlet UILabel *title;
@property (nonatomic ,assign) IBOutlet UILabel *content;
@property (nonatomic ,assign) IBOutlet UILabel *distance;
@property (nonatomic ,assign) IBOutlet UIImageView *hitMask;
@property (nonatomic ,assign) IBOutlet UIImageView *image;
@property (nonatomic, retain) UIImage *hitMaskTexture;
@property (assign) uint hitMaskHandle;
@property (assign) float aspectRatio;
@property (assign) float size;


- (UIImage *)drawMarker:(ARMarker *)marker;
- (void)initHitMask;


/*!  load a Marker Templated from a XIB file */
+ (ARMarkerTemplate *)loadMarkerTemplate:(NSString *)xibFilename;

/*!  load a Marker Templated from a XIB file and force it to be displayed in aspect 
 @param aspect: vertical size of the marker template (height / width) 
 */
+ (ARMarkerTemplate *)loadMarkerTemplate:(NSString *)xibFilename aspect:(float)pAspect;

/*!  load a Marker Templated from a XIB file and force it to be displayed in aspect 
 @param aspect: vertical size of the marker template (height / width) 
 */
+ (ARMarkerTemplate *)loadMarkerTemplate:(NSString *)xibFilename size:(float)theSize aspect:(float)pAspect;//stackingHeight:(float)theHeight;

@end
