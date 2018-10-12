/* CoreAnimation - CALayer.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CAMediaTiming.h>
#import <QuartzCore/CATransform3D.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSNull.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>

@class NSEnumerator, CAAnimation, CALayerArray;
@protocol CAAction, CALayerDelegate;

NS_ASSUME_NONNULL_BEGIN

/*
 定义图层的边缘如何被光栅化。 对于四个边（左，右，下，上）中的每一个，如果相应的
 位被设置，边将被反锯齿。 通常，此属性用于禁用对邻接其他图层边缘的边缘进行抗锯齿，
 以消除否则会出现的接缝。 默认值是所有的边缘都是反锯齿的。
 
 通常情况下，您将使用此属性来禁用与其他图层边缘邻接的抗锯齿功能，以消除否则会出现的接缝。
 Layer的edgeAntialiasingMask属性并不能有效抗锯齿，只需要在图片边缘加入1个像素的透明区域就可以完美实现图片抗锯齿。
 */
typedef NS_OPTIONS (unsigned int, CAEdgeAntialiasingMask)
{
  kCALayerLeftEdge      = 1U << 0,      /* Minimum X edge. */
  kCALayerRightEdge     = 1U << 1,      /* Maximum X edge. */
  kCALayerBottomEdge    = 1U << 2,      /* Minimum Y edge. */
  kCALayerTopEdge       = 1U << 3,      /* Maximum Y edge. */
};

/* 切圆角时切指定的角，默认切四个角*/
typedef NS_OPTIONS (NSUInteger, CACornerMask)
{
  kCALayerMinXMinYCorner = 1U << 0,
  kCALayerMaxXMinYCorner = 1U << 1,
  kCALayerMinXMaxYCorner = 1U << 2,
  kCALayerMaxXMaxYCorner = 1U << 3,
};

/** The base layer class. **/

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CALayer : NSObject <NSSecureCoding, CAMediaTiming>
{
@private
  struct _CALayerIvars {
    int32_t refcount;
    uint32_t magic;
    void *layer;
#if TARGET_OS_MAC && !TARGET_RT_64_BIT
    void * _Nonnull unused1[8];
#endif
  } _attr;
}

/** Layer creation and initialization. **/
+ (instancetype)layer;
/* The designated initializer. */
- (instancetype)init;

/*
 CoreAnimation使用此初始化程序创建图层的阴影副本，例如用作presentation表示层。
 子类可以重写此方法以将其实例变量复制到表示层中（子类之后应调用父类）。在任何其他情况下调用此方法将导致未定义的行为。
 */
- (instancetype)initWithLayer:(id)layer;

/*
 返回包含所有属性的图层副本，因为它们在当前事务开始时应用了任何活动动画。这给出了当前显示的图层版本的近似值。如果图层尚未提交，则返回nil。
 试图以任何方式修改返回层的效果未定义。。
 返回图层的`sublayers'，`mask'和`superlayer'属性返回这些属性的表示版本。这贯穿于只读层方法。
 例如，调用-hitTest：对-presentationLayer的结果将查询层树的表示值。
 
 presentationLayer是通过modelLayer提供属性进行绘制的
 展示层 用于显示动画
 */
- (nullable instancetype)presentationLayer;

/*
 调用-presentationLayer方法的结果时，返回具有当前模型值的基础图层。 在非表示层上调用时，返回接收方。
 在生成表示层的事务完成之后调用此方法的结果是未定义的。
 
 模型层 设置的layer属性就是在这个层
*/
- (instancetype)modelLayer;

/**
 CALayer为所有类及其子类定义的Objective C属性实现了标准的NSKeyValueCoding协议。
 它动态地为子类声明的属性实现缺少的访问器方法。
 
 当通过KVC访问不是对象的属性时，使用标准的KVC包装约定，扩展名为支持以下几种类型：
 C Type                  Class
 ------                  -----
 CGPoint                 NSValue
 CGSize                  NSValue
 CGRect                  NSValue
 CGAffineTransform       NSValue
 CATransform3D           NSValue
 
 返回指定属性的默认值，如果没有默认值，则返回nil。 重写此方法以定义其属性的默认值
 的子类应该为未知属性调用“super”
 */
+ (nullable id)defaultValueForKey:(NSString *)key;

/*
 子类重写的方法。 对给定的属性，当属性发生更改（包括由附加到图层的动画更改）时，
 将导致图层的内容重绘，这时返回true。默认实现返回NO。 子类应该为超类定义的属性
 调用super。 （例如，对于CALayer实现的属性不要试图返回YES是由，这样做会有未知的结果。）
 
 layer首次加载时会调用 +(BOOL)needsDisplayForKey:(NSString *)key方法来判断当前指定的属性key改变是否需要重新绘制。
 当Core Animartion中的key或者keypath等于+(BOOL)needsDisplayForKey:(NSString *)key方法中指定的key，便会自动调用setNeedsDisplay方法，这样就会触发重绘，达到我们想要的效果。
 
 layer方法响应链：
 [layer setNeedDisplay] -> [layer displayIfNeed] -> [layer display] -> [layerDelegate displayLayer:]
 
 如果layerDelegate实现了displayLayer:协议，layer就不会再调用自身的重绘代码
 [layer setNeedDisplay] -> [layer displayIfNeed] -> [layer display] -> [layer drawInContext:] -> [layerDelegate drawLayer: inContext:]
 
 只会在图层初始化的时候被调用一次。
 代码中通过判断图层的属性名称来决定是否需要对对应的Core Animation动画执行UI重绘工作(本例中就是对自定义的progress属性进行处理)。
 因为在needsDisplayForKey方法中指定了key的值是progress，所以这里的animationWithKeyPath动画操作会在动画执行期间，不停的促发Core Graphics的重绘工作，即不停的调用 - (void)drawInContext:(CGContextRef)ctx方法进行绘制。
 fillMode 和 removeOnCompletion 两个属性指定动画在绘制完成后，对应的动画对象不会从内存中移除掉。
 */
