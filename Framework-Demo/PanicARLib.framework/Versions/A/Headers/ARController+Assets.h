//
//  ARController+Assets.h
//  PanicARLib
//
//  Created by Andreas Zeitler on 15.10.11.
//  Copyright (c) 2011 doPanic. All rights reserved.
//

#import "ARController.h"
#import "ARUtils.h"

@class ARMesh;
@class ARTexture;
struct Mesh;


#pragma mark - Default Assets



@interface ARController (Assets)


- (void)loadRadarAssets;

- (ARMarkerTemplate *)defaultMarkerTemplate;
- (void)setDefaultMarkerTemplate:(ARMarkerTemplate *)tmpl;

- (ARMesh *)defaultMarkerMesh;
- (void)setDefaultMarkerMesh:(ARMesh *)mesh;

- (ARMesh *)radarMesh;
- (void)setRadarMesh:(ARMesh *)mesh;

- (ARTexture *) radarDotTexture;
- (void)loadRadarDotTexture:(NSString *)textureName;

- (ARTexture *) radarBGTexture;
- (void)loadRadarBGTexture:(NSString *)textureName;


#pragma mark - Asset Loading


/*! 
 load a mesh for use in the AR view (pass mesh as pointer to Mesh struct)
 
 supports loading of OBJ-files, specs: triangulated, single UV set, need to have material
 please note that popular 3d model tools may export OBJ without UVs when using materials without textures
 
 make sure mesh file is added to XCode first
 
 @return YES if mesh successfully loaded, otherwise NO
 */
+ (BOOL) loadMesh:(NSString *)meshFilename mesh:(Mesh&)mesh DEPRECATED_ATTRIBUTE;

/*! 
 load a mesh to mesh dictionary for use in the AR view
 meshs will be cached and shared based on their filename (each mesh file will only be loaded once)
 treat mesh file names like IDs in a dictionary
 
 supports loading of OBJ-files, specs: triangulated, single UV set, need to have material
 please note that popular 3d model tools may export OBJ without UVs when using materials without textures
 
 make sure mesh file is added to XCode first
 
 @return YES if mesh successfully loaded, otherwise NO
 */
+ (ARMesh *)loadMesh:(NSString *)meshFilename;


/*! 
 load a texture into OpenGL for use in the AR view
 
 loads all image formats supported by the SDK and creates a OpenGL texture name for it
 
 @return the OpenGL texture name (uint)
 */
+ (uint) loadTexture:(NSString *)textureFilename;


@end
