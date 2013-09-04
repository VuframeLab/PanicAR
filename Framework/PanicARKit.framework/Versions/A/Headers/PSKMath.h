/*
 *  PSKMath.h
 *  PanicAR
 *
 *  Created by Andreas Zeitler on 24.08.10.
 *  copyright 2013 doPanic. All rights reserved.
 *
 */

#ifndef PanicARLib_ARMath_h
#define PanicARLib_ARMath_h

#import "math.h"
#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>

#define PSK_PRECISION float
#define PSK_MATRIX_PRECISION float


#pragma mark - Conversions
#define DEGREES_TO_RADIANS (M_PI/180.0)
#define RADIANS_TO_DEGREES (180.0/M_PI)
double deg2rad(double degrees);
double rad2deg(double radians);
float deg2radf(float degrees);
float rad2degf(float radians);
double mile2km(double miles);
double km2mile(double kms);
double feet2meter(double feet);
double meter2feet(double meters);
double mile2meters(double x);

#pragma mark - Linear Math
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
float randomf (float number);
float randomRangef (float smallNumber, float bigNumber);

double lerp(double a, double b, double t);
float lerpf(float a, float b, float t);

float smoothf(float a, float b, float t);
static inline double lerpAngle (double a, double b, double f);
float lerpAnglef (float a, float b, float f);
float deltaAngle (float a, float b);
int repeat(int value, int max);
float frepeat(float value, float max);
float signf(float n);
float relativeAngle(float angle);
float linsin(float angle);
float lincos(float angle);
double clamp(double v, double min, double max);
float clampf(float v, float min, float max);
double magnitude(double x, double y, double z);
double sqrMagnitude(double x, double y, double z);
void normalize(double *x, double *y, double *z);

#pragma mark - CGPoint Extensions
CGPoint CGPointRotatePointAboutOrigin(CGPoint point, float angle);

#pragma mark - Vector
typedef struct PSKVector3 {
	PSK_PRECISION x;
	PSK_PRECISION y;
	PSK_PRECISION z;
} PSKVector3;
typedef struct PSKVector4 {
	PSK_PRECISION x;
	PSK_PRECISION y;
	PSK_PRECISION z;
	PSK_PRECISION w;
} PSKVector4;

PSKVector3 PSKVector3RotateXZByAngle(PSKVector3 vec, float deg);

PSKVector3 PSKVector3Normalize(PSKVector3 vec);
void PSKVector3Normalize_p(PSKVector3 *vec);
float PSKVector3AngleTowards(PSKVector3 from, PSKVector3 to);

float PSKVector3Angle(PSKVector3 vec);
float PSKVector4Angle(PSKVector4 vec);
float PSKVector3Elevation(PSKVector3 *vec);

float PSKVector3Magnitude(PSKVector3 vec);
float PSKVector3SqrMagnitude(PSKVector3 vec);

PSKVector3 PSKVector3Make(float x, float y, float z);
PSKVector3 PSKVector3MakeZero();
PSKVector4 PSKVector4Make(float x, float y, float z, float w);
PSKVector4 PSKVector4MakeZero();
void PSKVector3SetZero(PSKVector3 *vec);
void PSKVector3SetOne(PSKVector3 *vec);
void PSKVector3SetForward(PSKVector3 *vec);

void PSKVector4Print(PSKVector4 vec);
NSString *NSStringFromPSKVector3(PSKVector3 vec);
NSString *NSStringFromPSKVector3Short(PSKVector3 vec);

void PSKVector3Scalef(PSKVector3 *vec, const float s);
PSKVector3 PSKVector3Scale(PSKVector3 vec, const float s);
void PSKVector3Clamp(PSKVector3 *vec, float s);
void PSKVector3Print(PSKVector3 vec);
PSKVector3 PSKVector3Multiply(PSKVector3 vec, PSKVector3 mul);
PSKVector3 PSKVector3Subtract(PSKVector3 from, PSKVector3 vec);
void PSKVector3PrintWithTitle(NSString *title, PSKVector3 vec);

PSKVector3 PSKVector3Negate(PSKVector3 vector);
bool PSKVector3Equals(PSKVector3 v1, PSKVector3 v2);

float PSKVector3DotProduct (PSKVector3 vector1, PSKVector3 vector2);
PSKVector3 PSKVector3CrossProduct (PSKVector3 vector1, PSKVector3 vector2);
float PSKVector3AngleBetweenXZ (PSKVector3 vec);



#pragma mark - Matrix
typedef float PSKMatrix3x3[9];	// 3x3 PSKMatrix in column major order
typedef float PSKMatrix4x4[16];	// 4x4 PSKMatrix in column major order