+ (BOOL)needsDisplayForKey:(NSString *)key;

/*
 由对象的-encodeWithCoder：的实现调用，如果命名属性不应归档，则返回false。
 可以归档返回YES。 对于未知属性子类应该调用父类方法。
 */
- (BOOL)shouldArchiveValueForKey:(NSString *)key;

#park mark - 几何图层层次结构属性
/*
 图层的坐标大小。 默认为CGRectZero。支持动画
 */
@property CGRect bounds;

/*
 设置CALayer在父层中的位置,在父图层中的位置(图层边界矩形的锚点是对齐的。)，默认为零点。支持动画。
 
 position是layer中的anchorPoint点在superLayer中的位置坐标。
 因此可以说, position点是相对suerLayer的，anchorPoint点是相对layer。
 
 1、position是layer中的anchorPoint在superLayer中的位置坐标。
 2、互不影响原则：单独修改position与anchorPoint中任何一个属性都不影响另一个属性。
 3、frame、position与anchorPoint有以下关系：
 frame.origin.x = position.x - anchorPoint.x * bounds.size.width；
 frame.origin.y = position.y - anchorPoint.y * bounds.size.height；
 */
@property CGPoint position;

/*
 图层在父图层中的位置的Z分量。 默认为nil。支持动画。
 */
@property CGFloat zPosition;

/*
 定义图层边界rect的锚点，作为标准化图层坐标中的一个点 - '（0,0）'是边界rect的左下角(iOS左上角、OS X左下角)，'（1,1）'是右上角。
 默认为'（0.5,0.5）'，即边界rect的中心。支持动画。
 
 左上角(0,0)、右下角(1, 1)、左下角(0,1)、右上角(1,0)
 修改anchorPoint，但又不想要移动layer也就是不想修改frame.origin，那么根据前面的公式，就需要position做相应地修改。
 简单地推导，可以得到下面的公式：
 positionNew.x = positionOld.x + (anchorPointNew.x - anchorPointOld.x)  * bounds.size.width
 positionNew.y = positionOld.y + (anchorPointNew.y - anchorPointOld.y)  * bounds.size.height
 也可以在修改anchorPoint后再重新设置一遍frame就可以达到目的，这时position就会自动进行相应的改变。
 view.layer.anchorPoint = newAnchorpoint;
 view.frame = oldFrame;
 */
@property CGPoint anchorPoint;

/*
 图层锚点的Z分量（即位置和变换的参考点）。 默认为零。支持动画。
 */
@property CGFloat anchorPointZ;

/*
 矩阵 仿射变换: 相对于其边界rect的锚点(anchorPoint)应用于图层的变换。 默认为CATransform3DIdentity。支持动画。
 */
@property CATransform3D transform;

/*
 便捷方法获取和设置仿射变换值
 */
- (CGAffineTransform)affineTransform;
- (void)setAffineTransform:(CGAffineTransform)m;

/*
 与NSView不同，层次结构中的每个层都有一个隐式frame矩形，即“position”，“bounds”，“anchorPoint”和“transform”属性的函数。
 设置frame时，“position”和“bounds.size”会改变以匹配给定的frame。
*/
@property CGRect frame;

/*
 如果为true，则不显示图层及其子图层。 默认为NO。动画。
 */
@property(getter=isHidden) BOOL hidden;

/* 
 控制图层的背面是否要被绘制,支持动画。
 默认为YES，如果设置为NO，那么当图层正面从相机视角消失的时候，它将不会被绘制。
 */
@property(getter=isDoubleSided) BOOL doubleSided;

/*
 默认为NO，设置为YES所有子图层相对于左上角的位置改为相对于左下角位置

 层（及其子层）的几何是否垂直翻转。 默认为NO。 请注意，即使在翻转几何图形时，
 图像方向仍保持不变（即，假设在图层上没有变换，则存储在“contents”属性中的CGImageRef
 将在flipped=NO and flipped=YES时显示相同）。
 
 如果设置为yes，则子图层或者子视图本来相对于左上角放置改为相对于左下角放置。
 也可以这么理解geometryFlipped决定了一个图层的坐标是否相对于父图层垂直翻转，默认情况下是NO，也就是从左上角开始绘制；
 当把值改为YES的时候这个图层和他的子图层将会被垂直翻转，也就是从左下角开始绘制。
 
 该属性可以改变默认图层y坐标的方向。当翻转变换被调用时，使用该属性来调整图层的方向有的时候是必需的。
 如果父视图使用了翻转变换，它的子视图内容（以及它对应的图层）将经常被颠倒。在这种情况下，设置子图层的geometryFlipped属性为YES是一种修正该问题最简单的方法，但是一般不推荐使用geometryFlipped属性。
 */
