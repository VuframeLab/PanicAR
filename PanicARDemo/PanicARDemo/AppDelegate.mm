//
//  AppDelegate.m
//  PanicAR DevApp
//
//  Created by Andreas Zeitler on 15.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "AppDelegate.h"
#import <PanicARLib/PanicARLib.h>
#import "MyARViewController.h"
#import "AboutViewController.h"


@implementation AppDelegate

@synthesize window = _window;
@synthesize tabBarController = _tabBarController;

- (void)dealloc
{
    [_window release];
    [_tabBarController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    
    
    // Override point for customization after application launch.
    UIViewController *viewController1, *viewController2;
    UINavigationController* navigation1 = [[UINavigationController alloc] init];
    UINavigationController* navigation2 = [[UINavigationController alloc] init];
    navigation1.navigationBar.barStyle = UIBarStyleBlackOpaque;
    navigation2.navigationBar.barStyle = UIBarStyleBlackOpaque;
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        viewController1 = [[[MyARViewController alloc] initWithNibName:@"MyARViewController_iPhone" bundle:nil] autorelease];
        viewController2 = [[[AboutViewController alloc] initWithNibName:@"AboutViewController_iPhone" bundle:nil] autorelease];
    } else {
        viewController1 = [[[MyARViewController alloc] initWithNibName:@"MyARViewController_iPad" bundle:nil] autorelease];
        viewController2 = [[[AboutViewController alloc] initWithNibName:@"AboutViewController_iPad" bundle:nil] autorelease];
    }
    navigation1.viewControllers = [NSArray arrayWithObjects:viewController1, nil];
    navigation2.viewControllers = [NSArray arrayWithObjects:viewController2, nil];
    
    self.tabBarController = [[[UITabBarController alloc] init] autorelease];
    self.tabBarController.viewControllers = [NSArray arrayWithObjects:navigation1, navigation2, nil];
    self.window.rootViewController = self.tabBarController;
    [self.window makeKeyAndVisible];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

/*
// Optional UITabBarControllerDelegate method.
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController
{
}
*/

/*
// Optional UITabBarControllerDelegate method.
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed
{
}
*/


#pragma mark - Utils



@end
