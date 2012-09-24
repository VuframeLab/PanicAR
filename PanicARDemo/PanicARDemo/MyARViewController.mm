//
//  MyARViewController.m
//  PanicAR-App
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "MyARViewController.h"

//#define LABEL PARPoiLabel
#define LABEL PARPoiAdvancedLabel
static NSTimer *infoTimer = nil;

@implementation MyARViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        // set view controller properties and create Options button
        self.title = NSLocalizedString(@"AR", @"AR");
        self.navigationItem.title = self.title;
        self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc] initWithTitle:@"Options" style:UIBarButtonItemStyleBordered target:self action:@selector(showOptions:)] autorelease];
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
    
    [PARController deviceSupportsAR:YES]; // check if device supports AR if not show standard error alerts
    [_arRadarView setRadarRange:1500];
    // remove deprecated method: [[PSKSensorManager sharedSensorManager] enableUpdateHeadingFromLocationManager];
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // ensure infoLabels are sorted correctly (storyboard workaround)
    self.infoLabels = [self.infoLabels sortedArrayUsingComparator:^NSComparisonResult(UIView *label1, UIView *label2) {
        if ([label1 tag] < [label2 tag]) return NSOrderedAscending;
        else if ([label1 tag] > [label2 tag]) return NSOrderedDescending;
        else return NSOrderedSame;
    }];
    
    
    // setup AR manager properties
    [[_sensorManager locationManager] setDesiredAccuracy:kCLLocationAccuracyBestForNavigation];
    [_arView setLabelBaseline:0.0f];
    
    // create AR POIs
    [self createARPoiObjects];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    infoTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(updateInfoLabel) userInfo:nil repeats:YES];
    
    // setup radar
    CGRect rect = CGRectMake(0, 44, 0, 32);
    _radarThumbnailPosition = PARRadarPositionBottomRight;
    [_arRadarView setRadarToThumbnail:_radarThumbnailPosition withAdditionalOffset:rect];
    [_arRadarView showRadar];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [infoTimer invalidate];
    infoTimer = nil;
}


#pragma mark - AR Config

- (BOOL)usesCameraPreview {
    return YES;
}
- (BOOL)fadesInCameraPreview {
    return NO;
}
- (BOOL)rotatesARView {
    return YES;
}

- (void)switchFaceUp:(BOOL)inFaceUp {
    if (inFaceUp) {
        [_arRadarView setRadarToFullscreen];
    }
    else {
        [_arRadarView setRadarToThumbnail:_radarThumbnailPosition];
    }
}



#pragma mark - PARControllerDelegate

- (void)arDidTapObject:(id<PARObjectDelegate>)object {
    [PARController showAlert:@"Tap" 
                 withMessage:[NSString stringWithFormat:@"Label tapped: %@", object.title]
            andDismissButton:@"Okay"];
}

#pragma mark - PSKSensorDelegate
- (void)didReceiveErrorCode:(int)code {
    [self updateInfoLabel];
    
}

- (void)didUpdateLocation {
    CLLocation* l = [[_sensorManager deviceAttitude] location];
    CLLocationCoordinate2D c = [l coordinate];
    
    UILabel *_locationLabel = [_infoLabels objectAtIndex:1];
    _locationLabel.hidden = NO;
    UILabel *_locationDetailsLabel = [_infoLabels objectAtIndex:2];
    _locationDetailsLabel.hidden = NO;
    
    _locationLabel.text = [NSString stringWithFormat:@"%.4f° %.4f° %.2fm", c.latitude, c.longitude, l.altitude];
    _locationDetailsLabel.text = [NSString stringWithFormat:@"±%.2fm ±%.2fm", l.horizontalAccuracy, l.verticalAccuracy];
}

- (void)didUpdateHeading {
    UILabel *_headingLabel = [_infoLabels objectAtIndex:3];
    _headingLabel.hidden = NO;
    UILabel *_headingDetailsLabel = [_infoLabels objectAtIndex:4];
    _headingDetailsLabel.hidden = NO;
    
    _headingLabel.text = [NSString stringWithFormat:@"%.2f°", [[_sensorManager deviceAttitude] heading]];
    _headingDetailsLabel.text = [NSString stringWithFormat:@"±%.2f", [[_sensorManager deviceAttitude] headingAccuracy]];
}

- (void)didChangeDeviceOrientation:(UIDeviceOrientation)orientation {
    [super didChangeDeviceOrientation:orientation];
}

