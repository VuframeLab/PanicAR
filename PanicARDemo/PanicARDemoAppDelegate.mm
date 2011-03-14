#import "PanicARDemoAppDelegate.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif


@implementation PanicARDemoAppDelegate

@synthesize window;
@synthesize tabBarController;

- (void)applicationDidFinishLaunching:(UIApplication *)application {	
    tabBarController.delegate = self;
    [self.window addSubview:tabBarController.view];
	[window makeKeyAndVisible];
	
	[self createAR];
	[self createMarkers];
    
	[self showAR];
}

- (void) showAR {
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
    
    if (m_ARController != nil) {
        NSLog(@"ARView selected in TabBar");
        [ARController setRadarPosition:0 y:0];
        [[tabBarController.viewControllers objectAtIndex:0] setView:m_ARController.view];
        [m_ARController showController:NO showStatusBar:YES];
        [m_ARController setViewport:CGRectMake(0, 0, 320, 411)];
        //[m_ARController setViewport:CGRectMake(20, 40, 280, 300)];
    }
    else NSLog(@"No ARController available!");
    
}

- (void) updateButtons {
	createARController.enabled = m_ARController == nil;
	createARController.alpha = createARController.enabled ? 1.0 : 0.5;
	
	labelController.text = [[[NSString alloc] initWithFormat:m_ARController == nil ? @"AR Controller not allocated" : @"AR Controller allocated"] autorelease];
	
	releaseARController.enabled = m_ARController != nil;
	releaseARController.alpha = releaseARController.enabled ? 1.0 : 0.5;
	
	addARMarkers.enabled = m_ARController != nil;
	if (m_ARController != nil) addARMarkers.enabled = [m_ARController numberOfMarkers] < 1;
	addARMarkers.alpha = addARMarkers.enabled ? 1.0 : 0.5;
	
	clearARMarkers.enabled = m_ARController != nil;
	if (m_ARController != nil) clearARMarkers.enabled = [m_ARController numberOfMarkers] > 0;
	clearARMarkers.alpha = clearARMarkers.enabled ? 1.0 : 0.5;
	
	showModalView.enabled = m_ARController != nil;
	showModalView.alpha = showModalView.enabled ? 1.0 : 0.5;
	
	labelMarkers.hidden = m_ARController == nil;
	if (m_ARController != nil) 
		labelMarkers.text = [[[NSString alloc] initWithFormat:@"Number of markers: %d", [m_ARController numberOfMarkers]] autorelease];
}

- (void) createAR {
	//setup ARController properties
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
	
	//create ARController
	m_ARController = [[ARController alloc] initWithDelegate:self];
	
	[[tabBarController.viewControllers objectAtIndex:0] setView:nil];
	
#if (TARGET_IPHONE_SIMULATOR)
	// returns nil if AR not available on device
	if (m_ARController) {
		// simulator testing coordinates
		m_ARController.myLocation = [[CLLocation alloc] initWithLatitude:49.009860 longitude:12.108049];
	}
#endif
}



- (void) releaseAR {
	[m_ARController release];
	m_ARController = nil;
}

- (void) createMarkers {
	// now add markers
	// WARNING: use double-precision coordinates
    
	[m_ARController addMarkerAtLocation:
	 [[ARMarker alloc] initWithTitle:@"New York City" 
                        contentOrNil:@"New York, United States"] 
							 atLocation:[[[CLLocation alloc] initWithLatitude:40.708231 longitude:-74.005966] autorelease]
	 ];
	[m_ARController addMarkerAtLocation:
	 [[ARMarker alloc] initWithTitle:@"Berlin" 
                        contentOrNil:@"Germany"] 
							 atLocation:[[[CLLocation alloc] initWithLatitude:52.523402 longitude:13.41141] autorelease]
	 ];
	[m_ARController addMarkerAtLocation:
	 [[ARMarker alloc] initWithTitle:@"London" 
                        contentOrNil:@"United Kingdom"] 
							 atLocation:[[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257] autorelease]
	 ];
}





- (IBAction) webButton_click {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString: @"http://www.dopanic.com/ar"]];
}

- (void) markerTapped:(ARMarker*)marker {
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


- (void)tabBarController:(UITabBarController *)tabBar didSelectViewController:(UIViewController *)viewController {
	if ([tabBarController.viewControllers indexOfObject:viewController] == 0) {
		[self showAR];
	}
	else {
		[[tabBarController.viewControllers objectAtIndex:0] setView:nil];
		[m_ARController hideController];
	}
	
}


- (void)dealloc {
	if (m_ARController != nil) [m_ARController release];
	[window release];
	[super dealloc];
}


@end
