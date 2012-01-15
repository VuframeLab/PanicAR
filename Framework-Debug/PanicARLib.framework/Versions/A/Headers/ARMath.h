/*
 *  ARMath.h
 *  PanicAR
 *
 *  Created by Andreas Zeitler on 24.08.10.
 *  Copyright 2010 doPanic. All rights reserved.
 *
 */

#import "math.h"
#import <CoreMotion/CoreMotion.h>

#pragma mark - Conversions

inline double deg2rad(double degrees) { return degrees * M_PI / 180; } // degrees * pi over 180
inline double rad2deg(double radians) { return radians * 180 / M_PI; } // radians * 180 over pi
inline float deg2radf(float degrees) { return degrees * M_PI / 180; } // degrees * pi over 180
inline float rad2degf(float radians) { return radians * 180 / M_PI; } // radians * 180 over pi
inline double mile2km(double miles) { return miles * 1.609344; } 
inline double km2mile(double kms) { return kms * 0.621371192; } 
inline double feet2meter(double feet) { return feet * 0.3048; } 
inline double meter2feet(double meters) { return meters * 3.2808399; } 
inline double mile2meters(double x) { return (x * 1.609344 * 1000.0); }
#define DEGREES_TO_RADIANS (M_PI/180.0)

#pragma mark - Linear Math

inline double lerp(double a, double b, double t) {
    return a + (b - a) * fmin(t, 1.00);
}

inline float lerpf(float a, float b, float t) {
    return a + (b - a) * fminf(t, 1.00f);
}

#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
inline float smoothf(float a, float b, float t) {
    const float v = SMOOTHSTEP(t);
    return (a * v) + (b * (1 - v));
}

inline double lerpAngle (double a, double b, double f) {
	double tmp;
	if ( b - a >  180.0 ) tmp = a + 360.0 ; else
		if ( b - a < -180.0 ) tmp = a - 360.0 ; else tmp = a ;
	
	return tmp + f * ( b - tmp ) ;
} 
inline float lerpAnglef (float a, float b, float f) {
	float tmp;
	if ( b - a >  180.0 ) tmp = a + 360.0 ; else
		if ( b - a < -180.0 ) tmp = a - 360.0 ; else tmp = a ;
	
	return tmp + f * ( b - tmp ) ;
} 

inline float deltaAngle (float a, float b) {
	float difference = fmod((b - a), 360);
	if (difference > 180)
		difference -= 360;
	if (difference < -180)
		difference += 360;
	return difference;
} 

inline int repeat(int value, int max) {
	if (value < 0) return max + value;
	else return value % max;
}
inline float frepeat(float value, float max) {
	if (value < 0) return max + value;
	else return fmodf(value, max);
}

inline float signf(float n) {
    return n < 0 ? -1 : 1;
}

inline float relativeAngle(float angle) {
    const float cAngle = fmodf(angle, 180);
    const float aAngle = fabsf(cAngle);
    return (aAngle > 90 ? ((180 - aAngle) * signf(angle)) : cAngle);
}

inline float linsin(float angle) {
    return (relativeAngle(angle) / 90) * (fabsf(angle) > 180 ? -1 : 1);
}
inline float lincos(float angle) {
    return ((90.0f - fabsf(relativeAngle(angle))) / 90) * ((fabsf(angle) > 90 && (fabsf(angle) < 270)) ? -1 : 1);
}

inline double clamp(double v, double min, double max) {
    if(v > max)
        return max;
    else if(v < min)
        return min;
    else
        return v;
}
inline float clampf(float v, float min, float max) {
    if(v > max)
        return max;
    else if(v < min)
        return min;
    else
        return v;
}

#pragma mark - Vector


typedef struct {
	float x;
	float y;
	float z;
} ARVector3;
typedef struct {
	float x;
	float y;
	float z;
	float w;
} ARVector4;

