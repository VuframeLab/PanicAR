//
//  PARGLViewController.m
//  This advanced demo shows, how to use the attitude
//  information (your devices orientation in the 3D space) delivered by the
//  PanicSensorKit SensorManager (PSKSensorManager) to create an immersive
//  3D Panorama.
//
//  The panorama image (originally: rockhal.jpg) is from http://www.crazy8studio.com
//  and licensed under CC-By-NC http://creativecommons.org/licenses/by-nc/3.0
//
//  Created by Andreas Zeitler on 14.03.13.
//  copyright 2013 doPanic. All rights reserved.
//

#import "PARGLViewController.h"
#import "PARMesh.h"
#import "sphere_low.h"

@interface PARGLViewController ()
@property (nonatomic, strong, readwrite) EAGLContext *context;
@property (strong, nonatomic) NSMutableArray *touches;
@end

@implementation PARGLViewController {
    GLKMatrix4 _projectionMatrix;
    float _rotationX;
    float _rotationY;
    BOOL _gyroEnabled;
}

// temporary storage for the attitude matrix input
static PSKMatrix4x4 attituteMatrixInput;
// temporary storage for the attitude matrix result, use [self attitudeMatrix] to get the attitude matrix, not this
static PSKMatrix4x4 attitudeMatrixResult;
// the matrix used for rotating the sphere object, based on the device/interface orientation
static PSKMatrix4x4 rotationMatrix;

static float _orientationAngle;

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

    _gyroEnabled = YES;
    _touches = [[NSMutableArray alloc] init];
    
    // Register at PanicSensorKit as delegate and for updates on movement
    [[PSKSensorManager sharedSensorManager] setDelegate:self];
    [[PSKSensorManager sharedSensorManager] startForLocationBasedPoiAR];

    // Set angle for adjustment to Interface-Orientation changes depending on orientation
    [self setOrientationAngleFromUIInterfaceOrientation:self.interfaceOrientation];
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormatNone;
    
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

-(void)viewDidAppear:(BOOL)animated{
    [self setOrientationAngleFromUIInterfaceOrientation:self.interfaceOrientation];
        self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
}
-(void)viewWillDisappear:(BOOL)animated{
    self.navigationController.navigationBar.barStyle = UIBarStyleBlackOpaque;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    [self setOrientationAngleFromUIInterfaceOrientation:self.interfaceOrientation];
}

# pragma mark - device attitude - Immersive Panorama Demo
// Set the orientation angle to adapt view to device/interface rotation
- (void)setOrientationAngleFromUIInterfaceOrientation:(UIInterfaceOrientation)orientation {
    switch (orientation) {
        case UIInterfaceOrientationPortraitUpsideDown:
            [self setOrientationAngle:180];
            break;
        case UIInterfaceOrientationLandscapeLeft:
            [self setOrientationAngle:-90];
            break;
        case UIInterfaceOrientationLandscapeRight:
            [self setOrientationAngle:90];
            break;
        case UIInterfaceOrientationPortrait:
            [self setOrientationAngle:0];
            break;
    }

    // update projection matrix
    float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    _projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f),
                                                  aspect,
                                                  0.1f,
                                                  100.0f);
}

- (void)setOrientationAngle:(float)angle {
    _orientationAngle = angle;
    PSKMatrixSetZRotationUsingDegrees(rotationMatrix, _orientationAngle);
}

- (float)orientationAngle {
    return _orientationAngle;
}

- (PSKMatrix4x4 *)attitudeMatrix {
    PSKMatrixCopy(attituteMatrixInput, *[[[PSKSensorManager sharedSensorManager] deviceAttitude] attitudeMatrix]);
    PSKMatrixFastMultiplyWithMatrix(attitudeMatrixResult, rotationMatrix, attituteMatrixInput);
    return &attitudeMatrixResult;
}

