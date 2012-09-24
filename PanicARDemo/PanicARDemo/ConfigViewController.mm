//
//  ConfigViewController.m
//  PanicAR-App
//
//  Created by Andreas Zeitler on 15.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "ConfigViewController.h"

@implementation ConfigViewController

@synthesize mapView = _mapView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Config", @"Config");
        self.navigationItem.title = self.title;
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(doCompassTracking:)];
        self.navigationItem.leftBarButtonItem.enabled = NO;
    }
    return self;
}
							
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
    
	
	MKCoordinateRegion region = MKCoordinateRegionMake([[[PSKSensorManager sharedSensorManager] deviceAttitude] locationCoordinate], MKCoordinateSpanMake(0.02, 0.02));
	[_mapView setRegion:region animated:TRUE];
	[_mapView regionThatFits:region];
    [_mapView setUserTrackingMode:MKUserTrackingModeFollowWithHeading];
    [_mapView removeAnnotations:[_mapView annotations]];
    [_mapView setDelegate:self];
	
    
    for (PARPoi* poi in [[PARController sharedARController] arObjects]) {
        if ([poi conformsToProtocol:@protocol(MKAnnotation)]) {
            [_mapView addAnnotation:poi];
        }
    }
	//pin = [[MapPin alloc] initWithCoordinate: focusNote.location.coordinate];
	//[mapView addAnnotation:pin];
}

- (void)viewDidUnload
{
    [self setMapView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return YES;
    /*if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }*/
}

- (void)dealloc {
    [_mapView release];
    [super dealloc];
}


- (void)mapView:(MKMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated {
    self.navigationItem.leftBarButtonItem.enabled = mapView.userTrackingMode != MKUserTrackingModeFollowWithHeading;
}


- (IBAction)doCompassTracking:(id)sender {
    [_mapView setUserTrackingMode:MKUserTrackingModeFollowWithHeading];
}


@end
