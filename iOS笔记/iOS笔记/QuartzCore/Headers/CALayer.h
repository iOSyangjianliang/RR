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

/* Bit definitions for `edgeAntialiasingMask' property.
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

/* Bit definitions for `maskedCorners' property.
 切圆角时切指定的角，默认切四个角
 */
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
 呈现层 用于显示动画
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

/** Geometry and layer hierarchy properties. **/

/* The bounds of the layer. Defaults to CGRectZero. Animatable. */

@property CGRect bounds;

/* The position in the superlayer that the anchor point of the layer's
 * bounds rect is aligned to. Defaults to the zero point. Animatable. */

@property CGPoint position;

/* The Z component of the layer's position in its superlayer. Defaults
 * to zero. Animatable. */

@property CGFloat zPosition;

/* Defines the anchor point of the layer's bounds rect, as a point in
 * normalized layer coordinates - '(0, 0)' is the bottom left corner of
 * the bounds rect, '(1, 1)' is the top right corner. Defaults to
 * '(0.5, 0.5)', i.e. the center of the bounds rect. Animatable. */

@property CGPoint anchorPoint;

/* The Z component of the layer's anchor point (i.e. reference point for
 * position and transform). Defaults to zero. Animatable. */

@property CGFloat anchorPointZ;

/* A transform applied to the layer relative to the anchor point of its
 * bounds rect. Defaults to the identity transform. Animatable. */

@property CATransform3D transform;

/* Convenience methods for accessing the `transform' property as an
 * affine transform. */

- (CGAffineTransform)affineTransform;
- (void)setAffineTransform:(CGAffineTransform)m;

/* Unlike NSView, each Layer in the hierarchy has an implicit frame
 * rectangle, a function of the `position', `bounds', `anchorPoint',
 * and `transform' properties. When setting the frame the `position'
 * and `bounds.size' are changed to match the given frame. */

@property CGRect frame;

/* When true the layer and its sublayers are not displayed. Defaults to
 * NO. Animatable. */

@property(getter=isHidden) BOOL hidden;

/* When false layers facing away from the viewer are hidden from view.
 * Defaults to YES. Animatable.
 控制图层的背面是否要被绘制,支持动画。
 默认为YES，如果设置为NO，那么当图层正面从相机视角消失的时候，它将不会被绘制。
 */

@property(getter=isDoubleSided) BOOL doubleSided;

/*
 层（及其子层）的几何是否垂直翻转。 默认为NO。 请注意，即使在翻转几何图形时，
 图像方向仍保持不变（即，假设在图层上没有变换，则存储在“contents”属性中的CGImageRef
 将在flipped=NO and flipped=YES时显示相同）。
 
 如果设置为yes，则子图层或者子视图本来相对于左上角放置改为相对于左下角放置。也可以这么理解geometryFlipped决定了一个图层的坐标是否相对于父图层垂直翻转，默认情况下是NO，也就是从左上角开始绘制，当把值改为YES的时候这个图层和他的子图层将会被垂直翻转，也就是从左下角开始绘制。
 
 该属性可以改变默认图层y坐标的方向。当翻转变换被调用时，使用该属性来调整图层的方向有的时候是必需的。如果父视图使用了翻转变换，它的子视图内容（以及它对应的图层）将经常被颠倒。在这种情况下，设置子图层的geometryFlipped属性为YES是一种修正该问题最简单的方法，但是一般不推荐使用geometryFlipped属性。
 */
@property(getter=isGeometryFlipped) BOOL geometryFlipped;

/*
 如果图层的content属性的内容在相对于局部坐标空间渲染时将被隐式地翻转（例如，如果从接收者直到并包括根层的隐式容器，有一个奇数层的flippedGeometry = YES），那就返回YES。
 子类不应该尝试重新定义这个方法。
 当这个方法返回YES时，通过默认的-display方法传递给-drawInContext的CGContextRef对象将会被y翻转（传递给-setNeedsDisplayInRect的矩形将被类似地翻转）。
 
 渲染时，图层的content被隐式的翻转就返回YES，否则返回NO。这个方法默认是返回NO的。这个方法提供了关于在绘制过程中图层内容是否被翻转的信息，你不应该尝试重写给方法返回一个不同的值，如果layer需要翻转它的content，那么就返回YES，那么在传递给图层drawInContext:方法之前，就对当前上下文实施y方向上的翻转，类似的，该图层将传递给其 setNeedsDisplayInRect:的所有矩形转换为翻转的坐标空间。
 */
