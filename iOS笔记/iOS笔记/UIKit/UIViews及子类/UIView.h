//
//  UIView.h
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/11.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

//
//  UIView.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/NSLayoutConstraint.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIFocus.h>

NS_ASSUME_NONNULL_BEGIN

// 动画效果
typedef NS_ENUM(NSInteger, UIViewAnimationCurve) {
    UIViewAnimationCurveEaseInOut, //淡入淡出
    UIViewAnimationCurveEaseIn,    //开始慢
    UIViewAnimationCurveEaseOut,   //结束慢
    UIViewAnimationCurveLinear     //线性的

};

// 视图内容风格
typedef NS_ENUM(NSInteger, UIViewContentMode) {
    UIViewContentModeScaleToFill,         // 缩放内容到合适比例大小
    UIViewContentModeScaleAspectFit,      // 缩放内容到合适的大小，边界多余部分透明
    UIViewContentModeScaleAspectFill,     // 缩放内容填充到指定大小，边界多余的部分省略.
    UIViewContentModeRedraw,              // 重绘视图边界 (需调用 -setNeedsDisplay)
    UIViewContentModeCenter,              // 视图保持等比缩放,视图居中对齐
    UIViewContentModeTop,                 // 视图保持等比缩放,视图顶部对齐
    UIViewContentModeBottom,              // 视图保持等比缩放,视图底部对齐
    UIViewContentModeLeft,                // 视图保持等比缩放,视图左侧对齐
    UIViewContentModeRight,               // 视图保持等比缩放,视图右侧对齐
    UIViewContentModeTopLeft,             // 视图保持等比缩放,视图左上角对齐
    UIViewContentModeTopRight,            // 视图保持等比缩放,视图右上角对齐
    UIViewContentModeBottomLeft,          // 视图保持等比缩放,视图左下角对齐
    UIViewContentModeBottomRight,         // 视图保持等比缩放,视图右下角对齐
};


// 过渡动画
typedef NS_ENUM(NSInteger, UIViewAnimationTransition) {
    UIViewAnimationTransitionNone,          //没有动画效果
    UIViewAnimationTransitionFlipFromLeft,  //从左向右旋转翻页
    UIViewAnimationTransitionFlipFromRight, //从右向左旋转翻页
    UIViewAnimationTransitionCurlUp,        //卷曲翻页，从下往上
    UIViewAnimationTransitionCurlDown,      //卷曲翻页，从上往下
};


// 视图布局
typedef NS_OPTIONS(NSUInteger, UIViewAutoresizing) {
    
    UIViewAutoresizingNone                 //视图将不进行自动尺寸调整。
    UIViewAutoresizingFlexibleLeftMargin   //视图的左边界将随着父视图宽度的变化而按比例进行调整。否则，视图和其父视图的左边界的相对位置将保持不变。
    UIViewAutoresizingFlexibleWidth        //视图的宽度将和父视图的宽度一起成比例变化。否则，视图的宽度将保持不变
    UIViewAutoresizingFlexibleHeight       //视图的高度将和父视图的高度一起成比例变化。否则，视图的高度将保持不变
    UIViewAutoresizingFlexibleRightMargin  //视图的右边界将随着父视图宽度的变化而按比例进行调整。否则，视图和其父视图的右边界的相对位置将保持不变。
    UIViewAutoresizingFlexibleTopMargin    //视图的上边界将随着父视图高度的变化而按比例进行调整。否则，视图和其父视图的上边界的相对位置将保持不变。
    UIViewAutoresizingFlexibleBottomMargin //视图的底边界将随着父视图高度的变化而按比例进行调整。否则，视图和其父视图的底边界的相对位置将保持不变。

};

// 动画选项
typedef NS_OPTIONS(NSUInteger, UIViewAnimationOptions) {
    //1.常规动画属性设置（可以同时选择多个进行设置）
    UIViewAnimationOptionLayoutSubviews            = 1 <<  0, // 动画过程中保证子视图跟随运动。
    UIViewAnimationOptionAllowUserInteraction      = 1 <<  1, // 动画过程中允许用户交互。>>>>>>>>>>>>>>>>>
    UIViewAnimationOptionBeginFromCurrentState     = 1 <<  2, // 所有视图从当前状态开始运行
    UIViewAnimationOptionRepeat                    = 1 <<  3, // 重复运行动画。
    UIViewAnimationOptionAutoreverse               = 1 <<  4, // 动画运行到结束点后仍然以动画方式回到初始点
    UIViewAnimationOptionOverrideInheritedDuration = 1 <<  5, // 忽略嵌套动画时间设置
    UIViewAnimationOptionOverrideInheritedCurve    = 1 <<  6, // 忽略嵌套动画速度设置
    UIViewAnimationOptionAllowAnimatedContent      = 1 <<  7, // 动画过程中重绘视图（注意仅仅适用于转场动画）
    UIViewAnimationOptionShowHideTransitionViews   = 1 <<  8, // 视图切换时直接隐藏旧视图、显示新视图，而不是将旧视图从父视图移除（仅仅适用于转场动画）
    UIViewAnimationOptionOverrideInheritedOptions  = 1 <<  9, // 不继承父动画设置或动画类型。
    
    //2.动画速度控制（可从其中选择一个设置）
    UIViewAnimationOptionCurveEaseInOut            = 0 << 16, // default 动画先缓慢，然后逐渐加速。
    UIViewAnimationOptionCurveEaseIn               = 1 << 16, //动画逐渐变慢。
    UIViewAnimationOptionCurveEaseOut              = 2 << 16, //动画逐渐加速。
    UIViewAnimationOptionCurveLinear               = 3 << 16, //动画匀速执行，默认值。

    //3.转场类型（仅适用于转场动画设置，可以从中选择一个进行设置，基本动画、关键帧动画不需要设置）
    UIViewAnimationOptionTransitionNone            = 0 << 20, // default 没有转场动画效果
    UIViewAnimationOptionTransitionFlipFromLeft    = 1 << 20, //从左侧翻转效果
    UIViewAnimationOptionTransitionFlipFromRight   = 2 << 20, //从右侧翻转效果。
    UIViewAnimationOptionTransitionCurlUp          = 3 << 20, //向后翻页的动画过渡效果
    UIViewAnimationOptionTransitionCurlDown        = 4 << 20, //向前翻页的动画过渡效果。
    UIViewAnimationOptionTransitionCrossDissolve   = 5 << 20, //旧视图溶解消失显示下一个新视图的效果》
    UIViewAnimationOptionTransitionFlipFromTop     = 6 << 20, //从上方翻转效果。
    UIViewAnimationOptionTransitionFlipFromBottom  = 7 << 20, //从底部翻转效果。
    
    UIViewAnimationOptionPreferredFramesPerSecondDefault     = 0 << 24,// 默认
    UIViewAnimationOptionPreferredFramesPerSecond60          = 3 << 24,// 每秒60帧的刷新速率
    UIViewAnimationOptionPreferredFramesPerSecond30          = 7 << 24,// 每秒30帧的刷新速率
    
    
} NS_ENUM_AVAILABLE_IOS(4_0);

