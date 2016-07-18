//
//  PARDMapViewController.h
//  PanicARDemo
//
//  Created by Andreas Zeitler on 22.02.2013
//  Copyright (c) 2011 Vuframe Lab GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface PARDMapViewController : UIViewController <MKMapViewDelegate> {
    MKMapView* _mapView;
}

@property (retain, nonatomic) IBOutlet MKMapView *mapView;

- (IBAction)doCompassTracking:(id)sender;

@end
