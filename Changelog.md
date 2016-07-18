# Changelog

**Important: Review this document before upgrading your project to a new revisions of PanicAR**


---

### 3.0 (build 3261)

- add: Bitcode
- add: 64bit slice
- add: Xcode 7 support
- add: latest device definitions (iPad Pro, iPhone SE)
- add: iOS 9 support

### 2.2 (build 3025)

- add: missing localized strings

### 2.2 (build 3017)

- add: camera permission handling

### 2.2 (build 2980)

- fix: description for poilabel on iOS 8

### 2.2 (build 2955)

- add: iOS 8 supporting sensor kit version

### 2.2 (build 2930)

- demo: added PanicARKit.strings to enable localization
- fix: localization always loaded from builtin strings file

### 2.2 (build 2870)

- add: support for iOS 8

### 2.1 (build 2672)

- add: support for iPad Air, iPhone 5c, iPhone 5s
- demo: fixed some storyboard flags
- demo: PARPoiFactory now uses same class as defined for sample pois

### 2.1 (build 2668)
- fix: fixed a memory leak
- demo: adapted layout to iOS 7
- feature: added possibility to fake location (see Demo for code)

### 2.1 (build 2667)
- fix: A crash, that sometimes occured when opening MapView (Demo)
- add: Support for 64Bit Simulator

### 2.1 (build 2652)
- fix: a Message is shown, if the user has disabled compass calibration in Privacy Settings -> System Services (which breaks the compass)
- fix: rotation of the radarview was incorrect in landscape
- fix: ARView is rotated correctly when no navigation controller is used
- fix: Library did not support Architecture i386 (Simulator)
- fix: Crash on leaving PARGLViewController
- fix: RadarDots were not removed when changing Clipping
- add: Functionality to capture screenshots

### 2.1 (build 2646)
- fix: clean up console output

### 2.1 (build 2642)
- fix: ordering of POIs by distance was ignored
- add: Big Cities Feature: POIFactory knows the locations of the largest 829 cities of the world
- add: Possibility to tell PSKDeviceProperties to allow AR for non GPS devices.

### 2.1 (build 2583)

- fix: PARPoi:initWithImage does not fallback to load from PanicARKitResources.bundle
- add: sample Poi displaying an image

### 2.1 (build 2573)

**Updates**

- removes DEBUG and RELEASE variants of framework, only one PanicARKit.framework – always use that one
- supported devices now are: iPhone 4, iPhone 4s, iPhone 5, iPad 2, iPad 3 (new iPad), iPad 4, iPad Mini
- supported iOS versions now are: 5.x, 6.x
- adds a PanicARKitResources.bundle which contains all the default resources which will be loaded if the app's main bundle does not contain it, e.g. DefaultPoiLabel.xib
- adds support for CocoaPods, the repository contains a podspec (PanicAR.podspec) which we will submit to the central cocoapods podspec repository shortly
- adds *PARPoiFactor* (formerly *PARSimulator*) to the framework; this makes it easy to create POIs for test purposes
- the Demo app has been overhauled and improved:
	- integrates PARPoiFactory
	- drops the sloppy #define LABEL <type of poi class you want> in favor of some [PARPoiLabel class] runtime selection
	- removes redundant code
- PARObjectDelegate: changed renderInView:(PARView *)theView to renderInView:(UIView *)theView, add cast to (PARView *) to any of your code that previously was dependant on an PARView object being passed

**Fixes**

- fixes an issue where the radar will be distorted during orientation changes
- fixes an issue where the radar won't appear again once the device was in UIDeviceOrientationFaceDown orientation
- fixes an issue where PARController will not start the sensor update when no arObjects are added
- fixes an issue where POI objects are clipped to early at the upper screen border when a labelBaseline is set to something other than the default
- fixes an issue where PSKDeviceAttitude did not return nil for location when the location is invalid

**Deprecations**

*Don't use these methods any more, they will be removed in future revisions.*

- PARViewController: touchDragX, touchMovedX, touchDragY, touchMovedY, resetTouchDrag, tapped
- PARView: activeView, setActiveView
- PARRadarView: activeView, setActiveView

### v2.00 build 2231 **hotfix**

- fix: enable **ARC** on PanicARKit.framework (fixes _dyld: lazy symbol binding failed: Symbol not found: _objc_setProperty_nonatomic_ error on startup)
- fix: crash on MapView

### v2.00 build 2203 (to 2217)

