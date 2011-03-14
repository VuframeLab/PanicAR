#import <UIKit/UIKit.h>
#import <PanicARLib_Demo/PanicARLib.h>

@class ARController;

@interface PanicARDemoAppDelegate : NSObject <UIApplicationDelegate, ARControllerDelegate, UITabBarControllerDelegate> {
    UIWindow *window;
    UITabBarController *tabBarController;
	ARController* m_ARController;
	
	UIButton *showModalView;
	UIButton *createARController;
	UIButton *releaseARController;
	UIButton *addARMarkers;
	UIButton *clearARMarkers;
	UILabel *labelController;
	UILabel *labelMarkers;
}

@property (nonatomic, retain) IBOutlet UIWindow* window;
@property (nonatomic, retain) IBOutlet UITabBarController* tabBarController;

- (IBAction)webButton_click;

- (void) showAR;
- (void) createAR;
- (void) createMarkers;
- (void) releaseAR;
- (void) updateButtons;
- (void) markerTapped:(ARMarker*)marker;


@end
