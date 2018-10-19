/* CoreAnimation - CAAnimation.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString, CAMediaTimingFunction, CAValueFunction;
@protocol CAAnimationDelegate;

NS_ASSUME_NONNULL_BEGIN

/** The base animation class. **/
//CAAnimation是一个抽象类--- 不能直接使用,应该使用其具体子类。（一样的还有CAPropertyAnimation是基于属性的动画子类）

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAAnimation : NSObject
    <NSSecureCoding, NSCopying, CAMediaTiming, CAAction>
{
@private
  void *_attr;
  uint32_t _flags;
}

/* 创建一个新的动画对象。*/
+ (instancetype)animation;

/* 动画实现了CALayer定义的相同属性模型。 有关详细信息，请参阅CALayer.h。*/
+ (nullable id)defaultValueForKey:(NSString *)key;
- (BOOL)shouldArchiveValueForKey:(NSString *)key;

/* 定义动画节奏的计时函数。默认为nil表示线性步调。 */
@property(nullable, strong) CAMediaTimingFunction *timingFunction;

/*
 动画的代理。 此对象在动画对象的生命周期内保留(strong需特别注意)。 默认为nil。 请参阅下面的支持的委托方法。
 */
@property(nullable, strong) id <CAAnimationDelegate> delegate;

/* 如果为true，则一旦活动持续时间过去，动画将从渲染树中删除。 默认为YES。 */
@property(getter=isRemovedOnCompletion) BOOL removedOnCompletion;

@end

#park mark - CAAnimation动画代理方法。

@protocol CAAnimationDelegate <NSObject>
@optional

/* 在动画开始其活动持续时间时调用。 */
- (void)animationDidStart:(CAAnimation *)anim;

/* 当动画完成其活动持续时间、或从其附加到的对象（即图层）移除时调用。 如果动画到达其活动持续时间的末尾而未被删除，则“flag”为true。*/
- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag;

@end


#park mark - 属性动画
//CAAnimation的子类，也是个抽象类，要想创建动画对象，应该使用它的两个子类：CABasicAnimation和CAKeyframeAnimation
CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAPropertyAnimation : CAAnimation

/* 创建一个新的动画对象，其“keyPath”属性设置为“path”。*/
+ (instancetype)animationWithKeyPath:(nullable NSString *)path;

/* 描述要设置动画的属性的关键路径。即上面的path。 */
@property(nullable, copy) NSString *keyPath;

/*
 如果为true，则动画指定的值将“添加”到属性的当前显示值以生成新的演示文稿值。
 加法函数是类型相关的，例如， 对于仿射变换，两个矩阵是连接的。 默认为NO。
 
 如何处理多个动画在同一时间段执行的结果,若为YES,同一时间段的动画合成为一个动画。
 (使用 CAKeyframeAnimation 时必须将该属性指定为 YES ,否则不会出现期待的结果)*/
@property(getter=isAdditive) BOOL additive;

/* “cumulative”属性会影响重复动画如何产生结果。
 如果为true，则动画的当前值是上一个重复周期结束时的值加上当前重复周期的值。
 如果为false，则该值只是为当前重复周期计算的值。 默认为NO。*/
@property(getter=isCumulative) BOOL cumulative;

/*
 如果非nil，则在将插值设置为动画的目标属性的新显示值之前 应用于插值的函数。 默认为nil。
 该对象负责对属性改变的插值计算,系统已经提供了默认的插值计算方式,因此一般无须指定该属性。 */
@property(nullable, strong) CAValueFunction *valueFunction;

@end


#park mark - 基础动画
//CABaseAnimation用来实现一些比较简单的动画比如平移、缩放、旋转等,它本身只有三个属性,而且如果使用该动画,则至多有两个值不为nil。

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CABasicAnimation : CAPropertyAnimation

