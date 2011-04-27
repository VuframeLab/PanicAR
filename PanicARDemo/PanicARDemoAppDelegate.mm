//
//  PanicARDemoAppDelegate.mm
//  PanicAR Demo
//
//  Created by Andreas Zeitler on 9/1/11.
//  Copyright doPanic 2011. All rights reserved.
//

#import "PanicARDemoAppDelegate.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif


@implementation PanicARDemoAppDelegate

@synthesize window;
@synthesize tabBarController;
@synthesize arBarItem;


// application delegate method
- (void)applicationDidFinishLaunching:(UIApplication *)application {	
    tabBarController.delegate = self;
    [self.window addSubview:tabBarController.view];
	[window makeKeyAndVisible];
    
    // create ARController and Markers
 	[self createAR];
	[self createMarkers];
    
    // check if AR is available and if so show the controller in first view of TabBarController
    if ([self checkForAR:YES]) [self showAR];
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    NSLog(@"applicationDidEnterBackground");
	[m_ARController suspendToBackground];
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    NSLog(@"applicationWillEnterForeground");
    [self checkForAR:NO];
	[m_ARController resumeFromBackground];
}


// standard dealloc of the delegate
- (void)dealloc {
	if (m_ARController != nil) [m_ARController release];
	[window release];
	[super dealloc];
}

// check if AR is available, show error if it's not and set bar item
- (BOOL) checkForAR:(BOOL)showErrors {
    BOOL supportsAR = [ARController deviceSupportsAR];
    BOOL supportsLocations = [ARController locationServicesAvailable];
    BOOL result = supportsLocations && supportsAR;
    
    arBarItem.enabled = result;
    if (!result) {
        [tabBarController setSelectedIndex:1];
    }
    
    if (showErrors) {
        if (!supportsAR) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"AR not supported"
                                                            message:@"This device does not support AR functionality"
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"OK Button", @"OK") 
                                                  otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
        }
        
        if (!supportsLocations) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Location Denied Title", @"Error")
                                                            message:NSLocalizedString(@"Location Denied Message", @"GPS not available")
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"OK Button", @"OK") 
                                                  otherButtonTitles:nil, nil];
            [alert show];
            [alert release];
        }
    }
    
    return result;
}

// create the ARController
- (void) createAR {
	//setup ARController properties
    [ARController setAPIKey:@"none"];
	[ARController setEnableCameraView:YES];
	[ARController setEnableRadar:YES];
	[ARController setEnableInteraction:YES];
	[ARController setEnableAccelerometer:YES];
	[ARController setEnableAutoswitchToRadar:YES];
	[ARController setEnableViewOrientationUpdate:YES];
	[ARController setFadeInAnim:UIViewAnimationTransitionCurlDown];
	[ARController setFadeOutAnim:UIViewAnimationTransitionCurlUp];
	[ARController setCameraTint:0 g:0 b:0 a:0];
	[ARController setCameraTransform:1.25 y:1.25];
    [ARController setRange:5 Maximum:-1];
    [ARController setRadarPosition:0 y:-24];
     
	
	//create ARController
	m_ARController = [[ARController alloc] initWithNibName:@"ARController" bundle:nil delegate:self];
	
	//[[tabBarController.viewControllers objectAtIndex:0] setView:nil];
	
#if (TARGET_IPHONE_SIMULATOR)
	// returns nil if AR not available on device
	if (m_ARController) {
		// simulator testing coordinates
		m_ARController.lastLocation = [[CLLocation alloc] initWithLatitude:49.009860 longitude:12.108049];
	}
#endif
    
    arBarItem.enabled = [ARController locationServicesAvailable];
}

// create a few test markers
- (void) createMarkers {
    // first: setup a new marker with title and content
    ARMarker* newMarker = [[ARMarker alloc] initWithTitle:@"Rome" contentOrNil:@"Italy"];
    
    // second: add the marker to the ARController using the addMarkerAtLocation method
    // pass the geolocation (latitude, longitude) that specifies where the marker should be located
    // WARNING: use double-precision coordinates whenever possible (the following coordinates are from Google Maps which only provides 8-9 digit coordinates
	[m_ARController addMarkerAtLocation: newMarker atLocation:[[[CLLocation alloc] initWithLatitude:41.890156 longitude:12.492304] autorelease]];
    
    
    // add a second marker
    newMarker = [[ARMarker alloc] initWithTitle:@"Berlin" contentOrNil:@"Germany"];
    [m_ARController addMarkerAtLocation:newMarker atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]];
    
    // add a third marker, this time allocation of a new marker and adding to the ARController are wrapped up in one line
	[m_ARController addMarkerAtLocation:[[ARMarker alloc] initWithTitle:@"London" contentOrNil:@"United Kingdom"] atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]];
    
    /*newMarker = [[ARMarker alloc] initAs3DObject:@"msh_box.obj" 
                                         texture:@"59-info.png" 
                                        position:[ARVector vectorWithCoords:0 Y:0 Z:0] 
                                        rotation:[ARVector vectorWithCoords:0 Y:0 Z:0] 
                                           scale:1];*/
}