- (BOOL)contentsAreFlipped;

/* The receiver's superlayer object. Implicitly changed to match the
 * hierarchy described by the `sublayers' properties. */

@property(nullable, readonly) CALayer *superlayer;

/* Removes the layer from its superlayer, works both if the receiver is
 * in its superlayer's `sublayers' array or set as its `mask' value. */

- (void)removeFromSuperlayer;

/* The array of sublayers of this layer. The layers are listed in back
 * to front order. Defaults to nil. When setting the value of the
 * property, any newly added layers must have nil superlayers, otherwise
 * the behavior is undefined. Note that the returned array is not
 * guaranteed to retain its elements. */

@property(nullable, copy) NSArray<CALayer *> *sublayers;

/* Add 'layer' to the end of the receiver's sublayers array. If 'layer'
 * already has a superlayer, it will be removed before being added. */

- (void)addSublayer:(CALayer *)layer;

/* Insert 'layer' at position 'idx' in the receiver's sublayers array.
 * If 'layer' already has a superlayer, it will be removed before being
 * inserted. */

- (void)insertSublayer:(CALayer *)layer atIndex:(unsigned)idx;

/* Insert 'layer' either above or below the specified layer in the
 * receiver's sublayers array. If 'layer' already has a superlayer, it
 * will be removed before being inserted. */

- (void)insertSublayer:(CALayer *)layer below:(nullable CALayer *)sibling;
- (void)insertSublayer:(CALayer *)layer above:(nullable CALayer *)sibling;

/* Remove 'layer' from the sublayers array of the receiver and insert
 * 'layer2' if non-nil in its position. If the superlayer of 'layer'
 * is not the receiver, the behavior is undefined. */

- (void)replaceSublayer:(CALayer *)layer with:(CALayer *)layer2;

/* A transform applied to each member of the `sublayers' array while
 * rendering its contents into the receiver's output. Typically used as
 * the projection matrix to add perspective and other viewing effects
 * into the model. Defaults to identity. Animatable. */

@property CATransform3D sublayerTransform;

/* A layer whose alpha channel is used as a mask to select between the
 * layer's background and the result of compositing the layer's
 * contents with its filtered background. Defaults to nil. When used as
 * a mask the layer's `compositingFilter' and `backgroundFilters'
 * properties are ignored. When setting the mask to a new layer, the
 * new layer must have a nil superlayer, otherwise the behavior is
 * undefined. Nested masks (mask layers with their own masks) are
 * unsupported.

 将其alpha通道用作蒙版的图层，以在图层的背景和将图层内容与其过滤背景进行合成的结果之间进行选择。 默认为nil。
 当用作蒙板时，图层的“compositingFilter”和“backgroundFilters”属性将被忽略。 将遮罩设置为新图层时，新图层必须有一个nil的图层，
 否则行为未定义。 不支持嵌套蒙版（带有自己蒙版的蒙版图层）。
 
 这个属性的默认值是nil。 配置mask时，请记得设置遮罩层的大小和位置，以确保遮罩层与它遮罩的层正确对齐。
 您分配给此属性的图层不能有父图层。否则行为是不确定的。
 遮罩层必须至少有两个图层，上面的一个图层为“遮罩层”，下面的称“被遮罩层”；这两个图层中只有相重叠的地方才会被显示。也就是说在遮罩层中有对象的地方就是“透明”的，可以看到被遮罩层中的对象，而没有对象的地方就是不透明的，被遮罩层中相应位置的对象是看不见的。
 */
@property(nullable, strong) CALayer *mask;

/* When true an implicit mask matching the layer bounds is applied to
 * the layer (including the effects of the `cornerRadius' property). If
 * both `mask' and `masksToBounds' are non-nil the two masks are
 * multiplied to get the actual mask values. Defaults to NO.
 * Animatable.
 当设置YES，将匹配层边界的隐式掩码应用于层(包括“角半径”属性的影响)。
 如果“mask”和“masksToBounds”都是非空的，则将两个mask相乘以得到实际的mask值。
 默认NO。支持动画(iOS11开始才有动画)
 */
@property BOOL masksToBounds;

