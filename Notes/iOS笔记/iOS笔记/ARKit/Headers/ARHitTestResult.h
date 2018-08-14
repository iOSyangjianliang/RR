//
//  ARHitTestResult.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <simd/simd.h>

@class ARAnchor;

/**
 Option set of hit-test result types.
  命中测试结果类型的选项集。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_OPTIONS(NSUInteger, ARHitTestResultType) {
    /** Result type from intersecting the nearest feature point.
     与最近的特征点相交的结果类型。*/
    ARHitTestResultTypeFeaturePoint                                        = (1 << 0),
    
    /** Result type from intersecting a horizontal plane estimate, determined for the current frame.
     从与当前帧确定的水平平面估计相交的结果类型。*/
    ARHitTestResultTypeEstimatedHorizontalPlane                            = (1 << 1),
    
    /** Result type from intersecting a vertical plane estimate, determined for the current frame.
     结束垂直平面估计的结果类型，为当前帧确定。(11.3+)*/
    ARHitTestResultTypeEstimatedVerticalPlane API_AVAILABLE(ios(11.3))     = (1 << 2),
    
    /** Result type from intersecting with an existing plane anchor.
     与现有平面锚点相交的结果类型。*/
    ARHitTestResultTypeExistingPlane                                       = (1 << 3),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s extent.
     考虑到平面的范围，与现有平面锚点相交的结果类型。 */
    ARHitTestResultTypeExistingPlaneUsingExtent                            = (1 << 4),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s geometry.
     考虑到平面的几何形状，与现有平面锚点相交的结果类型。(11.3+)* */
    ARHitTestResultTypeExistingPlaneUsingGeometry API_AVAILABLE(ios(11.3)) = (1 << 5),
} NS_SWIFT_NAME(ARHitTestResult.ResultType);

NS_ASSUME_NONNULL_BEGIN

/**
 A result of an intersection found during a hit-test.
  在命中测试期间发现交叉点的结果。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARHitTestResult : NSObject

/**
 The type of the hit-test result.
  命中测试结果的类型。
 */
@property (nonatomic, readonly) ARHitTestResultType type;

/**
 The distance from the camera to the intersection in meters.
  从相机到交叉点的距离（以米为单位）。
 */
@property (nonatomic, readonly) CGFloat distance;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the anchor or nearest feature point.
  用于定义交点的旋转，平移和比例的变换矩阵
  相对于锚点或最近的特征点。
 */
@property (nonatomic, readonly) matrix_float4x4 localTransform;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the world.
 用于定义交点的旋转，平移和比例的变换矩阵
  相对于世界。
 */
@property (nonatomic, readonly) matrix_float4x4 worldTransform;

/**
 The anchor that the hit-test intersected.
 
 @discussion An anchor will only be provided for existing plane result types.
  击中测试相交的锚点。
  
  @discussion仅为现有的平面结果类型提供锚点。
 */
@property (nonatomic, strong, nullable, readonly) ARAnchor *anchor;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
