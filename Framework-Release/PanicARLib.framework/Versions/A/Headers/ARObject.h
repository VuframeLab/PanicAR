//
//  ARObjectDelegate.h
//  ArchiApp
//
//  Created by Andreas Zeitler on 05.06.11.
//  Copyright 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@class ARVector;

#define CLIP_AT_ANGLE_DEVIATION 35
#define HEAVY_SMOOTH 10
#define LIGHT_SMOOTH 5


@interface ARObject : NSObject {
    
	// virtual space
	ARVector*_virtualPosition; // position
	ARVector*_virtualRotation; // rotation
	ARVector*_virtualSize; // size
    float _virtualScale;
    
    // final open gl output values
	ARVector*_renderPosition;
	ARVector*_renderRotation;
	ARVector*_renderSize;
    
@protected
	BOOL _enabled; // is marker updated?
	BOOL _visible; // is marker visible?
	float _colorID; // color id for touch handling
    UIColor* _color; // color tint of the object
}

@property (nonatomic, retain) ARVector* position;
@property (nonatomic, retain) ARVector* rotation;
@property (nonatomic, retain) ARVector* size;
@property (nonatomic, assign) float scale;

- (BOOL)enabled;
- (BOOL)visible;

- (BOOL)shouldForceTextureReloadOnResume;
- (BOOL)shouldReactionToUserInteraction;

- (float)distance;
- (float)angle;
- (float)elevation;

- (int)colorID;
- (void)setColorID:(int)color;

/** refresh the AR marker (after changing content)
 @param immediately: use to force immediate update, if NO marker will be updated the next time it is rendered
 */
- (void)refresh:(BOOL)immediately;

- (void)freeMemory;

- (void)updateTexture;
- (void)update;

- (void)draw:(float)dt;
- (void)drawInteractionMask;
- (void)drawOnRadar:(float)alpha;


- (void)setPosition:(float)px Y:(float)py Z:(float)pz;
- (void)setRotation:(float)px Y:(float)py Z:(float)pz;
- (void)setSize:(float)px Y:(float)py Z:(float)pz;


@end
