//
//  PARPoiLabel.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  copyright 2013 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PARPoi.h"

#define SMALL_DISTANCE_INTERVAL 5.0f
#define LARGE_DISTANCE_INTERVAL 1000.0f

@class PARController;
@class PARPoiLabelTemplate;


#pragma mark - Interface

/*!  PARPoiLabel
 * @brief marker object to be rendered in the PARController's view */
@interface PARPoiLabel : PARPoi {
	NSString *_title;                                            // title of the labels
	NSString *_description;                                      // title of the labels
	NSString *_distance;                                         // distance of the labels
	UIImage *_image;                                             // image of the labels
	float _lastUpdateAtDistance;
	BOOL _loadedFromNib;
	PARPoiLabelTemplate *_labelTemplate;
	NSString *_xibFileName;
	CGSize _stackingSize;
}



/*! title of the marker (retained) */
@property (nonatomic, strong) NSString *title;

/*! content (description) of the marker (retained) */
@property (nonatomic, strong) NSString *description;

/*! image of the marker (retained)
 * depending on the size of the template this can be a icon or thumbnail
 * but also a full-sized image */
@property (nonatomic, strong) UIImage *image;

/** @brief create PARPoiLabel with Title
 * @param theTitle title of the label (may not be nil)
 * @param theLocation location of the label (may not be nil) */
- (id)initWithTitle:(NSString *)theTitle atLocation:(CLLocation *)theLocation;


/** @brief create PARPoiLabel with Title and Description (content)
 * @param theTitle title of the label (may not be nil)
 * @param theDescription description of the label (may be nil)
 * @param theLocation location of the label (may not be nil) */
- (id)initWithTitle:(NSString *)theTitle theDescription:(NSString *)theDescription atLocation:(CLLocation *)theLocation;


/** @brief create PARPoiLabel with Title, Description (content) and Image, Title is a mandatory parameter.
 * @param theTitle title of the label (may not be nil)
 * @param theDescription description of the label (may be nil)
 * @param theImage image to be rendered as specified in label template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 * @param theLocation location of the label (may not be nil) */
- (id)initWithTitle:(NSString *)theTitle theDescription:(NSString *)theDescription theImage:(UIImage *)theImage atLocation:(CLLocation *)theLocation;


/** create PARPoiLabel at Geolocation with Title, Description (content) and Image, Title is a mandatory parameter. Optional: use a custom template for this marker.
 * @param theTitle title of the label (may not be nil)
 * @param theDescription description of the label (may be nil)
 * @param theImage image to be rendered as specified in label template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 * @param theTemplateXib name of XIB-template-file from which the marker will be loaded; if nil: default template (DefaultPoiLabel.xib) will be used
 * @param theLocation location of the label (may not be nil) */
- (id)initWithTitle:(NSString *)theTitle theDescription:(NSString *)theDescription theImage:(UIImage *)theImage fromTemplateXib:(NSString *)theTemplateXib atLocation:(CLLocation *)theLocation;






@end