@property(getter=isGeometryFlipped) BOOL geometryFlipped;

/*
 获取当前layer内容在Y轴方向是否被翻转了

 如果图层的content属性的内容在相对于局部坐标空间渲染时将被隐式地翻转（例如，如果从接收者直到并包括根层的隐式容器，有一个奇数层的flippedGeometry = YES），那就返回YES。
 子类不应该尝试重新定义这个方法。
 当这个方法返回YES时，通过默认的-display方法传递给-drawInContext的CGContextRef对象将会被y翻转（传递给-setNeedsDisplayInRect的矩形将被类似地翻转）。
 
 渲染时，图层的content被隐式的翻转就返回YES，否则返回NO。这个方法默认是返回NO的。这个方法提供了关于在绘制过程中图层内容是否被翻转的信息，你不应该尝试重写给方法返回一个不同的值，如果layer需要翻转它的content，那么就返回YES，那么在传递给图层drawInContext:方法之前，就对当前上下文实施y方向上的翻转，类似的，该图层将传递给其 setNeedsDisplayInRect:的所有矩形转换为翻转的坐标空间。
 */
- (BOOL)contentsAreFlipped;

/*
 接收者的父类对象。 隐式更改以匹配'sublayers'属性所描述的层次结构。
 */
@property(nullable, readonly) CALayer *superlayer;

/*
 从父图层中移除图层，如果接收器位于其父图层的“子图层”数组中或设置为其“mask”值，则两者都可以“移除”。
*/
- (void)removeFromSuperlayer;

/*
 该图层的子图层数组。 这些图层按照前后顺序列出。 默认为nil。
 设置属性的值时，任何新添加的层必须没有父图层，否则行为未定义。 请注意，不保证返回的数组保留其元素。
 */
@property(nullable, copy) NSArray<CALayer *> *sublayers;

/*
 将“图层”添加到接收器的子图层数组的末尾。 如果'layer'已经有一个父图层，它将在添加之前被删除。
*/
- (void)addSublayer:(CALayer *)layer;

/*
 在接收器(self)的子图层数组中的“idx”位置插入“图层”。 如果'layer'已经有一个父图层，它将在插入之前被删除。
 */
- (void)insertSublayer:(CALayer *)layer atIndex:(unsigned)idx;

/*
 在接收器(self)的子图层数组中的指定图层的上方或下方插入“图层”。 如果'layer'已经有一个超级层，它将在插入之前被删除。
 */
- (void)insertSublayer:(CALayer *)layer below:(nullable CALayer *)sibling; //指定某个图层下面
- (void)insertSublayer:(CALayer *)layer above:(nullable CALayer *)sibling; //指定某个图层上面

/*
 从接收器(self)的子层数组中删除“layer”，如果其位置非nil，则插入“layer2”。 如果'layer'的父层不是接收者(即layer的父图层不是self)，则行为未定义。
 */
- (void)replaceSublayer:(CALayer *)layer with:(CALayer *)layer2;

/*
 子layer进行3D变换
 应用于“子层”数组的每个成员的转换，同时将其内容呈现到接收器(self)的输出中。 通常用作投影矩阵，以将透视和其他观看效果添加到模型中。
 默认为CATransform3DIdentity。支持动画。
 */
@property CATransform3D sublayerTransform;

/*
 图层蒙版layer
 
 将其alpha通道用作蒙版的图层，以在图层的背景和将图层内容与其过滤背景进行合成的结果之间进行选择。 默认为nil。
 当用作蒙板时，图层的“compositingFilter”和“backgroundFilters”属性将被忽略。 将遮罩设置为新图层时，新图层必须有一个nil的图层，
 否则行为未定义。 不支持嵌套蒙版（带有自己蒙版的蒙版图层）。
 
 这个属性的默认值是nil。 配置mask时，请记得设置遮罩层的大小和位置，以确保遮罩层与它遮罩的层正确对齐。
 您分配给此属性的图层不能有父图层。否则行为是不确定的。
 遮罩层必须至少有两个图层，上面的一个图层为“遮罩层”，下面的称“被遮罩层”；这两个图层中只有相重叠的地方才会被显示。也就是说在遮罩层中有对象的地方就是“透明”的，可以看到被遮罩层中的对象，而没有对象的地方就是不透明的，被遮罩层中相应位置的对象是看不见的。
 */
@property(nullable, strong) CALayer *mask;

/*
 当设置YES，将匹配层边界的隐式掩码应用于层(包括“角半径”属性的影响)。
 如果“mask”和“masksToBounds”都是非空的，则将两个mask相乘以得到实际的mask值。
 默认NO。支持动画(iOS11开始才有动画)
 */
@property BOOL masksToBounds;

#park mark - 层坐标和时间空间之间的映射.

