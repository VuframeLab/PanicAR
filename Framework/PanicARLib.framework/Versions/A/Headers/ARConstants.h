/*
 *  ARConstants.h
 *  PanicARLib
 *
 *  Created by Andreas Zeitler on 07.12.10.
 *  Copyright 2010 doPanic. All rights reserved.
 *
 */

//#define k_TextureSizeX 256
//#define k_TextureSizeY 128

#define k_RadarPlane -200
#define k_RadarSize 2.3
#define k_RadarDot 7
#define k_Radar_FadeBackwardDots NO

#define k_Sectors 36 
#define k_Segment()(360.0/k_Sectors)
#define k_infoLabelYOffset 1.6
#define k_infoLabelBaseLine -2

#define k_CameraMinTilt -45
#define k_CameraMaxTilt 90
#define k_SwipeSpeed 0.005f
#define k_SwipeSpeed_Y 0.2f

#define k_AccelSmooth 5
#define  k_CameraTurnXSmooth 15
#define  k_CameraTurnYSmooth 8
#define  k_CameraMoveYSmooth 8

#define k_zNear 0.1f
#define k_zFar 25000.0f
#define k_fieldOfView 33.3
#define k_fieldOfView_wide 50


#define k_ClipMarkersOutsideFOV 35
#define k_DisableMarkersOutsideFOV 50

#define k_MarkerSmooth 25
#define k_infoLabelSize 50
#define k_DistanceFactor 5