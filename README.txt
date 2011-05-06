PanicAR Framework
========================
README

INFORMATION
========================
Check the wiki for docs and guides on how to implement:
https://github.com/doPanic/PanicAR/wiki/

For common build errors and other issues check:
https://github.com/doPanic/PanicAR/wiki/Troubleshooting


CHANGELOG
========================
1.03b
fix: validateAPIKey: unrecognized selector sent to class
fix: authorizationStatus is asked in 4.2 and later

1.02b
fix: exception thrown in simulator and crashes on pre-iOS-4.0 devices (cf. Issues)


KNOWN ISSUES
========================
- iPhone 3G may crash without being able to display "Not Supported" dialog
- non-metric distances are not supported at the moment
- implementation of Localisation.strings file is mandatory
- open and re-save XIB-files if build throws warnings