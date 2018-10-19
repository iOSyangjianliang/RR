/* CoreAnimation - CAReplicatorLayer.h

   Copyright (c) 2008-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

/* The replicator layer creates a specified number of copies of its
 * sublayers, each copy potentially having geometric, temporal and
 * color transformations applied to it.
 *
 * Note: the CALayer -hitTest: method currently only tests the first
 * instance of z replicator layer's sublayers. This may change in the
 * future.
 
 复制器层创建其子层的指定数量的副本，每个副本可能具有应用于其的几何，时间和颜色变换。

 注意：CALayer -hitTest：方法目前仅测试z复制器层子层的第一个实例。 这可能在将来发生变化。
 */

CA_CLASS_AVAILABLE (10.6, 3.0, 9.0, 2.0)
@interface CAReplicatorLayer : CALayer

/* The number of copies to create, including the source object.
 * Default value is one (i.e. no extra copies). Animatable.
 要创建的副本数，包括源对象。 默认值为1（即没有额外的副本）。支持动画。
 */
@property NSInteger instanceCount;

/* Defines whether this layer flattens its sublayers into its plane or
 * not (i.e. whether it's treated similarly to a transform layer or
 * not). Defaults to NO. If YES, the standard restrictions apply (see
 * CATransformLayer.h).
 定义该层是否将其子层展平到其平面中（即它是否与变换层类似地处理）。 默认为NO。
 如果YES，则适用标准限制（请参阅CATransformLayer.h）。
 */
@property BOOL preservesDepth;

/* The temporal delay between replicated copies. Defaults to zero.
 * Animatable.
 复制副本之间的时间延迟。 默认为nil。支持动画。
 */
@property CFTimeInterval instanceDelay;

/* The matrix applied to instance k-1 to produce instance k. The matrix
 * is applied relative to the center of the replicator layer, i.e. the
 * superlayer of each replicated sublayer. Defaults to the identity
 * matrix. Animatable.
 矩阵应用于实例k-1以产生实例k。
 相对于复制器层的中心，即每个复制的子层的超层，应用矩阵。 默认为单位矩阵。支持动画。
 */
@property CATransform3D instanceTransform;

/* The color to multiply the first object by (the source object). Defaults
 * to opaque white. Animatable.
 用于将第一个对象乘以（源对象）的颜色。 默认为不透明白色。支持动画。
 
 设置多个复制图层的颜色,默认位白色
 */
@property(nullable) CGColorRef instanceColor;

/* The color components added to the color of instance k-1 to produce
 * the modulation color of instance k. Defaults to the clear color (no
 * change). Animatable.
 颜色分量添加到实例k-1的颜色以产生实例k的调制颜色。 默认为清晰颜色（无更改）。支持动画。
 
 设置每个复制图层相对上一个复制图层的红色、绿色、蓝色、透明度偏移量
 */
@property float instanceRedOffset;
@property float instanceGreenOffset;
@property float instanceBlueOffset;
@property float instanceAlphaOffset;

@end

NS_ASSUME_NONNULL_END
