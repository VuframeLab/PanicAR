# PanicAR Framework

## v1.30 (experimental)

* use 3d objects in AR view
 * ARFreeObject
 * ARGeoObject
 * ARBillboard
* access to render pipeline via pre and post render events (in ARControllerDelegate)

### Older Versions

* v1.20
 * adds iPad 2 support
 * AVFoundation
 * customizable Radar for Fullscreen and Thumbnail use

* v1.10
 * major API changes
 * sticks to convention
 * ARController for object management and config
 * ARViewController for rendering (subclass of UIViewController)

## INFORMATION

### Check the wiki for docs and guides on how to implement

https://github.com/doPanic/PanicAR/wiki/

### For common build errors and other issues check

https://github.com/doPanic/PanicAR/wiki/Troubleshooting

### API Reference

Available at:
http://documentation.dopanic.com/panicar/

Reference for the current experimental build available at:
http://documentation.dopanic.com/panicar-preview/

## KNOWN ISSUES

* iPhone 3G may crash without being able to display "Not Supported" dialog
* non-metric distances are not supported at the moment