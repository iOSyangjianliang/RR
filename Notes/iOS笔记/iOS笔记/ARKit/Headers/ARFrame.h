//
//  ARFrame.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <UIKit/UIApplication.h>
#import <simd/simd.h>
#import <ARKit/ARHitTestResult.h>

@class ARAnchor;
@class ARCamera;
@class ARLightEstimate;
@class ARPointCloud;
@class AVDepthData;

NS_ASSUME_NONNULL_BEGIN

/**
 An object encapsulating the state of everything being tracked for a given moment in time.
 @discussion The model provides a snapshot of all data needed to render a given frame.
 一个对象封装了在给定时刻跟踪的所有内容的状态。
  @discussion该模型提供渲染给定帧所需的所有数据的快照。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFrame : NSObject <NSCopying>

/**
 A timestamp identifying the frame.
  标识帧的时间戳。
 */
@property (nonatomic, readonly) NSTimeInterval timestamp;

/**
 The frame’s captured image.
  帧的捕获图像。
 */
@property (nonatomic, readonly) CVPixelBufferRef capturedImage;

/**
 The frame’s captured depth data.
 @discussion Depth data is only provided with face tracking on frames where depth data was captured.
 帧的捕获深度数据。
  @discussion深度数据仅在捕获深度数据的帧上提供面部跟踪。
 */
@property (nonatomic, strong, nullable, readonly) AVDepthData *capturedDepthData;

/**
 A timestamp identifying the depth data.
  标识深度数据的时间戳。
 */
@property (nonatomic, readonly) NSTimeInterval capturedDepthDataTimestamp;

/**
 The camera used to capture the frame’s image.
 @discussion The camera provides the device’s position and orientation as well as camera parameters.
 相机用于捕捉帧的图像。
  @discussion摄像机提供设备的位置和方向以及摄像机参数。
 */
@property (nonatomic, copy, readonly) ARCamera *camera;

/**
 A list of anchors in the scene.
  场景中的锚点列表。
 */
@property (nonatomic, copy, readonly) NSArray<ARAnchor *> *anchors;

/**
 A light estimate representing the light in the scene.
 @discussion Returns nil if there is no light estimation.
 表示场景中光线的光估计。
  @discussion如果没有光估计，则返回nil。
 */
@property (nonatomic, strong, nullable, readonly) ARLightEstimate *lightEstimate;

/**
 Feature points in the scene with respect to the frame’s origin.
 @discussion The feature points are only provided for configurations using world tracking.
 场景中的特征点与帧的原点有关。
  @discussion仅为使用世界跟踪的配置提供要素点。
 */
@property (nonatomic, strong, nullable, readonly) ARPointCloud *rawFeaturePoints;

/**
 Searches the frame for objects corresponding to a point in the captured image.
 
 @discussion A 2D point in the captured image’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the image-space coordinate system of the captured image.
 Values should range from (0,0) - upper left corner to (1,1) - lower right corner.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
  在帧中搜索与捕获图像中的点对应的对象。
  
  @discussion捕获图像的坐标空间中的2D点可以指沿线段的任何点
  在3D坐标空间中。命中测试是在该线段中找到世界中的对象的过程。
  @param point捕获图像的图像空间坐标系中的一个点。
  值的范围应为（0,0） - 左上角到（1,1） - 右下角。
  @param types要搜索的结果类型。
  @return从最近到最远排序的所有命中测试结果的数组。
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types;

/**
 Returns a display transform for the provided viewport size and orientation.
 
 @discussion The display transform can be used to convert normalized points in the image-space coordinate system
 of the captured image to normalized points in the view’s coordinate space. The transform provides the correct rotation
 and aspect-fill for presenting the captured image in the given orientation and size.
 @param orientation The orientation of the viewport.
 @param viewportSize The size of the viewport.
  返回提供的视图大小和方向的显示变换。
  
  @discussion显示变换可用于转换图像空间坐标系中的标准化点
  捕获图像到视图坐标空间中的标准化点。变换提供正确的旋转
  和方面填充，用于以给定的方向和大小呈现捕获的图像。
  @param orientation视图的方向。
  @param viewportSize视图的大小。
 */
- (CGAffineTransform)displayTransformForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