// 关键帧动画
typedef NS_OPTIONS(NSUInteger, UIViewKeyframeAnimationOptions) {

    UIViewKeyframeAnimationOptionLayoutSubviews            = UIViewAnimationOptionLayoutSubviews, // 子视图在指定的时间内完成在父视图上的自动布局的动画
    UIViewKeyframeAnimationOptionAllowUserInteraction      = UIViewAnimationOptionAllowUserInteraction, //动画过程中允许用户交互 -开启交互动画
    UIViewKeyframeAnimationOptionBeginFromCurrentState     = UIViewAnimationOptionBeginFromCurrentState, // 所有视图从当前状态开始运行-从当前值开始动画
    UIViewKeyframeAnimationOptionRepeat                    = UIViewAnimationOptionRepeat, // 无限重复
    UIViewKeyframeAnimationOptionAutoreverse               = UIViewAnimationOptionAutoreverse, // 动画运行到结束点后仍然以动画方式回到初始点-自动来回
    UIViewKeyframeAnimationOptionOverrideInheritedDuration = UIViewAnimationOptionOverrideInheritedDuration, // 忽略嵌套的动画的时间
    UIViewKeyframeAnimationOptionOverrideInheritedOptions  = UIViewAnimationOptionOverrideInheritedOptions, // 不继承任何动画类型
    
    UIViewKeyframeAnimationOptionCalculationModeLinear     = 0 << 10, //连续运算模式, 默认
    UIViewKeyframeAnimationOptionCalculationModeDiscrete   = 1 << 10, //离散运算模式.
    UIViewKeyframeAnimationOptionCalculationModePaced      = 2 << 10, //均匀执行运算模式.
    UIViewKeyframeAnimationOptionCalculationModeCubic      = 3 << 10, //平滑运算模式.
    UIViewKeyframeAnimationOptionCalculationModeCubicPaced = 4 << 10  //平滑均匀运算模式.
    
} NS_ENUM_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSUInteger, UISystemAnimation) {
    UISystemAnimationDelete,    // 完成时从视图中删除, removes the views from the hierarchy when complete
} NS_ENUM_AVAILABLE_IOS(7_0);

// 色彩调整风格
typedef NS_ENUM(NSInteger, UIViewTintAdjustmentMode) {
    UIViewTintAdjustmentModeAutomatic, // 与父视图相同
    UIViewTintAdjustmentModeNormal,    // 未经修改的
    UIViewTintAdjustmentModeDimmed,    // 饱和、暗淡的原始色
} NS_ENUM_AVAILABLE_IOS(7_0);

// 左右切换或左右布局
typedef NS_ENUM(NSInteger, UISemanticContentAttribute) {
    UISemanticContentAttributeUnspecified = 0, // 左右切换时视图翻转
    UISemanticContentAttributePlayback, // 音乐播放按钮设置，左右切换此视图不会翻转
    UISemanticContentAttributeSpatial, // 控件方向不能改变,控制导致某种形式的定向改变UI中,如分段控制文本对齐方式或在游戏中方向键
    UISemanticContentAttributeForceLeftToRight, //视图总是从左向右布局.
    UISemanticContentAttributeForceRightToLeft  //视图总是从右向左布局.
    
} NS_ENUM_AVAILABLE_IOS(9_0);

@protocol UICoordinateSpace <NSObject>
// 将当前的坐标空间点转换到指定的坐标空间
- (CGPoint)convertPoint:(CGPoint)point toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
// 将指定的坐标空间点转换到当前的坐标空间
- (CGPoint)convertPoint:(CGPoint)point fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
// 将当前的矩形坐标空间转换到指定的矩形坐标空间
- (CGRect)convertRect:(CGRect)rect toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
// 将指定的矩形坐标空间转换到当前的矩形坐标空间
- (CGRect)convertRect:(CGRect)rect fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
// 该view在本地坐标系统中的位置和大小(参照点是，本地坐标系统)
@property (readonly, nonatomic) CGRect bounds NS_AVAILABLE_IOS(8_0);

@end

@class UIBezierPath, UIEvent, UIWindow, UIViewController, UIColor, UIGestureRecognizer, UIMotionEffect, CALayer, UILayoutGuide;
//UIView 继承于UIResponder,所遵守的协议有 NSCoding 、UIAppearance、 UIAppearanceContainer,UIDynamicItem、 ..
NS_CLASS_AVAILABLE_IOS(2_0) @interface UIView : UIResponder <NSCoding, UIAppearance, UIAppearanceContainer, UIDynamicItem, UITraitEnvironment, UICoordinateSpace, UIFocusItem, CALayerDelegate>

#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) Class layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.
#else
+ (Class)layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.
#endif
// 初始化视图并设置位置和大小
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
// 用于xib初始化
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//决定与用户交互事件是否从被忽略并从事件队列中移除
@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is YES. if set to NO, user events (touch, keys) are ignored and removed from the event queue.
@property(nonatomic)                                 NSInteger tag;                // default is 0 当前视图标签
@property(nonatomic,readonly,strong)                 CALayer  *layer;              //用于视图渲染的核心动画层 returns view's layer. Will always return a non-nil value. view is layer's delegate

#if UIKIT_DEFINE_AS_PROPERTIES
// 视图是否可以成为焦点, 默认NO（返回YES可能是：视图被隐藏、透明度为0，userInteractionEnabled设置为NO等）
@property(nonatomic,readonly) BOOL canBecomeFocused NS_AVAILABLE_IOS(9_0); // NO by default
#else
- (BOOL)canBecomeFocused NS_AVAILABLE_IOS(9_0); // NO by default
#endif
// 当前项是否可以被聚焦
@property (readonly, nonatomic, getter=isFocused) BOOL focused NS_AVAILABLE_IOS(9_0);
//左右滑动翻转效果
@property (nonatomic) UISemanticContentAttribute semanticContentAttribute NS_AVAILABLE_IOS(9_0);

// This method returns the layout direction implied by the provided semantic content attribute relative to the application-wide layout direction (as returned by UIApplication.sharedApplication.userInterfaceLayoutDirection)该方法返回隐含的布局方向提供语义内容属性相对于应用程序布局方向(如由UIApplication.sharedApplication.userInterfaceLayoutDirection返回)。.
// 返回界面的方向
+ (UIUserInterfaceLayoutDirection)userInterfaceLayoutDirectionForSemanticContentAttribute:(UISemanticContentAttribute)attribute NS_AVAILABLE_IOS(9_0);

// This method returns the layout direction implied by the provided semantic content attribute relative to the provided layout direction. For example, when provided a layout direction of RightToLeft and a semantic content attribute of Playback, this method returns LeftToRight. Layout and drawing code can use this method to determine how to arrange elements, but might find it easier to query the container view’s effectiveUserInterfaceLayoutDirection property instead.
+ (UIUserInterfaceLayoutDirection)userInterfaceLayoutDirectionForSemanticContentAttribute:(UISemanticContentAttribute)semanticContentAttribute relativeToLayoutDirection:(UIUserInterfaceLayoutDirection)layoutDirection NS_AVAILABLE_IOS(10_0);

// Returns the user interface layout direction appropriate for arranging the immediate content of this view. Always consult the effectiveUserInterfaceLayoutDirection of the view whose immediate content is being arranged or drawn. Do not assume that the value propagates through the view’s subtree返回用户界面布局方向，以安排该视图的直接内容。总是立即查阅effectiveUserInterfaceLayoutDirection视图的内容被安排或画。不要假设值通过视图的子树传播。.
// 安排即时内容的布局的方向
@property (readonly, nonatomic) UIUserInterfaceLayoutDirection effectiveUserInterfaceLayoutDirection NS_AVAILABLE_IOS(10_0);

@end

@interface UIView(UIViewGeometry)

// animatable. do not use frame if view is transformed since it will not correctly reflect the actual location of the view. use bounds + center instead.
// 父视图位置(参照点是，父view坐标系统)
@property(nonatomic) CGRect            frame;

