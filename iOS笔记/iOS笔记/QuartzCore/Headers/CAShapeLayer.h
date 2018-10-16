/* CoreAnimation - CAShapeLayer.h

   Copyright (c) 2008-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

/* The shape layer draws a cubic Bezier spline in its coordinate space.
 *
 * The spline is described using a CGPath object and may have both fill
 * and stroke components (in which case the stroke is composited over
 * the fill). The shape as a whole is composited between the layer's
 * contents and its first sublayer.
 *
 * The path object may be animated using any of the concrete subclasses
 * of CAPropertyAnimation. Paths will interpolate as a linear blend of
 * the "on-line" points; "off-line" points may be interpolated
 * non-linearly (e.g. to preserve continuity of the curve's
 * derivative). If the two paths have a different number of control
 * points or segments the results are undefined.
 *
 * The shape will be drawn antialiased, and whenever possible it will
 * be mapped into screen space before being rasterized to preserve
 * resolution independence. (However, certain kinds of image processing
 * operations, e.g. CoreImage filters, applied to the layer or its
 * ancestors may force rasterization in a local coordinate space.)
 *
 * Note: rasterization may favor speed over accuracy, e.g. pixels with
 * multiple intersecting path segments may not give exact results.
 
 形状图层在其坐标空间中绘制三次贝塞尔样条曲线。
 *
 *使用CGPath对象描述样条曲线，并且可能同时具有填充和描边组件（在这种情况下，笔划在填充上合成）。整个形状在图层的内容和第一个子图层之间合成。
 *
 *路径对象可以使用CAPropertyAnimation的任何具体子类进行动画处理。路径将插值为“在线”点的线性混合; “离线”点可以非线性插值（例如，以保持曲线导数的连续性）。如果两个路径具有不同数量的控制点或段，则结果是不确定的。
 *
 *将绘制抗锯齿形状，并且在光栅化之前，它将被映射到屏幕空间以保持分辨率独立性。 （但是，应用于图层或其祖先的某些类型的图像处理操作，例如CoreImage滤镜，可能会强制在局部坐标空间中进行光栅化。）
 *
 *注意：光栅化可能有利于速度超过准确性，例如具有多个相交路径段的像素可能无法给出精确结果。
 */

CA_CLASS_AVAILABLE (10.6, 3.0, 9.0, 2.0)
@interface CAShapeLayer : CALayer

/* The path defining the shape to be rendered. If the path extends
 * outside the layer bounds it will not automatically be clipped to the
 * layer, only if the normal layer masking rules cause that. Upon
 * assignment the path is copied. Defaults to null. Animatable.
 * (Note that although the path property is animatable, no implicit
 * animation will be created when the property is changed.)
 
 定义要渲染的形状的路径。 如果路径延伸到图层边界之外，则只有在普通图层蒙版规则导致该图层时，它才会自动剪切到图层。
 在分配时，路径被复制。 默认为null。支持动画。
（请注意，尽管path属性是可动画的，但在更改属性时不会创建隐式动画。）
 */
@property(nullable) CGPathRef path;

/* 填充路径的颜色，或者没有填充的颜色。 默认为不透明黑色。支持动画。*/
@property(nullable) CGColorRef fillColor;

/* 填充路径时使用的填充规则。 值有两种，非零kCAFillRuleNonZero和奇偶数kCAFillRuleEvenOdd。默认为非零。 */
@property(copy) NSString *fillRule;

/* 描边色-填充路径描边轮廓的颜色，或者没有描边的颜色。 默认为nil。支持动画。 */
@property(nullable) CGColorRef strokeColor;

/*
 这些值定义用于绘制描边轮廓的路径的子区域。 值必须在[0,1]范围内，0表示路径的起点，1表示结束。
 零和一之间的值沿路径长度线性插值。 strokeStart默认为0，strokeEnd为1。 两者都是支持动画的。
 */
@property CGFloat strokeStart;
@property CGFloat strokeEnd;

/* 绘制路径时使用的线宽。 默认为1。支持动画。 */
@property CGFloat lineWidth;

/*
 绘制路径时使用的斜接限制。 默认为10。支持动画。
 
 miterLimit为最大斜接长度。斜接长度指的是在两条线交汇处和外交之间的距离。只有lineJoin属性为kCALineJoinMiter时miterLimit才有效。边角的角度越小，斜接长度就会越大。为了避免斜接长度过长，我们可以使用miterLimit属性。如果斜接长度超过miterLimit的值，边角会以lineJoin的“bevel”即kCALineJoinBevel类型来显示。
 */
@property CGFloat miterLimit;

/* 线端点类型-绘制路径时使用的上限样式。 选项是“butt”，“round”和“square”。 默认为“butt”。 */
@property(copy) NSString *lineCap;

/*
 线连接类型-描边路径时使用的连接样式。 选项是`miter', `round' and `bevel'.（“斜接”，“圆形”和“斜面”）。 默认为“miter”。
 */
@property(copy) NSString *lineJoin;

/* 创建笔划时应用的划线图案的相位。 默认为零。动画。
 线型模版的起始位置 */
@property CGFloat lineDashPhase;

/* 创建路径的描述版本时应用的破折号模式（NSNumbers数组）。 默认为零....
 线性模版，这是一个NSNumber的数组，索引从1开始记，奇数位数值表示实线长度，偶数位数值表示空白长度。*/
@property(nullable, copy) NSArray<NSNumber *> *lineDashPattern;

@end

/* `fillRule' values. */

CA_EXTERN NSString *const kCAFillRuleNonZero
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString *const kCAFillRuleEvenOdd
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* `lineJoin' values. */

CA_EXTERN NSString *const kCALineJoinMiter
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString *const kCALineJoinRound
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString *const kCALineJoinBevel
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* `lineCap' values. */

CA_EXTERN NSString *const kCALineCapButt
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString *const kCALineCapRound
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString *const kCALineCapSquare
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END



