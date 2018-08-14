//
//  ARReferenceImage.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <ImageIO/CGImageProperties.h>
#import <CoreVideo/CVPixelBuffer.h>

@class CIImage;

NS_ASSUME_NONNULL_BEGIN

/**
 A reference image to be detected in the scene.
  要在场景中检测的参考图像。（11.3+）

 */
API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARReferenceImage : NSObject<NSCopying>

/**
 An optional name used to identify the image.
  用于标识图像的可选名称。
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The physical size of the image in meters.
  图像的物理尺寸，以米为单位。
 */
@property (nonatomic, readonly) CGSize physicalSize;

/**
 Creates a new reference image.
 
 @param image The reference image as CGImage.
 @param orientation The image orientation.
 @param physicalWidth The width in meters of the physical object.
 @return Reference image or nil on error.
  创建新的参考图像。
  
  @param image参考图像为CGImage。
  @param orientation图像方向。
  @param physicalWidth物理对象的宽度（以米为单位）。
  @return参考图片或 出错时为nil。
 */
- (instancetype)initWithCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Creates a new reference image.
 
 @param pixelBuffer The reference image as CVPixelBuffer.
 @param physicalWidth The width in meters of the physical object.
 @param orientation The image orientation.
 @return Reference image or nil on error.
  创建新的参考图像。
  
  @param pixelBuffer参考图像为CVPixelBuffer。
  @param physicalWidth物理对象的宽度（以米为单位）。
  @param orientation图像方向。
  @return参考图片 或出错时为nil。
 */
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Returns the set of ARReferenceImages in the specified resource group and bundle.

 @param name The name of the resource group.
 @param bundle The bundle containing the image file or asset catalog. Specify nil to search the app’s main bundle.
 @return The set of reference images or nil on error.
 返回指定资源组和包中的ARReferenceImages集。
 
  @param name资源组的名称。
  @param bundle包含图像文件或资产目录的包。指定nil以搜索应用程序的主包。
  @return参考图像集 或错误时为nil。
 */
+ (nullable NSSet<ARReferenceImage *> *)referenceImagesInGroupNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

/** Unavailable 不可用*/
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