// use bounds/center and not frame if non-identity transform. if bounds dimension is odd, center may be have fractional part
// 该view在本地坐标系统中的位置和大小(参照点是，本地坐标系统)
@property(nonatomic) CGRect            bounds;      // default bounds is zero origin, frame size. animatable
@property(nonatomic) CGPoint           center;      // center is center of frame. animatable
@property(nonatomic) CGAffineTransform transform;   //视图的仿射变换 default is CGAffineTransformIdentity. animatable
@property(nonatomic) CGFloat           contentScaleFactor NS_AVAILABLE_IOS(4_0);//应用到当前视图的比例Scale，纯粹的资源的适配,比如设计分辨率是960x640，资源是320x480。为了让这个资源铺满屏幕，可以在所有设置资源的地方设置一个scale为2，也可以直接用setContentScaleFactor（0.5），那么所有的资源都会做2倍的缩放。为什么设置0.5是2倍缩放？因为这个的算法是（资源）/（设计分辨率）
//默认NO，是否支持多手指触摸交互
@property(nonatomic,getter=isMultipleTouchEnabled) BOOL multipleTouchEnabled __TVOS_PROHIBITED;   // default is NO
//决定当前视图是否是处理触摸事件的唯一对象
@property(nonatomic,getter=isExclusiveTouch) BOOL       exclusiveTouch __TVOS_PROHIBITED;         // default is NO

// 在指定点上点击测试指定事件
- (nullable UIView *)hitTest:(CGPoint)point withEvent:(nullable UIEvent *)event;   // recursively calls -pointInside:withEvent:. point is in the receiver's coordinate system
// 测试指定的点是否包含在接收对象中
- (BOOL)pointInside:(CGPoint)point withEvent:(nullable UIEvent *)event;   // default returns YES if point is in bounds

// 转换视图间坐标
//[sender.superview convertPoint:sender.center toView:[UIApplication sharedApplication].delegate.window];
//view= nil时，则转换的toView坐标系就是默认它的父视图
//  eg: CGPoint P2 = [A convertPoint:P1 toView:B];
//A:被转坐标系的视图
//B:要转到的指定视图
//P1:A上的点坐标
//P2:转到B上后的点坐标
//  eg: CGPoint P2 = [A convertPoint:P1 fromView:B]; //和上相反
//B:被转坐标系的视图
//A:要转到的指定视图
//P1:B上的点坐标
//P2:转到A上后的点坐标

// 转换一个点从接受对象的坐标系到指定视图
- (CGPoint)convertPoint:(CGPoint)point toView:(nullable UIView *)view;
// 与上面相反，指定视图坐标中的一个点转换为接收对象
- (CGPoint)convertPoint:(CGPoint)point fromView:(nullable UIView *)view;
// 将当前的矩形坐标空间转换到指定的矩形坐标空间
- (CGRect)convertRect:(CGRect)rect toView:(nullable UIView *)view;
// 将指定的矩形坐标空间转换到当前的矩形坐标空间
- (CGRect)convertRect:(CGRect)rect fromView:(nullable UIView *)view;

//自动尺寸调整8
@property(nonatomic) BOOL               autoresizesSubviews; // default is YES. if set, subviews are adjusted according to their autoresizingMask if self.bounds changes默认是YES。 如果设置，子视图根据autoresizingMask进行调整，如果self.bounds更改
// 决定当当前视图的父视图大小发生变化时，当前视图该怎么调整自己的size;自动调整子控件与父控件中间的位置，宽高（和SB上自动8个像素类似）
@property(nonatomic) UIViewAutoresizing autoresizingMask;    // simple resize. default is UIViewAutoresizingNone

//sizeToFit和sizeThatFits方法都没有递归，对subviews也不负责，只负责自己
- (CGSize)sizeThatFits:(CGSize)size;     // 返回“最佳”大小，以适应给定的大小。实际上并没有改变视图的大小。默认是返回现有视图大小

//sizeToFit会自动调用sizeThatFits方法,sizeToFit不应该在子类中被重写，应该重写sizeThatFits
- (void)sizeToFit; //

@end

@interface UIView(UIViewHierarchy)

@property(nullable, nonatomic,readonly) UIView       *superview;//view的父视图
@property(nonatomic,readonly,copy) NSArray<__kindof UIView *> *subviews;//view的所有子视图。这是个数组，当需要view上的某个子视图时根据数组下标取或遍历出来
@property(nullable, nonatomic,readonly) UIWindow     *window;//view的窗口

- (void)removeFromSuperview;//从父视图上移除
- (void)insertSubview:(UIView *)view atIndex:(NSInteger)index;//插入一个子视图，并指定索引位置
- (void)exchangeSubviewAtIndex:(NSInteger)index1 withSubviewAtIndex:(NSInteger)index2; //交换两个位置的子视图
- (void)addSubview:(UIView *)view;//添加一个子视图
- (void)insertSubview:(UIView *)view belowSubview:(UIView *)siblingSubview;//插入一个子视图在某个子视图的下面
- (void)insertSubview:(UIView *)view aboveSubview:(UIView *)siblingSubview;//插入一个子视图在某个子视图的上面


- (void)bringSubviewToFront:(UIView *)view;//将一个子视图移到前面
- (void)sendSubviewToBack:(UIView *)view;//将一个子视图移到后面

#park mark - 回调的方法
- (void)didAddSubview:(UIView *)subview;//view已经添加子视图
- (void)willRemoveSubview:(UIView *)subview; //将要移除子视图

- (void)willMoveToSuperview:(nullable UIView *)newSuperview; //将要移动到新的父视图!!!!
- (void)didMoveToSuperview;//已经移动到父视图
- (void)willMoveToWindow:(nullable UIWindow *)newWindow;//将要移动到新的window
- (void)didMoveToWindow;//已经移动到window

- (BOOL)isDescendantOfView:(UIView *)view;  //是否是指定view的子视图。返回YES或NO
- (nullable __kindof UIView *)viewWithTag:(NSInteger)tag; //根据tag值取出这个view

//UIView的setNeedsDisplay和setNeedsLayout方法。首先两个方法都是异步执行的。而setNeedsDisplay会自动调用drawRect方法，这样可以拿到UIGraphicsGetCurrentContext，就可以画画了。而setNeedsLayout会默认调用layoutSubViews，就可以处理子视图中的一些数据。

// 标记为需要重新布局，异步调用layoutIfNeeded刷新布局，不立即刷新，但layoutSubviews一定会被调用,在系统runloop的下一个周期自动调用layoutSubviews
- (void)setNeedsLayout;
//如果，有需要刷新的标记，立即调用layoutSubviews进行布局（如果没有标记，不会调用layoutSubviews）
//如果要立即刷新，要先调用[view setNeedsLayout]，把标记设为需要布局，然后马上调用[view layoutIfNeeded]，实现布局
//在视图第一次显示之前，标记总是“需要刷新”的，可以直接调用[view layoutIfNeeded]
- (void)layoutIfNeeded;

//layoutSubviews在以下情况下会被调用：
//1.init初始化不会触发layoutSubviews，但是是用initWithFrame进行初始化时，当rect的值不为CGRectZero时,也会触发
//2.addSubview添加子视图会触发layoutSubviews
//3.设置view的frame会触发layoutSubviews，当然前提是frame的值设置前后发生了变化
//4.滚动一个UIScrollView会触发layoutSubviews
//5.旋转screen会触发父UIView上的layoutSubviews事件
//6.改变一个UIView大小的时候也会触发父UIView上的layoutSubviews事件,但改变父视图不会触发子视图的layoutSubviews事件
//设置子控件的frame可以使用layoutSubviews;layoutSubviews一定要重写父方法
- (void)layoutSubviews;//layoutSubviews方法调用先于drawRect

