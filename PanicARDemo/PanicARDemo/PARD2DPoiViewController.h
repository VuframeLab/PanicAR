//
//  PARD2DPoiViewController.h
//  PanicARDemo
//  A basic example of UIKit-driven rendering of Points of Interest
//  POIs are automatically layouted and stacked
//
//
//  Created by Andreas Zeitler on 16.10.11.
//  Copyright (c) 2011 Vuframe Lab GmbH. All rights reserved.
//

#import <MapKit/MapKit.h>


@interface PARD2DPoiViewController : PARViewController <PARControllerDelegate, UIActionSheetDelegate> {
    
    IBOutlet UIImageView* _signalDisplay;
    PARRadarPosition _radarThumbnailPosition;

    //TODO: Explain why we need this
    BOOL _hasARPoiObjects;
}

@property (strong) IBOutletCollection(UILabel) NSArray *infoLabels;

- (void)updateInfoLabel;

- (IBAction)showOptions:(id)sender;

// Creates example Points of Interest
- (void)createARPoiObjects;

@end
