/* CoreAnimation - CAEmitterCell.h

   Copyright (c) 2007-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.6, 5.0, 9.0, 2.0)
@interface CAEmitterCell : NSObject <NSSecureCoding, CAMediaTiming>
{
@private
  void *_attr[2];
  void *_state;
  uint32_t _flags;
}

+ (instancetype)emitterCell;

/* 发射器单元实现与CALayer定义的相同的属性模型。 有关详细信息，请参阅CALayer.h。 */
//根据健 获 得 值
+ (nullable id)defaultValueForKey:(NSString *)key;
//是否 归 档莫 键值
- (BOOL)shouldArchiveValueForKey:(NSString *)key;

/* 粒子的名字。 用于构造关键路径。 默认为nil。 */
@property(nullable, copy) NSString *name;

/* 粒子是否被渲染 */
@property(getter=isEnabled) BOOL enabled;

/* 每秒创建的发射对象数。 默认值为零。支持动画。 */
@property float birthRate;

/*
 每个发射对象的生命周期（以秒为单位），指定为平均值和平均值范围。 两个值都默认为零。支持动画。
 */
//生命周期
@property float lifetime;
//生命周期范围
@property float lifetimeRange;

/*
 以弧度为单位的发射角的取向，相对于发射形状的自然取向角。 请注意，这里的纬度通常称为colatitude，天顶或phi，与z轴的角度。
 类似地，经度是x轴平面中与x轴的角度，通常称为方位角或θ。 两个值都默认为零，这相对于发射形状的方向没有变化。 这两个值都是支持动画的。
 */

//发射的 z 轴方向的角度
@property CGFloat emissionLatitude;
//x-y 平面的 发 射方向
@property CGFloat emissionLongitude;

/* 围绕发射角定义锥形的角度（以弧度表示）。 发射的物体均匀分布在该锥体上。 默认为零。支持动画。 */
@property CGFloat emissionRange;

/* 每个发射物体的初始平均速度及其范围。 两个值都默认为零。支持动画。 */
@property CGFloat velocity;
@property CGFloat velocityRange;

/* 应用于发射物体的加速度矢量。 默认为（0,0,0）。支持动画。*/
@property CGFloat xAcceleration;
@property CGFloat yAcceleration;
@property CGFloat zAcceleration;

/* 应用于每个发射对象的比例因子，定义为平均值和平均值范围。 比例默认为1，范围为零。支持动画。 */
@property CGFloat scale;     //缩放比例
@property CGFloat scaleRange;//缩放比例范围
@property CGFloat scaleSpeed;//缩放比例速度

/*
 应用于每个发射物体的自旋转速度，定义为平均值和平均值范围。 默认为零。支持动画。
 */
@property CGFloat spin;     //子旋转角度
@property CGFloat spinRange;//子旋转角度范围

/* 粒子的颜色-每个发射物体的平均颜色，以及该平均颜色的范围。 `color'默认为opaque white，`colorRange'为（0,0,0,0）。支持动画。 */
@property(nullable) CGColorRef color;

@property float redRange;
@property float greenRange;
@property float blueRange;
@property float alphaRange;

/* 发射物体的颜色分量在其寿命期间发生变化的速度，定义为每秒的变化率。 默认为（0,0,0,0）。支持动画。 */
@property float redSpeed;
@property float greenSpeed;
@property float blueSpeed;
@property float alphaSpeed;

/* 单元格内容，通常是CGImageRef。 默认为零。支持动画。 */
@property(nullable, strong) id contents;

/* 将绘制的内容图像的子矩形。 有关详细信息，请参阅CALayer.h。 默认为单位矩形[0 0 1 1]。支持动画。 */
@property CGRect contentsRect;

/* 定义应用于单元格内容的比例因子。 有关详细信息，请参阅CALayer.h。 */
@property CGFloat contentsScale;

/* 渲染“内容”图像时使用的滤镜参数。 有关详细信息，请参阅CALayer.h。 */
@property(copy) NSString *minificationFilter;
@property(copy) NSString *magnificationFilter;
@property float minificationFilterBias;

/*
 粒子发射的粒子
 包含此单元格的子单元格的数组，或nil（默认值）。 当非零时，由细胞发射的每个粒子将充当每个细胞的子细胞的发射体。
 发射点是当前粒子位置，发射角度是相对于粒子的当前方向。支持动画。 */
@property(nullable, copy) NSArray<CAEmitterCell *> *emitterCells;

/* 类似于Layer图层的继承属性。 */
@property(nullable, copy) NSDictionary *style;

@end

NS_ASSUME_NONNULL_END