/*
 -layoutMargins returns a set of insets from the edge of the view's bounds that denote a default spacing for laying out content.
 If preservesSuperviewLayoutMargins is YES, margins cascade down the view tree, adjusting for geometry offsets, so that setting the left value of layoutMargins on a superview will affect the left value of layoutMargins for subviews positioned close to the left edge of their superview's bounds
 If your view subclass uses layoutMargins in its layout or drawing, override -layoutMarginsDidChange in order to refresh your view if the margins change.
 */
//在iOS 8后，可以使用layoutMargins去定义view之间的间距,该属性只对AutoLayout布局生效
@property (nonatomic) UIEdgeInsets layoutMargins NS_AVAILABLE_IOS(8_0); //和StoryBoard或xib上的Constrain to margins一样，默认layoutMargins 为(8,8,8,8)，例如在SB上设置0间距，☑️Constrain to margins的话，显示间距为0，但实际为你提供额外8个单位间距，所以实际间距为8

/* directionalLayoutMargins.leading is used on the left when the user interface direction is LTR and on the right for RTL.
 Vice versa for directionalLayoutMargins.trailing.
 */
@property (nonatomic) NSDirectionalEdgeInsets directionalLayoutMargins API_AVAILABLE(ios(11.0),tvos(11.0));

@property (nonatomic) BOOL preservesSuperviewLayoutMargins NS_AVAILABLE_IOS(8_0); //一般不建议开起使用8个间距这东西；//这个属性默认是NO。如果把它设为YES，layoutMargins会根据屏幕中相关View的布局而改变

@property (nonatomic) BOOL insetsLayoutMarginsFromSafeArea API_AVAILABLE(ios(11.0),tvos(11.0));  // Default: YES

//在我们改变View的layoutMargins这个属性时，会触发- (void)layoutMarginsDidChange这个方法。我们在自己的View里面可以重写这个方法来捕获layoutMargins的变化。在大多数情况下，我们可以在这个方法里触发drawing和layout的Update。
- (void)layoutMarginsDidChange NS_AVAILABLE_IOS(8_0);

@property (nonatomic,readonly) UIEdgeInsets safeAreaInsets API_AVAILABLE(ios(11.0),tvos(11.0));
- (void)safeAreaInsetsDidChange API_AVAILABLE(ios(11.0),tvos(11.0));

/* The edges of this guide are constrained to equal the edges of the view inset by the layoutMargins
 */
@property(readonly,strong) UILayoutGuide *layoutMarginsGuide NS_AVAILABLE_IOS(9_0);

/// This content guide provides a layout area that you can use to place text and related content whose width should generally be constrained to a size that is easy for the user to read. This guide provides a centered region that you can place content within to get this behavior for this view.
@property (nonatomic, readonly, strong) UILayoutGuide *readableContentGuide  NS_AVAILABLE_IOS(9_0);

/* The top of the safeAreaLayoutGuide indicates the unobscured top edge of the view (e.g, not behind
 the status bar or navigation bar, if present). Similarly for the other edges.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *safeAreaLayoutGuide API_AVAILABLE(ios(11.0),tvos(11.0));
@end

@interface UIView(UIViewRendering)

- (void)drawRect:(CGRect)rect;//重写此方法，执行重绘任务

//setNeedsDisplay在receiver标上一个需要被重新绘图的标记，在下一个draw周期自动重绘，iphone device的刷新频率是60hz，也就是1/60秒后重绘
- (void)setNeedsDisplay;//标记为需要重绘，异步调用drawRect
- (void)setNeedsDisplayInRect:(CGRect)rect; //标记为需要局部重绘

@property(nonatomic)                 BOOL              clipsToBounds;              // 切出子视图超出父视图部分
//宏UI_APPEARANCE_SELECTOR    1.[[UIView appearance] setBackgroundColor:[UIColor redColor]];一旦这样修改，你App程序里面的所有UIView属性都会变为这个值，如果要单独修改某个2.view.backgroundColor = [UIColor blackColor],2必须在1执行之后才会有效blackColor
@property(nullable, nonatomic,copy)            UIColor          *backgroundColor UI_APPEARANCE_SELECTOR; // default is nil. Can be useful with the appearance proxy on custom UIView subclasses.
//默认是1.0，如果父视图alpha改变，那么所有子视图alpha都跟着改变
@property(nonatomic)                 CGFloat           alpha;
//默认是YES，提升绘制性能，如果开发中UIView是不透明的，opaque设置为YES， 如果opaque设置NO，那么Alpha应该小于1，否则产生的后果是不可预料的哦（屏幕绘制相关）~
@property(nonatomic,getter=isOpaque) BOOL              opaque;
//默认是YES,决定在视图重画之前是否先清理视图以前的内容
//如果你把这个属性设为NO，那么你要保证能在 drawRect：方法中正确的绘画。如果你的代码
//已经做了大量优化，那么设为NO可以提高性能，尤其是在滚动时可能只需要重新绘画视图的一部分
@property(nonatomic)                 BOOL              clearsContextBeforeDrawing;
//默认是NO,如果父视图hidden，那么所有子视图都跟着hidden
@property(nonatomic,getter=isHidden) BOOL              hidden;
//默认是 UIViewContentModeScaleToFill,决定当视图边界变时呈现视图内容的方式(填充样式)
@property(nonatomic)                 UIViewContentMode contentMode;
@property(nonatomic)                 CGRect            contentStretch NS_DEPRECATED_IOS(3_0,6_0) __TVOS_PROHIBITED; //视图内容如何拉伸 animatable. default is unit rectangle {{0,0} {1,1}}. Now deprecated: please use -[UIImage resizableImageWithCapInsets:] to achieve the same effect.
//一个通过alpha通道来掩盖一个view的内容的可选view.
@property(nullable, nonatomic,strong)          UIView           *maskView NS_AVAILABLE_IOS(8_0);

/*
 -tintColor always returns a color. The color returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, a system-defined color is returned.
 If this view's -tintAdjustmentMode returns Dimmed, then the color that is returned for -tintColor will automatically be dimmed.
 If your view subclass uses tintColor in its rendering, override -tintColorDidChange in order to refresh the rendering if the color changes.
 */
//色调颜色
@property(null_resettable, nonatomic, strong) UIColor *tintColor NS_AVAILABLE_IOS(7_0);

/*
 -tintAdjustmentMode always returns either UIViewTintAdjustmentModeNormal or UIViewTintAdjustmentModeDimmed. The value returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, UIViewTintAdjustmentModeNormal is returned.
 When tintAdjustmentMode has a value of UIViewTintAdjustmentModeDimmed for a view, the color it returns from tintColor will be modified to give a dimmed appearance.
 When the tintAdjustmentMode of a view changes (either the view's value changing or by one of its superview's values changing), -tintColorDidChange will be called to allow the view to refresh its rendering.
 */
//色调调整模式
@property(nonatomic) UIViewTintAdjustmentMode tintAdjustmentMode NS_AVAILABLE_IOS(7_0);

/*
 The -tintColorDidChange message is sent to appropriate subviews of a view when its tintColor is changed by client code or to subviews in the view hierarchy of a view whose tintColor is implicitly changed when its superview or tintAdjustmentMode changes.
 */
- (void)tintColorDidChange NS_AVAILABLE_IOS(7_0);//色调颜色改变执行方法

