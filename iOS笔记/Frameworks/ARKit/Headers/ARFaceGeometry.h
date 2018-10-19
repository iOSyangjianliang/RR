//
//  ARFaceGeometry.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>
#import <ARKit/ARFaceAnchor.h>

@protocol MTLBuffer;
@protocol MTLDevice;
@class ARFaceAnchor;

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing the geometry of a face.
 @discussion The face geometry will have a constant number of triangles
 and vertices, updating only the vertex positions from frame to frame.
  表示面部几何的对象。
  @discussion面几何将具有恒定数量的三角形
  和顶点，只更新帧到帧的顶点位置。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFaceGeometry : NSObject<NSSecureCoding, NSCopying>

/**
The number of mesh vertices of the geometry.
 几何图形的网格顶点数。
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
 几何图形的网格顶点。
 */
@property (nonatomic, readonly) const vector_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the face geometry.
 几何面纹理坐标的数量。
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
 几何图形的纹理坐标。
 */
@property (nonatomic, readonly) const vector_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles of the face geometry.
 几何面中三角形的数目。
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 The triangle indices of the geometry.
 几何图形的三角形索引。
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;//NS_REFINED_FOR_SWIFT宏指令是Xcode 7.0 新出的参考Xcode 7.0 release note，用它所标记的方法和变量在Objective-C中可以正常使用，但bridge到Swift语言时，编译器会在名称前加上__，注意是双下划线。

/**
 Creates and returns a face geometry by applying a set of given blend shape coefficients.
 
 @discussion An empty dictionary can be provided to create a neutral face geometry.
 @param blendShapes A dictionary of blend shape coefficients.
 @return Face geometry after applying the blend shapes.
  通过应用一组给定的混合形状系数来创建并返回几何面。
  
  @discussion可以提供空字典来创建中性几何面。
  @param blendShapes混合形状系数的字典。
  @return应用混合形状后的几何体。
 */
- (nullable instancetype)initWithBlendShapes:(NSDictionary<ARBlendShapeLocation, NSNumber*> *)blendShapes;

/** Unavailable 不可用 */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A SceneKit geometry representing a face.
 表示面部的SceneKit几何体。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSCNFaceGeometry : SCNGeometry

/**
 Creates a new face geometry using a Metal device.
 
 @param device A Metal device.
 @return A new face geometry.
  使用Metal设备创建新的面几何。
  
  @param device A Metal设备。
  @return一个新的面几何。
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device;


/**
 Creates a new face geometry using a Metal device.
 
 @discussion By default the regions between the eye lids as well as the region
 between the lips are not covered by geometry. For using the face geometry as an
 occlusion geometry set \p fillMesh to YES. This will fill
 in additional geometry into the gaps between the eye lids as well as into the
 gap between the lips.
 @param fillMesh Whether to fill in additional geometry into the
 gaps between the eye lids as well as into the gap between the lips.
 
 @return A new face geometry.
 
 使用Metal设备创建一个新的人脸几何。
 
 默认情况下，眼睛眼睑之间的区域以及区域
 嘴唇之间没有几何学的覆盖。使用面几何作为
 遮挡几何设置\p fillMesh为YES。这将填补
 在额外的几何进眼间隙之间的眼睑以及进入
 嘴唇之间的差距。
 @param填充网格是否填充其他几何体
 眼睑和嘴唇之间的间隙。
 
 @return一个新的face geometry。
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device
                              fillMesh:(BOOL)fillMesh;


/**
 Updates the geometry with the vertices of a face geometry.
 
 @param faceGeometry A face geometry.
   使用几何面的顶点更新几何。
   @param faceGeometry一个几何面。
 */
- (void)updateFromFaceGeometry:(ARFaceGeometry *)faceGeometry;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
