/* CoreAnimation - CAMediaTiming.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <objc/objc.h>
#import <Foundation/NSObject.h>


/* The CAMediaTiming protocol is implemented by layers and animations, it
 * models a hierarchical timing system, with each object describing the
 * mapping from time values in the object's parent to local time.
 *
 * Absolute time is defined as mach time converted to seconds. The
 * CACurrentMediaTime function is provided as a convenience for querying the
 * current absolute time.
 *
 * The conversion from parent time to local time has two stages:
 *
 * 1. conversion to "active local time". This includes the point at
 * which the object appears in the parent's timeline, and how fast it
 * plays relative to the parent.
 *
 * 2. conversion from active to "basic local time". The timing model
 * allows for objects to repeat their basic duration multiple times,
 * and optionally to play backwards before repeating.
 
 CAMediaTiming协议由CALayer图层和CAAnimation动画实现的，它为分层计时系统建模，每个对象描述从对象父级中的时间值到本地时间的映射。
  *
  绝对时间定义为转换为秒的马赫时间。 提供CACurrentMediaTime函数是为了方便查询当前的绝对时间。
  *
  *从父级时间到本地时间的转换有两个阶段：
  *
  * 1.转换为“本地活跃时间”。 这包括对象在父级时间轴中出现的点，以及它相对于父级的播放速度。
  *
  * 2.从活跃转换为“基本本地时间”。 计时模型允许对象多次重复其基本持续时间，并且可选地在重复之前向后播放。
 */

@class NSString;

NS_ASSUME_NONNULL_BEGIN

//CALayer和CAAnimation都实现了CAMediaTiming 协议
@protocol CAMediaTiming

/*
 动画开始的时间，所有类型对象的该值默认为0，它是一个相对值：
 举例：假如layer.beginTime = 1，图层上的动画animation.beginTime = CACurrentMediaTime() + 2 ，那么这个动画被加入之后就会延迟1+2=3秒钟开始执行
 */
@property CFTimeInterval beginTime;

/* 对象的基本持续时间。 默认为0*/
@property CFTimeInterval duration;

/*
 图层的速率。 用于将父级时间缩放到当地时间，例如 如果rate为2，则本地时间的进度是父时间的两倍。 默认为1。
 
 通俗来说就是运动速度，如果一个动画A :duration为1秒，speed为1；而另一个动画B：duration为2秒，speed为2。则两个动画的效果是相同的。不过前提是它们的super layer相同。
 
 eg：速度为2的动画组有一部分动画的速度为1.5，那么这个动画就是3倍于正常速度。
 如果一个速度为3的动画加到一个速度为0.5的layer上，这个动画最终将会以1.5倍的常速运行
 */
@property float speed;

/*
 活动本地时间的附加偏移量。 即从父时间tp转换为活动本地时间t：t =（tp-begin）* speed + offset。
 其中一个用途是通过将“speed”设置为零并将“offset”设置为合适的值来“暂停”一个图层。 默认为0。
 
 timeOffset和beginTime类似，但是和增加beginTime导致的延迟动画不同，增加timeOffset只是让动画快进到某一点，例如，对于一个持续1秒的动画来说，设置timeOffset为0.5意味着动画将从一半的地方开始。默认值0
 eg: timeOffset=2
 0-1-2-3-4
 2-3-4-1-0
 */
@property CFTimeInterval timeOffset;

/*
 对象的重复计数。 可能是分数。 默认为0。
 */
@property float repeatCount;

/*
 对象的重复持续时间。 默认为0。
 */
@property CFTimeInterval repeatDuration;

/*
 如果为true，则对象在向前播放后再向后播放。 默认为NO
 
 动画x执行完后再反向执行动画
 */
@property BOOL autoreverses;

/* 
 定义定时对象在其活动持续时间之外的行为方式。 可以将本地时间钳制到活动持续时间的任一端，或者可以从演示中移除该元素。
 可选值为 `backwards', `forwards', `both' and `removed'. 默认是`removed'(kCAFillModeRemoved)
 
 动画执行完事之后，应该怎么处理
 */
@property(copy) NSString *fillMode;

@end

/* `fillMode' 选项.
 kCAFillModeRemoved也是fillMode的默认属性，此时动画的效果：开始时，colorLayer的size为（20，20），当到2s的时候，colorLayer的size突然就变为（100，100），然后开始做动画，当到7s的时候colorLayer的duration已经完成，此时colorLayer的size会突然 变为（20，20），然后在持续3s，当总时间到10s时结束。
 
 当fillMode的属性设置为kCAFillModeForwards的时候，动画效果为：开始时，colorLayer的size为（20，20），当到2s的时候，colorLayer的size突然就变为（100，100），然后开始做动画，之前都和kCAFillModeRemoved都一样，不一样的时当到7s的时候colorLayer的duration已经完成，此时colorLayer的size还会保持在（400，400），然后在持续3s，当总时间到10s时结束，此时size才变为（20，20）
 
 当fillMode的属性设置为kCAFillModeBackwards的时候，动画效果为：开始时，colorLayer的size就为（100，100），当到2s的时候，colorLayer开始做动画，当到7s的时候colorLayer的duration已经完成，此时colorLayer的size会突然 变为（20，20），然后在持续3s，当总时间到10s时结束。
 
 kCAFillModeBoth就不在解释了，猜都能猜到应该是kCAFillModeForwards和kCAFillModeBackwards的结合。

 原文：https://blog.csdn.net/yaozhuoyu/article/details/9566511?utm_source=copy
 */

CA_EXTERN NSString * const kCAFillModeForwards
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAFillModeBackwards
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAFillModeBoth
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAFillModeRemoved
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