@end
#park mark - UIView动画
@interface UIView(UIViewAnimation)

//开始指定的动画，context附加的应用程序信息用来传递给动画代理消息
+ (void)beginAnimations:(nullable NSString *)animationID context:(nullable void *)context;  // additional context info passed to will start/did stop selectors. begin/commit can be nested
//结束一个动画块并开始当他在动画块外时。
//如果当前的动画块是最外层的动画块，当应用程序返回到循环运行时开始动画块。
//动画在一个独立的线程中所有应用程序不会中断。使用这个方法，多个动画可以被实现。
//查看setAnimationBeginsFromCurrentState:来了解如果开始一个动画当另外一个动画在播放的时候。
+ (void)commitAnimations;                                                 // starts up any animations when the top level animation is commited

// no getters. if called outside animation block, these setters have no effect。不getter,如果调用外部动画块，这些setter就没有效果。.
//设置动画消息的代理。
+ (void)setAnimationDelegate:(nullable id)delegate;                          // default = nil
//动画将要开始时调用选择器选择的方法
+ (void)setAnimationWillStartSelector:(nullable SEL)selector;                // default = NULL. -animationWillStart:(NSString *)animationID context:(void *)context
//动画结束后调用选择器选择的方法
+ (void)setAnimationDidStopSelector:(nullable SEL)selector;                  // default = NULL. -animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
//设置动画的持续时间
+ (void)setAnimationDuration:(NSTimeInterval)duration;              // default = 0.2
//在动画块中设置动画的延迟属性（以秒为单位）
+ (void)setAnimationDelay:(NSTimeInterval)delay;                    // default = 0.0
//设置动画开始时间
+ (void)setAnimationStartDate:(NSDate *)startDate;                  // default = now ([NSDate date])
//设置动画块中的动画属性变化的曲线。主要是阶段性快慢的变化，比如先快后慢，先慢后快...默认是淡入淡出
//动画曲线是动画运行过程中相对的速度。如果在动画块外调用这个方法将会无效
+ (void)setAnimationCurve:(UIViewAnimationCurve)curve;              // default = UIViewAnimationCurveEaseInOut
//设置动画重复的次数
+ (void)setAnimationRepeatCount:(float)repeatCount;                 // default = 0.0.  May be fractional
//设置动画是否自动重复播放
//参数repeatAutoreverses，如果动画自动重复就是YES否则NO。默认是NO
//使用setAnimationRepeatCount:方法来指定动画重复次数。如果重复次数为0将没有任何效果。
+ (void)setAnimationRepeatAutoreverses:(BOOL)repeatAutoreverses;    // default = NO. used if repeat count is non-zero
//设置动画从当前状态开始播放。
//参数fromCurrentState，如果动画需要从他们当前状态开始播放是YES。否则为NO。默认是NO
//如果设置为YES那么当动画在运行过程中，当前视图的位置将会作为新的动画的开始状态。如果设置为NO，当前动画结束前新动画将使用视图最后状态的位置作为开始状态。
+ (void)setAnimationBeginsFromCurrentState:(BOOL)fromCurrentState;  // default = NO. If YES, the current view position is always used for new animations -- allowing animations to "pile up" on each other. Otherwise, the last end state is used for the animation (the default)默认= NO。如果是的话，当前的视图位置总是被用于新的动画——允许动画在彼此之间“堆积”。否则，最后一个结束状态用于动画(默认)。

//设置动画类型
//参数transition，把一个过渡动画效果应用到视图中。
//参数view，需要过渡的视图对象。
//参数cache，如果是YES，那么在开始和结束图片视图渲染一次并在动画中创建帧，否则视图将会在每一帧都渲染。例如缓存，你不需要在视图转变中不停的更新，你只需要等到转换完成再去更新视图。
+ (void)setAnimationTransition:(UIViewAnimationTransition)transition forView:(UIView *)view cache:(BOOL)cache;  // current limitation - only one per begin/commit block

//设置是否激活动画
+ (void)setAnimationsEnabled:(BOOL)enabled;                         // ignore any attribute changes while set.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) BOOL areAnimationsEnabled;
#else
//返回一个布尔值表示动画是否结束。如果动画结束返回YES，否则NO。
+ (BOOL)areAnimationsEnabled;
#endif
//可以强制一些动作不使用动画
//它是一个简单的封装，先检查动画当前是否启用，然后禁止动画，执行块语句，最后重新启用动画。一个需要说明的地方是，它并不会阻塞基于CoreAnimation的动画。
+ (void)performWithoutAnimation:(void (NS_NOESCAPE ^)(void))actionsWithoutAnimation NS_AVAILABLE_IOS(7_0);

#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) NSTimeInterval inheritedAnimationDuration NS_AVAILABLE_IOS(9_0);
#else
+ (NSTimeInterval)inheritedAnimationDuration NS_AVAILABLE_IOS(9_0);
#endif

@end

@interface UIView(UIViewAnimationWithBlocks)
//duration动画时间，delay动画执行前的等待时间，options 动画方式
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);
//+设置视图切换时的动画，duration动画执行时间，动画执行的Block,在动画结束后执行回调
+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0); // delay = 0.0, options = 0
//设置视图动画
+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations NS_AVAILABLE_IOS(4_0); // delay = 0.0, options = 0, completion = NULL

/* Performs `animations` using a timing curve described by the motion of a spring. When `dampingRatio` is 1, the animation will smoothly decelerate to its final model values without oscillating. Damping ratios less than 1 will oscillate more and more before coming to a complete stop. You can use the initial spring velocity to specify how fast the object at the end of the simulated spring was moving before it was attached. It's a unit coordinate system, where 1 is defined as travelling the total animation distance in a second. So if you're changing an object's position by 200pt in this animation, and you want the animation to behave as if the object was moving at 100pt/s before the animation started, you'd pass 0.5. You'll typically want to pass 0 for the velocity. 
用弹簧的运动描述的时间曲线来执行动画。当dampingRatio为1时，动画会平稳地减速到最终的模型值，而不会震荡。小于1的阻尼比在到达完全停止之前会振荡得越来越多。您可以使用初始的spring velocity来指定模拟弹簧末端的对象在加载之前移动的速度。它是一个单位坐标系统，其中1被定义为在一秒内移动整个动画距离。如果你在动画中改变一个物体的位置，你想让动画在动画开始前移动到100pts/s，你就会超过0。5。你通常会想要传递速度的0
 */
//弹簧动画,在原来的基础上又增加了两个参数
//dampingRatio：这个参数是设置弹簧的阻尼比例,实际指弹簧动画的摩擦力大小。值的范围是0.0~1.0。当阻尼大小越小代表阻力越小，反之则阻力越大，阻力越小弹簧动画的幅度就越大，越大弹簧幅度就越小，与现实中弹簧拉伸的道理是一样的。
//velocity：指弹簧的变化的速度。速度越大，变化越快。
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay usingSpringWithDamping:(CGFloat)dampingRatio initialSpringVelocity:(CGFloat)velocity options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);
// 为指定的容器视图创建转换动画
+ (void)transitionWithView:(UIView *)view duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);
// 使用给定的参数在指定视图之间创建转换动画
+ (void)transitionFromView:(UIView *)fromView toView:(UIView *)toView duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0); // toView added to fromView.superview, fromView removed from its superview

