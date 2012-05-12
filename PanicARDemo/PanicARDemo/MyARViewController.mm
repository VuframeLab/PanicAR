//
//  MyARViewController.m
//  PanicAR-App
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
        self.title = NSLocalizedString(@"PAR", @"PAR");
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
    // IMPORTANT: set Api Key before calling super:loadView!
    [[PARController sharedARController] setApiKey:@""];
    [[PARController sharedARController] setDelegate:self];
    
    [super loadView];
    
    if ([PARController deviceSupportsAR:YES]) {
        [[PARController sharedARController] enableConsole];
        [_arRadarView setRadarRange:1500];
    }
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // setup AR manager properties
    [[[PARSensorManager sharedSensorManager] locationManager] setDesiredAccuracy:kCLLocationAccuracyBestForNavigation];
    [_arView setAlignLabelsToDeviceOrientation:YES];
    [_arView setLabelBaseline:0.7f];
    [[PARController sharedARController] hideConsole];
    
    // create AR POIs
    [self createARPoiObjects];
    
    // setup radar
    CGRect rect = CGRectMake(0, [PARController sharedARController].console.hidden ? 0 : 160, 0, 32);
    [_arRadarView setRadarToThumbnail:PARRadarPositionTopLeft withAdditionalOffset:rect];
    _radarThumbnailPosition = PARRadarPositionTopLeft;
    [_arRadarView showRadar];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations – but only if PARView is not rotated dynamically
    return (interfaceOrientation == UIInterfaceOrientationPortrait)
    || (!self.rotatesARView && (interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown
                                || interfaceOrientation == UIInterfaceOrientationLandscapeLeft
                                || interfaceOrientation == UIInterfaceOrientationLandscapeRight));
}
    
    
    
#pragma mark - AR Config
    
- (BOOL)usesCameraPreview {
    return YES;
}
- (BOOL)fadesInCameraPreview {
    return NO;
}
- (BOOL)rotatesARView {
    return NO;
}


#pragma mark - PAR Controller Delegate Methods



- (void)arDidTapObject:(id<PARObjectDelegate>)object {
   if ([PARController sharedARController].isFrozen) {
       [[PARController sharedARController] setFrozen:YES];
   }
   else {
       [[PARController sharedARController] setFrozen:NO];
   }
}


- (void)arDidReceiveErrorCode:(int)code {
    [self updateInfoLabel];
}



- (void)arDidUpdateLocation {
    [self updateInfoLabel];
}


- (void)arDidChangeOrientation:(UIInterfaceOrientation)orientation {
    
}

- (void)arSignalQualityChanged {
    switch ([PARSensorManager sharedSensorManager].userSignalQuality) {
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

/*! the console callback only happens with the Debug Build of the Framework */
- (void)arConsoleCallback {
    [self updateInfoLabel];
}
    
    
#pragma mark - Instance Methods
    
- (void)updateInfoLabel {
    if ([PARSensorManager sharedSensorManager].userLocation == nil) {
        _infoLabel.text = @"could not retrieve location";
        _infoLabel.textColor = [UIColor redColor];
    }
    else {
        _infoLabel.text = [NSString stringWithFormat:@"GPS signal quality: %.1d (~%.1f Meters)", [PARSensorManager sharedSensorManager].userSignalQuality, [PARSensorManager sharedSensorManager].userLocationQuality];
        _infoLabel.textColor = [UIColor whiteColor];
    }
}



#pragma mark - Actions

- (IBAction)radarButtonAction {
    CGRect rect = CGRectMake(0, [PARController sharedARController].console.hidden ? 0 : 160, 0, 32);
    if (!_arRadarView.isRadarVisible || _arRadarView.radarMode == PARRadarOff) {
        _radarThumbnailPosition = PARRadarPositionTopLeft;
        [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
        [_arRadarView showRadar];
    }
    else if (_arRadarView.radarMode == PARRadarThumbnail) {
        if (_radarThumbnailPosition == PARRadarPositionTopLeft) {
            _radarThumbnailPosition = PARRadarPositionTopRight;
            [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
            [_arRadarView showRadar];
        }
        else if (_radarThumbnailPosition == PARRadarPositionTopRight) {
            _radarThumbnailPosition = PARRadarPositionBottomLeft;
            [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
            [_arRadarView showRadar];
        }
        else if (_radarThumbnailPosition == PARRadarPositionBottomLeft) {
            _radarThumbnailPosition = PARRadarPositionBottomRight;
            [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
            [_arRadarView showRadar];
        }
        else {
            [_arRadarView setRadarToFullscreen:CGPointMake(0, -32) withSizeOffset:0];
            [_arRadarView showRadar];
        }
    }
    else {
        [_arRadarView hideRadar];
    }
}

- (IBAction)switchConsole:(id)sender { 
    [PARController sharedARController].console.hidden = ![PARController sharedARController].console.hidden;
}



#pragma mark - PAR Stuff



// create a few test markers
- (void)createARPoiObjects {
    PARPoi* newPoi = nil;
    PARPoiLabel* newPoiLabel = nil;
    
    // first: setup a new marker with title and content at the location you want
    // WARNING: use double-precision coordinates whenever possible (the following coordinates are from Google Maps which only provides 8-9 digit coordinates
    newPoiLabel = [[PARPoiLabel alloc] initWithTitle:@"Rome" theDescription:@"Italy" atLocation:[[[CLLocation alloc] initWithLatitude:41.890156 longitude:12.492304] autorelease]];
    // second: add the marker to the PARController using the addObject method
	[[PARController sharedARController] addObject: newPoiLabel];
    
    // add a second marker
    newPoiLabel = [[PARPoiLabel alloc] initWithTitle:@"Berlin" theDescription:@"Germany" atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]];
    [[PARController sharedARController] addObject:newPoiLabel];
    
    // add a third marker, this time allocation of a new marker and adding to the PARController are wrapped up in one line
	newPoiLabel = [[PARPoiLabel alloc] initWithTitle:@"London" theDescription:@"United Kingdom" atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
    [[PARController sharedARController] addObject:newPoiLabel];
    
	newPoi = [[PARPoi alloc] initWithImage:@"DefaultImage" atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
     newPoi.offset = CGPointMake(0, -64);
     [[PARController sharedARController] addObject:newPoi];
    
    NSLog(@"PAR Objects Created: %d", [[PARController sharedARController] numberOfObjects]);
    _hasARPoiObjects = YES;
}


@end
