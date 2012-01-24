# Changelog

**Important: Review this document before upgrading your project to a new revisions of PanicAR**

## v1.20

**Major Update:** UIKit, AVFoundation, iOS 5, Gyroscope-Tracking, Point of Interests

This version of PanicAR brings major updates and heavy refactoring in the API and objects. You need to change the code in your app in order for it to use PanicAR 1.2.

**Most Important Changes**

- the prefix of all PanicAR-classes has changed from 'AR' to 'PAR'
	- this heavy refactoring was neccessary to ensure compatibility to peoples own code (which might already implement classes with the same names as the old classes had: ARView, ARController, etc.)
	- -> rename all your references using Xcode refactoring
- the overall architecture changed
	- the AR framework now adheres to the ViewController-View pattern known from the iOS SDK
	- there is a detailed migration guide available here: [Migration Guide on gitHub.com](https://github.com/doPanic/PanicAR/wiki/Migration-Guide-1.0x----1.2)
	
- ARController
	- the ARController class has been split into two seperate classes: the PARController and the PARViewController
	- the PARController now handles sensors, configuration and all ar objects while the PARViewController handles rendering
	- PARViewController and PARView now follow the example of UIViewController and UIView
 	- PARViewController can now be subclassed and extended with own functionality
 	- PARView should not be subclassed
	- you can have more than one PARViewController (although all will display the same PAR objects)
- Terminology: 
	- objects displayed in Augmented Reality are now called "AR or PAR (PanicAR) objects"
	- AR objects tied to a Geolocation (formerly "PARMarkers") are now PanicAR POIs (Points of Interest)
	- arOrientation now of type UIInterfaceOrientation (previously UIDeviceOrientation)
	
- ARMarker 
 	- ARMarker is now PARPoiLabel 
	- is now based on PARPoi which implements MKAnnotation and is the simplest on-screen representation of a POI
	- PARPoiLabels are not stacked on screen any more – in order to be faster and allow for more POIs on screen – use PARPoiAdvancedLabel instead if you need stacking for your app
	- PARPoiAdvancedLabel provides a more extensively styled version of ARPoiLabel which changes appearance over distance and is dynamically stacked
	
- ARMarkerTemplate 
	- ARMarkerTemplateis now PARPoiLabelTemplate and can be loaded with custom size allowing for labels of different size
	- PARPoiLabelTemplate provides an updateAppearance method to update the appearance of a label template based on the distance to the user
	- PARPoi implements and updateAppearance as well, which will allows to customize a ARPoi's appearance on a per-object basis; in order to be called during the PARPoi's update cycle PARPoi.updatesAppearance must return YES. 

- you can customize a lot of aspects of how POIs are animated and rendered – see the API Documentation for further detail!

- AR Objects in General
	- you can implement your own object types using ARObjectDelegate
	- AR Objects are of type **id< ARObjectDelegate >**

- UIImagePickerController has been dropped – the camera feed is now rendered using AVFoundation
- the MapKit Framework is now a required dependency (my be weak linked)

**New Features**

- UIKit-driven Point-Of-Interest visualization
	- easily exchange existing templates for 
- gyroscope-based tracking with use of optimized iOS 5 features
- fallbacks for devices without Gyroscope or iOS 5
- compatible to virtually all UIKit elements (image, text, video, webview, etc.)
- the radar display is now handled by PARRadarView
 	- can be displayed in fullscreen mode or as a thumbnail
	- size and position are fully controllable
	- the radar representation of each PARPoi is accessible and can be customized
- more usable, Apple-style documentation
- better demo project / application
- PARViewController
	- support for all UI orientations (PARViewController.rotatesARView returns NO)
	- support for dynamic 360 degrees orientation of device (PARViewController.rotatesARView returns YES)

**PanicAR 3D Features**

We are offering an advanced edition of PanicAR which includes OpenGL-driven rendering of custom AR-Objects. Contact us if you are interested in PanicAR 3D.

- 3D Objects can be used in Augmented Reality view (anything you want: hotspots for wayfinding, routes, architecture, landmarks, etc.)
- virtual objects, that are not tied to a GPS location can be used in PAR (i.e. for user interface)
- many different object types: 3D Model, 3D Scene, Billboard, Virtual Object
- take picture of camera and PAR content rendered in (in any resolution you want)
- access the render pipeline for advanced rendering effects (like 110 Stories, www.110stories.com)

## v1.10 

**iPad 2 Support**

- add: support for iPad 2
- add: support for iPad
- add: support for different device orientations
- add: now using CoreMotion for better motion tracking


## v1.05

**iOS 5 Hotfix**

- fix: loading view freeze on iOS 5 devices
- add: build target for highly optimized Release-Framework-Build (only for licensees, missing in public repository)


## v1.04

- fix: loading view freeze on iOS 5 devices
- fix: enableLoadingView not supported in iOS 5
- change: enableLoadingView set to 'NO' by default
- move: PARMarker to PARObjects/PARMarker
- add: pre-requisites for marker archetypes
- add: PARObjectDelegate Protocol to identify PAR objects

## 1.03b

- fix: validateAPIKey: unrecognized selector sent to class
- fix: authorizationStatus is asked in 4.2 and later

## 1.02b

- fix: exception thrown in simulator and crashes on pre-iOS-4.0 devices (cf. Issues)
- add: fundamental performance and memory-footprint improvements
- add: new Marker types: PARGeoObject, PARFreeObject, PARRadialObject, PARBillboard
- add: PARMarker constructor to add location to marker
- add: PARController:addObject, PARController:removeObject, PARController:addObjects, PARController:numberOfObjects, PARController:clearObjects
- deprecated: PARController:addMarker, PARController:addMarkerAtLocation, PARController:removeMarker, PARController:addMarkers, PARController:numberOfMarkers, PARController:clearMarkers

## v1.01

### v1.01.08b

- add: extensive handling of location manager errors (authorization, turned off/on)
- add: callback to delegate for update of info label content


### v1.01.07b

- fix: setViewport bounds of main view
- fix: localization of distance units
- fix: camera view vanishes sometimes
- change: PARVector and make it public
- change: API for use with 3D objects in PAR View


### v1.01.06b

- fix: use lowercase representation of BundleID for validation of api key


### v1.01.05b

- add: loading and resuming screen (enableLoadingView)
- fix: viewport frame (setViewport called more than once)
- add: enableMovieCapture


### v1.01.04b

- fix: radar button visibility not correctly set (in showController)


### v1.01.03b

- fix: radar positioning


### v1.01.02b

- change: use NSAssert instead of C assert
- fix: viewport resizing
- add: update branding with viewport resizing

### v1.01.01b

- add: Demo Version of Framework with Branding on Background and rendered Markers
- change: DefaultLabel to DefaultMarker (terminology globally changed from "Label" to "Marker")
- fix: window layout in non-modal mode

## v1.00

- Initial release of easy-to-use PAR Framework for iPhone 3Gs / iPhone 4