/** Mapping between layer coordinate and time spaces. **/

- (CGPoint)convertPoint:(CGPoint)p fromLayer:(nullable CALayer *)l;
- (CGPoint)convertPoint:(CGPoint)p toLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r fromLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r toLayer:(nullable CALayer *)l;

- (CFTimeInterval)convertTime:(CFTimeInterval)t fromLayer:(nullable CALayer *)l;
- (CFTimeInterval)convertTime:(CFTimeInterval)t toLayer:(nullable CALayer *)l;

/** Hit testing methods. **/

/* Returns the farthest descendant of the layer containing point 'p'.
 * Siblings are searched in top-to-bottom order. 'p' is defined to be
 * in the coordinate space of the receiver's nearest ancestor that
 * isn't a CATransformLayer (transform layers don't have a 2D
 * coordinate space in which the point could be specified). */

- (nullable CALayer *)hitTest:(CGPoint)p;

/* Returns true if the bounds of the layer contains point 'p'. */

- (BOOL)containsPoint:(CGPoint)p;

/** Layer content properties and methods. **/

/* An object providing the contents of the layer, typically a CGImageRef,
 * but may be something else. (For example, NSImage objects are
 * supported on Mac OS X 10.6 and later.) Default value is nil.
 * Animatable. */

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

/* The filter types to use when rendering the `contents' property of
 * the layer. The minification filter is used when to reduce the size
 * of image data, the magnification filter to increase the size of
 * image data. Currently the allowed values are `nearest' and `linear'.
 * Both properties default to `linear'.
 渲染图层的“contents”属性时使用的过滤器类型。 minification过滤器用于缩小图像数据的大小时，magnification过滤器增加图像数据的大小。
 目前允许的值是`nearest' 和 `linear'的。 这两个属性默认为`linear'。
 */

@property(copy) NSString *minificationFilter;
@property(copy) NSString *magnificationFilter;

/* The bias factor added when determining which levels of detail to use
 * when minifying using trilinear filtering. The default value is 0.
 * Animatable.
 在确定使用三线性滤波进行缩放时要使用哪些细节级别时添加的偏移因子。 默认值是0，可动画。

*/

@property float minificationFilterBias;

/* A hint marking that the layer contents provided by -drawInContext:
 * is completely opaque. Defaults to NO. Note that this does not affect
 * the interpretation of the `contents' property directly. */

@property(getter=isOpaque) BOOL opaque;

/* Reload the content of this layer. Calls the -drawInContext: method
 * then updates the `contents' property of the layer. Typically this is
 * not called directly. */

- (void)display;

/* Marks that -display needs to be called before the layer is next
 * committed. If a region is specified, only that region of the layer
 * is invalidated. */

- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)r;

/* Returns true when the layer is marked as needing redrawing. */

- (BOOL)needsDisplay;

/* Call -display if receiver is marked as needing redrawing. */

- (void)displayIfNeeded;

/* When true -setNeedsDisplay will automatically be called when the
 * bounds of the layer changes. Default value is NO.
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

/* Defines how the edges of the layer are rasterized. For each of the
 * four edges (left, right, bottom, top) if the corresponding bit is
 * set the edge will be antialiased. Typically this property is used to
 * disable antialiasing for edges that abut edges of other layers, to
 * eliminate the seams that would otherwise occur. The default value is
 * for all edges to be antialiased.

 定义图层的边缘如何被光栅化。 对于四个边（左，右，下，上）中的每一个，如果相应的
 位被设置，边将被反锯齿。 通常，此属性用于禁用对邻接其他图层边缘的边缘进行抗锯齿，
 以消除否则会出现的接缝。 默认值是所有的边缘都是反锯齿的。

 
 */

@property CAEdgeAntialiasingMask edgeAntialiasingMask;

/* When true this layer is allowed to antialias its edges, as requested
 * by the value of the edgeAntialiasingMask property.
 *
 * The default value is read from the boolean UIViewEdgeAntialiasing
 * property in the main bundle's Info.plist. If no value is found in
 * the Info.plist the default value is NO.
 
 指示是否允许图层执行边缘抗锯齿。
 在使用view的缩放的时候，layer.border.width随着view的放大，会出现锯齿化的问题，解决这个问题可以设置这个属性。
 如果为true，则允许此层根据edgeAntialiasingMask属性的值的请求对其边缘进行抗锯齿处理。
 默认值从主包的Info.plist中的布尔UIViewEdgeAntialiasing属性中读取。 如果Info.plist中未找到任何值，则默认值为NO。
 */