/*
 定义属性值的对象在两者之间进行插值。
 *所有都是可选的，不超过两个应该是非零的。 对象类型应与要设置动画的属性的类型匹配（使用CALayer.h中描述的标准规则）。 支持的动画模式是：
 *
 * - “fromValue”和“toValue”都是非nil的。 在`fromValue'和`toValue'之间插值。
 *
 * - “fromValue”和“byValue”非nil。 在`fromValue'和`fromValue'加上'byValue'之间插值。
 *
 * - “byValue”和“toValue”非nil。 在“toValue”减去“byValue”和“toValue”之间插值。
 *
 * - “fromValue”非nil。 在`fromValue'和属性的当前表示值之间插值。
 *
 * - “toValue”非nil。 在层的渲染树中属性的当前值和“toValue”之间进行插值。
 *
  * - “byValue”非nil。 在渲染树中属性的图层当前值和加上“byValue”之间插值。
 */

@property(nullable, strong) id fromValue;
@property(nullable, strong) id toValue;
@property(nullable, strong) id byValue;

@end


/** General keyframe animation class. **/
#park mark - 属性动画

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAKeyframeAnimation : CAPropertyAnimation

/* 一组对象，为每个关键帧提供动画功能的值。
相当于CABasicAnimation中只有的toValue情况,不过这里是一个toValue的集合。 */
@property(nullable, copy) NSArray *values;

/*
 一个可选的路径对象，用于定义动画功能的行为。 当非nil覆盖`values'属性时。
 除了“moveto”点之外，路径中的每个点都定义了一个关键帧，用于定时和插值。
 默认为零。 对于沿路径的恒定速度动画，`calculationMode'应设置为`paced'。 在分配时，路径被复制。*/
@property(nullable) CGPathRef path;

/*
 关键帧动画每帧动画开始执行时间点的数组,取值范围为[0,1]内浮点数,即将 duration属性单位化。
 一般情况下数组中相邻两个值必须遵循后一个值大于或等于前一个值,并且最后的值不能为大于1。未设置时默认每帧动画执行时间均分。  */
@property(nullable, copy) NSArray<NSNumber *> *keyTimes;

/* CAMediaTimingFunction对象的可选数组。
 如果`values'数组定义了n个关键帧，那么`timingFunctions'数组中应该有n-1个对象。 每个函数都描述了一个关键帧到关键帧段的步调。 */
@property(nullable, copy) NSArray<CAMediaTimingFunction *> *timingFunctions;

/*
 “计算模式”。 可能的值是`discrete', `linear', `paced', `cubic' and `cubicPaced' （“离散”，“线性”，“节奏”，“立方”和“立方体”）。
 默认为“linear线性”。 设置为“paced”或“cubicPaced”时，动画的“keyTimes”和“timingFunctions”属性将被忽略并隐式计算。*/
@property(copy) NSString *calculationMode;

/*
 对于具有三次计算模式的动画，这些属性提供对插值方案的控制。 每个关键帧可能具有与之关联的张力，连续性和偏差值，每个都在[-1,1]范围内（这定义了Kochanek-Bartels样条，请参阅http://en.wikipedia.org/wiki/Kochanek-Bartels_spline）。
 
 张力值控制曲线的“紧密度”（正值更紧，负值更圆）。 连续性值控制段的连接方式（正值给出尖角，负值给出倒角）。 偏差值定义曲线发生的位置（正值在控制点之前移动曲线，负值在控制点之后移动它）。
 
 每个数组中的第一个值定义第一个控制点的切线的行为，第二个值控制第二个点的切线，依此类推。 任何未指定的值都默认为零（如果未指定所有值，则给出Catmull-Rom样条曲线）。
 */

@property(nullable, copy) NSArray<NSNumber *> *tensionValues;    // 张力值
@property(nullable, copy) NSArray<NSNumber *> *continuityValues; //连续性值
@property(nullable, copy) NSArray<NSNumber *> *biasValues;       //偏置值

/*
 定义沿路径动画的对象是否旋转以匹配路径切线。 可能的值是`auto'和`autoReverse'。 默认为零。
 未定义未提供路径对象时将此属性设置为非零值的效果。 `autoReverse'旋转以匹配切线加180度。
 
 定义沿着路径y运行体是否自动旋转调整以使自身横截面匹配路径切线,默认为nil。(只有设置了 path才有意义)。
 */
@property(nullable, copy) NSString *rotationMode;

@end

/* `calculationMode' strings. */