inline double magnitude(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

inline double sqrMagnitude(double x, double y, double z) {
    return x * x + y * y + z * z;
}

inline void normalize(double *x, double *y, double *z) {
	double s = 1.0f / magnitude(*x, *y, *z);
	*x *= s;
	*y *= s;
	*z *= s;
}

inline float ARVector3Magnitude(ARVector3 *vec) {
    return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

inline float ARVector3SqrMagnitude(ARVector3 *vec) {
    return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

inline ARVector3 *ARVector3Init(float x, float y, float z) {
    ARVector3 *vec = (ARVector3*)malloc(sizeof(ARVector3));
    vec->x = x;
    vec->y = y;
    vec->z = z;
    return vec;
}
inline ARVector4 *ARVector4Init(float x, float y, float z, float w) {
    ARVector4 *vec = (ARVector4*)malloc(sizeof(ARVector4));
    vec->x = x;
    vec->y = y;
    vec->z = z;
    vec->w = w;
    return vec;
}
inline ARVector4 *ARVector4GetZero() {
    ARVector4 *vec = (ARVector4*)malloc(sizeof(ARVector4));
    vec->x = 0;
    vec->y = 0;
    vec->z = 0;
    vec->w = 0;
    return vec;
}

inline void ARVector3SetZero(ARVector3 *vec) {
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}
inline void ARVector3SetOne(ARVector3 *vec) {
	vec->x = 1;
	vec->y = 1;
	vec->z = 1;
}
inline void ARVector3SetForward(ARVector3 *vec) {
	vec->x = 0;
	vec->y = 0;
	vec->z = 1;
}

inline void ARVector3Scalef(ARVector3 *vec, const float s) {
	vec->x *= s;
	vec->y *= s;
	vec->z *= s;
}

inline void ARVector3Clamp(ARVector3 *vec, float s) {
	vec->x = clampf(vec->x, -s, s);
	vec->y = clampf(vec->y, -s, s);
	vec->z = clampf(vec->z, -s, s);
}

inline void ARVector3Scale(ARVector3 *vec, const double s) {
	vec->x *= ((float)s);
	vec->y *= ((float)s);
	vec->z *= ((float)s);
}

inline void ARVector3Print(ARVector3 vec) {
    printf("Vector3:\n%f,%f,%f\n", 
           vec.x, vec.y, vec.z);
}

void ARVector3Normalize(ARVector3 *vec);
float ARVector3AngleTowards(ARVector3 *from, ARVector3 *to);

float ARVector3Angle(ARVector3 *vec);
float ARVector4Angle(ARVector4 *vec);
float ARVector3Elevation(ARVector3 *vec);


inline GLfloat ARVector3DotProduct (ARVector3 vector1, ARVector3 vector2)
{		
    return (vector1.x*vector2.x) + 
    (vector1.y*vector2.y) + 
    (vector1.z*vector2.z);
}
inline ARVector3 ARVector3CrossProduct (ARVector3 vector1, ARVector3 vector2)
{
    ARVector3 ret;
    ret.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    ret.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    ret.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
    return ret;
}

#pragma mark - Matrix
typedef float ARMatrix3x3[9];	// 3x3 ARMatrix in column major order
typedef float ARMatrix4x4[16];	// 4x4 ARMatrix in column major order

void ARMatrixCopy(ARMatrix4x4 mout, ARMatrix4x4 *from);
void ARMatrix3SetIdentity(ARMatrix3x3 mout);
void ARMatrixSetIdentity(ARMatrix4x4 mout);
void ARMatrixSetXRotationUsingRadians(ARMatrix4x4 mout, float degrees);
void ARMatrixSetXRotationUsingDegrees(ARMatrix4x4 mout, float degrees);
void ARMatrixSetYRotationUsingRadians(ARMatrix4x4 mout, float degrees);
void ARMatrixSetYRotationUsingDegrees(ARMatrix4x4 mout, float degrees);
void ARMatrixSetZRotationUsingRadians(ARMatrix4x4 mout, float degrees);
void ARMatrixSetZRotationUsingDegrees(ARMatrix4x4 mout, float degrees);
void ARMatrixPrint(const ARMatrix4x4 mat);

// Creates a projection ARMatrix using the given y-axis field-of-view, aspect ratio, and near and far clipping planes
void ARMatrixCreateProjection(ARMatrix4x4 mout, float fovy, float aspect, float zNear, float zFar);
void ARMatrixCreateOrthographic(ARMatrix4x4 mout, float left, float right, float bottom, float top, float zNear, float zFar);

// Matrix-vector and ARMatrix-matricx multiplication routines
void ARMatrix3x3MultiplyWithVector3(ARVector3 *vout, const ARMatrix3x3 m, const ARVector3 v);
void ARMatrix3x3MultiplyWithMatrix3x3(ARMatrix3x3 c, const ARMatrix3x3 a, const ARMatrix3x3 b);

void ARMatrixMultiplyWithVector(ARVector4 *vout, const ARMatrix4x4 m, const ARVector4 v);
void ARMatrixMultiplyWithVector3(ARVector3 *vout, const ARMatrix4x4 m, const ARVector3 v);
void ARMatrixMultiplyWithMatrix(ARMatrix4x4 c, const ARMatrix4x4 a, const ARMatrix4x4 b);
void ARMatrixFastMultiplyWithMatrix(ARMatrix4x4 result, ARMatrix4x4 m1, ARMatrix4x4 m2);

// Initialize mout to be an affine transform corresponding to the same rotation specified by m
void ARMatrixFromCMRotationMatrix(ARMatrix4x4 mout, const CMRotationMatrix *m);


#pragma mark - Quaternion

#define QUATERNION_TRACE_ZERO_TOLERANCE 0.00001

typedef struct {
    float x;
    float y;
    float z;
    float w;
} ARQuaternion;

void ARQuaternionNormalize(ARQuaternion *quaternion);
ARQuaternion ARQuaternionMakeWithMatrix3D(ARMatrix4x4 matrix);
void Matrix3DSetUsingQuaternion3D(ARMatrix4x4 matrix, ARQuaternion quat);
ARQuaternion ARQuaternionMakeWithAxisAndAngle(ARVector3 axis, float angle);
void ARQuaternionExtractAxisAndAngle(ARQuaternion quat, ARVector3 *axis, float *angle);
void ARQuaternionMultiply(ARQuaternion *quat1, ARQuaternion *quat2);
void ARQuaternionInvert(ARQuaternion  *quat);
ARQuaternion ARQuaternionMakeWithEulerAngles(float x, float y, float z);


#pragma mark - Geodetic Utils

#define WGS84_A	(6378137.0)				// WGS 84 semi-major axis constant in meters
#define WGS84_E (8.1819190842622e-2)	// WGS 84 eccentricity

// Converts latitude, longitude to ECEF coordinate system
void convertLatLonToEcef(double lat, double lon, double alt, double *x, double *y, double *z);

// Coverts ECEF to ENU coordinates centered at given lat, lon
void ecefToEnu(double lat, double lon, double x, double y, double z, double xr, double yr, double zr, double *e, double *n, double *u);