@property BOOL allowsEdgeAntialiasing;

/* The background color of the layer. Default value is nil. Colors
 * created from tiled patterns are supported. Animatable. */

@property(nullable) CGColorRef backgroundColor;

/* When positive, the background of the layer will be drawn with
 * rounded corners. Also effects the mask generated by the
 * `masksToBounds' property. Defaults to zero. Animatable.
 当为正数时，图层的背景用圆角绘制。还会影响“masksToBounds”属性生成的掩码。默认值为零。
 支持动画。(在iOS11.0之前圆角是不支持动画的)
 */
@property CGFloat cornerRadius;

/* Defines which of the four corners receives the masking when using
 * `cornerRadius' property. Defaults to all four corners.
 使用cornerRadius圆角属性时，定义四个角中的哪一个接收遮罩。 默认为所有四个角(iOS11+)。
 例如只切两个圆角:kCALayerMinXMinYCorner | kCALayerMaxXMinYCorner;
*/
@property CACornerMask maskedCorners
  CA_AVAILABLE_STARTING (10.13, 11.0, 11.0, 4.0);

/* The width of the layer's border, inset from the layer bounds. The
 * border is composited above the layer's content and sublayers and
 * includes the effects of the `cornerRadius' property. Defaults to
 * zero. Animatable. */

@property CGFloat borderWidth;

/* The color of the layer's border. Defaults to opaque black. Colors
 * created from tiled patterns are supported. Animatable. */

@property(nullable) CGColorRef borderColor;

/* The opacity of the layer, as a value between zero and one. Defaults
 * to one. Specifying a value outside the [0,1] range will give undefined
 * results. Animatable. */

@property float opacity;

/* When true, and the layer's opacity property is less than one, the
 * layer is allowed to composite itself as a group separate from its
 * parent. This gives the correct results when the layer contains
 * multiple opaque components, but may reduce performance.
 *
 * The default value of the property is read from the boolean
 * UIViewGroupOpacity property in the main bundle's Info.plist. If no
 * value is found in the Info.plist the default value is YES for
 * applications linked against the iOS 7 SDK or later and NO for
 * applications linked against an earlier SDK. */

@property BOOL allowsGroupOpacity;

/* A filter object used to composite the layer with its (possibly
 * filtered) background. Default value is nil, which implies source-
 * over compositing. Animatable.
 *
 * Note that if the inputs of the filter are modified directly after
 * the filter is attached to a layer, the behavior is undefined. The
 * filter must either be reattached to the layer, or filter properties
 * should be modified by calling -setValue:forKeyPath: on each layer
 * that the filter is attached to. (This also applies to the `filters'
 * and `backgroundFilters' properties.) */

@property(nullable, strong) id compositingFilter;

/* An array of filters that will be applied to the contents of the
 * layer and its sublayers. Defaults to nil. Animatable. */

@property(nullable, copy) NSArray *filters;

/* An array of filters that are applied to the background of the layer.
 * The root layer ignores this property. Animatable. */

@property(nullable, copy) NSArray *backgroundFilters;

/* When true, the layer is rendered as a bitmap in its local coordinate
 * space ("rasterized"), then the bitmap is composited into the
 * destination (with the minificationFilter and magnificationFilter
 * properties of the layer applied if the bitmap needs scaling).
 * Rasterization occurs after the layer's filters and shadow effects
 * are applied, but before the opacity modulation. As an implementation
 * detail the rendering engine may attempt to cache and reuse the
 * bitmap from one frame to the next. (Whether it does or not will have
 * no affect on the rendered output.)
 *
 * When false the layer is composited directly into the destination
 * whenever possible (however, certain features of the compositing
 * model may force rasterization, e.g. adding filters).
 *
 * Defaults to NO. Animatable. */

@property BOOL shouldRasterize;

/* The scale at which the layer will be rasterized (when the
 * shouldRasterize property has been set to YES) relative to the
 * coordinate space of the layer. Defaults to one. Animatable. */

@property CGFloat rasterizationScale;

/** Shadow properties. **/

