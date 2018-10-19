//
//  ARVideoFormat.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3))
NS_SWIFT_NAME(ARConfiguration.VideoFormat)
@interface ARVideoFormat : NSObject <NSCopying>

/**
 Image resolution.
 图像分辨率。
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 Frame rate.
 帧率。
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
