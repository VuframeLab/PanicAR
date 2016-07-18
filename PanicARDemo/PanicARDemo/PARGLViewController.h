//
//  PARGLViewController.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 24.02.13.
//  copyright 2013 Vuframe Lab GmbH. All rights reserved.
//

#import <GLKit/GLKit.h>

@class PARMesh;

@interface PARGLViewController : GLKViewController <GLKViewDelegate, PARViewControllerDelegate, PSKSensorDelegate>

@property (nonatomic, strong, readonly) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *effect;

- (IBAction)ResetTouch:(id)sender;
- (IBAction)ToggleGyro:(id)sender forEvent:(UIEvent *)event;

@property (nonatomic, strong) PARMesh *sphereMesh;


@end