/* The color of the shadow. Defaults to opaque black. Colors created
 * from patterns are currently NOT supported. Animatable. */

@property(nullable) CGColorRef shadowColor;

/* The opacity of the shadow. Defaults to 0. Specifying a value outside the
 * [0,1] range will give undefined results. Animatable. */

@property float shadowOpacity;

/* The shadow offset. Defaults to (0, -3). Animatable. */

@property CGSize shadowOffset;

/* The blur radius used to create the shadow. Defaults to 3. Animatable. */

@property CGFloat shadowRadius;

/* When non-null this path defines the outline used to construct the
 * layer's shadow instead of using the layer's composited alpha
 * channel. The path is rendered using the non-zero winding rule.
 * Specifying the path explicitly using this property will usually
 * improve rendering performance, as will sharing the same path
 * reference across multiple layers. Upon assignment the path is copied.
 * Defaults to null. Animatable. */

@property(nullable) CGPathRef shadowPath;

/** Layout methods. **/

/* Returns the preferred frame size of the layer in the coordinate
 * space of the superlayer. The default implementation calls the layout
 * manager if one exists and it implements the -preferredSizeOfLayer:
 * method, otherwise returns the size of the bounds rect mapped into
 * the superlayer. */

- (CGSize)preferredFrameSize;

/* Marks that -layoutSublayers needs to be invoked on the receiver
 * before the next update. If the receiver's layout manager implements
 * the -invalidateLayoutOfLayer: method it will be called.
 *
 * This method is automatically invoked on a layer whenever its
 * `sublayers' or `layoutManager' property is modified, and is invoked
 * on the layer and its superlayer whenever its `bounds' or `transform'
 * properties are modified. Implicit calls to -setNeedsLayout are
 * skipped if the layer is currently executing its -layoutSublayers
 * method. */

- (void)setNeedsLayout;

/* Returns true when the receiver is marked as needing layout. */

- (BOOL)needsLayout;

/* Traverse upwards from the layer while the superlayer requires layout.
 * Then layout the entire tree beneath that ancestor. */

- (void)layoutIfNeeded;

/* Called when the layer requires layout. The default implementation
 * calls the layout manager if one exists and it implements the
 * -layoutSublayersOfLayer: method. Subclasses can override this to
 * provide their own layout algorithm, which should set the frame of
 * each sublayer. */

- (void)layoutSublayers;

/** Action methods. **/

/* An "action" is an object that responds to an "event" via the
 * CAAction protocol (see below). Events are named using standard
 * dot-separated key paths. Each layer defines a mapping from event key
 * paths to action objects. Events are posted by looking up the action
 * object associated with the key path and sending it the method
 * defined by the CAAction protocol.
 *
 * When an action object is invoked it receives three parameters: the
 * key path naming the event, the object on which the event happened
 * (i.e. the layer), and optionally a dictionary of named arguments
 * specific to each event.
 *
 * To provide implicit animations for layer properties, an event with
 * the same name as each property is posted whenever the value of the
 * property is modified. A suitable CAAnimation object is associated by
 * default with each implicit event (CAAnimation implements the action
 * protocol).
 *
 * The layer class also defines the following events that are not
 * linked directly to properties:
 *
 * onOrderIn
 *      Invoked when the layer is made visible, i.e. either its
 *      superlayer becomes visible, or it's added as a sublayer of a
 *      visible layer
 *
 * onOrderOut
 *      Invoked when the layer becomes non-visible. */

/* Returns the default action object associated with the event named by
 * the string 'event'. The default implementation returns a suitable
 * animation object for events posted by animatable properties, nil
 * otherwise. */

+ (nullable id<CAAction>)defaultActionForKey:(NSString *)event;

/* Returns the action object associated with the event named by the
 * string 'event'. The default implementation searches for an action
 * object in the following places:
 *
 * 1. if defined, call the delegate method -actionForLayer:forKey:
 * 2. look in the layer's `actions' dictionary
 * 3. look in any `actions' dictionaries in the `style' hierarchy
 * 4. call +defaultActionForKey: on the layer's class
 *
 * If any of these steps results in a non-nil action object, the
 * following steps are ignored. If the final result is an instance of
 * NSNull, it is converted to `nil'. */

- (nullable id<CAAction>)actionForKey:(NSString *)event;

/* A dictionary mapping keys to objects implementing the CAAction
 * protocol. Default value is nil. */

