/* CoreAnimation - CAMediaTimingFunction.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CAMediaTiming.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString;

NS_ASSUME_NONNULL_BEGIN

/* Represents one segment of a function describing a timing curve. The
 * function maps an input time normalized to the range [0,1] to an
 * output time also in the range [0,1]. E.g. these functions are used
 * to define the pacing of an animation over its duration (or over the
 * duration of one keyframe).

 表示描述时序曲线的函数的一个段。 该函数将归一化到范围[0,1]的输入时间映射到也在[0,1]范围内的输出时间。
 例如。 这些函数用于定义动画在其持续时间内（或在一个关键帧的持续时间内）的调步。
 */

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAMediaTimingFunction : NSObject <NSSecureCoding>
{
@private
  struct CAMediaTimingFunctionPrivate *_priv;
}

/* A convenience method for creating common timing functions. The
 * currently supported names are `linear', `easeIn', `easeOut' and
 * `easeInEaseOut' and `default' (the curve used by implicit animations
 * created by Core Animation).
 一种创建通用定时功能的便捷方法。
 目前支持的名称是“linear”，“easeIn”，“easeOut”和“easeInEaseOut”以及“default”（由Core Animation创建的隐式动画使用的曲线）。
 */

+ (instancetype)functionWithName:(NSString *)name;

/* Creates a timing function modelled on a cubic Bezier curve. The end
 * points of the curve are at (0,0) and (1,1), the two points 'c1' and
 * 'c2' defined by the class instance are the control points. Thus the
 * points defining the Bezier curve are: '[(0,0), c1, c2, (1,1)]'
 
 创建以三次贝塞尔曲线为模型的定时功能。 曲线的终点位于（0,0）和（1,1），由类实例定义的两个点'c1'和'c2'是控制点。
 因此，定义贝塞尔曲线的点是：'[（0,0），c1，c2，（1,1）]'
 */
+ (instancetype)functionWithControlPoints:(float)c1x :(float)c1y :(float)c2x :(float)c2y;

- (instancetype)initWithControlPoints:(float)c1x :(float)c1y :(float)c2x :(float)c2y;

/* 'idx'是0到3之间的值，包括0和3。 */

- (void)getControlPointAtIndex:(size_t)idx values:(float[_Nonnull 2])ptr;

@end

/** Timing function names. **/

CA_EXTERN NSString * const kCAMediaTimingFunctionLinear
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAMediaTimingFunctionEaseIn
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAMediaTimingFunctionEaseOut
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAMediaTimingFunctionEaseInEaseOut
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAMediaTimingFunctionDefault
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
