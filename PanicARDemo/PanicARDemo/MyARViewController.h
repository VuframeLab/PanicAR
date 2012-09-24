//
//  MyARViewController.h
//  PanicAR-App
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <MapKit/MapKit.h>


@interface MyARViewController : PARViewController <PARControllerDelegate, UIActionSheetDelegate> {
    
    IBOutlet UIImageView* _signalDisplay;
    PARRadarPosition _radarThumbnailPosition;
    BOOL _hasARPoiObjects;
}

@property (strong) IBOutletCollection(UILabel) NSArray *infoLabels;

- (void)updateInfoLabel;
- (void)changeTracking;

- (IBAction)showOptions:(id)sender;

- (void)createARPoiObjects;

@end
