//
//  ARView.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 30.12.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ARObjectDelegate.h"
#import "ARMath.h"



@class ARController;
@class ARPoi;
@class ARViewController;


extern ARView* _activeView;

@interface ARView : UIView {
	ARController* _arController;
	ARViewController* _arViewController;
	id<ARObjectDelegate> _currentObject;
    
	ARMatrix4x4 _perspectiveMatrix;
	ARMatrix4x4 _perspectiveCameraMatrix;
}


@property (nonatomic, retain) ARViewController* arViewController;
- (ARMatrix4x4*) perspectiveCameraMatrix;


#pragma mark - Main
- (void)start;
- (void)stop;




#pragma mark - Utilities
- (UIImage *)renderToImageWithSize:(float)theWidth Height:(float)theHeight;

#pragma mark - Class Methods
+ (void)setActiveView:(ARView *)theView;
+ (ARView *)activeView;

@end