// display the ARView in the tab bar (non-modal)
- (void) showAR {
    // on DEVICE: show error if device does not support AR functionality
    // AR is not supported if either camera or compass is not available
#if !(TARGET_IPHONE_SIMULATOR)
    if (![ARController deviceSupportsAR]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"No AR Error Title", @"No AR Support")
                                                        message:NSLocalizedString(@"No AR Error Message"@, "This device does not support AR functionality!") 
                                                       delegate:nil 
                                              cancelButtonTitle:NSLocalizedString(@"OK Button", @"OK") 
                                              otherButtonTitles:nil];
        [alert show];
        return;
    }
#endif
    
    // check if ARController instance is valid
    if (m_ARController == nil) {
        NSLog(@"No ARController available!");
        return;
    }
    
    // show AR Controller in tab bar by assigning the ARView to the first view controller of the tab bar
    [[tabBarController.viewControllers objectAtIndex:0] setView:m_ARController.view];
    // now tell the ARController to become visbiel in a non-modal way while keeping the status bar visible
    // NOTE: the camera feed will mess with the status bar's visibility while being loaded, so far there is no way to avoid that (iOS SDK weakness)
    [m_ARController showController:NO showStatusBar:YES];
    // when showing the ARView non-modal the viewport has to be set each time it becomes visible in order to avoid positioning and resizing problems
    [m_ARController setViewport:CGRectMake(0, 0, 320, 411)];
    
    NSLog(@"ARView selected in TabBar");
}



#pragma mark -
#pragma mark AR Callbacks

// marker interaction delegate
// called when the AR view is tapped
// marker is the marker that was tapped, or nil if none was hit
- (void) arDidTapMarker:(ARMarker*)marker {
	if (marker != nil) {
		marker.touchDownColorR = 1;
		marker.touchDownColorG = 0.5;
		marker.touchDownColorB = 0.5;
		marker.touchDownColorA = 1;
		marker.touchDownScale = 1.25;
		
		NSLog(@"markerClicked: %@", marker.title);
		m_ARController.infoLabel.text = [[[NSString alloc] initWithFormat:@"%@ - %@", marker.title, marker.content] autorelease];
	}
	else m_ARController.infoLabel.text = [[[NSString alloc] initWithFormat:@""] autorelease];
}

// update callback, fills the info label of the ARController with signal quality information
- (void) arDidUpdateLocation {
    if (m_ARController.lastLocation == nil) {
        m_ARController.infoLabel.text = @"could not retrieve location";
        m_ARController.infoLabel.textColor = [UIColor redColor];
    }
    else {
        m_ARController.infoLabel.text = [NSString stringWithFormat:@"GPS signal quality: %f Meters", m_ARController.lastLocationQuality];
        m_ARController.infoLabel.textColor = [UIColor whiteColor];
    }
}

// orientation update callback: updates orientation and positioning of radar screen
- (void) arDidChangeOrientation:(UIDeviceOrientation)orientation radarOrientation:(UIDeviceOrientation)radarOrientation {
    if (!m_ARController.isVisible || (m_ARController.isVisible && !m_ARController.isModalView)) {
        if (radarOrientation == UIDeviceOrientationPortrait) [ARController setRadarPosition:0 y:-11];
        else if (radarOrientation == UIDeviceOrientationPortraitUpsideDown) [ARController setRadarPosition:0 y:11];
        else if (radarOrientation == UIDeviceOrientationFaceUp) [ARController setRadarPosition:0 y:-11];
        else if (radarOrientation == UIDeviceOrientationLandscapeLeft) [ARController setRadarPosition:-11 y:0];
        else if (radarOrientation == UIDeviceOrientationLandscapeRight) [ARController setRadarPosition:11 y:0];
    }
}

- (void) arDidReceiveErrorCode:(int)code {
    
}



#pragma mark -
#pragma mark UI Methods

// tab bar delegate method, switches the views displayed by the app
- (void)tabBarController:(UITabBarController *)tabBar didSelectViewController:(UIViewController *)viewController {
	if ([tabBarController.viewControllers indexOfObject:viewController] == 0) {
		[self showAR];
        arIsVisible = YES;
	}
	else {
		[[tabBarController.viewControllers objectAtIndex:0] setView:nil];
		[m_ARController hideController];
        arIsVisible = NO;
	}
	
}

// about dialog weblink action
- (IBAction) webButton_click {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString: @"http://www.dopanic.com/ar"]];
}

@end
