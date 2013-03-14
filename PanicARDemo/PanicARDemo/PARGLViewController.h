//
//  PARGLViewController.h
//  PanicARKit
//
//  Created by Andreas Zeitler on 24.02.13.
//  copyright 2013 doPanic. All rights reserved.
//

#import <GLKit/GLKit.h>

@class PARMesh;

@interface PARGLViewController : GLKViewController <GLKViewDelegate, PARViewControllerDelegate>

@property (nonatomic, strong, readonly) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *effect;
@property (nonatomic, strong) PARMesh *cubeMesh;

@end