- (CGPoint)convertPoint:(CGPoint)p fromLayer:(nullable CALayer *)l;
- (CGPoint)convertPoint:(CGPoint)p toLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r fromLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r toLayer:(nullable CALayer *)l;

//转换CAMediaTiming协议的相对时间
- (CFTimeInterval)convertTime:(CFTimeInterval)t fromLayer:(nullable CALayer *)l;
- (CFTimeInterval)convertTime:(CFTimeInterval)t toLayer:(nullable CALayer *)l;

#park mark - 命中测试方法。
/*
 返回包含某一点的最上层的子layer
 返回包含点'p'的图层的最远后代。 兄弟姐妹按从上到下的顺序进行搜索。 'p'定义在接收器(self)最近的父图层的坐标空间中，该坐标空间不是CATransformLayer（变换图层没有可以指定点的2D坐标空间）。
 */
- (nullable CALayer *)hitTest:(CGPoint)p;

/*
 判断layer是否包含某一点p
*/
- (BOOL)containsPoint:(CGPoint)p;

#park mark - 图层内容属性和方法。
/*
 提供图层内容的对象，通常是CGImageRef，但也可能是其他内容。 （例如，Mac OS X 10.6及更高版本支持NSImage对象。）默认值为nil。支持动画。
 */
@property(nullable, strong) id contents;

/*
 标准化的图像坐标中的矩形定义了将被绘制到图层中的“contents”属性的子矩形。
 如果需要单位矩形外的像素，则内容图像的边缘像素将向外扩展。 如果提供了一个空的矩形，结果是不确定的。
 contentRect是一个比例值[0-1]，而不是屏幕上真实的像素点，默认为单位矩形[0 0 1 1]。支持动画
 */
@property CGRect contentsRect;

/*
 一个字符串定义了layer的contents是如何映射到它的边界矩形内部的，选项有`center', `top',
 `bottom', `left', `right', `topLeft', `topRight', `bottomLeft', `bottomRight',
 `resize', `resizeAspect', `resizeAspectFill'，默认值是`resize'，
 注意"bottom"意思是"Minimum Y"，"top"的意思是"Maximum Y"。
 
 和cotentMode一样，contentsGravity的目的是为了决定内容在图层的边界中怎么对齐，
 */
@property(copy) NSString *contentsGravity;

/*
 定义应用于图层内容的比例因子。 如果内容的物理尺寸是“（w，h）”，那么逻辑尺寸（即用于contentGravity计算）被定义为'（w / contentsScale，h / contentsScale）'。 适用于显式提供的图像和通过-drawInContext提供的内容（即如果contentsScale是2，-drawInContext：将绘制到缓冲区大小为layer bounds的2倍）， 默认为1，可动画。
 
该值定义了图层的逻辑坐标空间（以点为单位）和物理坐标空间（以像素为单位）之间的映射。 较高的比例因子表示在渲染时间层中的每个点由多于一个像素表示。 例如，如果比例因子为2.0，图层边界为50 x 50点，则用于呈现图层内容的位图大小为100 x 100像素。
 */
@property CGFloat contentsScale
  CA_AVAILABLE_STARTING (10.7, 4.0, 9.0, 2.0);

/*
 标准化图像坐标中的矩形定义“contents”图像的缩放中心部分。 当由于其“contentsGravity”属性而调整图像大小时
 中心部分隐含地定义了3x3网格，其控制如何将图像缩放到其绘制的大小。 中间部分在两个方向都被拉伸; 顶部和底部只有水平伸展; 左右部分只是垂直拉伸; 四个角落部分根本不被拉伸。 （这通常被称为“9-slice scaling”）。
 在应用“contentsRect”属性的效果之后，该矩形被解释。 它默认为单位矩形[0 0 1 1]，意味着整个图像被缩放。 作为特殊情况，如果宽度或高度为零，则隐式地调整为以该位置为中心的单个源像素的宽度或高度。 如果矩形延伸到[0 0 1 1]单位矩形之外，则结果是不确定的，支持动画。
 */
@property CGRect contentsCenter;

/*
 -drawLayerInContext提供的图层内容的所需存储格式的提示
 默认值是kCAContentsFormatRGBA8Uint。
 UIView和图层支持的NSView对象可能会将值更改为适合当前设备的格式。
 */
@property(copy) NSString *contentsFormat
  CA_AVAILABLE_STARTING (10.12, 10.0, 10.0, 3.0);

/*
 渲染图层的“contents”属性时使用的过滤器类型。 minification过滤器用于缩小图像数据的大小时，magnification过滤器增加图像数据的大小。
 目前允许的值是`nearest' 和 `linear'的。 这两个属性默认为`linear'。
 */
@property(copy) NSString *minificationFilter;
@property(copy) NSString *magnificationFilter;

/*
 在确定使用三线性滤波进行缩放时要使用哪些细节级别时添加的偏移因子。 默认值是0，支持动画。
*/
@property float minificationFilterBias;

/*
 提示标记-drawInContext：提供的图层内容是完全不透明的。 默认为NO。 请注意，这不会直接影响`contents'属性的解释。
 */
@property(getter=isOpaque) BOOL opaque;

