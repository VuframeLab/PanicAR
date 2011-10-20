/*
 *  ARMath.h
 *  PanicAR
 *
 *  Created by Andreas Zeitler on 24.08.10.
 *  Copyright 2010 doPanic. All rights reserved.
 *
 */

#import "math.h"

inline double DEG2RAD(double degrees) { return degrees * M_PI / 180; } // degrees * pi over 180
inline double RAD2DEG(double radians) { return radians * 180 / M_PI; } // radians * 180 over pi
inline double Mile2Km(double miles) { return miles * 1.609344; } 
inline double Km2Mile(double kms) { return kms * 0.621371192; } 
inline double Feet2Meter(double feet) { return feet * 0.3048; } 
inline double Meter2Feet(double meters) { return meters * 3.2808399; } 

inline double Mile2Meters(double x) { return (x * 1.609344 * 1000.0); }

inline double lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

inline float lerpf(float a, float b, float t) {
    return a + (b - a) * t;
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
