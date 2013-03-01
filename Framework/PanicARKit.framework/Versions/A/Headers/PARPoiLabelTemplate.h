//
//  PARPoiLabelTemplate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 18.08.10.
//  copyright 2013 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class PARPoiLabel;
@class PARController;

extern float _appearanceCloseRange, _appearanceFarRange;

/*!  PARPoiLabelTemplate
 * @brief template for how a marker is styled and rendered
 *
 * 1. use PARPoiLabelTemplate as base class for a view in Interface Builder
 * 2. use Interface Builder to design how your arObjects should look
 * 3. make all necessary reference connections
 * 4. save to a *.xib file and load it as a PARPoiLabelTemplate
 * 5. pass loaded template to any PARPoiLabel you create
 *
 * @remarks more info at https://github.com/doPanic/PanicAR/wiki */
@interface PARPoiLabelTemplate : UIView {
	UILabel *__weak _title;
	UILabel *__weak _content;
	UILabel *__weak _distance;
	UIImageView *__weak _image;
	PARPoiLabel *__weak _poiLabel;
	PARController *_controller;
	CGSize _originalSize;
}

/*! reference to the PARPoiLabel instance this template belongs to */
@property (nonatomic, weak) PARPoiLabel *poiLabel;

/*! UILabel displaying the title of the POI */
@property (nonatomic, weak) IBOutlet UILabel *title;
/*! UILabel displaying the description (i.e. additional text content) of the POI */
@property (nonatomic, weak) IBOutlet UILabel *content;
/*! UILabel displaying a string formated with the distance of the POI of the POI */
@property (nonatomic, weak) IBOutlet UILabel *distance;
/*! UIImageView displaying the image of the POI, if no image is set in POI or no UIImageView is assigned no image will be displayed */
@property (nonatomic, weak) IBOutlet UIImageView *image;

/*! the original size of the label template
 * used internally for updating its appearance */
@property (nonatomic, assign) CGSize originalSize;

/*! applys appearance effects to the label based on the current distance to the user and the settings in appearanceCloseRange and appearanceFarRange */
- (void)updateAppearance;

- (IBAction)labelTappedAction:(id)sender;

/*! @brief load a Marker Templated from a XIB file
 * @param xibFilename name of the marker template xib file
 * @ref loadPoiLabelTemplate */
+ (PARPoiLabelTemplate *)loadMarkerTemplate:(NSString *)xibFilename  __attribute__ ((deprecated));
/*! @brief load a Marker Templated from a XIB file
 * @param xibFilename name of the marker template xib file */
+ (PARPoiLabelTemplate *)loadPoiLabelTemplate:(NSString *)xibFilename;
/*! @brief load a Marker Templated from a XIB file in bundle
 * @param xibFilename name of the marker template xib file
 * @param bundle is the NSBundle the nib file will be loaded from */
+ (PARPoiLabelTemplate *)loadPoiLabelTemplate:(NSString *)xibFilename fromBundle:(NSBundle *)bundle;

/*! @brief ranges for calculating appearance effects
 * @param closeRange if poi label is closer than closeRange no effects will be applied
 * @param farRange animation of effects stops at farRange
 * @remarks defaults to close = 500 meters and far = 100 kilometers
 * @remarks the defaul poi label template fades out over distance and gets smaller; implement your own effects in a sub-class */
+ (void)setAppearanceRange:(float)closeRange andFarRange:(float)farRange;
/*! distance at which appearance effects start */
+ (float)appearanceCloseRange;
/*! distance at which appearance effects reach maximum */
+ (float)appearanceFarRange;

@end
