//
//  ARMarkerDelegate.h
//  PanicAR
//
//  Created by Andreas Zeitler on 01.09.10.
//  Copyright 2010 doPanic. All rights reserved.
//


#include "ARMarker.h"

@class ARMarker;

@protocol AREventHandler
	- (void) markerClicked:(ARMarker*)marker;
@end
