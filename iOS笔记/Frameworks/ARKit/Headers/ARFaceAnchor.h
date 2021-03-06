//
//  ARFaceAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Blend shape locations of a face geometry.
 @discussion Each location defines an area of the face that can be displaced with a provided coefficient.
  混合面几何的形状位置。
  每个位置定义一个可以用提供的系数移动的面部区域。
 */
typedef NSString *ARBlendShapeLocation NS_STRING_ENUM NS_SWIFT_NAME(ARFaceAnchor.BlendShapeLocation) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眉毛下垂向左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownLeft           API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眉毛下垂向右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownRight          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眉间向内
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowInnerUp            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眉毛外向左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眉毛外向右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//脸颊膨胀
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekPuff              API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//向左斜视
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//向右斜视
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眨左眼
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkLeft           API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眨右眼
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkRight          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看左下
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看右下
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看左内
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看右内
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看左外
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看右外
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看左上
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛看右上
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛斜视左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//眼睛斜视右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//左眼大
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideLeft            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//右眼大
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideRight           API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//下巴向前
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawForward             API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//下巴向左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawLeft                API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//下巴开
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawOpen                API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//下巴向右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawRight               API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//闭嘴
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthClose             API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴巴留下了左酒窝
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴巴留下了右酒窝
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴皱眉左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴皱眉右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//口漏斗
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFunnel            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴巴左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLeft              API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴低下左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownLeft     API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴低下右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownRight    API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴按左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴按右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴里褶皱
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPucker            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴巴右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRight             API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴卷降低
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollLower         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴巴上卷
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollUpper         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴向下
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugLower        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴向上
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugUpper        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//微笑向左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//微笑向右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//口伸展左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchLeft       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//口伸展右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchRight      API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴上部左上
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpLeft       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//嘴上部右上
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpRight      API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//鼻子冷笑左
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
//鼻子冷笑右
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@class ARFaceGeometry;

/**
 An anchor representing a face and its geometry.
 表示面部及其几何形状的锚点。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFaceAnchor : ARAnchor <ARTrackable>

/**
 The face geometry updated based on the computed blend shapes.
 基于计算的混合形状更新面几何。
 */
@property (nonatomic, readonly) ARFaceGeometry *geometry;

/**
 A dictionary of blend shape coefficients for each blend shape location.
 @discussion Blend shapes coefficients define the amount of displacement of a neutral shape at a specific location on the face.
 每个混合形状位置的混合形状系数的字典。
   @discussion混合形状系数定义了面部特定位置的中性形状的位移量。
 */
@property (nonatomic, readonly) NSDictionary<ARBlendShapeLocation, NSNumber*> *blendShapes;

/** Unavailable 不可用*/
- (instancetype)initWithTransform:(matrix_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
