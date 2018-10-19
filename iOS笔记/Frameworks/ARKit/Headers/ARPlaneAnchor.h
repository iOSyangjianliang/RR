//
//  ARPlaneAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class ARPlaneGeometry;

/**
 A value describing the alignment of a plane anchor.
  描述平面锚点对齐的值。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, ARPlaneAnchorAlignment) {
    /** A plane that is horizontal with respect to gravity.
     相对于重力水平的平面。 */
    ARPlaneAnchorAlignmentHorizontal,
    
    /** A plane that is vertical with respect to gravity.
     相对于重力垂直的平面。*/
    ARPlaneAnchorAlignmentVertical API_AVAILABLE(ios(11.3))
} NS_SWIFT_NAME(ARPlaneAnchor.Alignment);


/**
 An anchor representing a planar surface in the world.
 @discussion Planes are defined in the X and Z direction, where Y is the surface’s normal.
 代表全局平面的锚。
  @discussion平面在X和Z方向定义，其中Y是曲面的法线。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARPlaneAnchor : ARAnchor

/**
 The alignment of the plane.
  平面的对齐。
 */
@property (nonatomic, readonly) ARPlaneAnchorAlignment alignment;

/**
 The center of the plane in the anchor’s coordinate space.
  锚点坐标空间中平面的中心。
 */
@property (nonatomic, readonly) vector_float3 center;

/**
 The extent of the plane in the anchor’s coordinate space.
 锚点坐标空间中平面的范围。
 */
@property (nonatomic, readonly) vector_float3 extent;

/**
 Geometry of the plane in the anchor's coordinate space.
  锚点坐标空间中的几何平面。
 */
@property (nonatomic, strong, readonly) ARPlaneGeometry *geometry API_AVAILABLE(ios(11.3));

/** Unavailable 不可用*/
- (instancetype)initWithTransform:(matrix_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
