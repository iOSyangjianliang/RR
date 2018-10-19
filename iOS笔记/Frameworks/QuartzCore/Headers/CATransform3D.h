/* CoreAnimation - CATransform3D.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#ifndef CATRANSFORM_H
#define CATRANSFORM_H

#include <QuartzCore/CABase.h>

#ifdef __OBJC__
#import <Foundation/NSValue.h>
#endif

/* Homogeneous three-dimensional transforms.均匀的三维变换。 */

struct CATransform3D
{
  CGFloat m11, m12, m13, m14;
  CGFloat m21, m22, m23, m24;
  CGFloat m31, m32, m33, m34;
  CGFloat m41, m42, m43, m44;
};

typedef struct CATransform3D CATransform3D;

CA_EXTERN_C_BEGIN

/* The identity transform: [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]. */
//默认单位矩阵
CA_EXTERN const CATransform3D CATransform3DIdentity
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns true if 't' is the identity transform. */
//是否是默认的单位矩阵
CA_EXTERN bool CATransform3DIsIdentity (CATransform3D t)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns true if 'a' is exactly equal to 'b'. */
//比较两个transform3D对象是否等同
CA_EXTERN bool CATransform3DEqualToTransform (CATransform3D a,
    CATransform3D b)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns a transform that translates by '(tx, ty, tz)':
 * t' =  [1 0 0 0; 0 1 0 0; 0 0 1 0; tx ty tz 1]. */
//平移---返回一个平移变换的transform3D对象 tx，ty，tz对应x，y，z轴的平移
CA_EXTERN CATransform3D CATransform3DMakeTranslation (CGFloat tx,
    CGFloat ty, CGFloat tz)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns a transform that scales by `(sx, sy, sz)':
 * t' = [sx 0 0 0; 0 sy 0 0; 0 0 sz 0; 0 0 0 1]. */
//缩放---x，y，z分别对应x轴，y轴，z轴的缩放比例
CA_EXTERN CATransform3D CATransform3DMakeScale (CGFloat sx, CGFloat sy,
    CGFloat sz)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns a transform that rotates by 'angle' radians about the vector
 * '(x, y, z)'. If the vector has length zero the identity transform is
 * returned. */
//旋转---angle参数是旋转的角度 ，x，y，z决定了旋转围绕的中轴，取值为-1 — 1之间，如（1，0，0）,则是绕x轴旋转，（0.5，0.5，0），则是绕x轴与y轴中间45度为轴旋转
CA_EXTERN CATransform3D CATransform3DMakeRotation (CGFloat angle, CGFloat x,
    CGFloat y, CGFloat z)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Translate 't' by '(tx, ty, tz)' and return the result:
 * t' = translate(tx, ty, tz) * t. */
//平移---在某个transform3D变换的基础上进行平移变换，t是上一个transform3D
CA_EXTERN CATransform3D CATransform3DTranslate (CATransform3D t, CGFloat tx,
    CGFloat ty, CGFloat tz)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Scale 't' by '(sx, sy, sz)' and return the result:
 * t' = scale(sx, sy, sz) * t. */
//缩放---在一个transform3D变换的基础上进行缩放变换
CA_EXTERN CATransform3D CATransform3DScale (CATransform3D t, CGFloat sx,
    CGFloat sy, CGFloat sz)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Rotate 't' by 'angle' radians about the vector '(x, y, z)' and return
 * the result. If the vector has zero length the behavior is undefined:
 * t' = rotation(angle, x, y, z) * t. */
//旋转---在一个transform3D的基础上进行旋转变换
CA_EXTERN CATransform3D CATransform3DRotate (CATransform3D t, CGFloat angle,
    CGFloat x, CGFloat y, CGFloat z)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Concatenate 'b' to 'a' and return the result: t' = a * b. */
//将两个 transform3D对象变换属性进行叠加，返回一个新的transform3D对象
CA_EXTERN CATransform3D CATransform3DConcat (CATransform3D a, CATransform3D b)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Invert 't' and return the result. Returns the original matrix if 't'
 * has no inverse. */
//类似CGAffineTransform 中的CGAffineTransformInvert 代表 反向变换
CA_EXTERN CATransform3D CATransform3DInvert (CATransform3D t)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Return a transform with the same effect as affine transform 'm'. */

//CATransform3D和CGAffineTransform相互转换
//将一个CGAffineTransform转化为CATransform3D
CA_EXTERN CATransform3D CATransform3DMakeAffineTransform (CGAffineTransform m)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns true if 't' can be represented exactly by an affine transform. */

//判断一个CATransform3D是否可以转换为CGAffineTransform
CA_EXTERN bool CATransform3DIsAffine (CATransform3D t)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Returns the affine transform represented by 't'. If 't' can not be
 * represented exactly by an affine transform the returned value is
 * undefined. */
//将CATransform3D转换为CGAffineTransform
CA_EXTERN CGAffineTransform CATransform3DGetAffineTransform (CATransform3D t)
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

CA_EXTERN_C_END

/** NSValue support. **/

#ifdef __OBJC__

NS_ASSUME_NONNULL_BEGIN

@interface NSValue (CATransform3DAdditions)

+ (NSValue *)valueWithCATransform3D:(CATransform3D)t;

@property(readonly) CATransform3D CATransform3DValue;

@end

NS_ASSUME_NONNULL_END

#endif /* __OBJC__ */

#endif /* CATRANSFORM_H */