/* Performs the requested system-provided animation on one or more views. Specify addtional animations in the parallelAnimations block. These additional animations will run alongside the system animation with the same timing and duration that the system animation defines/inherits. Additional animations should not modify properties of the view on which the system animation is being performed. Not all system animations honor all available options.
 在一个或多个视图上执行所请求的系统提供的动画。在并行动画块中指定添加动画。这些额外的动画将在系统动画与系统动画定义/继承的时间和持续时间一起运行。额外的动画不应该修改系统动画正在执行的视图的属性。并不是所有的系统动画都能尊重所有可用的选项
 */
//在一组视图上执行指定的系统动画，并可以并行自定义的动画
//其中parallelAnimations就是与系统动画并行的自定义动画(删除视图动画)
+ (void)performSystemAnimation:(UISystemAnimation)animation onViews:(NSArray<__kindof UIView *> *)views options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))parallelAnimations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

@end
#park mark - UIView+关键帧动画
@interface UIView (UIViewKeyframeAnimations)
//为当前视图创建一个可以用于设置基本关键帧动画的block对象，从IOS7开始使用
//这个方法可以与下个方法结合使用
+ (void)animateKeyframesWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewKeyframeAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

//指定一个关键帧的单个帧的时间和动画，从IOS7开始使用
//第一个frameStartTime其实是个倍数从0到1，假设一个动画持续的时间是2秒
//设置frameStartTime为0.5，那么后面设置的动画，将会在整体动画执行1秒后开始执行
//第二个参数frameDuration同第一个，是指动画持续时间
//第三个是一个block对象，里面就是你设置的所要执行的动画，无参数和返回值
+ (void)addKeyframeWithRelativeStartTime:(double)frameStartTime relativeDuration:(double)frameDuration animations:(void (^)(void))animations NS_AVAILABLE_IOS(7_0); // start time and duration are values between 0.0 and 1.0 specifying time and duration relative to the overall time of the keyframe animation

@end

@interface UIView (UIViewGestureRecognizers)
//当前视图所附加的手势识别器
@property(nullable, nonatomic,copy) NSArray<__kindof UIGestureRecognizer *> *gestureRecognizers NS_AVAILABLE_IOS(3_2);

// 为视图添加一个手势识别器
- (void)addGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer NS_AVAILABLE_IOS(3_2);
// 删除视图上的一个手势识别器
- (void)removeGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer NS_AVAILABLE_IOS(3_2);

// called when the recognizer attempts to transition out of UIGestureRecognizerStatePossible if a touch hit-tested to this view will be cancelled as a result of gesture recognition
// returns YES by default. return NO to cause the gesture recognizer to transition to UIGestureRecognizerStateFailed
// subclasses may override to prevent recognition of particular gestures. for example, UISlider prevents swipes parallel to the slider that start in the thumb当识别视图离开uigesturerecognizerstatepossible如果碰撞测试这一观点会由于手势识别取消，默认返回yes。还没有使手势识别过渡到uigesturerecognizerstatefailed，子类可以覆盖以防止对特定手势的识别。例如，防止滑动滑块UIslider转平行，拇指开始
//一个手势识别器开始的回调
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer NS_AVAILABLE_IOS(6_0);

@end

@interface UIView (UIViewMotionEffects)

/*! Begins applying `effect` to the receiver. The effect's emitted keyPath/value pairs will be
 applied to the view's presentation layer.
 
 Animates the transition to the motion effect's values using the present UIView animation
 context. */
//开始向视图中添加运动效果
- (void)addMotionEffect:(UIMotionEffect *)effect NS_AVAILABLE_IOS(7_0);

/*! Stops applying `effect` to the receiver. Any affected presentation values will animate to
 their post-removal values using the present UIView animation context. */
// 删除视图中的运动效果
- (void)removeMotionEffect:(UIMotionEffect *)effect NS_AVAILABLE_IOS(7_0);
//当前视图所有的运动效果
@property (copy, nonatomic) NSArray<__kindof UIMotionEffect *> *motionEffects NS_AVAILABLE_IOS(7_0);

@end


//
// UIView Constraint-based Layout Support
//

typedef NS_ENUM(NSInteger, UILayoutConstraintAxis) {
    UILayoutConstraintAxisHorizontal = 0,//以水平线为中心
    UILayoutConstraintAxisVertical = 1 //以垂直线为中心
};

// Installing Constraints

/* A constraint is typically installed on the closest common ancestor of the views involved in the constraint.
 It is required that a constraint be installed on _a_ common ancestor of every view involved.  The numbers in a constraint are interpreted in the coordinate system of the view it is installed on.  A view is considered to be an ancestor of itself.
 */
@interface UIView (UIConstraintBasedLayoutInstallingConstraints)//<将来会废弃>

// 视图所持有的所有约束
@property(nonatomic,readonly) NSArray<__kindof NSLayoutConstraint *> *constraints NS_AVAILABLE_IOS(6_0);
// 添加一个约束
- (void)addConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead, set NSLayoutConstraint's active property to YES.
// 添加多个约束
- (void)addConstraints:(NSArray<__kindof NSLayoutConstraint *> *)constraints NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead use +[NSLayoutConstraint activateConstraints:].
// 移除视图上指定的约束
- (void)removeConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead set NSLayoutConstraint's active property to NO.
// 移除指定的一组约束
- (void)removeConstraints:(NSArray<__kindof NSLayoutConstraint *> *)constraints NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead use +[NSLayoutConstraint deactivateConstraints:].
@end

// Core Layout Methods

/* To render a window, the following passes will occur, if necessary.
 
 update constraints
 layout
 display
 
 Please see the conceptual documentation for a discussion of these methods.
 */

@interface UIView (UIConstraintBasedLayoutCoreMethods)
// 更新视图和其子视图的约束
- (void)updateConstraintsIfNeeded NS_AVAILABLE_IOS(6_0); // Updates the constraints from the bottom up for the view hierarchy rooted at the receiver. UIWindow's implementation creates a layout engine if necessary first.从底部向上更新来自于接收方的视图层次结构的约束。如果需要的话，UIWindow的实现会创建一个布局引擎
// 为视图更新约束
- (void)updateConstraints NS_AVAILABLE_IOS(6_0) NS_REQUIRES_SUPER; // 在约束更新过程中，重写这个以调整您的特殊约束。Override this to adjust your special constraints during a constraints update pass
// 视图的约束是否需要更新
- (BOOL)needsUpdateConstraints NS_AVAILABLE_IOS(6_0);
// 设置视图的约束需要更新
- (void)setNeedsUpdateConstraints NS_AVAILABLE_IOS(6_0);
@end

// Compatibility and Adoption

@interface UIView (UIConstraintBasedCompatibility)

/* By default, the autoresizing mask on a view gives rise to constraints that fully determine
 the view's position. This allows the auto layout system to track the frames of views whose
 layout is controlled manually (through -setFrame:, for example).
 When you elect to position the view using auto layout by adding your own constraints,
 you must set this property to NO. IB will do this for you。如果你定义的view想用autolayout，就将translatesAutoresizingMaskIntoConstraints设为NO，如果你使用的不是autolayout，就将translatesAutoresizingMaskIntoConstraints设为YES,当通过添加自己的约束时，选择使用自动布局来定位视图，您必须将此属性设置为“否”，IB将为您执行此操作。(masory里已设置self.translatesAutoresizingMaskIntoConstraints = NO;)
 */
// 是否自动尺寸转换为自动布局
@property(nonatomic) BOOL translatesAutoresizingMaskIntoConstraints NS_AVAILABLE_IOS(6_0); // Default YES