- (void)didChangeSignalQuality:(PSKSignalQuality)newSignalQuality {
    switch (newSignalQuality) {
        case kPSKSignalQualityBest:
            _signalDisplay.image = [UIImage imageNamed:@"signal4.png"];
            break;
        case kPSKSignalQualityOkay:
            _signalDisplay.image = [UIImage imageNamed:@"signal3.png"];
            break;
        case kPSKSignalQualityMedium:
            _signalDisplay.image = [UIImage imageNamed:@"signal2.png"];
            break;
        case kPSKSignalQualityBad:
            _signalDisplay.image = [UIImage imageNamed:@"signal1.png"];
            break;
            
        default:
            _signalDisplay.image = [UIImage imageNamed:@"signal0.png"];
            break;
    }
    
    // optionally: hide GPS meter if signal is fine
    _signalDisplay.hidden = NO;
    
    if (newSignalQuality < kPSKSignalQualityBad) {
        if (!_signalDisplay.hidden) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 3.0 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
                _signalDisplay.hidden = YES;
            });
        }
    }
}



#pragma mark - Instance Methods

- (void)updateInfoLabel {
    UILabel *_infoLabel = [_infoLabels objectAtIndex:0];
    NSString *display = nil;
    if (![_deviceAttitude hasLocation]) {
        _infoLabel.textColor = [UIColor redColor];
        display = @"could not retrieve location";
    }
    else {
        display = [NSString stringWithFormat:@"GPS signal quality: %.1d (~%.1f Meters)", [_deviceAttitude signalQuality], [_deviceAttitude locationAccuracy]];
        _infoLabel.textColor = [UIColor whiteColor];
    }
    
    _infoLabel.text = [display stringByAppendingFormat:@"\nTracking: Gyroscope (iOS 5): y:%+.4f, p:%+.4f, r:%+.4f", [_deviceAttitude attitudeYaw], [_deviceAttitude attitudePitch], [_deviceAttitude attitudeRoll]];
}


- (void)changeTracking {
    
}


#pragma mark - Actions

- (IBAction)radarButtonAction {
    CGRect rect = CGRectMake(0, 44, 0, 0);
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

- (IBAction)showOptions:(id)sender { 
    UIActionSheet* options = [[[UIActionSheet alloc] initWithTitle:@"Options" 
                                                          delegate:self 
                                                 cancelButtonTitle:@"Cancel" 
                                            destructiveButtonTitle:@"Remove AR Objects" 
                                                 otherButtonTitles:@"Re-create Default Markers", nil] autorelease];
    options.tag = 1;
    [options showFromBarButtonItem:self.navigationItem.rightBarButtonItem animated:YES];
}


- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    NSLog(@"%d", buttonIndex);
    switch (buttonIndex) {
        case 0:
            [[PARController sharedARController] clearObjects];
            break;
        case 1:
            [self createARPoiObjects];
            break;
            
        default:
            break;
    }
}

#pragma mark - PAR Stuff


// create a few test poi objects
- (void)createARPoiObjects {
    PARPoi* newPoi = nil;
    LABEL* newPoiLabel = nil;
    
    // first: setup a new poi label with title and description at the location you want
    // WARNING: use double-precision coordinates whenever possible (the following coordinates are from Google Maps which only provides 8-9 digit coordinates
    newPoiLabel = [[[LABEL alloc] initWithTitle:@"Rome" 
                                 theDescription:@"Italy" 
                                     atLocation:[[[CLLocation alloc] initWithLatitude:41.890156 longitude:12.492304] autorelease]
                    ] autorelease];
    // second: add the poi label to the PARController using the addObject method
	[[PARController sharedARController] addObject:newPoiLabel];
    
    // add a second poi label
    newPoiLabel = [[[LABEL alloc] initWithTitle:@"Berlin" 
                                 theDescription:@"Germany" 
                                     atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]] autorelease];
    [[PARController sharedARController] addObject:newPoiLabel];
    
    // add a third poi label, this time allocation of a new marker and adding to the PARController are wrapped up in one line
	newPoiLabel = [[[LABEL alloc] initWithTitle:@"London" 
                                 theDescription:@"United Kingdom" 
                                     atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]
                    ] autorelease];
    [[PARController sharedARController] addObject:newPoiLabel];
    
    // now add a poi (a graphic only - no text)
	newPoi = [[[PARPoi alloc] initWithImage:@"DefaultImage" 
                                atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]
              ] autorelease];
    newPoi.offset = CGPointMake(0, 0);
    [[PARController sharedARController] addObject:newPoi];
    
    // local pois
    newPoiLabel = [[[LABEL alloc] initWithTitle:@"Dom" 
                                theDescription:@"Regensburger Dom" 
                                    atLocation:[[[CLLocation alloc] initWithLatitude:49.019512 longitude:12.097709] autorelease]
                   ] autorelease];
    [[PARController sharedARController] addObject:newPoiLabel];
    
    NSLog(@"PAR Objects Created: %d", [[PARController sharedARController] numberOfObjects]);
    _hasARPoiObjects = YES;
}

@end
