//
//  ARCamera.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIApplication.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A value describing the camera’s tracking state.
  描述摄像机跟踪状态的值。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, ARTrackingState) {
    /** Tracking is not available.
     摄像机跟踪不可用*/
    ARTrackingStateNotAvailable,
    
    /** Tracking is limited. See tracking reason for details.
     摄像机跟踪受限。请参阅跟踪原因了解详情。*/
    ARTrackingStateLimited,
    
    /** Tracking is Normal.
     摄像机跟踪是正常的。*/
    ARTrackingStateNormal,
} NS_REFINED_FOR_SWIFT;

/**
 A reason describing why the camera’s tracking state is limited.
  描述相机跟踪状态受限的原因。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, ARTrackingStateReason) {
    /** Tracking is not limited.
     跟踪不受限制。*/
    ARTrackingStateReasonNone,
    
    /** Tracking is limited due to initialization in progress.
     由于正在进行初始化，跟踪受到限制。*/
    ARTrackingStateReasonInitializing,
    
    /** Tracking is limited due to a excessive motion of the camera.
     由于相机过度运动，跟踪受限。*/
    ARTrackingStateReasonExcessiveMotion,
    
    /** Tracking is limited due to a lack of features visible to the camera.
     由于缺乏摄像头可见的特征，跟踪是受限的。*/
    ARTrackingStateReasonInsufficientFeatures,
    
    /** Tracking is limited due to a relocalization in progress.
     由于正在进行的重新定位，跟踪是受限的。(11.3+)。*/
    ARTrackingStateReasonRelocalizing API_AVAILABLE(ios(11.3)),
} NS_REFINED_FOR_SWIFT;


/**
 A model representing the camera and its parameters.
  表示相机及其参数的模型。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARCamera : NSObject <NSCopying>

/**
 The transformation matrix that defines the camera’s rotation and translation in world coordinates.
  转换矩阵，用于定义摄像机在世界坐标中的旋转和平移。
 */
@property (nonatomic, readonly) matrix_float4x4 transform;

/**
 The camera’s orientation defined as Euler angles.
 
 @dicussion The order of components in this vector matches the axes of rotation:
               1. Pitch (the x component) is the rotation about the node’s x-axis (in radians)
               2. Yaw   (the y component) is the rotation about the node’s y-axis (in radians)
               3. Roll  (the z component) is the rotation about the node’s z-axis (in radians)
            ARKit applies these rotations in the reverse order of the components:
               1. first roll
               2. then yaw
               3. then pitch
  相机的方向定义为欧拉角。
  
  @dicussion此向量中的组件顺序与旋转轴匹配：
                1.间距（x分量）是绕节点x轴的旋转（以弧度表示）
                2.偏航（y分量）是绕节点y轴的旋转（以弧度表示）
                3.滚动（z分量）是绕节点的z轴旋转（以弧度表示）
             ARKit以与组件相反的顺序应用这些旋转：
                1.第一次滚动
                然后偏航
                然后投球
 */
@property (nonatomic, readonly) vector_float3 eulerAngles;

/**
 The tracking state of the camera.
  相机的跟踪状态。
 */
@property (nonatomic, readonly) ARTrackingState trackingState NS_REFINED_FOR_SWIFT;

/**
 The reason for the camera’s current tracking state.
  摄像机当前跟踪状态的原因。
 */
@property (nonatomic, readonly) ARTrackingStateReason trackingStateReason NS_REFINED_FOR_SWIFT;

/**
 The camera intrinsics.
 @discussion The matrix has the following contents:
 fx 0   px
 0  fy  py
 0  0   1
 fx and fy are the focal length in pixels.
 px and py are the coordinates of the principal point in pixels.
 The origin is at the center of the upper-left pixel.
 相机内在的。
  @discussion矩阵具有以下内容：
  fx 0  px
  0  fy py
  0  0  1
  fx和fy是以像素为单位的焦距。
  px和py是主要点的坐标，以像素为单位。
  原点位于左上角像素的中心。
 */
@property (nonatomic, readonly) matrix_float3x3 intrinsics;

/**
 The camera image resolution in pixels.
  相机图像分辨率，以像素为单位
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 The projection matrix of the camera.
 @discussion The projection matrix assumes no far clipping plane limit.
 相机的投影矩阵。
  @discussion投影矩阵假定没有远剪裁平面限制。
*/
@property (nonatomic, readonly) matrix_float4x4 projectionMatrix;

/**
 Project a 3D point in world coordinate system into 2D viewport space.
 
 @param point 3D point in world coordinate system.
 @param orientation Viewport orientation.
 @param viewportSize Viewport (or image) size.
 @return 2D point in viewport coordinate system with origin at top-left.

 将全局坐标系中的3D点投影到2D视口空间。
  
  @param指向全局坐标系中的3D点。
  @param orientation视口方向。
  @param viewportSize视口（或图像）大小。
  @return视口坐标系中的2D点，原点位于左上角。
 */
- (CGPoint)projectPoint:(vector_float3)point orientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;

/**
 Creates a projection matrix for the camera given rendering parameters.
 
 @discussion The projection matrix returned provides an aspect fill for the provided viewport size and orientation.
             If zFar is set to 0, an infinite projection matrix will be returned.
 @param orientation Viewport orientation.
 @param viewportSize Viewport size.
 @param zNear Near depth limit.
 @param zFar Far depth limit.
 在给定渲染参数的情况下为相机创建投影矩阵。
  
  @discussion返回的投影矩阵为提供的视口大小和方向提供方面填充。
              如果zFar设置为0，则返回无限投影矩阵。
  @param orientation视口方向。
  @param viewportSize视口大小。
  @param zNear近深度限制。
  @param zFar远深限制。
 */
- (matrix_float4x4)projectionMatrixForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize zNear:(CGFloat)zNear zFar:(CGFloat)zFar;

/**
 Creates a view matrix for the camera given an interface orientation.
 
 @discussion The view matrix can be used to transform geometry into camera space for a given orientation
 @param orientation The interface orientation that will be used to render the camera’s view.
  给定界面方向，为摄像机创建视图矩阵。
  
  @discussion视图矩阵可用于将几何图形转换为给定方向的相机空间
  @param orientation用于渲染摄像机视图的界面方向。
 */
- (matrix_float4x4)viewMatrixForOrientation:(UIInterfaceOrientation)orientation;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