- fix: removing a POI leaves the dot on the radar behind
- add: PanicARKitTests.mm for use with GHUnit (SenTestingKit and integrated Xcode Tests don't work!)
- add: Storyboard IBOutletCollection order workaround

## v2.00

- Framework is now called PanicARKit
- iOS 6 support and pre-iOS 5 deprecation
- **armv7s compatible**
- supported devices now are: iPhone 4, iPhone 4s, iPhone 5, iPad 2, iPad 3 (new iPad)
- supported iOS versions now are: 5.0 and later
- supports all orientations and dynamic changes with and without orientation lock
- accuracy and stability fixes
- UI improvements: radar view improvements, new notificationView (e.g. "Location Services Denied")
- handling for changes in authorization status for location services

_This version of PanicAR brings major updates and heavy refactoring in the API and objects. You need to change the code in your app in order for it to use PanicAR 2.0._

**Most Important Changes**

- Demo Project now compatible with Retina iPad and 4 inch iPhone
- PanicARLib.framework > PanicARKit.framework – make sure you update your import directive to **_#import &lt;PanicARKit/PanicARKit.h&gt;_**
- Sensor-handling code moved to PanicSensorKit (included in PanicARKit.framework)
- Localizable.strings is now PanicARKit.strings and contains all default localization strings
- PanicSensorKit (PSK-prefixed classes) which handles all sensor access and device compatbility
	- PSKSensorManager (formerly _PARSensorManager_):
		- removed _enableUpdateHeadingFromLocationManager_
	- PSKSensorDelegate: dropped _ar_ prefix from all delegate methods
- PARCapabilities has been dropped in favor of the PSKDeviceProperties class
- PARManager
	- removed public API _updateAfterLocationChange__ and _sortMarkersByDistance_
	- deprecated _isFrozen_ and _setFrozen_ use PARViewController _isPaused_ and _setPaused_ for same functionality
- PARControllerDelegate: removed _arPreRenderPass_ and _arPostRenderPass_ because they are not used
- PARViewController
	- now uses supportedInterfaceOrientations instead of shouldAutorotateToInterfaceOrientation
	- supportedInterfaceOrientations will return UIInterfaceOrientationMaskAllButUpsideDown if _rotatesARView_ is NO, otherwise it returns UIInterfaceOrientationMaskPortrait
	- override supportedInterfaceOrientations in your PARViewController subclass to change this behavior
- Additions: PARAvailability enum, PSKStatus enum
- refactored a lot of unneccesarily exposed members into private categories. Let me know if you are experiences issues with that at azeitler@dopanic.com.

---

### v1.20.1072 to v1.20.1085 - critical fix

change: PARCapabilities changed the casing on some of its members
fix: BAD_ACCESS on PARController:clearObjects and PARController:removeObject when using PARPoi objects

### v1.20.1062 to v1.20.1071 - critical fix

fix: BAD_ACCESS on PARController:clearObjects and PARController:removeObject
fix: Memory Leak in PARSensorManager:deviceType

### v1.20.995 to v1.20.1056 - minor bug fixes

fix: PARPoi and subclass-objects are not removed from View when removing object from PARController
fix: removing a PARObjectDelegate-object from PARController will cause BAD_ACCESS
fix: localisation strings not included / not correctly formated
fix: tap-interaction sample code in demo app not working -> replaced with showing Alert on tapping a label

---

## v1.20

**Major Update:**

- UIKit-only rendering
- AVFoundation camera preview
- iOS 5 support
- Gyroscope tracking
- Point of Interest

_This version of PanicAR brings major updates and heavy refactoring in the API and objects. You need to change the code in your app in order for it to use PanicAR 1.2._

**Most Important Changes**

- the prefix of all PanicAR-classes has changed from 'AR' to 'PAR'
	- this heavy refactoring was neccessary to ensure compatibility to peoples own code (which might already implement classes with the same names as the old classes had: ARView, ARController, etc.)
	- -> rename all your references using Xcode refactoring
- the overall architecture changed
	- the AR framework now adheres to the ViewController-View pattern known from the iOS SDK

- ARController
	- the ARController class has been split into two seperate classes: the PARController, PARSensorManager and the PARViewController
	- the PARController now handles configuration and all ar objects while the PARSensorManager handles device sensors and fallbacks and the PARViewController handles rendering
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
- Console functionality has been removed – is now displayed directly in MyARViewController view UI

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

---

### v1.10

**iPad 2 Support**

- add: support for iPad 2
- add: support for iPad
- add: support for different device orientations
- add: now using CoreMotion for better motion tracking

---

### v1.05

**iOS 5 Hotfix**

- fix: loading view setFrozen:NO on iOS 5 devices
- add: build target for highly optimized Release-Framework-Build (only for licensees, missing in public repository)


### v1.04

- fix: loading view setFrozen:NO on iOS 5 devices
- fix: enableLoadingView not supported in iOS 5
- change: enableLoadingView set to 'NO' by default
- move: PARMarker to PARObjects/PARMarker
- add: pre-requisites for marker archetypes
- add: PARObjectDelegate Protocol to identify PAR objects

### 1.03b

- fix: validateAPIKey: unrecognized selector sent to class
- fix: authorizationStatus is asked in 4.2 and later

### 1.02b

- fix: exception thrown in simulator and crashes on pre-iOS-4.0 devices (cf. Issues)
- add: fundamental performance and memory-footprint improvements
- add: new Marker types: PARGeoObject, PARFreeObject, PARRadialObject, PARBillboard
- add: PARMarker constructor to add location to marker
- add: PARController:addObject, PARController:removeObject, PARController:addObjects, PARController:numberOfObjects, PARController:clearObjects
- deprecated: PARController:addMarker, PARController:addMarkerAtLocation, PARController:removeMarker, PARController:addMarkers, PARController:numberOfMarkers, PARController:clearMarkers

### v1.01

#### v1.01.08b

- add: extensive handling of location manager errors (authorization, turned off/on)
- add: callback to delegate for update of info label content


#### v1.01.07b

- fix: setViewport bounds of main view
- fix: localization of distance units
- fix: camera view vanishes sometimes
- change: PARVector and make it public
- change: API for use with 3D objects in PAR View


#### v1.01.06b

- fix: use lowercase representation of BundleID for validation of api key


#### v1.01.05b

- add: loading and resuming screen (enableLoadingView)
- fix: viewport frame (setViewport called more than once)
- add: enableMovieCapture


#### v1.01.04b

- fix: radar button visibility not correctly set (in showController)


#### v1.01.03b

- fix: radar positioning


#### v1.01.02b

- change: use NSAssert instead of C assert
- fix: viewport resizing
- add: update branding with viewport resizing

#### v1.01.01b

- add: Demo Version of Framework with Branding on Background and rendered Markers
- change: DefaultLabel to DefaultMarker (terminology globally changed from "Label" to "Marker")
- fix: window layout in non-modal mode

### v1.00

- Initial release of easy-to-use PAR Framework for iPhone 3Gs / iPhone 4
