//
//  MyARViewController.m
//  PanicAR DevApp
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "MyARViewController.h"

@implementation MyARViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"AR", @"AR");
        self.tabBarItem.image = [UIImage imageNamed:@"first"];
        self.navigationItem.title = self.title;
#if DEBUG
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemBookmarks target:self action:@selector(switchConsole:)];
#endif
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
    [super loadView];
    
    if ([self checkForAR:YES]) {
        [[ARController sharedARController] enableConsole];
        [self setRadarRange:1500];
    }
    
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [ARController sharedARController].delegate = self;
    [self createARPoiObjects];
    [self createARContent];
    [self createARBuilding];
    
    [ARController sharedARController].console.hidden = YES;
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


#pragma mark - AR Controller Delegate Methods



- (void)arDidTapObject:(ARObject *)object {
    
}


- (void)arDidReceiveErrorCode:(int)code {
    [self updateInfoLabel];
}



- (void)arDidUpdateLocation {
    [self updateInfoLabel];
}


- (void)arDidChangeOrientation:(UIDeviceOrientation)orientation radarOrientation:(UIDeviceOrientation)radarOrientation {
    
}

- (void)arSignalQualityChanged {
    switch ([ARController sharedARController].userSignalQuality) {
        case 0:
            _signalDisplay.image = [UIImage imageNamed:@"signal4.png"];
            break;
        case 1:
            _signalDisplay.image = [UIImage imageNamed:@"signal3.png"];
            break;
        case 2:
            _signalDisplay.image = [UIImage imageNamed:@"signal2.png"];
            break;
        case 3:
            _signalDisplay.image = [UIImage imageNamed:@"signal1.png"];
            break;
            
        default:
            _signalDisplay.image = [UIImage imageNamed:@"signal0.png"];
            break;
    }
    
    /*
    // optionally: hide GPS meter if signal is fine
    _signalDisplay.hidden = NO;
    
    if ([ARController sharedARController].userSignalQuality < 3) {
        if (!_signalDisplay.hidden) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 3.0 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
                _signalDisplay.hidden = YES;
            });
        }
    }*/
}

- (void)arPreRenderPass {
    
}
- (void)arPostRenderPass {
    
}

- (void)arBeganToTakePicture {
    
}
- (void)arDidTakePicture:(UIImage *)image {
    
}


#pragma mark - DEBUG

#if DEBUG

/*! the console callback only happens with the Debug Build of the Framework */
- (void)arConsoleCallback {
    [self updateInfoLabel];
}
#endif

- (void)updateInfoLabel {
    if ([ARController sharedARController].userLocation == nil) {
        _infoLabel.text = @"could not retrieve location";
        _infoLabel.textColor = [UIColor redColor];
    }
    else {
        if (_hasARBuilding) {
            _infoLabel.text = [NSString stringWithFormat:@"GPS signal quality: %.1d (~%.1f Meters)\ndistance to building: %.1f Meters", [ARController sharedARController].userSignalQuality, [ARController sharedARController].userLocationQuality, [_building distance]];
        }
        else {
            _infoLabel.text = [NSString stringWithFormat:@"GPS signal quality: %.1d (~%.1f Meters)", [ARController sharedARController].userSignalQuality, [ARController sharedARController].userLocationQuality];
        }
        _infoLabel.textColor = [UIColor whiteColor];
    }
}



#pragma mark - Actions

- (IBAction)radarButtonAction {
    CGRect rect = CGRectMake(0, 0, 0, 40);
    if (!radarVisible || radarMode == ARRadarOff) {
        [self showRadarThumbnail:ARRadarPositionTopLeft withAdditionalOffset:rect];
        _radarThumbnailPosition = ARRadarPositionTopLeft;
    }
    else if (radarMode == ARRadarThumbnail) {
        if (_radarThumbnailPosition == ARRadarPositionTopLeft) {
            [self showRadarThumbnail:ARRadarPositionTopRight withAdditionalOffset:rect];
            _radarThumbnailPosition = ARRadarPositionTopRight;
        }
        else if (_radarThumbnailPosition == ARRadarPositionTopRight) {
            [self showRadarThumbnail:ARRadarPositionBottomLeft withAdditionalOffset:rect];
            _radarThumbnailPosition = ARRadarPositionBottomLeft;
        }
        else if (_radarThumbnailPosition == ARRadarPositionBottomLeft) {
            [self showRadarThumbnail:ARRadarPositionBottomRight withAdditionalOffset:rect];
            _radarThumbnailPosition = ARRadarPositionBottomRight;
        }
        else {
            [self showRadarInMode:ARRadarFullscreen];
        }
    }
    else {
        [self hideRadar];
    }
}

- (IBAction)switchConsole:(id)sender { 
    [ARController sharedARController].console.hidden = ![ARController sharedARController].console.hidden;
}



#pragma mark - AR Stuff


