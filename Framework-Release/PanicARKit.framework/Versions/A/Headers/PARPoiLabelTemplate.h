//
//  PARPoiLabelTemplate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 18.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class PARPoiLabel;
@class PARController;

extern float _appearanceCloseRange, _appearanceFarRange;

/*! @class PARPoiLabelTemplate
 @brief template for how a marker is styled and rendered
 
 1. use PARPoiLabelTemplate as base class for a view in Interface Builder
 2. use Interface Builder to design how your arObjects should look
 3. make all necessary reference connections
 4. save to a *.xib file and load it as a PARPoiLabelTemplate
 5. pass loaded template to any PARPoiLabel you create
 
 @remarks more info at https://github.com/doPanic/PanicAR/wiki */
@interface PARPoiLabelTemplate : UIView {
	
    UILabel* _title;
    UILabel* _content;
    UILabel* _distance;
    UIImageView* _image;
    PARPoiLabel* _poiLabel;
    PARController* _controller;
    CGSize _originalSize;
}

/*! reference to the PARPoiLabel instance this template belongs to */
@property (nonatomic,assign) PARPoiLabel *poiLabel;

/*! UILabel displaying the title of the POI */
@property (nonatomic,assign) IBOutlet UILabel *title;
/*! UILabel displaying the description (i.e. additional text content) of the POI */
@property (nonatomic,assign) IBOutlet UILabel *content;
/*! UILabel displaying a string formated with the distance of the POI of the POI */
@property (nonatomic,assign) IBOutlet UILabel *distance;
/*! UIImageView displaying the image of the POI, if no image is set in POI or no UIImageView is assigned no image will be displayed */
@property (nonatomic,assign) IBOutlet UIImageView *image;

/*! the original size of the label template
 used internally for updating its appearance */
@property (nonatomic,assign) CGSize originalSize;

/*! applys appearance effects to the label based on the current distance to the user and the settings in appearanceCloseRange and appearanceFarRange */
- (void)updateAppearance;


/*! @brief load a Marker Templated from a XIB file
 @param xibFilename name of the marker template xib file */
+ (PARPoiLabelTemplate *)loadMarkerTemplate:(NSString *)xibFilename;

/*! @brief ranges for calculating appearance effects
 @param closeRange if poi label is closer than closeRange no effects will be applied 
 @param farRange animation of effects stops at farRange 
 @remarks defaults to close = 500 meters and far = 100 kilometers
 @remarks the defaul poi label template fades out over distance and gets smaller; implement your own effects in a sub-class */
+ (void)setAppearanceRange:(float)closeRange andFarRange:(float)farRange;
/*! distance at which appearance effects start */
+ (float)appearanceCloseRange;
/*! distance at which appearance effects reach maximum */
+ (float)appearanceFarRange;

@end
