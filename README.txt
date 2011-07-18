PanicAR Framework
========================
README

INFORMATION
========================
Check the wiki for docs and guides on how to implement:
https://github.com/doPanic/PanicAR/wiki/

For common build errors and other issues check:
https://github.com/doPanic/PanicAR/wiki/Troubleshooting


VERSION: 1.04 (iOS 5 hotfix)
========================
fix: loading view freeze on iOS 5 devices
fix: enableLoadingView not supported in iOS 5
change: enableLoadingView set to 'NO' by default
move: ARMarker to ARObjects/ARMarker
add: pre-requisites for marker archetypes
add: ARObjectDelegate Protocol to identify AR objects


KNOWN ISSUES
========================
- iPhone 3G may crash without being able to display "Not Supported" dialog
- non-metric distances are not supported at the moment
- implementation of Localisation.strings file is mandatory
- open and re-save XIB-files if build throws warnings