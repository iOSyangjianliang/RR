/* CoreAnimation - CAScrollLayer.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

//CAScrollLayer的可滚动区域的范围是由它的子层布局来确定的。 CAScrollLayer不提供键盘或鼠标事件处理，也没有提供可见滚动条。

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAScrollLayer : CALayer

/* 将图层的原点更改为“p”。 把指定点p滚动到左上角。点坐标可以是负值。*/
- (void)scrollToPoint:(CGPoint)p;

/* 滚动图层的内容以确保rect'r'可见。 */
- (void)scrollToRect:(CGRect)r;

/* 定义可以滚动图层的轴(水平垂直两个方向)。 可能的值是“none”，“vertical”，“horizontal”或“both”（默认值）。 */
@property(copy) NSString *scrollMode;

@end


//在CALayer的分类中实现的，所以所有CALayer子类都可以调用次方法来获取当前显示的可见区域范围。但是必须要是在CAScrollLayer的子图层。
@interface CALayer (CALayerScrolling)
/*
 通过从自身到父视图查找CAScrollLayer，进行对应操作，如果没有就不做处理！
 */
//从自身开始往父图层找到最近的CAScrollLayer层，然后调用-scrollToPoint: 方法，如果没有找到CAScrollLayer层则不做任何处理。
- (void)scrollPoint:(CGPoint)p;
//从自身开始往父图层找到最近的CAScrollLayer层，然后调用-scrollToRect: 方法，如果没有找到CAScrollLayer层则不做任何处理。
- (void)scrollRectToVisible:(CGRect)r;

/* 返回接收器的可见区域，在其自己的坐标空间中。 可见区域是未被包含滚动层剪切的区域。 */
@property(readonly) CGRect visibleRect;

@end

/* `scrollMode' values. */


CA_EXTERN NSString * const kCAScrollNone          //禁止滚动
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAScrollVertically    //垂直方向滑动
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAScrollHorizontally  //水平方向滑动
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAScrollBoth          //无限制滑动
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
