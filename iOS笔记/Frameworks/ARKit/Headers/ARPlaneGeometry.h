//
//  ARPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>
#import <simd/simd.h>

@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing the geometry of a plane.
 @discussion The plane geometry will have a growing number of triangles
 and vertices updated from frame to frame.
 表示几何平面的对象。
  @discussion平面几何体将具有越来越多的三角形
  顶点从一帧到另一帧更新。（11.3+）
 */
API_AVAILABLE(ios(11.3))
@interface ARPlaneGeometry : NSObject<NSSecureCoding>

/**
 The number of mesh vertices of the geometry.
  几何体的网格顶点数。
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
  几何的网格顶点。
 */
@property (nonatomic, readonly) const vector_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the geometry.
  几何的纹理坐标数。
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
  几何的纹理坐标。
 */
@property (nonatomic, readonly) const vector_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles of the geometry.
  几何的三角形数量。
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 The triangle indices of the geometry.
  几何的三角形索引。
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 The number of boundary vertices of the geometry.
  几何的边界顶点数。
 */
@property (nonatomic, readonly) NSUInteger boundaryVertexCount NS_REFINED_FOR_SWIFT;

/**
 The vertices of the geometry's outermost boundary.
  几何体最外边界的顶点。
 */
@property (nonatomic, readonly) const vector_float3 *boundaryVertices NS_REFINED_FOR_SWIFT;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A SceneKit geometry representing a plane.
  表示平面的SceneKit几何体。
 */
API_AVAILABLE(ios(11.3))
@interface ARSCNPlaneGeometry : SCNGeometry

/**
 Creates a new plane geometry using a Metal device.
 
 @param device A Metal device.
 @return A new plane geometry.
  使用Metal设备创建新的平面几何体。
  
  @param device A Metal设备。
  @return一个新的平面几何体。
 */
+ (nullable instancetype)planeGeometryWithDevice:(id<MTLDevice>)device;

/**
 Updates the geometry with the vertices of a plane geometry.
 
 @param planeGeometry A plane geometry.
  使用平面几何体的顶点更新几何体。
  
  @param planeGeometry平面几何。
 */
- (void)updateFromPlaneGeometry:(ARPlaneGeometry *)planeGeometry;

@end

NS_ASSUME_NONNULL_END
