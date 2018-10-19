/* CoreAnimation - CAValueFunction.h

   Copyright (c) 2008-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.6, 3.0, 9.0, 2.0)
@interface CAValueFunction : NSObject <NSSecureCoding>
{
@protected
  NSString *_string;
  void *_impl;
}

+ (nullable instancetype)functionWithName:(NSString *)name;

@property(readonly) NSString *name;

@end

/** Value function names. **/

/* The `rotateX', `rotateY', `rotateZ' functions take a single input
 * value in radians, and construct a 4x4 matrix representing the
 * corresponding rotation matrix.

 `rotateX'，`rotateY'，`rotateZ'函数以弧度为单位输入一个值，并构造一个表示相应旋转矩阵的4x4矩阵。
 */

CA_EXTERN NSString * const kCAValueFunctionRotateX
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionRotateY
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionRotateZ
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `scale' function takes three input values and constructs a
 * 4x4 matrix representing the corresponding scale matrix.
 
 “scale”函数接受三个输入值并构造一个表示相应比例矩阵的4x4矩阵。
 */

CA_EXTERN NSString * const kCAValueFunctionScale
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `scaleX', `scaleY', `scaleZ' functions take a single input value
 * and construct a 4x4 matrix representing the corresponding scaling
 * matrix.

 `scaleX'，`scaleY'，`scaleZ'函数采用单个输入值并构造表示相应缩放矩阵的4x4矩阵。
 */

CA_EXTERN NSString * const kCAValueFunctionScaleX
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionScaleY
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionScaleZ
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `translate' function takes three input values and constructs a
 * 4x4 matrix representing the corresponding scale matrix.
 
 `translate'函数接受三个输入值并构造一个表示相应比例矩阵的4x4矩阵。
 */

CA_EXTERN NSString * const kCAValueFunctionTranslate
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `translateX', `translateY', `translateZ' functions take a single
 * input value and construct a 4x4 matrix representing the corresponding
 * translation matrix.

`translateX'，`translateY'，`translateZ'函数采用单个输入值并构造表示相应转换矩阵的4x4矩阵。
 */

CA_EXTERN NSString * const kCAValueFunctionTranslateX
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionTranslateY
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionTranslateZ
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