/* constraint-based layout engages lazily when someone tries to use it (e.g., adds a constraint to a view).  If you do all of your constraint set up in -updateConstraints, you might never even receive updateConstraints if no one makes a constraint.  To fix this chicken and egg problem, override this method to return YES if your view needs the window to use constraint-based layout.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
// 视图是否依赖于基础自动布局的约束
@property(class, nonatomic, readonly) BOOL requiresConstraintBasedLayout NS_AVAILABLE_IOS(6_0);
#else
+ (BOOL)requiresConstraintBasedLayout NS_AVAILABLE_IOS(6_0);
#endif

@end

// Separation of Concerns

@interface UIView (UIConstraintBasedLayoutLayering)

/* Constraints do not actually relate the frames of the views, rather they relate the "alignment rects" of views.  This is the same as the frame unless overridden by a subclass of UIView.  Alignment rects are the same as the "layout rects" shown in Interface Builder 3.  Typically the alignment rect of a view is what the end user would think of as the bounding rect around a control, omitting ornamentation like shadows and engraving lines.  The edges of the alignment rect are what is interesting to align, not the shadows and such.
 */

/* These two methods should be inverses of each other.  UIKit will call both as part of layout computation.
 They may be overridden to provide arbitrary transforms between frame and alignment rect, though the two methods must be inverses of each other.
 However, the default implementation uses -alignmentRectInsets, so just override that if it's applicable.  It's easier to get right.
 A view that displayed an image with some ornament would typically override these, because the ornamental part of an image would scale up with the size of the frame.
 Set the NSUserDefault UIViewShowAlignmentRects to YES to see alignment rects drawn.
 */
// 返回给定框架的视图的对齐矩阵
- (CGRect)alignmentRectForFrame:(CGRect)frame NS_AVAILABLE_IOS(6_0);
// 返回给定对齐矩形的视图的frame
- (CGRect)frameForAlignmentRect:(CGRect)alignmentRect NS_AVAILABLE_IOS(6_0);

/* override this if the alignment rect is obtained from the frame by insetting each edge by a fixed amount.  This is only called by alignmentRectForFrame: and frameForAlignmentRect:.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
// 返回从视图的frame上定义的对齐矩阵的边框
@property(nonatomic, readonly) UIEdgeInsets alignmentRectInsets NS_AVAILABLE_IOS(6_0);
#else
- (UIEdgeInsets)alignmentRectInsets NS_AVAILABLE_IOS(6_0);
#endif

// 返回满足基线约束条件的视图
- (UIView *)viewForBaselineLayout NS_DEPRECATED_IOS(6_0, 9_0, "Override -viewForFirstBaselineLayout or -viewForLastBaselineLayout as appropriate, instead") __TVOS_PROHIBITED;

/* -viewForFirstBaselineLayout is called by the constraints system when interpreting
 the firstBaseline attribute for a view.
 For complex custom UIView subclasses, override this method to return the text-based
 (i.e., UILabel or non-scrollable UITextView) descendant of the receiver whose first baseline
 is appropriate for alignment.
 UIView's implementation returns [self viewForLastBaselineLayout], so if the same
 descendant is appropriate for both first- and last-baseline layout you may override
 just -viewForLastBaselineLayout.
 */
// 返回用于满足第一基线约束的视图
@property(readonly,strong) UIView *viewForFirstBaselineLayout NS_AVAILABLE_IOS(9_0);

/* -viewForLastBaselineLayout is called by the constraints system when interpreting
 the lastBaseline attribute for a view.
 For complex custom UIView subclasses, override this method to return the text-based
 (i.e., UILabel or non-scrollable UITextView) descendant of the receiver whose last baseline
 is appropriate for alignment.
 UIView's implementation returns self.
 */
// 返回用于满足上次基线约束的视图
@property(readonly,strong) UIView *viewForLastBaselineLayout NS_AVAILABLE_IOS(9_0);

/* Override this method to tell the layout system that there is something it doesn't natively understand in this view, and this is how large it intrinsically is.  A typical example would be a single line text field.  The layout system does not understand text - it must just be told that there's something in the view, and that that something will take a certain amount of space if not clipped.
 
 In response, UIKit will set up constraints that specify (1) that the opaque content should not be compressed or clipped, (2) that the view prefers to hug tightly to its content.
 
 A user of a view may need to specify the priority of these constraints.  For example, by default, a push button
 -strongly wants to hug its content in the vertical direction (buttons really ought to be their natural height)
 -weakly hugs its content horizontally (extra side padding between the title and the edge of the bezel is acceptable)
 -strongly resists compressing or clipping content in both directions.
 
 However, you might have a case where you'd prefer to show all the available buttons with truncated text rather than losing some of the buttons. The truncation might only happen in portrait orientation but not in landscape, for example. In that case you'd want to setContentCompressionResistancePriority:forAxis: to (say) UILayoutPriorityDefaultLow for the horizontal axis.
 
 The default 'strong' and 'weak' priorities referred to above are UILayoutPriorityDefaultHigh and UILayoutPriorityDefaultLow.
 
 Note that not all views have an intrinsicContentSize.  UIView's default implementation is to return (UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric).  The _intrinsic_ content size is concerned only with data that is in the view itself, not in other views. Remember that you can also set constant width or height constraints on any view, and you don't need to override instrinsicContentSize if these dimensions won't be changing with changing view content.
 */
UIKIT_EXTERN const CGFloat UIViewNoIntrinsicMetric NS_AVAILABLE_IOS(6_0); // -1
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) CGSize intrinsicContentSize NS_AVAILABLE_IOS(6_0);
#else
// 返回接收对象的原本大小
- (CGSize)intrinsicContentSize NS_AVAILABLE_IOS(6_0);
#endif
// 废除视图原本内容的size
- (void)invalidateIntrinsicContentSize NS_AVAILABLE_IOS(6_0); // call this when something changes that affects the intrinsicContentSize.  Otherwise UIKit won't notice that it changed.
// 设置当视图要变大时，视图的压缩改变方式，返回一个优先权（确定view有多大的优先级阻止自己变大）
- (UILayoutPriority)contentHuggingPriorityForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
// 设置放先权
- (void)setContentHuggingPriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);

// 设置当视图要变小时，视图的压缩改变方式，是水平缩小还是垂直缩小，并返回一个优先权（确定有多大的优先级阻止自己变小）
- (UILayoutPriority)contentCompressionResistancePriorityForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
// 设置优先权
- (void)setContentCompressionResistancePriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
@end

// Size To Fit

UIKIT_EXTERN const CGSize UILayoutFittingCompressedSize NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN const CGSize UILayoutFittingExpandedSize NS_AVAILABLE_IOS(6_0);

@interface UIView (UIConstraintBasedLayoutFittingSize)
/* The size fitting most closely to targetSize in which the receiver's subtree can be laid out while optimally satisfying the constraints. If you want the smallest possible size, pass UILayoutFittingCompressedSize; for the largest possible size, pass UILayoutFittingExpandedSize.
 Also see the comment for UILayoutPriorityFittingSizeLevel.
 */
// 返回满足持有约束的视图的size 例如获取xib的cell按照约束(约束要完整到上下左右)需要的size
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize NS_AVAILABLE_IOS(6_0); // Equivalent to sending -systemLayoutSizeFittingSize:withHorizontalFittingPriority:verticalFittingPriority: with UILayoutPriorityFittingSizeLevel for both priorities.
// 返回满足它所包含的约束的视图的大小
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize withHorizontalFittingPriority:(UILayoutPriority)horizontalFittingPriority verticalFittingPriority:(UILayoutPriority)verticalFittingPriority NS_AVAILABLE_IOS(8_0);
@end

@interface UIView (UILayoutGuideSupport)

