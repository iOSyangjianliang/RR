/* CoreAnimation - CAGradientLayer.h

   Copyright (c) 2008-2017, Apple Inc.
   All rights reserved. */

/* The gradient layer draws a color gradient over its background color,
 * filling the shape of the layer (i.e. including rounded corners). */

#import <QuartzCore/CALayer.h>
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.6, 3.0, 9.0, 2.0)
@interface CAGradientLayer : CALayer

/* CGColorRef对象数组定义每个渐变色标的颜色。 默认为nil。支持动画。 */
@property(nullable, copy) NSArray *colors;

/*
 一个可选的NSNumber对象数组，将每个渐变停止点的位置定义为[0,1]范围内的值。
 值必须单调递增。 如果给出nil数组，则假定停靠点在[0,1]范围内均匀分布。 渲染时，颜色在插入之前映射到输出颜色空间。 默认为nil。支持动画。
 
 locations的数组长度和color一致，各个颜色阶梯的区间百分比
 eg:
 colors = 3个颜色、locations = [0.1,0.6,1]表示第一个颜色占0%-10%，第二个占10%-60%的区间...每种颜色最亮的位置
 */
@property(nullable, copy) NSArray<NSNumber *> *locations;

/*
 绘制到图层坐标空间时渐变的起点和终点。 起点对应于第一个梯度停止，终点对应于最后一个梯度停止。
 两个点都在单位坐标空间中定义，然后在绘制时将其映射到图层的边界矩形。 （即。[0,0]是图层的左下角，[1,1]是右上角。）默认值分别为[0.5,0]和[0.5,1],也就是默认从上至下垂直渐变。 两者都是可动画的。
 */
@property CGPoint startPoint;
@property CGPoint endPoint;

/*
 将绘制的渐变类型-像素均匀变化。 目前唯一允许的值是“axial”（默认值kCAGradientLayerAxial）。 */
@property(copy) NSString *type;

@end

/** `type' values. **/

CA_EXTERN NSString * const kCAGradientLayerAxial
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
