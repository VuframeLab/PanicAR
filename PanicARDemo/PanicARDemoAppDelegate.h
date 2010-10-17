#import <UIKit/UIKit.h>
#import "ARController.h"
#import <MobileCoreServices/UTCoreTypes.h>
#import <MobileCoreServices/UTType.h>

@class ARController;

@interface PanicARDemoAppDelegate : NSObject <UIApplicationDelegate, AREventHandler> 
{
    UIWindow *window;
    UIWindow *overlay;
	ARController* m_ARController;
	bool arActive;
	
	UIButton *startButton;
	UIButton *stopButton;
	UIButton *radarButton;
	UILabel *debugLabel;
	UISlider *cameraXSlider;
	UISlider *cameraYSlider;
}

@property (nonatomic, retain) IBOutlet UIWindow* window;
@property (nonatomic, retain) IBOutlet UIView* overlay;

@property (nonatomic, retain) IBOutlet UIButton *startButton;
@property (nonatomic, retain) IBOutlet UIButton *stopButton;
@property (nonatomic, retain) IBOutlet UIButton *radarButton;
@property (nonatomic, retain) IBOutlet UILabel *debugLabel;
@property (nonatomic, retain) IBOutlet UISlider *cameraXSlider;
@property (nonatomic, retain) IBOutlet UISlider *cameraYSlider;

- (IBAction)doStartButton;
- (IBAction)doStopButton;
- (IBAction)doRadarButton;
- (IBAction)changeCameraXSlider;
- (IBAction)changeCameraYSlider;

- (void) setupAR;
- (void) markerClicked:(ARMarker*)marker;


@end

