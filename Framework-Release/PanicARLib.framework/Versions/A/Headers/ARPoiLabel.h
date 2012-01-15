//
//  ARPoiLabel.h
//  PanicAR
//
//  Created by Andreas Zeitler on 30.07.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/ES1/glext.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "ARPoi.h"


#define SMALL_DISTANCE_INTERVAL 5.0f
#define LARGE_DISTANCE_INTERVAL 1000.0f

@class ARController;
@class ARPoiLabelTemplate;

extern BOOL _loadsDefaultRadarGfx;

#pragma mark - Interface

/*! @class ARPoiLabel
 @brief marker object to be rendered in the ARController's view */
@interface ARPoiLabel : ARPoi {
    NSString* _title; // title of the marker's infoLabel
    NSString* _description; // title of the marker's infoLabel
    NSString* _distance; // distance of the marker's infoLabel
    UIImage* _image; // image of the marker's infoLabel
    float _lastUpdateAtDistance;
    BOOL _loadedFromNib;
    NSString* _xibFileName;
}

/*! title of the marker (retained) */
@property (nonatomic, retain) NSString *title;

/*! content (description) of the marker (retained) */
@property (nonatomic, retain) NSString *description;

/*! image of the marker (retained)
 depending on the size of the template this can be a icon or thumbnail
 but also a full-sized image */
@property (nonatomic, retain) UIImage *image;

/** @brief create ARPoiLabel with Title
 @param theTitle title of the marker (may not be nil) */
- (id)initWithTitle:(NSString *)theTitle atLocation:(CLLocation *)theLocation;


/** @brief create ARPoiLabel with Title and Description (content)
 @param theTitle title of the marker (may not be nil)
 @param theContent description/content of the marker (may be nil) */
- (id)initWithTitle:(NSString *)theTitle theDescription:(NSString *)theDescription atLocation:(CLLocation *)theLocation;


/** @brief create ARPoiLabel with Title, Description (content) and Image, Title is a mandatory parameter.
 @param theTitle title of the marker (may not be nil)
 @param theContent description/content of the marker (may be nil)
 @param theImage image to be rendered as specified in marker template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil) */
- (id)initWithTitle:(NSString *)theTitle theDescription:(NSString *)theDescription theImage:(UIImage *)theImage atLocation:(CLLocation *)theLocation;


/** create ARPoiLabel at Geolocation with Title, Description (content) and Image, Title is a mandatory parameter. Optional: use a custom template for this marker.
 @param theTitle title of the marker (may not be nil)
 @param theContent description/content of the marker (may be nil)
 @param theImage image to be rendered as specified in marker template, can be used for anything: icon, thumbnail, portrait, etc. (may be nil)
 @param theTemplate template that will be used to render the marker (may be nil); if nil: default template will be used */
- (id)initWithTitle:(NSString *)theTitle theDescription:(NSString *)theDescription theImage:(UIImage *)theImage fromTemplateXib:(NSString *)theTemplateXib atLocation:(CLLocation *)theLocation;



#pragma mark - Class Methods
/*! returns YES if default radar gfx (RadarDot.png) should be loaded automatically when creating a new @ref AR PoiLabel */
+ (BOOL)loadsDefaultRadarGfx;
/*! set to YES if default radar gfx (RadarDot.png) should be loaded automatically when creating a new @ref AR PoiLabel
 @param theState YES to load default radar gfx*/
+ (void)setLoadsDefaultRadarGfx:(BOOL)theState;


@end