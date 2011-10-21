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
        
        _radarMode = RadarSmall;
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
        [[ARController sharedARController] enableRadar];
        [[ARController sharedARController] setRadarRange:5*1000];
    }
    
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [ARController sharedARController].delegate = self;
    [self createARMarkers];
    [self createARContent];
    [self createARBuilding];
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
    return YES;//(interfaceOrientation == UIInterfaceOrientationPortrait);
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
- (void)arConsoleCallback {
    [self updateInfoLabel];
    
}


- (void)updateInfoLabel {
    if ([ARController sharedARController].userLocation == nil) {
        _infoLabel.text = @"could not retrieve location";
        _infoLabel.textColor = [UIColor redColor];
    }
    else {
        _infoLabel.text = [NSString stringWithFormat:@"GPS signal quality: %d ~%f Meters", [ARController sharedARController].userSignalQuality, [ARController sharedARController].userLocationQuality];
        _infoLabel.textColor = [UIColor whiteColor];
    }
}
#endif



#pragma mark - Actions

- (IBAction)radarButtonAction {
    switch (_radarMode) {
        case RadarOff:
            _radarMode = RadarSmall;
            [_arView showRadar];
            [_arView setRadarToThumbnail];
            break;
            
        case RadarSmall:
            _radarMode = RadarFullscreen;
            [_arView setRadarToFullscreen];
            break;
            
        case RadarFullscreen:
            _radarMode = RadarOff;
            [_arView hideRadar];
            break;
            
        default:
            break;
    }
}



#pragma mark - AR Stuff


// check if AR is available, show error if it's not and set bar item
- (BOOL)checkForAR:(BOOL)showErrors {
    BOOL supportsAR = [ARController deviceSupportsAR];
    BOOL supportsLocations = [ARController locationServicesAvailable];
    BOOL result = supportsLocations && supportsAR;
    
    /*arBarItem.enabled = result;
     if (!result) {
     [tabBarController setSelectedIndex:1];
     }*/
    
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
- (void)createARMarkers {
    // first: setup a new marker with title and content
    ARMarker* newMarker = [[ARMarker alloc] initWithTitle:@"Rome" theContent:@"Italy" atLocation:[[[CLLocation alloc] initWithLatitude:41.890156 longitude:12.492304] autorelease]];
    
    // second: add the marker to the ARController using the addMarkerAtLocation method
    // pass the geolocation (latitude, longitude) that specifies where the marker should be located
    // WARNING: use double-precision coordinates whenever possible (the following coordinates are from Google Maps which only provides 8-9 digit coordinates
	[[ARController sharedARController] addObject: newMarker];
    
    // add a second marker
    newMarker = [[ARMarker alloc] initWithTitle:@"Berlin" theContent:@"Germany" atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]];
    [[ARController sharedARController] addObject:newMarker];
    
    // add a third marker, this time allocation of a new marker and adding to the ARController are wrapped up in one line
	newMarker = [[ARMarker alloc] initWithTitle:@"London" theContent:@"United Kingdom" atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
    [[ARController sharedARController] addObject:newMarker];
    
    NSLog(@"AR Objects Created: %d", [[ARController sharedARController] numberOfObjects]);
}


- (void)createARContent {
    ARMesh* scaleMesh = [[ARMesh alloc] initFromFile:@"scale.obj"];
    ARTexture* scaleTexture = [[ARTexture alloc] initFromFile:@"scale.png"];
    
    ARFreeObject* scale = [[ARFreeObject alloc] initWithParams:scaleMesh texture:scaleTexture position:nil rotation:nil size:[ARVector vectorWithCoords:1 Y:0.25 Z:1] scale:0.5];
    [[ARController sharedARController] addObject:scale];
    
    scale = [[ARFreeObject alloc] initWithParams:scaleMesh texture:scaleTexture position:nil rotation:[ARVector vectorWithCoords:90 Y:0 Z:0] size:[ARVector vectorWithCoords:1 Y:0.25 Z:1] scale:0.5];
    [[ARController sharedARController] addObject:scale];
    
    scale = [[ARFreeObject alloc] initWithParams:scaleMesh texture:scaleTexture position:nil rotation:[ARVector vectorWithCoords:0 Y:0 Z:90] size:[ARVector vectorWithCoords:1 Y:0.25 Z:1] scale:0.5];
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
}

- (void)createARBuilding {
    ARMesh* buildingMesh = [[ARMesh alloc] initFromFile:@"building.obj"];
    ARTexture* buildingTexture = [[ARTexture alloc] initFromFile:@"building.png"];
    ARGeoObject* building = [[ARGeoObject alloc] initWithParams:buildingMesh texture:buildingTexture latitude:49.01028938880215 longitude:12.101826667785645 altitude:320 heading:135 scale:5];
    [[ARController sharedARController] addObject:building];
}

@end
