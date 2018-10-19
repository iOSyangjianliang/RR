/* CoreAnimation - CAEmitterLayer.h

   Copyright (c) 2007-2017, Apple Inc.
   All rights reserved. */

/* Particle emitter layer.
 *
 * Each emitter has an array of cells, the cells define how particles
 * are emitted and rendered by the layer.
 *
 * Particle system is affected by layer's timing. The simulation starts
 * at layer's beginTime.
 *
 * The particles are drawn above the backgroundColor and border of the
 * layer.
 
 粒子发射层。
 *
 *每个发射器都有一个单元阵列，单元定义了粒子如何发射和渲染。
 *
 *粒子系统受图层时序的影响。 模拟从图层的beginTime开始。
 *
 *粒子绘制在backgroundColor和图层边框上方。
 */

#import <QuartzCore/CALayer.h>

@class CAEmitterCell;

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.6, 5.0, 9.0, 2.0)
@interface CAEmitterLayer : CALayer

/* 附着在图层上的发射器单元阵列。 每个对象都必须具有CAEmitterCell类。 */
@property(nullable, copy) NSArray<CAEmitterCell *> *emitterCells;

/* 将每个细胞的出生率乘以该数，得出每秒产生的实际粒子数。 默认值为1。支持动画。 */
@property float birthRate;

/* 创建粒子时，单元生命周期范围乘以此值。 默认为1。支持动画。 */
@property float lifetime;

/* 发射形状的中心。 默认为（0,0,0）。支持动画。 */
@property CGPoint emitterPosition;
@property CGFloat emitterZPosition;

/* 发射形状的大小。 默认为（0,0,0）。支持动画。 根据`emitterShape'属性，可以忽略某些值。 */
@property CGSize emitterSize;
@property CGFloat emitterDepth;

/*
 定义所用发射形状类型的字符串。 当前选项有：'point'（默认值），`line'，`rectangle'，`circle'，`cuboid'和`sphere'。
 */
@property(copy) NSString *emitterShape;

/* 一个字符串，定义如何相对于发射形状创建粒子。 当前选项是“points”，“outline”，“surface”和“volume”（默认值）。*/
@property(copy) NSString *emitterMode;

/*
 定义粒子如何合成到图层图像中的字符串。 当前选项是“unordered”（默认），“oldestFirst”，“oldestLast”，“backToFront”（即按Z顺序排序）和“additive”。 前四个使用源代码合成，最后一个使用添加剂合成。
 */
@property(copy) NSString *renderMode;

/* 当为YES时，粒子被渲染为好像它们直接位于层的超层的三维坐标空间中，而不是首先被平展到层的平面中。 默认为NO。
 如果为true，则未定义图层的“filters”，“backgroundFilters”和阴影相关属性的效果。 */
@property BOOL preservesDepth;

/* 将cell定义的粒子速度相乘。 默认为1。支持动画。 */
@property float velocity;

/* 将细胞定义的粒子尺度相乘。 默认为1。支持动画。*/
@property float scale;

/* 将细胞定义的粒子旋转相乘。 默认为1。支持动画。 */
@property float spin;

/* The seed used to initialize the random number generator. Defaults to
 * zero. Each layer has its own RNG state. For properties with a mean M
 * and a range R, random values of the properties are uniformly
 * distributed in the interval [M - R/2, M + R/2].
 
 种子用于初始化随机数发生器。 默认为零。 每个层都有自己的RNG状态。 对于具有平均值M和范围R的属性，属性的随机值均匀地分布在区间[M-R / 2，M + R / 2]中。
 */
@property unsigned int seed;

@end

/** `emitterShape' values. **/

CA_EXTERN NSString * const kCAEmitterLayerPoint
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerLine
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerRectangle
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerCuboid
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerCircle
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerSphere
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);

/** `emitterMode' values. **/

CA_EXTERN NSString * const kCAEmitterLayerPoints
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerOutline
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerSurface
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerVolume
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);

/** `renderMode' values. **/

CA_EXTERN NSString * const kCAEmitterLayerUnordered
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerOldestFirst
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerOldestLast
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerBackToFront
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAEmitterLayerAdditive
    CA_AVAILABLE_STARTING (10.6, 5.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
