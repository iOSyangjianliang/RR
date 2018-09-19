//
//  ARConfiguration.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ARReferenceImage;
@class ARVideoFormat;

/**
 Enum constants for indicating the world alignment.
  枚举常量用于指示全局对齐方式。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, ARWorldAlignment) {
    /** Aligns the world with gravity that is defined by vector (0, -1, 0).
     将全局设置与由矢量（0，-1,0）定义的重力对齐。*/
    ARWorldAlignmentGravity,
    
    /** Aligns the world with gravity that is defined by the vector (0, -1, 0)
     and heading (w.r.t. True North) that is given by the vector (0, 0, -1).
     将全局设置与由向量（0，-1,0）定义的重力对齐
      和向量（w.r.t. True North）由向量（0,0，-1）给出。*/
    ARWorldAlignmentGravityAndHeading,
    
    /** Aligns the world with the camera’s orientation.
     将全局设置与相机的方向对齐。*/
    ARWorldAlignmentCamera
} NS_SWIFT_NAME(ARConfiguration.WorldAlignment);


/**
 Option set indicating the type of planes to detect.
  选项集，指示要检测的平面类型。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_OPTIONS(NSUInteger, ARPlaneDetection) {
    /** No plane detection is run.
     没有运行平面检测。*/
    ARPlaneDetectionNone                              = 0,
    
    /** Plane detection determines horizontal planes in the scene.
     平面检测确定场景中的水平平面。*/
    ARPlaneDetectionHorizontal                        = (1 << 0),
    
    /** Plane detection determines vertical planes in the scene.
     平面检测确定场景中的垂直平面。*/
    ARPlaneDetectionVertical API_AVAILABLE(ios(11.3)) = (1 << 1)
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.PlaneDetection);


/**
 An object to describe and configure the Augmented Reality techniques to be used in an ARSession.
  描述和配置要在ARSession中使用的增强现实技术的对象。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARConfiguration : NSObject <NSCopying>

/**
 Determines whether this device supports the ARConfiguration.
  确定此设备是否支持ARConfiguration。
  一般A9芯片以下设备不支持
 */
@property (class, nonatomic, readonly) BOOL isSupported;

/**
 A list of supported video formats for this configuration and device.
 @discussion The first element in the list is the default format for session output.
 此配置和设备支持的视频格式列表。
  @discussion列表中的第一个元素是会话输出的默认格式。
 */
@property (class, nonatomic, strong, readonly) NSArray<ARVideoFormat *> *supportedVideoFormats API_AVAILABLE(ios(11.3));

/**
 Video format of the session output.
  会话输出的视频格式。
 */
@property (nonatomic, strong, readwrite) ARVideoFormat *videoFormat API_AVAILABLE(ios(11.3));

/**
 Determines how the coordinate system should be aligned with the world.
 @discussion The default is ARWorldAlignmentGravity.
 确定坐标系应如何与全局对齐。
  @discussion默认为ARWorldAlignmentGravity。
 */
@property (nonatomic, readwrite) ARWorldAlignment worldAlignment;

/**
 Enable or disable light estimation.
 @discussion Enabled by default.
 启用或禁用光估计。
  @discussion默认启用。
 */
@property (nonatomic, readwrite, getter=isLightEstimationEnabled) BOOL lightEstimationEnabled;

/**
 Determines whether to capture and provide audio data.
 @discussion Disabled by default.
 确定是否捕获和提供音频数据。
  @discussion默认禁用。
 */
@property (nonatomic, readwrite) BOOL providesAudioData;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A configuration for running world tracking.
 
 @discussion World tracking provides 6 degrees of freedom tracking of the device.
 By finding feature points in the scene, world tracking enables performing hit-tests against the frame.
 Tracking can no longer be resumed once the session is paused.
 用于运行全局跟踪的配置。
  
  @discussion全局跟踪提供6个自由度跟踪设备。
  通过在场景中查找特征点，全局跟踪可以对帧执行命中测试。
  会话暂停后，无法再恢复跟踪。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARWorldTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
  启用或禁用连续自动对焦。
  @discussion默认启用。
 */
@property (nonatomic, readwrite, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
  要在场景中检测的平面类型。
  @discussion如果设置，将继续检测新平面并随时更新。检测到的飞机将被添加到会话中
  ARPlaneAnchor对象。如果合并了两个平面，则将删除较新的平面。默认为ARPlaneDetectionNone。
 */
@property (nonatomic, readwrite) ARPlaneDetection planeDetection;

/**
 Images to detect in the scene.
 @discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
  要在场景中检测的图像。
  @discussion如果设置会话将尝试检测指定的图像。检测到图像时，会将ARImageAnchor添加到会话中。
 */
@property (nonatomic, copy, nullable, readwrite) NSSet<ARReferenceImage *> *detectionImages API_AVAILABLE(ios(11.3));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running orientation tracking.
 
 @discussion Orientation tracking provides 3 degrees of freedom tracking of the device.
 用于运行方向跟踪的配置。
  @discussion方向跟踪提供3个自由度跟踪设备。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface AROrientationTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 启用或禁用连续自动对焦。
  @discussion默认启用。
 */
@property (nonatomic, readwrite, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running face tracking.
 
 @discussion Face tracking uses the front facing camera to track the face in 3D providing details on the topology and expression of the face.
 A detected face will be added to the session as an ARFaceAnchor object which contains information about head pose, mesh, eye pose, and blend shape
 coefficients. If light estimation is enabled the detected face will be treated as a light probe and used to estimate the direction of incoming light.
 /**
   用于运行面部跟踪的配置。
  
   @discussion面部跟踪使用前置摄像头以3D形式跟踪面部，提供有关拓扑和面部表情的详细信息。
   检测到的面部将作为ARFaceAnchor对象添加到会话中，该对象包含有关头部姿势，网格，眼睛姿势和混合形状的信息
  系数。 如果启用光估计，则将检测到的面部视为光探测器并用于估计入射光的方向。
  */
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFaceTrackingConfiguration : ARConfiguration

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

NS_ASSUME_NONNULL_END