// check if AR is available, show error if it's not and set bar item
- (BOOL)checkForAR:(BOOL)showErrors {
    BOOL supportsAR = [ARController deviceSupportsAR];
    BOOL supportsLocations = [ARController locationServicesAvailable];
    BOOL result = supportsLocations && supportsAR;
    
    if (showErrors) {
        if (!supportsAR) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"AR not supported", @"AR not supported")
                                                            message:NSLocalizedString(@"This device does not support AR functionality", @"This device does not support AR functionality")
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"OK", @"OK") 
                                                  otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
        }
        
        if (!supportsLocations) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Error", @"Error")
                                                            message:NSLocalizedString(@"App is not allowed to use GPS", @"App is not allowed to use GPS")
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"OK", @"OK") 
                                                  otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
        }
    }
    
    return result;
}



// create a few test markers
- (void)createARPoiObjects {
    // first: setup a new marker with title and content
    ARPoiLabel* newPoiLabel = [[ARPoiLabel alloc] initWithTitle:@"Rome" theContent:@"Italy" atLocation:[[[CLLocation alloc] initWithLatitude:41.890156 longitude:12.492304] autorelease]];
    
    // second: add the marker to the ARController using the addMarkerAtLocation method
    // pass the geolocation (latitude, longitude) that specifies where the marker should be located
    // WARNING: use double-precision coordinates whenever possible (the following coordinates are from Google Maps which only provides 8-9 digit coordinates
	[[ARController sharedARController] addObject: newPoiLabel];
    
    // add a second marker
    newPoiLabel = [[ARPoiLabel alloc] initWithTitle:@"Berlin" theContent:@"Germany" atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]];
    [[ARController sharedARController] addObject:newPoiLabel];
    
    // add a third marker, this time allocation of a new marker and adding to the ARController are wrapped up in one line
	newPoiLabel = [[ARPoiLabel alloc] initWithTitle:@"London" theContent:@"United Kingdom" atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
    [[ARController sharedARController] addObject:newPoiLabel];
    
    NSLog(@"AR Objects Created: %d", [[ARController sharedARController] numberOfObjects]);
    _hasARPoiObjects = YES;
}


- (void)createARContent {
    ARMesh* scaleMesh = [[ARMesh alloc] initFromFile:@"scale.obj"];
    ARTexture* scale1Texture = [[ARTexture alloc] initFromFile:@"scale1.png"];
    ARTexture* scale2Texture = [[ARTexture alloc] initFromFile:@"scale2.png"];
    
    ARFreeObject* scale = [[ARFreeObject alloc] initWithParams:scaleMesh texture:scale1Texture position:nil rotation:nil size:[ARVector vectorWithCoords:1 Y:0.25 Z:1] scale:0.5];
    [[ARController sharedARController] addObject:scale];
    
    scale = [[ARFreeObject alloc] initWithParams:scaleMesh texture:scale1Texture position:nil rotation:[ARVector vectorWithCoords:90 Y:0 Z:0] size:[ARVector vectorWithCoords:1 Y:0.25 Z:1] scale:0.5];
    [[ARController sharedARController] addObject:scale];
    
    scale = [[ARFreeObject alloc] initWithParams:scaleMesh texture:scale2Texture position:nil rotation:[ARVector vectorWithCoords:0 Y:0 Z:90] size:[ARVector vectorWithCoords:1 Y:0.25 Z:1] scale:0.5];
    [[ARController sharedARController] addObject:scale];
    
    
    ARMesh* cubeMesh = [[ARMesh alloc] initFromFile:@"cube1.obj"];
    ARTexture* cubeTexture = [[ARTexture alloc] initFromFile:@"cube.png"];
    
    ARFreeObject* cube = [[ARFreeObject alloc] initWithParams:cubeMesh texture:cubeTexture position:[ARVector vectorWithCoords:0 Y:0 Z:-10] rotation:nil size:nil scale:1];
    [[ARController sharedARController] addObject:cube];
    
    cube = [[ARFreeObject alloc] initWithParams:cubeMesh texture:cubeTexture position:[ARVector vectorWithCoords:0 Y:0 Z:10] rotation:nil size:nil scale:1];
    [[ARController sharedARController] addObject:cube];
    
    cube = [[ARFreeObject alloc] initWithParams:cubeMesh texture:cubeTexture position:[ARVector vectorWithCoords:10 Y:0 Z:0] rotation:nil size:nil scale:1];
    [[ARController sharedARController] addObject:cube];
    
    cube = [[ARFreeObject alloc] initWithParams:cubeMesh texture:cubeTexture position:[ARVector vectorWithCoords:-10 Y:0 Z:0] rotation:nil size:nil scale:1];
    [[ARController sharedARController] addObject:cube];
    _hasARContent = YES;
}

- (void)createARBuilding {
    ARMesh* buildingMesh = [[ARMesh alloc] initFromFile:@"building.obj"];
    ARTexture* buildingTexture = [[ARTexture alloc] initFromFile:@"building.png"];
    _building = [[ARPoiObject alloc] initWithMesh:buildingMesh andTexture:buildingTexture atLatitude:49.018301 atLongitude:12.095929 atAltitude:320 withHeading:135 withScale:2.5];
    [[ARController sharedARController] addObject:_building];
    _hasARBuilding = YES;
}


@end
