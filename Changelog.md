# Changelog

**Important: Review this document before upgrading your project to a new revisions of PanicAR**

## v1.20

**Major Update:** 3D Objects, Buildings, Virtual Markers, Point of Interests

This version of PanicAR brings major updates and heavy refactoring in the API and objects. You need to change the code in your app in order for it to use PanicAR 1.2.

**Most Important Changes**

- the old ARController has been split into two seperate classes: the ARController and the ARViewController
	- the ARController now handles sensors, configuration and all ar objects while the ARViewController handles rendering
	- ARViewController and ARView now follow the example of UIViewController and UIView
 	- ARViewController can now be subclassed and extended with own functionality
 	- ARView should not be subclassed
	- you can have more than one ARViewController (although all will display the same AR objects)
- Terminology: 
	- objects displayed in Augmented Reality are now called "AR objects"
	- AR objects tied to a Geolocation (formerly "ARMarkers") are now AR POIs (Points of Interest)
- ARMarker is now ARPoiLabel and based on ARPoi which implements MKAnnotation
- ARMarkerTemplate is now ARPoiLabelTemplate and can be loaded with custom size allowing for labels of different size
- the MapKit Framework is now a required dependency

**New Features**

- 3D Objects can be used in Augmented Reality view (anything you want: architecture, cars, etc.)
- virtual objects, that are not tied to a GPS location can be used in AR (i.e. for user interface)
- many different object types: Billboard, Poi Object, Virtual Object
- more usable, Apple-style documentation
- better demo project / application
- take picture of camera and AR content rendered in (in any resolution you want)
- access the render pipeline for advanced rendering effects (like 110 Stories, www.110stories.com)
- radar can now be displayed in fullscreen mode or as a thumbnail, size and position are fully controllable

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
- move: ARMarker to ARObjects/ARMarker
- add: pre-requisites for marker archetypes
- add: ARObjectDelegate Protocol to identify AR objects

## 1.03b

- fix: validateAPIKey: unrecognized selector sent to class
- fix: authorizationStatus is asked in 4.2 and later

## 1.02b

- fix: exception thrown in simulator and crashes on pre-iOS-4.0 devices (cf. Issues)
- add: fundamental performance and memory-footprint improvements
- add: new Marker types: ARGeoObject, ARFreeObject, ARRadialObject, ARBillboard
- add: ARMarker constructor to add location to marker
- add: ARController:addObject, ARController:removeObject, ARController:addObjects, ARController:numberOfObjects, ARController:clearObjects
- deprecated: ARController:addMarker, ARController:addMarkerAtLocation, ARController:removeMarker, ARController:addMarkers, ARController:numberOfMarkers, ARController:clearMarkers

## v1.01

### v1.01.08b

- add: extensive handling of location manager errors (authorization, turned off/on)
- add: callback to delegate for update of info label content


### v1.01.07b

- fix: setViewport bounds of main view
- fix: localization of distance units
- fix: camera view vanishes sometimes
- change: ARVector and make it public
- change: API for use with 3D objects in AR View


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

- Initial release of easy-to-use AR Framework for iPhone 3Gs / iPhone 4