#pragma mark - Sensor Delegate
- (void)didChangeDeviceOrientation:(UIDeviceOrientation)orientation{};
- (void)didChangeStatus:(PSKSensorManagerStatus)newStatus {};
- (void)didReceiveErrorCode:(int)code;{};
- (void)didChangeSensorUpdateMode:(PSKSensorManagerUpdateMode)newUpdateMode fromMode:(PSKSensorManagerUpdateMode)oldUpdateMode{};
- (void)didUpdateLocation:(CLLocation *)orignewLocationinalLocation{};
- (void)didUpdateHeading:(CLHeading *)newHeading{};
- (void)didChangeSignalQuality:(PSKSignalQuality)newSignalQuality{};
- (void)didChangeAuthorizationStatus:(CLAuthorizationStatus)status{}

#pragma mark - GLKViewControllerDelegate

- (void)setupGL {
    
    [EAGLContext setCurrentContext:self.context];
    self.effect = [[GLKBaseEffect alloc] init];
    self.sphereMesh = [[PARMesh alloc] initWithEffect:self.effect
                                          andMeshData:sphere_low_MeshVertexData
                                        andMeshLength:sphere_low_Length
                                     andTextureAtPath:[[NSBundle mainBundle] pathForResource:@"panorama" ofType:@"jpg"]
                       ];

    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 0);

    self.effect.transform.modelviewMatrix = modelViewMatrix;
}

- (void)tearDownGL {
    
    [EAGLContext setCurrentContext:self.context];
    
    [self.sphereMesh teardown];
    self.sphereMesh = nil;
    self.effect = nil;
}

- (void)update {
    if(_gyroEnabled){
        GLKMatrix4 tempProjectionMatrix = GLKMatrix4Rotate(_projectionMatrix, _rotationX, 1.0f, 0.0f, 0.0f);
        tempProjectionMatrix = GLKMatrix4Rotate(tempProjectionMatrix, _rotationY, 0.0f, 1.0f, 0.0f);
        // Multiply the attitude into the projection matrix

        tempProjectionMatrix = GLKMatrix4Multiply(tempProjectionMatrix, GLKMatrix4MakeWithArray(*[self attitudeMatrix]));

        // Rotate the projection  matrix by 90 degrees (as part of the conversion from PSK to GLK).
        tempProjectionMatrix = GLKMatrix4Rotate(tempProjectionMatrix, GLKMathDegreesToRadians(90), 1, 0, 0);

        // Update the projection matrix
        self.effect.transform.projectionMatrix = tempProjectionMatrix;}
    else {
        GLKMatrix4 tempProjectionMatrix = GLKMatrix4Rotate(_projectionMatrix, _rotationX, 1.0f, 0.0f, 0.0f);
        tempProjectionMatrix = GLKMatrix4Rotate(tempProjectionMatrix, _rotationY, 0.0f, 1.0f, 0.0f);
        // Update the projection matrix
        self.effect.transform.projectionMatrix = tempProjectionMatrix;
    }
}

#pragma mark - touches

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    float distanceY = [touch locationInView:touch.view].y -
    [touch previousLocationInView:touch.view].y;
    float distanceX = [touch locationInView:touch.view].x -
    [touch previousLocationInView:touch.view].x;
    distanceX *= -0.005;
    distanceY *= -0.005;
    _rotationX += distanceY;
    _rotationY += distanceX;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *touch in touches) {
        [_touches removeObject:touch];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *touch in touches) {
        [_touches addObject:touch];
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *touch in touches) {
        [_touches removeObject:touch];
    }
}



#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    
    glClearColor(0, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    [[self sphereMesh] draw];
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


- (void)setNotification:(NSString *)notification {}

- (void)switchFaceUp:(BOOL)inFaceUp {}

- (void)switchFaceDown:(BOOL)inFaceDown {};

- (IBAction)ResetTouch:(id)sender {
    _rotationX = 0;
    _rotationY = 0;
}
- (IBAction)ToggleGyro:(id)sender forEvent:(UIEvent *)event {
    UISegmentedControl *segmentedControl = (UISegmentedControl *) sender;

    NSLog(@"%d",segmentedControl.selectedSegmentIndex);
        if(segmentedControl.selectedSegmentIndex == 0)
        {
            _gyroEnabled = YES;
        }
        else if(segmentedControl.selectedSegmentIndex == 1)
        {
            _gyroEnabled = NO;
        }
}

@end
