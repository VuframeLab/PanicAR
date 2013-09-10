# PanicAR Framework

![PanicAR Image](https://raw.github.com/doPanic/PanicAR/beta/Screenshots/product.png)

by doPanic GmbH - for sales and support contact info@dopanic.com

## Why PanicAR?

* It’s fast, simple and affordable
* No monthly or annual fees
* It’s completely customizable
* It’s small (only ~4 mb)
* It's platform agnostic - powered by Cocoa and Cocoa only
* It’s ridiculously easy to integrate

## Why PanicAR – really?

* does the same things all the other frameworks do: even some more (i.e. "altitude")
* maintained for you by us: new devices and new OS releases will be supported
* pay on a per-app basis: a white-label license is really cheap (see here: www.dopanic.com/ar)
* support for CocoaPods (www.cocoapods.org)

## Get started now – using CocoaPods

Just add

    pod 'PanicAR', '~> 2.1'

to your podfile and do a
    
    pod install
    
simple as that. Really.


## Read More

Check API Reference
http://docs.dopanic.com/panicar

Check the wiki for tipps and guides on how to implement:
https://github.com/doPanic/PanicAR/wiki/

For common build errors and other issues check:
https://github.com/doPanic/PanicAR/wiki/Troubleshooting

## Frequently Asked Questions
### How do I enable PanicAR on non-GPS devices?

By default, PanicAR only runs, when the device is GPS enabled (i.e. all iPhones and the 3G/4G iPads), to give the best possible performance.
However, you can enable PanicAR for all devices, by calling 

    [PSKDeviceProperties setSimulateGPSForAllDevices:YES];

in your appdelegate. 

### My POIs are shown on the edge of the radar instead of the middle.

POIs, which are further away than the radar range, are shown at the edge.
You can set this range by calling

    [self.arRadarView setRadarRange:1500];

with a higher value in your PARViewController extension.
The value sets the radius of the radar view in meters.

### I want to replace the image of a POI on the radar view

You can change the image of the POI on the radar view by setting the POIs radarView property:

    PARPoi* poi = [[poiLabelClass alloc] initWithTitle:@"circle"
                    theDescription:@"circle"
                    atLocation:[[CLLocation alloc] initWithLatitude:51.500141 longitude:-0.126257]
    ];
    poi.radarView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"myDot"]];

### I want to have labels for North/East/South/West on my Radarview

You can achieve this by setting the backgroundImageView property of the RadarView (you need to rotate it depending on the heading).

OR 

by adding 4 POIs, each with an image containing the Letter (N, E, S, W) placed North/East/South/West of the user.

### How do I change a POIs location without making it flicker?

To change the position of an existing POI, use the setLocation method, followed by updateLocation:

    // Move all POIs along the Latitudes.
    for(PARPoi* poi in [[PARController sharedARController] arObjects]) {
        CLLocation * loc = [poi location];
        CLLocationCoordinate2D coord = [loc coordinate];
        [poi setLocation: [[CLLocation alloc] initWithLatitude:coord.latitude += 0.0001f longitude:coord.longitude]];
        [poi updateLocation];
    };

### I get a message "Wrong Orientation!" when looking up

Make sure to override the switchFaceDown method:

    -(void)switchFaceDown:(BOOL)inFaceDown {
        // make sure this is an empty call; otherwise the PARViewController will display a HUD text once the device goes
        // into UIDeviceOrientationFaceDown (which it will when the user looks up)
    }

### How do I get the labels to stack above each other?

Extend PARPoiAdvancedLabel (not just PARPOILabel) and overwrite -(BOOL)stacksInView so that it returns YES

### How can I enable interaction with the POI labels?

POILabels are just views, so anything that is possible with them is also possible with POI labels.

### Where do i put the API key?
You need to set the API key via the setApiKey method of [PARController sharedARController].
You e.g. can do this in the loadView method of your controller:

     - (void)loadView
      {
       // IMPORTANT: set Api Key before calling super:loadView!
       [[PARController sharedARController] setApiKey:@""];
       [[PARController sharedARController] setDelegate:self];
       [super loadView];
       [self.arRadarView setRadarRange:1500];
    }

### I get duplicate symbol warnings
This can happen if the -load_all linker flag is used, reportedly. Try removing it.
