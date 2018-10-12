/* CoreAnimation - CADisplayLink.h

   Copyright (c) 2009-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

@class NSString, NSRunLoop;

NS_ASSUME_NONNULL_BEGIN

/** 表示绑定到显示vsync的计时器的类。 **/

CA_CLASS_AVAILABLE_IOS(3.1, 9.0, 2.0)
@interface CADisplayLink : NSObject
{
@private
  void *_impl;
}

/*
 为主显示创建一个新的显示链接对象。 它将在'target'上调用名为'sel'的方法，该方法具有签名'（void）选择器：（CADisplayLink *）sender'。
 */
+ (CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel;

/*
 将接收器添加到给定的运行循环和模式。 除非暂停，它将触发每个vsync，直到删除。
 每个对象只能添加到单个run-loop运行循环中，但可以一次添加多个模式。 在添加到run-loop运行循环时，它将隐式保留。
 */
- (void)addToRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/*
 从runloop的给定模式中删除接收器(self)。 当从已注册的最后一个模式中删除时，这将隐式释放它。
 */
- (void)removeFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/*
 从所有runloop模式中移除对象（如果已隐式保留接收器，则释放接收器）并释放“target”对象。
 */
- (void)invalidate;

/*
 与之关联的显示帧的当前时间和持续时间，使用正常的Core Animation约定表示时间，即Mach主机时间转换为秒。
 */
//上一次Selector被调用的时间(屏幕显示的上一帧的时间戳)， 只读
@property(readonly, nonatomic) CFTimeInterval timestamp;
//屏幕刷新时间间隔， 目前iOS刷新频率是60HZ(iphoneXs系列 120), 所以刷新时间间隔是16.7ms
@property(readonly, nonatomic) CFTimeInterval duration;

/* 客户端应为其渲染目标设置的下一个时间戳。*/
//下一次被调用到时间
@property(readonly, nonatomic) CFTimeInterval targetTimestamp CA_AVAILABLE_IOS_STARTING(10.0, 10.0, 3.0);

/* 是否暂停,如果为true，则禁止对象触发。 初始状态为NO. */
@property(getter=isPaused, nonatomic) BOOL paused;

/*
 间隔多少帧调用一次selector 方法:
 定义每次显示链接触发之间必须传递多少个显示帧。默认值为1，这意味着显示链接将为每个显示帧触发。
 将间隔设置为2将导致显示链接触发每一个其他显示帧，依此类推。使用值小于1时的行为是未定义的。
 DEPRECATED(iOS10开始弃用) - 使用preferredFramesPerSecond代替。
 */
@property(nonatomic) NSInteger frameInterval
  CA_AVAILABLE_BUT_DEPRECATED_IOS (3.1, 10.0, 9.0, 10.0, 2.0, 3.0, "use preferredFramesPerSecond");

/* 
 为此显示链接定义所需的每秒帧数回调率。
 默认值为60.如果设置为零，则显示链接将以显示硬件的本机节奏触发。显示链接将尽力尝试以请求的速率发出回调。
 */
//事件触发间隔。是指两次selector触发之间间隔几次屏幕刷新，默认值为1，
//也就是说屏幕每刷新一次，执行一次selector，这个也可以间接用来控制动画速度
@property(nonatomic) NSInteger preferredFramesPerSecond CA_AVAILABLE_IOS_STARTING(10.0, 10.0, 3.0);

@end

NS_ASSUME_NONNULL_END