CA_EXTERN NSString * const kCAAnimationLinear
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationDiscrete
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationPaced
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationCubic
    CA_AVAILABLE_STARTING (10.7, 4.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationCubicPaced
    CA_AVAILABLE_STARTING (10.7, 4.0, 9.0, 2.0);

/* `rotationMode' strings. */

CA_EXTERN NSString * const kCAAnimationRotateAuto       //自动匹配。
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationRotateAutoReverse //在上一常量的基础上顺时针多旋转180°。
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);


#park mark - 弹性动画
// 弹性动画父类是CABasicAnimation,主要用来设置类似于缓冲、减速动画。

CA_CLASS_AVAILABLE (10.11, 9.0, 9.0, 2.0)
@interface CASpringAnimation : CABasicAnimation

/* 物体的质量附着在弹簧的末端。 必须大于0.默认为1。
 质量-影响图层运动时的弹簧惯性,质量越大,惯性越大,弹簧拉伸和压缩的幅度越大。
 */
@property CGFloat mass;

/* 弹簧刚度系数。 必须大于0.默认为100。
 弹簧刚度系数-刚度系数越大,形变产生的力就越大,弹性运动越快
 */
@property CGFloat stiffness;

/* 阻尼系数。 必须大于或等于0.默认为10。
 阻尼/减幅-阻止弹簧伸缩的系数,阻尼系数越大,停止越快(可以看成阻力~)
 */
@property CGFloat damping;

/* 附着在弹簧上的物体的初始速度。 默认为零，表示一个不动的对象。 负值表示物体远离弹簧附着点，正值表示物体朝向弹簧附着点移动。
 即：速率为正数时,速度方向与运动方向一致,速率为负数时,速度方向会向与运动方向相反的方向先做运动。 */
@property CGFloat initialVelocity;

/* 返回弹簧系统静止时所需的估计持续时间。 评估当前动画参数的持续时间。 */
@property(readonly) CFTimeInterval settlingDuration;

@end

#park mark - 转场动画
// 主要用于从一个场景向另一个场景的动画过渡。

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CATransition : CAAnimation

/*
 过渡的名称类型。 目前的合法转换类型包括`fade'，`moveIn'，`push'和`reveal'。 默认为“fade淡入淡出”。
 
 除了公开的还有一些私有的:"cube"立方体翻转效果、 "suckEffect"收缩效果、 "rippleEffect"水滴波纹效果、 "pageCurl"向上翻页效果、
 "pageUnCurl"向下翻页效果、 "oglFlip"翻转效果、"cameraIrisHollowOpen"摄像头打开效果、"cameraIrisHollowClose"摄像头关闭果。 */
@property(copy) NSString *type;

/*
 转换的可选子类型。 例如。 用于指定基于运动的转换的转换方向，在这种情况下，合法值是“fromLeft”，“fromRight”，“fromTop”和“fromBottom”。 */
@property(nullable, copy) NSString *subtype;

/*
 开始和结束执行的过渡进度。 合法值是[0,1]范围内的浮点数。 `endProgress'必须大于或等于`startProgress'。 默认值分别为0和1。*/
@property float startProgress; //开始进度,默认为0,范围[0 , 1],如果设置0.2,那么动画将从动画的0.2的部分开始。
@property float endProgress;   //结束进度,默认为1,范围[0 , 1],如果设置0.7,那么动画将从动画的0.7的部分开始。

@end

/* Common transition types. */

CA_EXTERN NSString * const kCATransitionFade     //淡进淡出;
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionMoveIn   //新视图移动到旧视图上;
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionPush     //推出新视图
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionReveal   //揭开显示新视图
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Common transition subtypes. */

CA_EXTERN NSString * const kCATransitionFromRight
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionFromLeft
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionFromTop
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionFromBottom
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);


#park mark - 动画组

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAAnimationGroup : CAAnimation

/* 一组CAAnimation对象。 数组的每个成员将使用常规规则在父动画的时空中并发运行。 */
@property(nullable, copy) NSArray<CAAnimation *> *animations;

@end

NS_ASSUME_NONNULL_END
