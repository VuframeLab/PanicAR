//
//  ARController.h
//  PanicAR
//
//  Created by Andreas Zeitler on 17.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "ARView.h"
#import "ARMarker.h"
#import "AREventHandler.h"
#import "ARMarkerDelegate.h"
#include "Mesh.h"
#import "ARLabelTemplate.h"
#import <MobileCoreServices/UTCoreTypes.h>
#import <MobileCoreServices/UTType.h>

@class ARMarker;
@class ARController;
@class ARLabelTemplate;
@class ARView;

#pragma mark -
#pragma mark Constants

//#define k_TextureSizeX 256
//#define k_TextureSizeY 128

#define k_CameraTransform_X 1
#define k_CameraTransform_Y 1

#define k_RadarPlane -200
#define k_RadarSize 2.3
#define k_RadarDot 7
#define k_Radar_FadeBackwardDots NO

#define k_Sectors 36 
#define k_Segment()(360.0/k_Sectors)
#define k_LabelYOffset 1.6
#define k_LabelBaseLine -2

#define k_CameraMinTilt -45
#define k_CameraMaxTilt 90
#define k_SwipeSpeed 0.005f
#define k_SwipeSpeed_Y 0.2f

#define k_AccelSmooth 5
#define  k_CameraTurnXSmooth 15
#define  k_CameraTurnYSmooth 8
#define  k_CameraMoveYSmooth 8

#define k_zNear 0.1f
#define k_zFar 25000.0f
#define k_fieldOfView 33.3
#define k_fieldOfView_wide 50


#define k_ClipMarkersOutsideFOV 35
#define k_DisableMarkersOutsideFOV 50

#define k_MarkerSmooth 25
#define k_LabelSize 50
#define k_DistanceFactor 5


extern ARController* activeController;
extern ARLabelTemplate* defaultLabelTemplate;
extern Mesh defaultLabelMesh;
extern Mesh radarMesh;
extern uint radarDot;
extern uint radarBG;
extern bool useViewRotation;
extern Mesh coordinatesMesh;
extern uint coordinatesTexture;
extern NSString* locationErrorMessage;

#pragma mark -
#pragma mark Interface

/*! @class ARController
	@brief main controller of AR functionality
 
	the ARController creates and controls the CameraView, the OpenGL 3D View and the LocationManager
	it will handle all Augmented Reality calculations and the drawing of the markers
*/
@interface ARController : UIViewController <CLLocationManagerDelegate, UIAccelerometerDelegate> {
	
	bool isActive;
    bool hasLocation;
    bool needsSorting;
	
	bool useAccelerometer;
	bool autoSwitchToRadar;
	
	bool inRadarMode;
	double directionFromAccelerometer;
	double xRoll;
	double yRoll;
	double zRoll;
	double pitch;
	double roll;
	float accelerationSign;
	float rotationSign;
	bool isLandscapeView;
	
	UIDeviceOrientation arOrientation;
	float osVersion;
	
	//markers
	NSMutableArray *markers;
	NSArray *sortedMarkers;
	
	id<AREventHandler> eventHandler;
	
	//base components
	UIView* mainView;
	UIImagePickerController* cameraView; // live camera feed view
	ARView* m_ARView;
	CGRect viewport;
	float contentScale;
	
	UILabel* debugLabel;
	
	UIAccelerometer *accelerometer;
	CLLocationManager	*locationManager;
	CLLocation	*myLocation;
	double myBearing;
	
	NSTimer* m_timer;
	
	bool _markerSectors[k_Sectors][100];
	int _markerSectorsY[k_Sectors];
	
	FrameBuffer touchBuffer;
}


#pragma mark -
#pragma mark Properties

@property (nonatomic, retain) CLLocationManager	*locationManager;
@property (nonatomic, retain) id<AREventHandler> eventHandler;
@property (readonly) bool isActive;
@property (readonly) bool inRadarMode;
@property (readonly) bool hasLocation;
@property (readonly) bool useAccelerometer;
@property (readonly) bool autoSwitchToRadar;
@property (assign) double myBearing;
@property (assign) double directionFromAccelerometer;
@property (assign) bool needsSorting;
@property (nonatomic, retain) ARView	*m_ARView;
@property (nonatomic, retain) CLLocation	*myLocation;
@property (nonatomic, retain) NSMutableArray	*markers;
@property (assign) UILabel *debugLabel;
@property (readonly) CGRect viewport;
@property (readonly) float contentScale;
@property (readonly) bool isLandscapeView;
@property (readonly) float accelerationSign;
@property (readonly) float rotationSign;
@property (readonly) UIView* mainView;


#pragma mark -
#pragma mark Instance Methods


/*! @brief create ARController with startup default parameters
 
 initWithFrame: 
	allocates and initializes a new ARController instance with default settings
 
	default settings:
		- the ARController will be started (made visible) automatically
		- accelerometer is enabled (view rotates and the radar view is automatically activated if device faces down)
	
	parameters:
		- frame: ARController's view bounds
		- eHandler: event handler handling click events
*/
- (id)initWithFrame:(CGRect)frame eventHandler:(id<AREventHandler>)eHandler;

/*! @brief create ARController with startup custom parameters
 
 initWithFrame: 
	allocates and initializes a new ARController instance with custom settings
 
	parameters:
		- frame: ARController's view bounds
		- eHandler: event handler handling click events
 */
- (id)initWithFrame:(CGRect)frame autostart:(bool)autostart useAccelerom:(bool)useAccelerom useAutoSwitchToRadar:(bool)useAutoSwitchToRadar useViewRotation:(bool)viewRotation eventHandler:(id<AREventHandler>)eHandler;


- (ARMarker*)addMarkerAtLocation:(ARMarker*)marker atLocation:(CLLocation*)cllocation;
- (ARMarker*)addMarkerAsVirtual:(ARMarker*)marker angle:(float)angle distance:(float)distance;

- (void) removeMarker:(ARMarker*)marker;
- (void) clearMarkers;
- (void) sortMarkers;

- (int) numberOfMarkers;
- (void) updateMarkers:(NSTimer*)theTimer;
- (bool)markerSector:(int)y sector:(int)i;
- (int)markerSector:(int)i;
- (void)occupyMarkerSector:(int)y sector:(int)i;

- (void) deviceOrientationChanged:(NSNotification *)notification;
- (void) setViewOrientation;

- (void) start;
- (void) stop;

- (void) showRadar;
- (void) hideRadar;

- (void) TouchEvent:(CGPoint)point;
- (void) markerClicked:(ARMarker*)marker;

#pragma mark -
#pragma mark Class Methods

+ (BOOL)deviceSupportsAR;
+ (BOOL) loadMesh:(NSString*)meshFilename mesh:(Mesh&)mesh;
+ (uint) loadTexture:(NSString*)textureFilename;

@end