/*
 重新加载此图层的内容。 调用-drawInContext：方法、然后更新图层的`contents'属性。 通常，这不是直接调用的。
 */
- (void)display;

/*
 标记在下次提交图层之前需要调用-display更新图层。 如果指定了区域，则只有该区域的区域无效。
 */
- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)r;

/*
 当图层标记为需要重绘时，返回true。
 */
- (BOOL)needsDisplay;

/*
 如果接收器(self)被标记为需要重绘，则调用-display。
 */
- (void)displayIfNeeded;

/*
   当YES时，方法-setNeedsDisplay将在图层的边界改变时自动被调用。
   当其值为YES时，bounds发生改变就重绘，NO就不重绘，默认值为NO。
 */
@property BOOL needsDisplayOnBoundsChange;

/*
 如果为YES，则传递给-drawInContext：方法的CGContext对象可以对提交给它的绘图命令进行排队，以便稍后执行（即与执行-drawInContext：方法异步）。 这可能会使图层比同步执行时更快地完成绘图操作。 默认值是NO
 1.当此属性设置为YES时，用于绘制图层内容的图形上下文将绘制命令排队，并在后台线程上执行它们，而不是同步执行它们。 异步执行这些命令可以提高某些应用程序的性能。 但是，在启用此功能之前，您应始终测量实际的性能优势。
 2.该属性适用于图层内容需要反复重绘的情况，此时设成true可能会改善性能，比如需要反复绘制大量粒子的粒子发射器图层CAEmitterLayer。
 3.对于CATiledLayer。除了将图层再次分割成独立更新的小块（类似于脏矩形自动更新的概念），CATiledLayer还有一个有趣的特性：在多个线程中为每个小块同时调用-drawLayer:inContext:方法。这就避免了阻塞用户交互而且能够利用多核心新片来更快地绘制。只有一个小块的CATiledLayer是实现异步更新图片视图的简单方法。
 4.它与CATiledLayer使用的异步绘制并不相同。drawsAsynchronously的-drawLayer:inContext:方法只会在主线程调用，但是CGContext并不等待每个绘制命令的结束。相反地，它会将命令加入队列，当方法返回时，在后台线程逐个执行真正的绘制。
 5.这种方式就是先记录绘制命令，然后在后台线程执行。为了实现这个过程，更多的事情不得不做，更多的内存开销。最后只是把一些工作从主线程移动出来。这个过程是需要权衡，测试的。
 */
@property BOOL drawsAsynchronously
  CA_AVAILABLE_STARTING (10.8, 6.0, 9.0, 2.0);

/*
 当正在更新contents属性时，通过-display方法调用。 默认实现什么都不做。 可以剪辑
 上下文以保护有效的图层内容。 希望找到要绘制的实际区域的子类
 可以调用CGContextGetClipBoundingBox（）
 */
- (void)drawInContext:(CGContextRef)ctx;

/**
 将接收器及其子层渲染到“ctx”。 该方法直接从图层树中呈现。 渲染在图层的坐标空间。
 警告：目前这个方法没有实现完整的CoreAnimation composition模型，谨慎使用。
 
 该方法可以用于截屏，但是要注意，尝试去截取WKWebView的图。截图的结果返回的就仅仅只是一张背景图, 显然截图失败。如果直接调用layer.renderInContext需要获取对应的Context, 但是在WKWebView中执行UIGraphicsGetCurrentContext()的返回结果是nil ，一种解决思路是使用UIView的drawViewHierarchyInRect方法去截取屏幕视图。通过直接调用WKWebView的drawViewHierarchyInRect方法(afterScreenUpdates参数必须为true), 可以成功的截取WKWebView的屏幕内容。
 
 30         //获取图形上下文
 31         UIGraphicsBeginImageContext(self.contentView.frame.size);
 32         //将view绘制到图形上下文中
 33         [self.contentView.layer renderInContext:UIGraphicsGetCurrentContext()];
 34         //将截屏保存到相册
 35         UIImage *newImage=UIGraphicsGetImageFromCurrentImageContext();
 
 */
- (void)renderInContext:(CGContextRef)ctx;

/*
 定义图层的边缘如何被光栅化。 对于四个边（左，右，下，上）中的每一个，如果相应的
 位被设置，边将被反锯齿。 通常，此属性用于禁用对邻接其他图层边缘的边缘进行抗锯齿，
 以消除否则会出现的接缝。 默认值是所有的边缘都是反锯齿的。
 */
@property CAEdgeAntialiasingMask edgeAntialiasingMask;

/*
 指示是否允许图层执行边缘抗锯齿。
 在使用view的缩放的时候，layer.border.width随着view的放大，会出现锯齿化的问题，解决这个问题可以设置这个属性。
 如果为true，则允许此层根据edgeAntialiasingMask属性的值的请求对其边缘进行抗锯齿处理。
 默认值从主包的Info.plist中的布尔UIViewEdgeAntialiasing属性中读取。 如果Info.plist中未找到任何值，则默认值为NO。
 */
@property BOOL allowsEdgeAntialiasing;

/*
 图层的背景颜色。 默认值为nil。 支持从平铺图案创建的颜色。支持动画。
 */
