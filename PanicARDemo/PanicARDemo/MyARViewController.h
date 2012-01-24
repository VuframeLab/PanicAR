//
//  MyARViewController.h
//  PanicAR-App
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <PanicARLib/PanicARLib.h>
#import <MapKit/MapKit.h>



@interface MyARViewController : PARViewController <PARControllerDelegate> {
    IBOutlet UILabel* _infoLabel;
    IBOutlet UIImageView* _signalDisplay;
    PARRadarPosition _radarThumbnailPosition;
    BOOL _hasARPoiObjects;
}

- (void)updateInfoLabel;

#if DEBUG
/*! console is only used in debug mode */
- (IBAction)switchConsole:(id)sender;
#endif

- (void)createARPoiObjects;

@end
