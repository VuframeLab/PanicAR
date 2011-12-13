//
//  ARPoiLabelTemplate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 18.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class ARPoiLabel;

/*! @class ARPoiLabelTemplate
 @brief template for how a marker is styled and rendered
 
 1. use ARPoiLabelTemplate as base class for a view in Interface Builder
 2. use Interface Builder to design how your arObjects should look
 3. make all necessary reference connections
 4. save to a *.xib file and load it as a ARPoiLabelTemplate
 5. pass loaded template to any ARPoiLabel you create
 */
@interface ARPoiLabelTemplate : UIView {
	
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


- (UIImage *)drawMarker:(ARPoiLabel *)marker;
- (void)initHitMask;


/*! @brief load a Marker Templated from a XIB file
 @param xibFilename name of the marker template xib file 
 @remarks assumes aspect of 1.0 and size of 50
 */
+ (ARPoiLabelTemplate *)loadMarkerTemplate:(NSString *)xibFilename;

/*!  load a Marker Templated from a XIB file and force it to be displayed in aspect 
 @param xibFilename name of the marker template xib file
 @param pAspect vertical size of the marker template (height / width) 
 @remarks assumes size of 50
 */
+ (ARPoiLabelTemplate *)loadMarkerTemplate:(NSString *)xibFilename aspect:(float)pAspect;

/*!  load a Marker Templated from a XIB file and force it to be displayed in aspect 
 @param xibFilename name of the marker template xib file
 @param theSize the size of the marker
 @param pAspect vertical size of the marker template (height / width) 
 @remarks default size for a marker is 50
 */
+ (ARPoiLabelTemplate *)loadMarkerTemplate:(NSString *)xibFilename size:(float)theSize aspect:(float)pAspect;//stackingHeight:(float)theHeight;

@end