@property(nullable) CGColorRef backgroundColor;

/*
 当为正数时，图层的背景用圆角绘制。还会影响“masksToBounds”属性生成的掩码。默认值为零。
 支持动画。(在iOS11.0之前圆角是不支持动画的)
 */
@property CGFloat cornerRadius;

/*
 使用cornerRadius圆角属性时，定义四个角中的哪一个接收遮罩。 默认为所有四个角(iOS11+)。
 例如只切两个圆角:kCALayerMinXMinYCorner | kCALayerMaxXMinYCorner;
*/
@property CACornerMask maskedCorners
  CA_AVAILABLE_STARTING (10.13, 11.0, 11.0, 4.0);

/*
 图层边框的宽度，从层边界插入。边界被合成在层内容和子层之上，并包含“角半径”属性的效果。默认值为零。支持动画。
 */
@property CGFloat borderWidth;

/*
 图层边框的颜色。默认为不透明黑色。支持由瓷砖图案创建的颜色。支持动画。
 */
@property(nullable) CGColorRef borderColor;

/*
 图层的不透明度，在0和1之间的值。默认为1。在[0,1]范围之外指定一个值将给出未定义的结果。支持动画。
 */
@property float opacity;

/*
 如果为true，并且图层的opacity属性小于1，则允许该图层将其自身组合为与其父图像分开的组。 当图层包含多个不透明组件时，这会给出正确的结果，但可能会降低性能。
 从主包的Info.plist中的布尔UIViewGroupOpacity属性中读取属性的默认值。
 如果Info.plist中未找到任何值，则对于针对iOS 7 SDK或更高版本链接的应用程序，默认值为YES; 对于与早期SDK链接的应用程序，默认值为NO。
 */
@property BOOL allowsGroupOpacity;

/*
 用于将图层与其（可能已过滤）背景合成的过滤器对象。 默认值为nil，表示源代码合成。支持动画。
 请注意，如果在将过滤器附加到图层后直接修改过滤器的输入，则行为未定义。 必须将过滤器重新附加到图层，或者应通过在附加过滤器的每个图层上调用-setValue：forKeyPath：来修改过滤器属性。 （这也适用于`filters'和`backgroundFilters'属性。）
 */
@property(nullable, strong) id compositingFilter;

/*
 将应用于图层及其子图层内容的过滤器数组。 默认为nil。支持动画。
*/
@property(nullable, copy) NSArray *filters;

/*
 应用于图层背景的滤镜数组。
 根层忽略此属性。支持动画。
*/
@property(nullable, copy) NSArray *backgroundFilters;

/*
 如果为YES，则图层将在其局部坐标空间（“栅格化”）中呈现为位图，然后将位图合成到目标中（如果位图需要缩放，则应用图层的minificationFilter和magnificationFilter属性）。 应用图层的滤镜和阴影效果后，但在不透明度调制之前，会发生光栅化。 作为实现细节，呈现引擎可以尝试从一帧到下一帧缓存和重用位图。 （它是否对渲染输出没有影响。）
   
 如果为NO，则尽可能将图层直接合成到目标中（但是，合成模型的某些特征可能会强制光栅化，例如添加滤镜）。
 *默认为NO。支持动画。
 
 eg:当shouldRasterize设成true时,layer被渲染成一个bitmap,并缓存起来,等下次使用时不会再重新去渲染了。实现圆角本身就是在做颜色混合(blending),如果每次页面出来时都blending,消耗太大,这时shouldRasterize = yes,下次就只是简单的从渲染引擎的cache里读取那张bitmap,节约系统资源。如果在滚动tableView时,每次都执行圆角设置,肯定会阻塞UI,设置这个将会使滑动更加流畅。
*/
@property BOOL shouldRasterize;

/*
 将图层光栅化的比例（当shouldRasterize属性设置为YES时）相对于图层的坐标空间。 默认为1，支持动画
 
 eg:切圆角shouldRasterize > cornerRadius > 要比mask高效很多。
 self.layer.shouldRasterize = YES;
 self.layer.rasterizationScale = [UIScreen mainScreen].scale;
 */
@property CGFloat rasterizationScale;


#park mark - 阴影属性。
/*
 设置阴影不要切超出父视图边距(clipsToBounds=NO)
*/

/*
 阴影颜色。 默认为不透明黑色。 目前不支持从模式创建的颜色。支持动画。
 */
@property(nullable) CGColorRef shadowColor;

/*
 阴影的不透明度。 默认为0. 指定[0,1]范围之外的值将给出未定义的结果。支持动画。
 */
@property float shadowOpacity;

/*
 阴影偏移。 默认为（0，-3），x向右偏移，y向下偏移（00四周偏移）。支持动画。
 */
@property CGSize shadowOffset;

/*
 阴影的模糊半径。 默认为3.支持动画。
 */
@property CGFloat shadowRadius;

/*
 按照指定路径绘制阴影
 当非空时，此路径定义用于构造图层阴影的轮廓，而不是使用图层的合成Alpha通道。 使用非零缠绕规则渲染路径。 使用此属性显式指定路径通常会提高渲染性能，因为跨多个层共享相同的路径引用。 在分配时，路径被复制。
 默认为null。支持动画。
 */
