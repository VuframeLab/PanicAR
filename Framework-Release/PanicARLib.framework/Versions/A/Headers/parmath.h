/*
 *  PARMath.h
 *  PanicAR
 *
 *  Created by Andreas Zeitler on 24.08.10.
 *  Copyright 2010 doPanic. All rights reserved.
 *
 */

#ifndef PanicARLib_ARMath_h
#define PanicARLib_ARMath_h

#import "math.h"
#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>


#pragma mark - Vector

typedef struct {
	float x;
	float y;
	float z;
} PARVector3;
typedef struct {
	float x;
	float y;
	float z;
	float w;
} PARVector4;

PARVector3 PARVector3Normalize(PARVector3 vec);
float PARVector3AngleTowards(PARVector3 from, PARVector3 to);

float PARVector3Angle(PARVector3 *vec);
float PARVector4Angle(PARVector4 *vec);
float PARVector3Elevation(PARVector3 *vec);

#pragma mark - Matrix
typedef float PARMatrix3x3[9];	// 3x3 PARMatrix in column major order
typedef float PARMatrix4x4[16];	// 4x4 PARMatrix in column major order

void PARMatrixCopy(PARMatrix4x4 mout, PARMatrix4x4 from);
void PARMatrixCopyFromMatrix3(PARMatrix4x4 mout, PARMatrix3x3 from);
void PARMatrix3SetIdentity(PARMatrix3x3 mout);
void PARMatrixSetIdentity(PARMatrix4x4 mout);
void PARMatrixSetXRotationUsingRadians(PARMatrix4x4 mout, float degrees);
void PARMatrixSetXRotationUsingDegrees(PARMatrix4x4 mout, float degrees);
void PARMatrixSetYRotationUsingRadians(PARMatrix4x4 mout, float degrees);
void PARMatrixSetYRotationUsingDegrees(PARMatrix4x4 mout, float degrees);
void PARMatrixSetZRotationUsingRadians(PARMatrix4x4 mout, float degrees);
void PARMatrixSetZRotationUsingDegrees(PARMatrix4x4 mout, float degrees);
void PARMatrixPrint(NSString *title, const PARMatrix4x4 mat);

// Creates a projection PARMatrix using the given y-axis field-of-view, aspect ratio, and near and far clipping planes
void PARMatrixCreateProjection(PARMatrix4x4 mout, float fovy, float aspect, float zNear, float zFar);
void PARMatrixCreateOrthographic(PARMatrix4x4 mout, float left, float right, float bottom, float top, float zNear, float zFar);

// Matrix-vector and PARMatrix-matricx multiplication routines
void PARMatrix3x3MultiplyWithVector3(PARVector3 *vout, const PARMatrix3x3 m, const PARVector3 v);
void PARMatrix3x3MultiplyWithMatrix3x3(PARMatrix3x3 c, const PARMatrix3x3 a, const PARMatrix3x3 b);

void PARMatrixMultiplyWithVector(PARVector4 *vout, const PARMatrix4x4 m, const PARVector4 v);
void PARMatrixMultiplyWithVector3(PARVector3 *vout, const PARMatrix4x4 m, const PARVector3 v);
void PARMatrixMultiplyWithMatrix(PARMatrix4x4 c, const PARMatrix4x4 a, const PARMatrix4x4 b);
void PARMatrixFastMultiplyWithMatrix(PARMatrix4x4 result, PARMatrix4x4 m1, PARMatrix4x4 m2);

// Initialize mout to be an affine transform corresponding to the same rotation specified by m
void PARMatrixFromCMRotationMatrix(PARMatrix4x4 mout, const CMRotationMatrix *m);


#pragma mark - Quaternion

#define QUATERNION_TRACE_ZERO_TOLERANCE 0.00001

typedef struct {
    float x;
    float y;
    float z;
    float w;
} PARQuaternion;

void PARQuaternionNormalize(PARQuaternion *quaternion);
PARQuaternion PARQuaternionMakeWithMatrix3D(PARMatrix4x4 matrix);
void PARMatrix4SetUsingQuaternion3D(PARMatrix4x4 matrix, PARQuaternion quat);
PARQuaternion PARQuaternionMakeWithAxisAndAngle(PARVector3 axis, float angle);
void PARQuaternionExtractAxisAndAngle(PARQuaternion quat, PARVector3 *axis, float *angle);
void PARQuaternionMultiply(PARQuaternion *quat1, PARQuaternion *quat2);
void PARQuaternionInvert(PARQuaternion  *quat);
PARQuaternion PARQuaternionMakeWithEulerAngles(float x, float y, float z);
PARVector3 PARQuaternionToEuler(PARQuaternion q);
PARQuaternion PARQuaternionConjugate (PARQuaternion q);
PARVector3 PARQuaternionMultiplyVector3 (PARQuaternion q, PARVector3 vec);


#pragma mark - Geodetic Utils


#define WGS84_A	(6378137.0)				// WGS 84 semi-major axis constant in meters
#define WGS84_E (8.1819190842622e-2)	// WGS 84 eccentricity

/// <summary>
/// Calculates the end-point from a given source at a given range (meters) and bearing (degrees).
/// This methods uses simple geometry equations to calculate the end-point.
/// </summary>
/// <param name="source">Point of origin</param>
/// <param name="range">Range in meters</param>
/// <param name="bearing">Bearing in degrees</param>
/// <returns>End-point from the source given the desired range and bearing.</returns>
CLLocationCoordinate2D calculatePositionInDistance(CLLocationCoordinate2D source, double range, double bearing);

// Converts latitude, longitude to ECEF coordinate system
void convertLatLonToEcef(double lat, double lon, double alt, double *x, double *y, double *z);

// Coverts ECEF to ENU coordinates centered at given lat, lon
void ecefToEnu(double lat, double lon, double x, double y, double z, double xr, double yr, double zr, double *e, double *n, double *u);


#endif