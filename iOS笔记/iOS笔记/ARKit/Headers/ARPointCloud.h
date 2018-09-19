//
//  ARPointCloud.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARPointCloud : NSObject <NSSecureCoding>

/**
 The number of points in the point cloud.
  点云中的点数。
 */
@property (nonatomic, readonly) NSUInteger count NS_REFINED_FOR_SWIFT;

/**
 The 3D points comprising the point cloud.
点云中包含的3D点
 */
@property (nonatomic, readonly) const vector_float3 *points NS_REFINED_FOR_SWIFT;

/**
 The 3D point identifiers comprising the point cloud.
 点云中包括的3D点的标识符。
 */
@property (nonatomic, readonly) const uint64_t *identifiers NS_REFINED_FOR_SWIFT;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
