#import "PanicARDemoAppDelegate.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif


@implementation PanicARDemoAppDelegate

@synthesize window, overlay;
@synthesize startButton;
@synthesize stopButton;
@synthesize radarButton;
@synthesize debugLabel;
@synthesize cameraXSlider;
@synthesize cameraYSlider;


- (void)applicationDidFinishLaunching:(UIApplication *)application 
{	
	// show status bar (gets overwritten by UIImagePicker otherwise)
	window.autoresizesSubviews = YES;
	window.clipsToBounds = YES;
	window.frame = CGRectMake(0, 20, 320, 460);
	window.bounds = CGRectMake(0, 20, 320, 460);
	
	[self setupAR];
	
	[window makeKeyAndVisible];
}

- (void) setupAR {
	
	//create ARController and autostart
	m_ARController = [[ARController alloc] initWithFrame:CGRectMake(0, 20, 320, 460) autostart:YES useAccelerom:YES useAutoSwitchToRadar:YES useViewRotation:YES eventHandler:self]; 
	
	// returns nil if AR not available on device
	if (m_ARController) { 
		
		// add to main window beneath the overlay-window
		[window insertSubview:m_ARController.mainView atIndex:0];
		
		
		// now add markers
		// WARNING: use double-precision coordinates
		
		NSString* textureFilename = [[NSString alloc] initWithFormat:@"%@/regensburgerdom.jpg", [[NSBundle mainBundle] resourcePath]];
		UIImage* texture1 = [[UIImage alloc] initWithContentsOfFile:textureFilename];
		[textureFilename release];
		textureFilename = [[NSString alloc] initWithFormat:@"%@/cinemaxx.jpg", [[NSBundle mainBundle] resourcePath]];
		UIImage* texture2 = [[UIImage alloc] initWithContentsOfFile:textureFilename];
		[textureFilename release];
		textureFilename = [[NSString alloc] initWithFormat:@"%@/dez.jpg", [[NSBundle mainBundle] resourcePath]];
		UIImage* texture3 = [[UIImage alloc] initWithContentsOfFile:textureFilename];
		[textureFilename release];
		/*textureFilename = [[NSString alloc] initWithFormat:@"%@/rathaus.jpg", [[NSBundle mainBundle] resourcePath]];
		 UIImage* texture4 = [[UIImage alloc] initWithContentsOfFile:textureFilename];
		 [textureFilename release];*/
		
		ARLabelTemplate* imageLabel = [ARLabelTemplate loadLabelTemplate:@"ImageLabelTemplate_512"];
		
		//[m_ARController addMarker:nil title:@"Kupferwerk GmbH" content:@"Im Gewerbepark C35\n93053 Regensburg" image:texture location:[[[CLLocation alloc] initWithLatitude:49.02945177431651 longitude:12.125371098518372] autorelease]];
		
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Dom" contentOrNil:@"keine Beschreibung" imageOrNil:texture1 templateOrNil:imageLabel] atLocation:[[CLLocation alloc] initWithLatitude:49.0186773 longitude:12.0980308]];
		
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"DEZ" contentOrNil:@"keine Beschreibung" imageOrNil:texture2] atLocation:[[CLLocation alloc] initWithLatitude:49.023241 longitude:12.115811]];
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Cinemaxx" contentOrNil:@"in den Arcaden" imageOrNil:texture3] atLocation:[[CLLocation alloc] initWithLatitude:49.010514581750044 longitude:12.1004319190979]];
		//[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Altes Rathaus" contentOrNil:@"Historische Altstadt" imageOrNil:texture4 templateOrNil:imageLabel] atLocation:[[CLLocation alloc] initWithLatitude:49.020279 longitude:12.094955]];
		
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Furtmayrstraße" contentOrNil:@"Ecke Landshuter" imageOrNil:nil] atLocation:[[CLLocation alloc] initWithLatitude:49.009050809382046 longitude:12.113370895385742]];
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Furtmayrstraße" contentOrNil:@"Ecke Hermann-Geib-Straße" imageOrNil:nil] atLocation:[[CLLocation alloc] initWithLatitude:49.009304157679125 longitude:12.11066722869873]];
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Hermann-Geib-Straße" contentOrNil:@"Ecke Landshuter" imageOrNil:nil] atLocation:[[CLLocation alloc] initWithLatitude:49.01026123961204 longitude:12.111096382141113]];
		[m_ARController addMarkerAtLocation:[[ARMarker alloc] init:@"Furtmayrstraße" contentOrNil:@"Ecke Galgenbergbrücke" imageOrNil:nil] atLocation:[[CLLocation alloc] initWithLatitude:49.01028938880215 longitude:12.101826667785645]];
		
#ifdef DEBUG
		m_ARController.debugLabel = debugLabel;
