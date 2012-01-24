//
//  PARMathInline.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 17.01.12.
//  Copyright (c) 2012 doPanic. All rights reserved.
//

#ifndef PanicARLib_ARMathInline_h
#define PanicARLib_ARMathInline_h

#import "PARMath.h"

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
#define RADIANS_TO_DEGREES (180.0/M_PI)

#pragma mark - Linear Math

inline float randomf (float number) {
    return (((float) (arc4random() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * number) ;
}
inline float randomf (float smallNumber, float bigNumber) {
    float diff = bigNumber - smallNumber;
    return (((float) (arc4random() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * diff) + smallNumber;
}

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

inline float PARVector3Magnitude(PARVector3 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

inline float PARVector3SqrMagnitude(PARVector3 vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

inline PARVector3 PARVector3Init(float x, float y, float z) {
    PARVector3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}
inline PARVector4 PARVector4Init(float x, float y, float z, float w) {
    PARVector4 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}
inline PARVector4 PARVector4GetZero() {
    PARVector4 vec;
    vec.x = 0;
    vec.y = 0;
    vec.z = 0;
    vec.w = 0;
    return vec;
}

inline void PARVector3SetZero(PARVector3 *vec) {
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}
inline void PARVector3SetOne(PARVector3 *vec) {
	vec->x = 1;
	vec->y = 1;
	vec->z = 1;
}
inline void PARVector3SetForward(PARVector3 *vec) {
	vec->x = 0;
	vec->y = 0;
	vec->z = 1;
}

inline void PARVector3Scalef(PARVector3 *vec, const float s) {
	vec->x *= s;
	vec->y *= s;
	vec->z *= s;
}
inline PARVector3 PARVector3Scale(PARVector3 vec, const float s) {
	vec.x *= s;
	vec.y *= s;
	vec.z *= s;
    return vec;
}

inline void PARVector3Clamp(PARVector3 *vec, float s) {
	vec->x = clampf(vec->x, -s, s);
	vec->y = clampf(vec->y, -s, s);
	vec->z = clampf(vec->z, -s, s);
}

inline void PARVector3Scale(PARVector3 *vec, const double s) {
	vec->x *= ((float)s);
	vec->y *= ((float)s);
	vec->z *= ((float)s);
}

inline void PARVector3Print(PARVector3 vec) {
    printf("Vector3:\n%f,%f,%f\n", 
           vec.x, vec.y, vec.z);
}


inline GLfloat PARVector3DotProduct (PARVector3 vector1, PARVector3 vector2)
{		
    return (vector1.x*vector2.x) + 
    (vector1.y*vector2.y) + 
    (vector1.z*vector2.z);
}
inline PARVector3 PARVector3CrossProduct (PARVector3 vector1, PARVector3 vector2)
{
    PARVector3 ret;
    ret.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    ret.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    ret.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
    return ret;
}

#endif
