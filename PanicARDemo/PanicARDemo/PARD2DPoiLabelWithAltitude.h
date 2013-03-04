//
//  PARD2DPoiLabelWithAltitude.h
//  PanicARDemo
//
// An Extension of the PARPoiLabel that also includes altitude information
//
//  Created by Andreas Zeitler on 26.02.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

@interface PARD2DPoiLabelWithAltitude : PARPoiLabel

// add a field to store the altitude information
@property (nonatomic,assign) float altitude;

@end
