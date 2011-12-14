//
//  ConfigViewController.h
//  PanicAR DevApp
//
//  Created by Andreas Zeitler on 15.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PanicARLib/PanicARLib.h>
#import <MapKit/MapKit.h>

@interface ConfigViewController : UIViewController <MKMapViewDelegate> {
    MKMapView* _mapView;
}

@property (retain, nonatomic) IBOutlet MKMapView *mapView;

- (IBAction)doCompassTracking:(id)sender;

@end
