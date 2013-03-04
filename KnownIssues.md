# Known Issues

## In 2.1.2573

* Radar distorts the displayed dots when looking up (UIDeviceOrientationFaceDown)
* Sometimes the Kit thinks WiFi models of devices are capable of running AR

## Fixed with 2.00.x

* orientation changes in PARViewController not yet supported; will screw up PAR orientation in space, use only Portrait for now.
* radar view will update radar dots correctly only in non-landscape orientations