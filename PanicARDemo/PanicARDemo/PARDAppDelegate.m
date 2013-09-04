//
//  PARDAppDelegate.m
//  PanicARDemo
//
//  Created by Andreas Zeitler on 22.02.13.
//  Copyright (c) 2013 doPanic GmbH. All rights reserved.
//

#import "PARDAppDelegate.h"

@implementation PARDAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
   
    // Allow all devices to use Location Services.
    [PSKDeviceProperties setSimulateGPSForAllDevices:YES];
    
    return YES;
}
							
- (void)applicationWillResignActive{

}

- (void)applicationDidEnterBackground:(UIApplication *)application
{    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.

    // Always call this when becoming inactive
    [[PARController sharedARController] suspendToBackground];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.

    // Always call this when becoming active again
    [[PARController sharedARController] resumeFromBackground];
    
    // check, if device supports AR everytime the application becomes active
    // this way, we can react to changing settings, like disabled location services
    // if the device currently does not support AR, show standard error alerts
    [PARController deviceSupportsAR:YES];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
}


- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}





@end
