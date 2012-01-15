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
        [_arRadarView setRadarRange:1500];
    }
    
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [ARController sharedARController].delegate = self;
    [self createARPoiObjects];
    
    [ARController sharedARController].console.hidden = YES;
    
    // setup radar
    CGRect rect = CGRectMake(0, [ARController sharedARController].console.hidden ? 0 : 160, 0, 32);
    [_arRadarView setRadarToThumbnail:ARRadarPositionTopLeft withAdditionalOffset:rect];
    _radarThumbnailPosition = ARRadarPositionTopLeft;
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
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


#pragma mark - AR Controller Delegate Methods



- (void)arDidTapObject:(id<ARObjectDelegate>)object {
   if ([ARController sharedARController].isFrozen) {
       [[ARController sharedARController] unfreeze];
   }
   else {
       [[ARController sharedARController] freeze];
   }
}


- (void)arDidReceiveErrorCode:(int)code {
    [self updateInfoLabel];
}



- (void)arDidUpdateLocation {
    [self updateInfoLabel];
}


- (void)arDidChangeOrientation:(UIDeviceOrientation)orientation {
    
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

/*! the console callback only happens with the Debug Build of the Framework */
- (void)arConsoleCallback {
    [self updateInfoLabel];
}

- (void)updateInfoLabel {
    if ([ARController sharedARController].userLocation == nil) {
        _infoLabel.text = @"could not retrieve location";
        _infoLabel.textColor = [UIColor redColor];
    }
    else {
        _infoLabel.text = [NSString stringWithFormat:@"GPS signal quality: %.1d (~%.1f Meters)", [ARController sharedARController].userSignalQuality, [ARController sharedARController].userLocationQuality];
        _infoLabel.textColor = [UIColor whiteColor];
    }
}



#pragma mark - Actions

- (IBAction)radarButtonAction {
    CGRect rect = CGRectMake(0, [ARController sharedARController].console.hidden ? 0 : 160, 0, 32);
    if (!_arRadarView.isRadarVisible || _arRadarView.radarMode == ARRadarOff) {
        _radarThumbnailPosition = ARRadarPositionTopLeft;
        [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
        [_arRadarView showRadar];
    }
    else if (_arRadarView.radarMode == ARRadarThumbnail) {
        if (_radarThumbnailPosition == ARRadarPositionTopLeft) {
            _radarThumbnailPosition = ARRadarPositionTopRight;
            [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
            [_arRadarView showRadar];
        }
        else if (_radarThumbnailPosition == ARRadarPositionTopRight) {
            _radarThumbnailPosition = ARRadarPositionBottomLeft;
            [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
            [_arRadarView showRadar];
        }
        else if (_radarThumbnailPosition == ARRadarPositionBottomLeft) {
            _radarThumbnailPosition = ARRadarPositionBottomRight;
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
    [ARController sharedARController].console.hidden = ![ARController sharedARController].console.hidden;
}



#pragma mark - AR Stuff


// check if AR is available, show error if it's not and set bar item
- (BOOL)checkForAR:(BOOL)showErrors {
#if !TARGET_IPHONE_SIMULATOR
    BOOL supportsAR = [ARController deviceSupportsAR];
#else
    BOOL supportsAR = YES;
#endif
    
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
    ARPoi* newPoi = nil;
    ARPoiLabel* newPoiLabel = nil;
    
    // first: setup a new marker with title and content at the location you want
    // WARNING: use double-precision coordinates whenever possible (the following coordinates are from Google Maps which only provides 8-9 digit coordinates
    newPoiLabel = [[ARPoiLabel alloc] initWithTitle:@"Rome" theDescription:@"Italy" atLocation:[[[CLLocation alloc] initWithLatitude:41.890156 longitude:12.492304] autorelease]];
    // second: add the marker to the ARController using the addObject method
	[[ARController sharedARController] addObject: newPoiLabel];
    
    // add a second marker
    newPoiLabel = [[ARPoiLabel alloc] initWithTitle:@"Berlin" theDescription:@"Germany" atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]];
    [[ARController sharedARController] addObject:newPoiLabel];
    
    // add a third marker, this time allocation of a new marker and adding to the ARController are wrapped up in one line
	newPoiLabel = [[ARPoiLabel alloc] initWithTitle:@"London" theDescription:@"United Kingdom" atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
    [[ARController sharedARController] addObject:newPoiLabel];
    
	newPoi = [[ARPoi alloc] initWithImage:@"DefaultImage" atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
     newPoi.offset = CGPointMake(0, -64);
     [[ARController sharedARController] addObject:newPoi];
    
    NSLog(@"AR Objects Created: %d", [[ARController sharedARController] numberOfObjects]);
    _hasARPoiObjects = YES;
}


@end
