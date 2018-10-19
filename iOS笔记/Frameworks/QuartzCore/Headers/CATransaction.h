/* CoreAnimation - CATransaction.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

/**
 CALayer的“Animatable”属性的设置都应该属于某一个CATransaction事务，CATransaction的作用是保证多个“Animatable”的变化同时进行。也就是说CALayer的属性修改需要依赖CATransaction。
 CATransaction 事务类,可以对多个layer的属性同时进行修改.它分隐式事务,和显式事务.
 [隐式]在某次RunLoop中设置了一个“Animatable”属性，如果当前没有设置事务，则会自动创建一个CATransaction，并在当前线程的下一个RunLoop中commit这个CATransaction。
 [显式]就是直接调用CATransaction的[CATransaction begin]，[CATransaction commit]等相关方法。比如我们不希望self.subLayer.position = CGPointMake(100, 100)产生动画，则可以在CATransaction中设置。
 区分隐式动画和隐式事务：隐式动画通过隐式事务实现动画 。
 区分显式动画和显式事务：显式动画有多种实现方式，显式事务是一种实现显式动画的方式。
 
 原文：https://blog.csdn.net/ci915194561/article/details/50100963?utm_source=copy
*/

/*
 事务是CoreAnimation的机制，用于将多个层树操作批处理到渲染树的原子性更新。 对层树的每次修改都要求事务成为其中的一部分。
 *
 * CoreAnimation支持两种事务，“显式”事务和“隐式”事务。
 *
 * 显式事务是程序员在修改层树之前调用“[CATransaction begin]”的地方，之后是“[CATransaction commit]”。
 *
 * 当没有活动事务的线程修改层树时，CoreAnimation会自动创建隐式事务。当线程的run-loop接下来迭代时，它们会自动提交。 在某些情况下（即没有运行循环或运行循环被阻止），可能需要使用显式事务来及时获取渲染树更新。
 */

@class CAMediaTimingFunction;

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CATransaction : NSObject

/* Begin a new transaction for the current thread; nests.
 为当前线程开始一个新事务;
 */
+ (void)begin;

/*
 提交当前事务期间所做的所有更改。 如果不存在当前事务，则引发异常。
 */
+ (void)commit;

/*
 提交任何现存的隐含交易。 将延迟实际提交，直到任何嵌套显式事务完成。
 */
+ (void)flush;

/*
 锁定和解锁全局锁的方法。
 图层方法在修改共享状态时自动获取此值，但调用者可能需要锁定多个操作以确保一致性。 锁是一种递归的自旋锁（即不应长时间保持）。
 */
+ (void)lock;
+ (void)unlock;

/*
 每个线程事务属性的“animationDuration”访问器。 定义添加到图层的动画的默认持续时间。 默认为0.25s。
 */
+ (CFTimeInterval)animationDuration;
+ (void)setAnimationDuration:(CFTimeInterval)dur;

/*
 每个线程事务属性的“animationTimingFunction”的访问器。 默认值为nil，当设置为非零值时，添加到图层的任何动画都将此值设置为其“timingFunction”属性。 在Mac OS X 10.6中添加。
 */
+ (nullable CAMediaTimingFunction *)animationTimingFunction;
+ (void)setAnimationTimingFunction:(nullable CAMediaTimingFunction *)function;

/*
 每个线程事务属性的“disableActions”访问器。 定义图层的-actionForKey：方法是否用于为每个图层属性更改查找操作（也称为隐式动画）。
 默认为NO，即启用隐式动画。...
 */
+ (BOOL)disableActions;
+ (void)setDisableActions:(BOOL)flag;

/*
 “completionBlock”每线程事务属性的访问器。
 一旦设置为非零值，只要此事务组随后添加的所有动画都已完成（或已被删除），就可以保证在（在主线程上）调用该块。
 如果在提交当前事务组之前未添加动画（或者将完成块设置为其他值），则将立即调用该块。 在Mac OS X 10.6中添加。
 */

#if __BLOCKS__
+ (nullable void (^)(void))completionBlock;
+ (void)setCompletionBlock:(nullable void (^)(void))block;
#endif

/*
 将任意键控数据与当前事务（即与当前线程）相关联。
 *
 *嵌套事务具有嵌套数据范围，即读取键搜索已设置它的最内部范围，设置键始终将其设置在最内层范围内。
 *
 *目前支持的事务属性包括：“animationDuration”，“animationTimingFunction”，“completionBlock”，“disableActions”。 有关每个属性的描述，请参阅上面的方法声明。
 *
 *尝试将属性设置为其文档类型以外的类型具有未定义的结果。
 */

+ (nullable id)valueForKey:(NSString *)key;
+ (void)setValue:(nullable id)anObject forKey:(NSString *)key;

@end

/** Transaction property ids. **/

CA_EXTERN NSString * const kCATransactionAnimationDuration
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransactionDisableActions
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransactionAnimationTimingFunction
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransactionCompletionBlock
    CA_AVAILABLE_STARTING (10.6, 4.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
