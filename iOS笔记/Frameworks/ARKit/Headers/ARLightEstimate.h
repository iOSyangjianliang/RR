//
//  ARLightEstimate.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A light estimate representing the light in the scene.
  表示场景中光线的光估计。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) //只在iOS11手机上可用
@interface ARLightEstimate : NSObject

/**
 Ambient intensity of the lighting.
 
 @discussion In a well lit environment, this value is close to 1000. It typically ranges from 0 (very dark) to around 2000 (very bright).
  
  照明的环境强度。
  在光线充足的环境中，此值接近1000.通常范围从0（非常暗）到2000左右（非常明亮）。
 */
@property (nonatomic, readonly) CGFloat ambientIntensity;

/**
 The ambient color temperature of the lighting.

 @discussion This specifies the ambient color temperature of the lighting in Kelvin (6500 corresponds to pure white).
  照明的环境色温。
  以开尔文为单位指定照明的环境色温（6500对应纯白色）。
*/
@property (nonatomic, readonly) CGFloat ambientColorTemperature;

/** Unavailable (废弃）*/
- (instancetype)init NS_UNAVAILABLE;//宏:必须要用某参数来初始化的
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A directional light estimate representing the light intensity and direction in the scene.
  定向光估计，表示场景中的光强度和方向。
*/
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARDirectionalLightEstimate : ARLightEstimate

/**
 Second degree spherical harmonics coefficients representing the intensity of light.
 
 @discussion The data is an array of 27 32-bit floating-point values, containing three non-interleaved data sets
 corresponding to the red, green, and blue sets of coefficients.
  
  表示光强度的二度球谐函数系数。
  数据是一个由27个32位浮点值组成的数组，包含三个非交错数据集
  对应于红色，绿色和蓝色系数集。
 */
@property (nonatomic, copy, readonly) NSData *sphericalHarmonicsCoefficients;

/**
 The primary direction of light.
  光的主要方向。
 */
@property (nonatomic, readonly) vector_float3 primaryLightDirection;

/**
 The intensity of light in the primary direction.
  主要方向的光强度。
 */
@property (nonatomic, readonly) CGFloat primaryLightIntensity;

@end

NS_ASSUME_NONNULL_END