void PSKMatrixCopy(PSKMatrix4x4 mout, PSKMatrix4x4 from);
void PSKMatrixCopyFromMatrix3(PSKMatrix4x4 mout, PSKMatrix3x3 from);
void PSKMatrix3SetIdentity(PSKMatrix3x3 mout);
void PSKMatrixSetIdentity(PSKMatrix4x4 mout);
void PSKMatrixSetXRotationUsingRadians(PSKMatrix4x4 mout, float degrees);
void PSKMatrixSetXRotationUsingDegrees(PSKMatrix4x4 mout, float degrees);
void PSKMatrixSetYRotationUsingRadians(PSKMatrix4x4 mout, float degrees);
void PSKMatrixSetYRotationUsingDegrees(PSKMatrix4x4 mout, float degrees);
void PSKMatrixSetZRotationUsingRadians(PSKMatrix4x4 mout, float degrees);
void PSKMatrixSetZRotationUsingDegrees(PSKMatrix4x4 mout, float degrees);
void PSKMatrixPrint(NSString *title, const PSKMatrix4x4 mat);
NSString* NSStringFromPSKMatrix4x4(NSString *title, const PSKMatrix4x4 mat);
bool PSKMatrixToEulerXYZ(PSKMatrix4x4 m, double *rfYAngle, double *rfPAngle, double *rfRAngle);
bool PSKMatrixToEulerZXY (PSKMatrix4x4 m, double *rfYAngle, double *rfPAngle, double *rfRAngle);
PSKVector3 PKSVector3AsForwardDirectionFromMatrix(PSKMatrix4x4 mat);
PSKVector3 PKSVector3AsUpDirectionFromMatrix(PSKMatrix4x4 mat);
PSKVector3 PKSVector3AsRightDirectionFromMatrix(PSKMatrix4x4 mat);

// Creates a projection PSKMatrix using the given y-axis field-of-view, aspect ratio, and near and far clipping planes
void PSKMatrixCreateProjection(PSKMatrix4x4 mout, float fovy, float aspect, float zNear, float zFar);
void PSKMatrixCreateOrthographic(PSKMatrix4x4 mout, float left, float right, float bottom, float top, float zNear, float zFar);

// Matrix-vector and PSKMatrix-matricx multiplication routines
void PSKMatrix3x3MultiplyWithVector3(PSKVector3 *vout, const PSKMatrix3x3 m, const PSKVector3 v);
void PSKMatrix3x3MultiplyWithMatrix3x3(PSKMatrix3x3 c, const PSKMatrix3x3 a, const PSKMatrix3x3 b);

void PSKMatrixMultiplyWithVector(PSKVector4 *vout, const PSKMatrix4x4 m, const PSKVector4 v);
void PSKMatrixMultiplyWithVector3(PSKVector3 *vout, const PSKMatrix4x4 m, const PSKVector3 v);
void PSKMatrixMultiplyWithMatrix(PSKMatrix4x4 c, const PSKMatrix4x4 a, const PSKMatrix4x4 b);
void PSKMatrixFastMultiplyWithMatrix(PSKMatrix4x4 result, PSKMatrix4x4 m1, PSKMatrix4x4 m2);

// Initialize mout to be an affine transform corresponding to the same rotation specified by m
void PSKMatrixFromCMRotationMatrix(PSKMatrix4x4 mout, const CMRotationMatrix *m);


#pragma mark - Quaternion
typedef struct PSKQuaternion {
    float x;
    float y;
    float z;
    float w;
} PSKQuaternion;

PSKQuaternion PSKQuaternionFromCMQuaternion(CMQuaternion q);
void PSKQuaternionNormalize(PSKQuaternion *quaternion);
PSKQuaternion PSKQuaternionMakeWithMatrix3D(PSKMatrix4x4 matrix);
void PSKMatrix4SetUsingQuaternion3D(PSKMatrix4x4 matrix, PSKQuaternion quat);
PSKQuaternion PSKQuaternionMakeWithAxisAndAngle(PSKVector3 axis, float angle);
void PSKQuaternionExtractAxisAndAngle(PSKQuaternion quat, PSKVector3 *axis, float *angle);
void PSKQuaternionMultiply(PSKQuaternion *quat1, PSKQuaternion *quat2);
void PSKQuaternionInvert(PSKQuaternion  *quat);
PSKQuaternion PSKQuaternionMakeWithEulerAngles(float x, float y, float z);
PSKVector3 PSKQuaternionToEuler(PSKQuaternion q);
PSKQuaternion PSKQuaternionConjugate (PSKQuaternion q);
PSKVector3 PSKQuaternionMultiplyVector3 (PSKQuaternion q, PSKVector3 vec);


#pragma mark - Geodetic Utils
/*! Calculates the end-point from a given source at a given range (meters) and bearing (degrees).
 This methods uses simple geometry equations to calculate the end-point.
 
 @param source Point of origin
 @param range Range in meters
 @param bearing Bearing in degrees
 
 @return End-point from the source given the desired range and bearing. 
 */
CLLocationCoordinate2D PSKCalculatePositionInDistance(CLLocationCoordinate2D source, double range, double bearing);

/*! Converts latitude, longitude to ECEF coordinate system */
void PSKConvertLatLonToEcef(double lat, double lon, double alt, double *x, double *y, double *z);

/*! Coverts ECEF to ENU coordinates centered at given lat, lon */
void PSKEcefToEnu(double lat, double lon, double x, double y, double z, double xr, double yr, double zr, double *e, double *n, double *u);


#pragma mark - Other Utils
CGPoint PSKRadarCoordinatesFromVectorWithGravity(PSKVector3 v, PSKVector3 g);
CGPoint PSKAtittudePitchCoordinates(PSKVector3 v, PSKVector3 g);
#endif
