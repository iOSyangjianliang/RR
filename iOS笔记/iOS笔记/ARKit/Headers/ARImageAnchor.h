//
//  ARImageAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@class ARReferenceImage;

NS_ASSUME_NONNULL_BEGIN

/**
 An anchor representing an image in the world.
  代表全局图像的锚。
 */
API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARImageAnchor : ARAnchor

/**
 Reference to the detected image.
  参考检测到的图像。
 */
@property (nonatomic, strong, readonly) ARReferenceImage *referenceImage;

/** Unavailable 不可用*/
- (instancetype)initWithTransform:(matrix_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