@property(nullable) CGPathRef shadowPath;

#park mark - 布局方法。
/*
 返回父图层的坐标空间中图层的首选帧大小。
 默认实现调用布局管理器（如果存在）并且它实现-preferredSizeOfLayer：方法，否则返回映射到父图层的bounds的大小。
 */
- (CGSize)preferredFrameSize;

/*
 标记在下次更新之前需要在接收器(self)上调用-layoutSublayers。
 如果接收者的布局管理器实现-invalidateLayoutOfLayer：方法，则会调用它。
  
 只要修改了`sublayers'或`layoutManager'属性，就会在图层上自动调用此方法，并且只要修改了`bounds'或`transform'属性，就会在图层及其父图层上调用此方法。 如果图层当前正在执行其-layoutSublayers方法，则会跳过对-setNeedsLayout的隐式调用。
 */
- (void)setNeedsLayout;

/*
 当接收器(self)标记为需要布局时返回true。
 */
- (BOOL)needsLayout;

/*
 当父图层需要布局时，从图层向上遍历。 然后在整个祖先下面布置整个树。
 eg:[view.superview layoutIfNeeded]、父视图将在必要时布局自身及自身的整个子视图树
 */
- (void)layoutIfNeeded;

/*
 当图层需要布局时调用。 默认实现调用布局管理器（如果存在）并实现-layoutSublayersOfLayer：方法。
 子类可以重写它以提供自己的布局算法，该算法应设置每个子层的帧。
 */
- (void)layoutSublayers;



#park mark - Action动作方法
/*
 “动作”是通过CAAction协议响应“事件”的对象（见下文）。事件使用标准的点分隔键路径命名。每个层定义从事件键路径到操作对象的映射。通过查找与密钥路径关联的操作对象并向其发送CAAction协议定义的方法来发布事件。
  *
  *当调用一个动作对象时，它接收三个参数：命名事件的键路径，事件发生的对象（即图层），以及可选的特定于每个事件的命名参数字典。
  *
  *要为图层属性提供隐式动画，只要修改了属性的值，就会发布与每个属性同名的事件。默认情况下，合适的CAAnimation对象与每个隐式事件相关联（CAAnimation实现操作协议）。
  *
  *图层类还定义了以下未直接链接到属性的事件：
  *
  * onOrderIn  (底部定义的静态常量kCAOnOrderIn)
  *当图层可见时调用，即其超级图层变为可见，或者将其添加为可见图层的子图层
  *
  * onOrderOut (底部定义的静态常量kCAOnOrderOut)
  *当图层变得不可见时调用。 * /
 
  返回与字符串'event'命名的事件关联的默认操作对象。默认实现为动画属性发布的事件返回合适的动画对象，否则返回nil。
 */

+ (nullable id<CAAction>)defaultActionForKey:(NSString *)event;

/*
 返回与字符串'event'命名的事件关联的操作对象。 默认实现在以下位置搜索操作对象：
  *
  * 1.如果已定义，则调用委托方法-actionForLayer：forKey：
  * 2.查看图层的`actions'字典
  * 3.查看“样式”层次结构中的任何“动作”词典
  * 4.在图层的类上调用+ defaultActionForKey：
  *
 如果这些步骤中的任何步骤导致非nil操作对象，则忽略以下步骤。 如果最终结果是NSNull的实例，则将其转换为“nil”。
 */
- (nullable id<CAAction>)actionForKey:(NSString *)event;

/*
 将字符映射到实现CAAction协议的对象的字典。 默认值为nil。
 */
@property(nullable, copy) NSDictionary<NSString *, id<CAAction>> *actions;

#park mark - Animation动画方法
/*
 将动画对象附加到图层。 通常，这是通过作为CAAnimation对象的操作隐式调用的。
  *
  *'key'可以是任何字符串，使得每层仅添加每个唯一键一个动画。 特殊键“transition”(静态常量kCATransition)自动用于过渡动画。 nil指针也是有效键。
  *
  *如果动画的“持续时间”属性为零或为负，则给定默认持续时间，即“animationDuration”事务属性的值，否则为0.25秒。
  *
  *动画在被添加到图层之前被复制，因此除非将动画添加到另一个图层，否则对“动画”的任何后续修改都不会产生任何影响。
 */
- (void)addAnimation:(CAAnimation *)anim forKey:(nullable NSString *)key;

/*
 删除附加到图层的所有动画。
 */
- (void)removeAllAnimations;

/*
 删除“key”值对应的附加到图层的任何动画。
 */
- (void)removeAnimationForKey:(NSString *)key;

/*
 返回一个数组，其中包含当前连接到接收器(self)的所有动画的键。 数组的顺序与动画的应用顺序相匹配。
 */
- (nullable NSArray<NSString *> *)animationKeys;

/*
 返回添加到具有标识符“key”或nil的图层的动画
 如果不存在此类动画。 尝试修改返回对象(CAAnimation)的任何属性将导致未定义的行为。
 */
- (nullable CAAnimation *)animationForKey:(NSString *)key;

