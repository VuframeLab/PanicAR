//
//  MyARViewController.h
//  PanicAR DevApp
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <PanicARLib/PanicARLib.h>
#import <MapKit/MapKit.h>


typedef enum {
    RadarOff,
    RadarSmall,
    RadarFullscreen
} RadarMode;

@interface MyARViewController : ARViewController <ARControllerDelegate> {
    IBOutlet UILabel* _infoLabel;
    IBOutlet UIImageView* _signalDisplay;
    
    RadarMode _radarMode;
}

- (void)updateInfoLabel;


- (BOOL)checkForAR:(BOOL)showErrors;
- (void)createARMarkers;
- (void)createARContent;
- (void)createARBuilding;

@end