/* UILayoutGuide objects owned by the receiver.
 */
// 此视图拥有布局向导对象的数组
@property(nonatomic,readonly,copy) NSArray<__kindof UILayoutGuide *> *layoutGuides NS_AVAILABLE_IOS(9_0);

/* Adds layoutGuide to the receiver, passing the receiver in -setOwningView: to layoutGuide.
 */
// 向视图中添加布局向导
- (void)addLayoutGuide:(UILayoutGuide *)layoutGuide NS_AVAILABLE_IOS(9_0);

/* Removes layoutGuide from the receiver, passing nil in -setOwningView: to layoutGuide.
 */
// 移除视图中的布局向导
- (void)removeLayoutGuide:(UILayoutGuide *)layoutGuide NS_AVAILABLE_IOS(9_0);
@end

@class NSLayoutXAxisAnchor,NSLayoutYAxisAnchor,NSLayoutDimension;
@interface UIView (UIViewLayoutConstraintCreation)
/* Constraint creation conveniences. See NSLayoutAnchor.h for details.
 */
@property(readonly, strong) NSLayoutXAxisAnchor *leadingAnchor NS_AVAILABLE_IOS(9_0);//布局视图的前缘框的布局锚点
@property(readonly, strong) NSLayoutXAxisAnchor *trailingAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的后缘边框的布局锚点
@property(readonly, strong) NSLayoutXAxisAnchor *leftAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的左边框的布局锚点
@property(readonly, strong) NSLayoutXAxisAnchor *rightAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的右边框的布局锚点
@property(readonly, strong) NSLayoutYAxisAnchor *topAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的顶边框的布局锚点
@property(readonly, strong) NSLayoutYAxisAnchor *bottomAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的底边框的布局锚点
@property(readonly, strong) NSLayoutDimension *widthAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的宽度
@property(readonly, strong) NSLayoutDimension *heightAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的高度
@property(readonly, strong) NSLayoutXAxisAnchor *centerXAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的水平中心轴
@property(readonly, strong) NSLayoutYAxisAnchor *centerYAnchor NS_AVAILABLE_IOS(9_0);// 布局视图的垂直中心轴
@property(readonly, strong) NSLayoutYAxisAnchor *firstBaselineAnchor NS_AVAILABLE_IOS(9_0);// 一个代表对视图中的文本的最高线基线布置锚
@property(readonly, strong) NSLayoutYAxisAnchor *lastBaselineAnchor NS_AVAILABLE_IOS(9_0);// 一个代表对视图中的文本的最低线基线布置锚


@end

// Debugging

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.
 */
@interface UIView (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).这将返回影响接收者当前位置的所有约束的列表。约束不一定涉及到接收者，它们可能间接地影响框架。通过UILayoutConstraintAxisHorizontal约束的影响(自我中心)。x和CGRectGetWidth([自我界限]),和UILayoutConstraintAxisVertical约束影响(自我中心)。y和CGRectGetHeight([self bounds])。
 */
// 返回影响一个给定轴视图布局的约束数组
- (NSArray<__kindof NSLayoutConstraint *> *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 -exerciseAmbiguousLayout does more.  It randomly changes the view layout to a different valid layout.  Making the UI jump back and forth can be helpful for figuring out where you're missing a constraint.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
// 视图的位置是否不完全指定
@property(nonatomic, readonly) BOOL hasAmbiguousLayout NS_AVAILABLE_IOS(6_0);
#else
- (BOOL)hasAmbiguousLayout NS_AVAILABLE_IOS(6_0);
#endif

// 在不同的有效值之间用一个模糊的布局随机改变视图的frame
- (void)exerciseAmbiguityInLayout NS_AVAILABLE_IOS(6_0);
@end

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.
 */
@interface UILayoutGuide (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).
 */
//返回对给定轴影响视图布局的约束
- (NSArray<__kindof NSLayoutConstraint *> *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(10_0);

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
// 确定影响视图布局的约束是否完全指定视图的位置
@property(nonatomic, readonly) BOOL hasAmbiguousLayout NS_AVAILABLE_IOS(10_0);
#else
- (BOOL)hasAmbiguousLayout NS_AVAILABLE_IOS(10_0);
#endif
@end

@interface UIView (UIStateRestoration)
//该标示符决定该视图是否支持恢复状态，其实也只是个标示符而已
//个人觉得就相当于配置表视图每个单元格时使用的标示符一样，可以直接在内存中重用，提高了性能
//还有一点需注意，不应该简单的定义这个标示符，因为其所属的view controller ，还有view controller的
//所有 父view controllers都必须有一个恢复标识符
@property (nullable, nonatomic, copy) NSString *restorationIdentifier NS_AVAILABLE_IOS(6_0);
// 编码视图的状态信息
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
// 解码一个视图状态信息
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
@end

@interface UIView (UISnapshotting)
/*
 * When requesting a snapshot, 'afterUpdates' defines whether the snapshot is representative of what's currently on screen or if you wish to include any recent changes before taking the snapshot.
 
 If called during layout from a committing transaction, snapshots occurring after the screen updates will include all changes made, regardless of when the snapshot is taken and the changes are made. For example:
 
 - (void)layoutSubviews {
 UIView *snapshot = [self snapshotViewAfterScreenUpdates:YES];
 self.alpha = 0.0;
 }
 
 The snapshot will appear to be empty since the change in alpha will be captured by the snapshot. If you need to animate the view during layout, animate the snapshot instead.
 
 * Creating snapshots from existing snapshots (as a method to duplicate, crop or create a resizable variant) is supported. In cases where many snapshots are needed, creating a snapshot from a common superview and making subsequent snapshots from it can be more performant. Please keep in mind that if 'afterUpdates' is YES, the original snapshot is committed and any changes made to it, not the view originally snapshotted, will be included.
 */
/*
 *请求快照时，'afterUpdates'定义快照是否代表屏幕上正在显示的内容，或者如果您希望在拍摄快照之前包含任何最新更改。
 
 如果在提交事务的布局期间调用，则在屏幕更新后发生的快照将包括所做的所有更改，而不管何时拍摄快照并进行更改。例如：
 
  - （void）layoutSubviews {
     UIView * snapshot = [self snapshotViewAfterScreenUpdates：YES];
     self.alpha = 0.0;
     }
 
 快照将显示为空，因为快照会捕获alpha中的更改。如果您需要在布局过程中为视图设置动画，请改为使快照动画化。
 
 *支持从现有快照创建快照（作为复制，裁剪或创建可调整大小的变体的方法）。在需要许多快照的情况下，从公共超级视图创建快照并从中创建后续快照可以更高效。请记住，如果'afterUpdates'为YES，则会提交原始快照，并且会对其进行任何更改，而不是最初快照的视图。
 */

//根据当前视图的内容返回快照视图
- (nullable UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
// 返回一个基于当前视图指定内容的快照视图，可插入;缩放一个view默认是从中心点进行缩放的
- (nullable UIView *)resizableSnapshotViewFromRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates withCapInsets:(UIEdgeInsets)capInsets NS_AVAILABLE_IOS(7_0);  // Resizable snapshots will default to stretching the center
// Use this method to render a snapshot of the view hierarchy into the current context. Returns NO if the snapshot is missing image data, YES if the snapshot is complete. Calling this method from layoutSubviews while the current transaction is committing will capture what is currently displayed regardless if afterUpdates is YES.
// 呈现一个快照的完整视图层次可见屏幕为当前上下文
- (BOOL)drawViewHierarchyInRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
@end

NS_ASSUME_NONNULL_END