#park mark - 杂项属性
/* 图层的名称。 由一些布局管理器使用。 默认为零。*/
@property(nullable, copy) NSString *name;

/*
 将接收下面定义的CALayerDelegate代理方法的对象(对于它实现的方法)。此属性的值不保留。默认值为nil。
 */
@property(nullable, weak) id <CALayerDelegate> delegate;

/*
 当非nil时，取消引用字典以查找未由层明确定义的属性值。（这个字典可能反过来有一个'style'属性，形成一个默认值的层次结构。）
 如果样式字典未定义属性的值，则调用+ defaultValueForKey：方法。 默认为零。

 请注意，如果修改了字典或其任何祖先，则在重置“style”属性之前，不会定义图层属性的值。
 */
@property(nullable, copy) NSDictionary *style;

@end

/** 动作（事件处理程序）协议。 **/
@protocol CAAction

/*
 被调用以在接收器(self)上触发名为“path”的事件。
 事件发生的对象（例如图层）是“anObject”。 参数字典可以是nil，如果是非nil，它携带与事件相关的参数。
 */
- (void)runActionForKey:(NSString *)event object:(id)anObject
    arguments:(nullable NSDictionary *)dict;

@end

/** NSNull协议一致性 **/

@interface NSNull (CAActionAdditions) <CAAction>

@end

#park mark - CALayerDelegate代理方法

@protocol CALayerDelegate <NSObject>
@optional

/*
 如果已定义该协议方法，则由-display方法的默认实现调用，在这种情况下，它应该实现整个显示过程（通常通过设置`contents'属性）。
 */
- (void)displayLayer:(CALayer *)layer;

/*
 如果已定义，则由-drawInContext的默认实现调用：
 */
- (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx;

/*
 如果已定义，则由-display方法的默认实现调用。允许委托在-drawLayer:InContext:之前配置影响内容的任何层状态，比如' contentsFormat'和' '。如果委托实现-displayLayer就不会调用它。
 */
- (void)layerWillDraw:(CALayer *)layer
  CA_AVAILABLE_STARTING (10.12, 10.0, 10.0, 3.0);

/*
 在检查布局管理器之前，由默认的-layoutSublayers实现调用。注意，如果调用委托方法，布局管理器将被忽略。
 */
- (void)layoutSublayersOfLayer:(CALayer *)layer;

/*
 如果已定义，则由-actionForKey：方法的默认实现调用。 应返回实现CAAction协议的对象。 如果委托没有为当前事件指定行为，则可以返回'nil'。
 返回空对象（即'[NSNull null]'）明确强制不再进行搜索。 （即，不会调用+ defaultActionForKey：方法。）
 */
- (nullable id<CAAction>)actionForLayer:(CALayer *)layer forKey:(NSString *)event;

@end

/** contentsGravity可以取下面的值 **/

CA_EXTERN NSString * const kCAGravityCenter
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityTop
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityBottom
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityLeft
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityRight
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityTopLeft
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityTopRight
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityBottomLeft
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityBottomRight
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityResize
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAGravityResizeAspect
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);//kCAGravityResizeAspect的效果等同于cotentMode的UIViewContentModeScaleAspectFit，同时它还能在图层中等比例拉伸以适应图层的边界
CA_EXTERN NSString * const kCAGravityResizeAspectFill
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/** Layer `contentsFormat` values. **/

CA_EXTERN NSString * const kCAContentsFormatRGBA8Uint /* RGBA UInt8 per component */
  CA_AVAILABLE_STARTING (10.12, 10.0, 10.0, 3.0);
CA_EXTERN NSString * const kCAContentsFormatRGBA16Float /* RGBA half-float 16-bit per component */
  CA_AVAILABLE_STARTING (10.12, 10.0, 10.0, 3.0);
CA_EXTERN NSString * const kCAContentsFormatGray8Uint /* Grayscale with alpha (if not opaque) UInt8 per component */
  CA_AVAILABLE_STARTING (10.12, 10.0, 10.0, 3.0);

/** Contents filter names. **/
//最近过滤-就是取样最近的单像素点而不管其他的颜色。这样做非常快，也不会使图片模糊。
//但是，最明显的效果就是，会使得压缩图片更糟，图片放大之后也显得块状或是马赛克严重。
CA_EXTERN NSString * const kCAFilterNearest
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
//采用双线性滤波算法，放大倍数比较大的时候图片就模糊不清了。
CA_EXTERN NSString * const kCAFilterLinear
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Trilinear minification filter. Enables mipmap generation. Some
 * renderers may ignore this, or impose additional restrictions, such
 * as source images requiring power-of-two dimensions.
 三线缩小滤波器。 启用mipmap生成。 某些渲染器可能会忽略这一点，或施加其他限制，例如需要二维功率的源图像。
 
 三线性滤波算法存储了多个大小情况下的图片（也叫多重贴图），并三维取样，同时结合大图和小图的存储进而得到最后的结果。
 */
CA_EXTERN NSString * const kCAFilterTrilinear
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/** Layer event names. **/

CA_EXTERN NSString * const kCAOnOrderIn
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAOnOrderOut
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/** The animation key used for transitions. **/

CA_EXTERN NSString * const kCATransition
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
