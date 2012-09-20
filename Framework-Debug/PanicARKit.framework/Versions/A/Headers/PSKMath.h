/*
 *  PSKMath.h
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

#pragma mark - Conversions

static inline double deg2rad(double degrees) { return degrees * M_PI / 180; } // degrees * pi over 180
static inline double rad2deg(double radians) { return radians * 180 / M_PI; } // radians * 180 over pi
static inline float deg2radf(float degrees) { return degrees * M_PI / 180; } // degrees * pi over 180
static inline float rad2degf(float radians) { return radians * 180 / M_PI; } // radians * 180 over pi
static inline double mile2km(double miles) { return miles * 1.609344; } 
static inline double km2mile(double kms) { return kms * 0.621371192; } 
static inline double feet2meter(double feet) { return feet * 0.3048; } 
static inline double meter2feet(double meters) { return meters * 3.2808399; } 
static inline double mile2meters(double x) { return (x * 1.609344 * 1000.0); }
#define DEGREES_TO_RADIANS (M_PI/180.0)
#define RADIANS_TO_DEGREES (180.0/M_PI)

#pragma mark - Linear Math

static inline float randomf (float number) {
    return (((float) (arc4random() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * number) ;
}
static inline float randomRangef (float smallNumber, float bigNumber) {
    float diff = bigNumber - smallNumber;
    return (((float) (arc4random() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * diff) + smallNumber;
}

static inline double lerp(double a, double b, double t) {
    return a + (b - a) * fmin(t, 1.00);
}

static inline float lerpf(float a, float b, float t) {
    return a + (b - a) * fminf(t, 1.00f);
}

#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
static inline float smoothf(float a, float b, float t) {
    const float v = SMOOTHSTEP(t);
    return (a * v) + (b * (1 - v));
}

static inline double lerpAngle (double a, double b, double f) {
	double tmp;
	if ( b - a >  180.0 ) tmp = a + 360.0 ; else
		if ( b - a < -180.0 ) tmp = a - 360.0 ; else tmp = a ;
	
	return tmp + f * ( b - tmp ) ;
} 
static inline float lerpAnglef (float a, float b, float f) {
	float tmp;
	if ( b - a >  180.0 ) tmp = a + 360.0 ; else
		if ( b - a < -180.0 ) tmp = a - 360.0 ; else tmp = a ;
	
	return tmp + f * ( b - tmp ) ;
} 

static inline float deltaAngle (float a, float b) {
	float difference = fmod((b - a), 360);
	if (difference > 180)
		difference -= 360;
	if (difference < -180)
		difference += 360;
	return difference;
} 

static inline int repeat(int value, int max) {
	if (value < 0) return max + value;
	else return value % max;
}
static inline float frepeat(float value, float max) {
	if (value < 0) return max + value;
	else return fmodf(value, max);
}

static inline float signf(float n) {
    return n < 0 ? -1 : 1;
}

static inline float relativeAngle(float angle) {
    const float cAngle = fmodf(angle, 180);
    const float aAngle = fabsf(cAngle);
    return (aAngle > 90 ? ((180 - aAngle) * signf(angle)) : cAngle);
}

static inline float linsin(float angle) {
    return (relativeAngle(angle) / 90) * (fabsf(angle) > 180 ? -1 : 1);
}
static inline float lincos(float angle) {
    return ((90.0f - fabsf(relativeAngle(angle))) / 90) * ((fabsf(angle) > 90 && (fabsf(angle) < 270)) ? -1 : 1);
}

static inline double clamp(double v, double min, double max) {
    if(v > max)
        return max;
    else if(v < min)
        return min;
    else
        return v;
}
static inline float clampf(float v, float min, float max) {
    if(v > max)
        return max;
    else if(v < min)
        return min;
    else
        return v;
}

static inline double magnitude(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

static inline double sqrMagnitude(double x, double y, double z) {
    return x * x + y * y + z * z;
}

static inline void normalize(double *x, double *y, double *z) {
	double s = 1.0f / magnitude(*x, *y, *z);
	*x *= s;
	*y *= s;
	*z *= s;
}

#pragma mark - Vector

typedef struct {
	float x;
	float y;
	float z;
} PSKVector3;
typedef struct {
	float x;
	float y;
	float z;
	float w;
} PSKVector4;

PSKVector3 PSKVector3Normalize(PSKVector3 vec);
float PSKVector3AngleTowards(PSKVector3 from, PSKVector3 to);

float PSKVector3Angle(PSKVector3 vec);
float PSKVector4Angle(PSKVector4 vec);
float PSKVector3Elevation(PSKVector3 *vec);

static inline float PSKVector3Magnitude(PSKVector3 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

static inline float PSKVector3SqrMagnitude(PSKVector3 vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

static inline PSKVector3 PSKVector3Make(float x, float y, float z) {
    PSKVector3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}
static inline PSKVector3 PSKVector3MakeZero() {
    PSKVector3 vec;
    vec.x = 0;
    vec.y = 0;
    vec.z = 0;
    return vec;
}
static inline PSKVector4 PSKVector4Make(float x, float y, float z, float w) {
    PSKVector4 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}
static inline PSKVector4 PSKVector4MakeZero() {
    PSKVector4 vec;
    vec.x = 0;
    vec.y = 0;
    vec.z = 0;
    vec.w = 0;
    return vec;
}

static inline void PSKVector4Print(PSKVector4 vec) {
    printf("Vector4:\n%f,%f,%f,%f\n",
           vec.x, vec.y, vec.z, vec.w);
}
NSString *NSStringFromPSKVector3(PSKVector3 vec);

static inline void PSKVector3SetZero(PSKVector3 *vec) {
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}
static inline void PSKVector3SetOne(PSKVector3 *vec) {
	vec->x = 1;
	vec->y = 1;
	vec->z = 1;
}
static inline void PSKVector3SetForward(PSKVector3 *vec) {
	vec->x = 0;
	vec->y = 0;
	vec->z = 1;
}

static inline void PSKVector3Scalef(PSKVector3 *vec, const float s) {
	vec->x *= s;
	vec->y *= s;
	vec->z *= s;
}
static inline PSKVector3 PSKVector3Scale(PSKVector3 vec, const float s) {
	vec.x *= s;
	vec.y *= s;
	vec.z *= s;
    return vec;
}

static inline void PSKVector3Clamp(PSKVector3 *vec, float s) {
	vec->x = clampf(vec->x, -s, s);
	vec->y = clampf(vec->y, -s, s);
	vec->z = clampf(vec->z, -s, s);
}


static inline void PSKVector3Print(PSKVector3 vec) {
    printf("Vector3:\n%f,%f,%f\n", 
           vec.x, vec.y, vec.z);
}

PSKVector3 PSKVector3Negate(PSKVector3 vector);
bool PSKVector3Equals(PSKVector3 v1, PSKVector3 v2);


static inline GLfloat PSKVector3DotProduct (PSKVector3 vector1, PSKVector3 vector2) {		
    return (vector1.x*vector2.x) + 
    (vector1.y*vector2.y) + 
    (vector1.z*vector2.z);
}
static inline PSKVector3 PSKVector3CrossProduct (PSKVector3 vector1, PSKVector3 vector2) {
    PSKVector3 ret;
    ret.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    ret.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    ret.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
    return ret;
}

static inline float PSKVector3AngleBetweenXZ (PSKVector3 vec) {
    float angle = atan2f(vec.x, vec.z);
    if (angle < 0) angle += 2 * M_PI;
    return rad2degf(angle);
}

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

#define QUATERNION_TRACE_ZERO_TOLERANCE 0.00001

typedef struct {
    float x;
    float y;
    float z;
    float w;
} PSKQuaternion;

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