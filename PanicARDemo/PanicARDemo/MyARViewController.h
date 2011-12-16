//
//  MyARViewController.h
//  PanicAR DevApp
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <PanicARLib/PanicARLib.h>
#import <MapKit/MapKit.h>



@interface MyARViewController : ARViewController <ARControllerDelegate> {
    IBOutlet UILabel* _infoLabel;
    IBOutlet UIImageView* _signalDisplay;
    ARRadarPosition _radarThumbnailPosition;
    BOOL _hasARContent;
    BOOL _hasARPoiObjects;
    BOOL _hasARBuilding;
    ARPoiObject* _building;
}

- (void)updateInfoLabel;

#if DEBUG
/*! console is only used in debug mode */
- (IBAction)switchConsole:(id)sender;
#endif

- (BOOL)checkForAR:(BOOL)showErrors;
- (void)createARPoiObjects;
- (void)createARContent;
- (void)createARBuilding;

@end
