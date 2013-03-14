//
//  PARGLViewController.m
//  PanicARKit
//
//  Created by Andreas Zeitler on 24.02.13.
//  copyright 2013 doPanic. All rights reserved.
//

#import "PARGLViewController.h"
#import "PARMesh.h"


@interface PARGLViewController ()
@property (nonatomic, strong, readwrite) EAGLContext *context;
@end

@implementation PARGLViewController {
    
    // test
    float _curRed;
    BOOL _increasing;
    float _rotation;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - View lifecycle

- (void)loadView {
    [super loadView];
    
    _increasing = YES;
    _curRed = 0.0;
    
    //self.delegate = self;
    self.preferredFramesPerSecond = 60;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    
    [self setupGL];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

#pragma mark - GLKViewDelegate
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    
    glClearColor(_curRed, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    [self.effect prepareToDraw];
    
    [[self cubeMesh] draw];
}

#pragma mark - GLKViewControllerDelegate

- (void)setupGL {
    
    [EAGLContext setCurrentContext:self.context];
    self.effect = [[GLKBaseEffect alloc] init];
    self.cubeMesh = [[PARMesh alloc] init];
    [[self cubeMesh] setup];
}

- (void)tearDownGL {
    
    [EAGLContext setCurrentContext:self.context];
    
    [self.cubeMesh teardown];
    self.cubeMesh = nil;
    
    self.effect = nil;
}

- (void)update {
    if (_increasing) {
        _curRed += 1.0 * self.timeSinceLastUpdate;
    } else {
        _curRed -= 1.0 * self.timeSinceLastUpdate;
    }
    if (_curRed >= 1.0) {
        _curRed = 1.0;
        _increasing = NO;
    }
    if (_curRed <= 0.0) {
        _curRed = 0.0;
        _increasing = YES;
    }
    
    // set projection matrix
    const float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    const GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 1.0f, 1000.0f);
    self.effect.transform.projectionMatrix = projectionMatrix;
    
    // set model matrix
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, -6.0f);
    _rotation += 90 * self.timeSinceLastUpdate;
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, GLKMathDegreesToRadians(_rotation), 0, 0, 1);
    self.effect.transform.modelviewMatrix = modelViewMatrix;
}


#pragma mark - PARViewControllerDelegate

- (BOOL)fadesInCameraPreview
{
	return YES;
}

- (BOOL)usesCameraPreview
{
	return YES;
}

- (BOOL)startsARAutomatically
{
	return YES;
}

- (BOOL)showARViewInOrientation:(UIDeviceOrientation)orientation {
    return YES;
}

- (BOOL)rotatesARView
{
	return YES;
}

- (float)sizeOfNotification
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        return 256;
    }
	return 128;
}

- (void)setNotification:(NSString *)notification
{
    
}

- (void)switchFaceUp:(BOOL)inFaceUp
{
}

- (void)switchFaceDown:(BOOL)inFaceDown
{
    
}


@end