@property(nullable, copy) NSDictionary<NSString *, id<CAAction>> *actions;

/** Animation methods. **/

/* Attach an animation object to the layer. Typically this is implicitly
 * invoked through an action that is an CAAnimation object.
 *
 * 'key' may be any string such that only one animation per unique key
 * is added per layer. The special key 'transition' is automatically
 * used for transition animations. The nil pointer is also a valid key.
 *
 * If the `duration' property of the animation is zero or negative it
 * is given the default duration, either the value of the
 * `animationDuration' transaction property or .25 seconds otherwise.
 *
 * The animation is copied before being added to the layer, so any
 * subsequent modifications to `anim' will have no affect unless it is
 * added to another layer. */

- (void)addAnimation:(CAAnimation *)anim forKey:(nullable NSString *)key;

/* Remove all animations attached to the layer. */

- (void)removeAllAnimations;

/* Remove any animation attached to the layer for 'key'. */

- (void)removeAnimationForKey:(NSString *)key;

/* Returns an array containing the keys of all animations currently
 * attached to the receiver. The order of the array matches the order
 * in which animations will be applied. */

- (nullable NSArray<NSString *> *)animationKeys;

/* Returns the animation added to the layer with identifier 'key', or nil
 * if no such animation exists. Attempting to modify any properties of
 * the returned object will result in undefined behavior. */

- (nullable CAAnimation *)animationForKey:(NSString *)key;


/** Miscellaneous properties. **/

/* The name of the layer. Used by some layout managers. Defaults to nil. */

@property(nullable, copy) NSString *name;

/* An object that will receive the CALayer delegate methods defined
 * below (for those that it implements). The value of this property is
 * not retained. Default value is nil. */

@property(nullable, weak) id <CALayerDelegate> delegate;

/* When non-nil, a dictionary dereferenced to find property values that
 * aren't explicitly defined by the layer. (This dictionary may in turn
 * have a `style' property, forming a hierarchy of default values.)
 * If the style dictionary doesn't define a value for an attribute, the
 * +defaultValueForKey: method is called. Defaults to nil.
 *
 * Note that if the dictionary or any of its ancestors are modified,
 * the values of the layer's properties are undefined until the `style'
 * property is reset. */

@property(nullable, copy) NSDictionary *style;

@end

/** Action (event handler) protocol. **/

@protocol CAAction

/* Called to trigger the event named 'path' on the receiver. The object
 * (e.g. the layer) on which the event happened is 'anObject'. The
 * arguments dictionary may be nil, if non-nil it carries parameters
 * associated with the event. */

- (void)runActionForKey:(NSString *)event object:(id)anObject
    arguments:(nullable NSDictionary *)dict;

@end

/** NSNull protocol conformance. **/

@interface NSNull (CAActionAdditions) <CAAction>

@end

/** Delegate methods. **/

@protocol CALayerDelegate <NSObject>
@optional

/* If defined, called by the default implementation of the -display
 * method, in which case it should implement the entire display
 * process (typically by setting the `contents' property). */

- (void)displayLayer:(CALayer *)layer;

/* If defined, called by the default implementation of -drawInContext: */

- (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx;

/* If defined, called by the default implementation of the -display method.
 * Allows the delegate to configure any layer state affecting contents prior
 * to -drawLayer:InContext: such as `contentsFormat' and `opaque'. It will not
 * be called if the delegate implements -displayLayer. */

- (void)layerWillDraw:(CALayer *)layer
  CA_AVAILABLE_STARTING (10.12, 10.0, 10.0, 3.0);

/* Called by the default -layoutSublayers implementation before the layout
 * manager is checked. Note that if the delegate method is invoked, the
 * layout manager will be ignored. */

- (void)layoutSublayersOfLayer:(CALayer *)layer;

/* If defined, called by the default implementation of the
 * -actionForKey: method. Should return an object implementating the
 * CAAction protocol. May return 'nil' if the delegate doesn't specify
 * a behavior for the current event. Returning the null object (i.e.
 * '[NSNull null]') explicitly forces no further search. (I.e. the
 * +defaultActionForKey: method will not be called.) */

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
 */
//三线性滤波算法存储了多个大小情况下的图片（也叫多重贴图），并三维取样，同时结合大图和小图的存储进而得到最后的结果。
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
