//
//  Tests.m
//  Tests
//
//  Created by Andreas Zeitler on 08.08.12.
//  Copyright (c) 2012 doPanic GmbH. All rights reserved.
//

#import <SenTestingKit/SenTestingKit.h>
#import <PanicARKit/PanicARKit.h>

@interface PanicARKitTests : SenTestCase

@end

@implementation PanicARKitTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)test_DefaultPoiLabel
{
    STAssertNotNil([PARPoiLabelTemplate loadPoiLabelTemplate:@"DefaultPoiLabel"], @"DefaultPoiLabel is nil, include 'DefaultPoiLabel.xib' in the target!");
}

@end