#endif
		debugLabel.text = [[NSString alloc] initWithFormat:@""];
		/*[m_ARController addMarker:nil title:@"lat-" location:[[CLLocation alloc] initWithLatitude:39.009860 longitude:12.108049]];
		 [m_ARController addMarker:nil title:@"lat+" location:[[CLLocation alloc] initWithLatitude:49.009861 longitude:12.108049]];
		 [m_ARController addMarker:nil title:@"lat+" location:[[CLLocation alloc] initWithLatitude:59.009860 longitude:12.108049]];
		 [m_ARController addMarker:nil title:@"lat+" location:[[CLLocation alloc] initWithLatitude:50.009860 longitude:12.108049]];
		 
		 [m_ARController addMarker:nil title:@"lon-" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:2.108049]];
		 [m_ARController addMarker:nil title:@"lon-" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:12.108050]];
		 [m_ARController addMarker:nil title:@"lon+" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:22.108049]];
		 [m_ARController addMarker:nil title:@"lon+" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:13.108049]];*/
		
		
		/* //test items for long-lat displacements
		 [m_ARController addMarker:@"lat-" location:[[CLLocation alloc] initWithLatitude:39.009860 longitude:12.108049]];
		 [m_ARController addMarker:@"lat+" location:[[CLLocation alloc] initWithLatitude:59.009860 longitude:12.108049]];
		 [m_ARController addMarker:@"lon-" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:2.108049]];
		 [m_ARController addMarker:@"lon+" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:22.108049]];
		 
		 [m_ARController addMarker:@"lon-" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:12.108049]];
		 [m_ARController addMarker:@"lon-" location:[[CLLocation alloc] initWithLatitude:44.009860 longitude:7.108049]];
		 [m_ARController addMarker:@"lon-" location:[[CLLocation alloc] initWithLatitude:39.009860 longitude:2.108049]];
		 
		 [m_ARController addMarker:@"lat-" location:[[CLLocation alloc] initWithLatitude:44.009860 longitude:12.108049]];
		 [m_ARController addMarker:@"lat+" location:[[CLLocation alloc] initWithLatitude:54.009860 longitude:12.108049]];
		 [m_ARController addMarker:@"lon-" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:7.108049]];
		 [m_ARController addMarker:@"lon+" location:[[CLLocation alloc] initWithLatitude:49.009860 longitude:17.108049]];*/
		
		
		/*float tD = 700;
		 int t = 0;
		 for (int i = 0; i < 15; i++) {
		 [m_ARController addMarker:nil title:[[NSString alloc] initWithFormat:@"Test %d", t] content:@"" angle:100 distance:tD+t];
		 t++;
		 }
		 for (int i = 0; i < 18; i++) {
		 [m_ARController addMarker:nil title:[[NSString alloc] initWithFormat:@"Test %d", t] content:@"" angle:5+i*20 distance:tD+t];
		 t++;
		 }
		 for (int i = 0; i < 9; i++) {
		 [m_ARController addMarker:nil title:[[NSString alloc] initWithFormat:@"Test %d", t] content:@"" angle:10+i*30 distance:tD+t];
		 t++;
		 }*/
		
		/*[m_ARController addMarker:@"Test" angle:170 distance:tD];
		 [m_ARController addMarker:@"Test" angle:180 distance:tD];
		 [m_ARController addMarker:@"Test" angle:190 distance:tD];*/
		
		/*[m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.010514581750044 longitude:12.1004319190979]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:48.982989 longitude:12.2738]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.0186773 longitude:12.0308]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:19.241 longitude:12.0]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:16.00550044 longitude:12.49190979]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:48.92989 longitude:5]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.01773 longitude:12.0308]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.023241 longitude:12.115811]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:25.010514581750044 longitude:12.1004319190979]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:48.9982989 longitude:12.0952738]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.0186773 longitude:45.0980308]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.023241 longitude:12.115811]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:36 longitude:12.1004319190979]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:48.9982989 longitude:12.0952738]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:49.0186773 longitude:13.0980308]];
		 [m_ARController addMarker:@"Test" location:[[CLLocation alloc] initWithLatitude:4.023241 longitude:11.11811]];*/
		
		// hide button to switch to radar if autoswitch is enabled
		radarButton.hidden = m_ARController.autoSwitchToRadar;
		
		
#if (TARGET_IPHONE_SIMULATOR)
		// simulator testing coordinates
		m_ARController.myLocation = [[CLLocation alloc] initWithLatitude:49.009860 longitude:12.108049];
#endif
	}
	
	
	overlay.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	[m_ARController.mainView addSubview:overlay];
	overlay.frame = CGRectMake(0, 0, 320, 460);
	
	arActive = YES;
}


- (void) markerClicked:(ARMarker*)marker {
	if (marker != nil) {
		DLog(@"markerClicked: %@", marker.title);
		debugLabel.text = [[[NSString alloc] initWithFormat:@"%@ - %@", marker.title, marker.content] autorelease];
	}
	else debugLabel.text = [[[NSString alloc] initWithFormat:@""] autorelease];
}


- (void)dealloc 
{
	[m_ARController release];//release OpenGL view
	[window release];
	[super dealloc];
}

- (IBAction) doStartButton {
	if (arActive) return;
	
	[overlay removeFromSuperview];
    [self setupAR];
}

- (IBAction) doStopButton {
	if (!arActive) return;
	
	[overlay removeFromSuperview];
	[window addSubview:overlay];
	overlay.frame = CGRectMake(0, 20, 320, 460);
	[m_ARController stop];
	[m_ARController clearMarkers];
    [m_ARController.mainView removeFromSuperview];
    [m_ARController release];
	arActive = NO;
}

- (IBAction) doRadarButton {
	if (!m_ARController.inRadarMode) [m_ARController showRadar];
	else [m_ARController hideRadar];
}

- (IBAction) changeCameraXSlider {
	m_ARController.m_ARView.cameraTargetAngleX = cameraXSlider.value;
}
- (IBAction) changeCameraYSlider {
	m_ARController.directionFromAccelerometer = cameraYSlider.value;
}

@end
