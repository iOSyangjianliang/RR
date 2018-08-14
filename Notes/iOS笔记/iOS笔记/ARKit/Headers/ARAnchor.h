//
//  ARAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing a physical location and orientation in 3D space.
  表示3D空间中物理位置和方向的对象。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARAnchor : NSObject <NSCopying, NSSecureCoding>

/**
 Unique identifier of the anchor.
 锚的唯一标识符。
 */
@property (nonatomic, readonly) NSUUID *identifier;

/**
 The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
  转换矩阵，用于定义锚点在世界坐标中的旋转，平移和缩放。
 */
@property (nonatomic, readonly) matrix_float4x4 transform;

/**
 Initializes a new anchor object.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 初始化一个新的锚点对象。
  @param transform定义锚点在世界坐标中的旋转，平移和缩放的变换矩阵。
 */
- (instancetype)initWithTransform:(matrix_float4x4)transform;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A real world object or location in the scene that is being tracked.
  正在跟踪的场景中的真实世界对象或位置。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol ARTrackable <NSObject>

/**
 Tracking state of the anchor
 @discussion The isTracked value is used to determine the anchor transform’s validity. When the object being tracked is no longer detected in the
 camera image, its anchor will return NO for isTracked.
  跟踪锚的状态
  @discussion isTracked值用于确定锚变换的有效性。当不再检测到被跟踪的对象时
  相机图像，其锚点将返回NO为isTracked。
 */
@property (nonatomic, readonly) BOOL isTracked;

@end

NS_ASSUME_NONNULL_END
