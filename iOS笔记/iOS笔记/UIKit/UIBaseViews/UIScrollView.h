//
//  UIScrollView.h
//  UIKit
//
//  Copyright (c) 2007-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIRefreshControl.h>

NS_ASSUME_NONNULL_BEGIN

//滚动条样式
typedef NS_ENUM(NSInteger, UIScrollViewIndicatorStyle) {
    UIScrollViewIndicatorStyleDefault,     // black with white border. good against any background
    UIScrollViewIndicatorStyleBlack,       // 黑色风格 black only. smaller. good against a white background
    UIScrollViewIndicatorStyleWhite        // 白色风格 white only. smaller. good against a black background
};
//设置键盘消失的模式
typedef NS_ENUM(NSInteger, UIScrollViewKeyboardDismissMode) {
    UIScrollViewKeyboardDismissModeNone,
    UIScrollViewKeyboardDismissModeOnDrag,      // 手指滑动视图键盘就会消失
    
    //手指滑动视图后可以与键盘交互，上下滑动键盘会跟随手指上下移动;必须要拖拽到键盘才可以关闭键盘，很少使用
    UIScrollViewKeyboardDismissModeInteractive, // the keyboard follows the dragging touch off screen, and may be pulled upward again to cancel the dismiss 键盘跟随拖动触摸屏幕，并且可能再次向上拉取消消失
} NS_ENUM_AVAILABLE_IOS(7_0);

//滚动条展示模式
typedef NS_ENUM(NSInteger, UIScrollViewIndexDisplayMode) {
    UIScrollViewIndexDisplayModeAutomatic,    // the index will show or hide automatically as needed  索引将根据需要自动显示或隐藏
    UIScrollViewIndexDisplayModeAlwaysHidden, // the index will never be displayed 索引将永远不会显示出来
} API_AVAILABLE(tvos(10.2));

//ScrollerView自动偏移机制（11+）
typedef NS_ENUM(NSInteger, UIScrollViewContentInsetAdjustmentBehavior) {
    
    UIScrollViewContentInsetAdjustmentAutomatic, // Similar to .scrollableAxes, but for backward compatibility will also adjust the top & bottom contentInset when the scroll view is owned by a view controller with automaticallyAdjustsScrollViewInsets = YES inside a navigation controller, regardless of whether the scroll view is scrollable
    UIScrollViewContentInsetAdjustmentScrollableAxes, // Edges for scrollable axes are adjusted (i.e., contentSize.width/height > frame.size.width/height or alwaysBounceHorizontal/Vertical = YES)
    UIScrollViewContentInsetAdjustmentNever, // contentInset is not adjusted
    UIScrollViewContentInsetAdjustmentAlways, // contentInset is always adjusted by the scroll view's safeAreaInsets
} API_AVAILABLE(ios(11.0),tvos(11.0));

//1.UIScrollViewContentInsetAdjustmentAutomatic：如果scrollview在一个automaticallyAdjustsScrollViewContentInset = YES的controller上，并且这个Controller包含在一个navigation controller中，这种情况下会设置在top & bottom上 adjustedContentInset = safeAreaInset + contentInset不管是否滚动。其他情况下与UIScrollViewContentInsetAdjustmentScrollableAxes相同
//2.UIScrollViewContentInsetAdjustmentScrollableAxes: 在可滚动方向上adjustedContentInset = safeAreaInset + contentInset，在不可滚动方向上adjustedContentInset = contentInset；依赖于scrollEnabled和alwaysBounceHorizontal / vertical = YES，scrollEnabled默认为yes，所以大多数情况下，计算方式还是adjustedContentInset = safeAreaInset + contentInset
//3.UIScrollViewContentInsetAdjustmentNever: adjustedContentInset = contentInset
//4.UIScrollViewContentInsetAdjustmentAlways: adjustedContentInset = safeAreaInset + contentInset
//当contentInsetAdjustmentBehavior设置为UIScrollViewContentInsetAdjustmentNever的时候，adjustContentInset值不受SafeAreaInset值的影响。

//减速速率
UIKIT_EXTERN const CGFloat UIScrollViewDecelerationRateNormal NS_AVAILABLE_IOS(3_0);  //0.998000
UIKIT_EXTERN const CGFloat UIScrollViewDecelerationRateFast NS_AVAILABLE_IOS(3_0);    //0.9999

@class UIEvent, UIImageView, UIPanGestureRecognizer, UIPinchGestureRecognizer; //点击、长按手势
@protocol UIScrollViewDelegate;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIScrollView : UIView <NSCoding>

@property(nonatomic)         CGPoint                      contentOffset;                  // default CGPointZero 滚动内容的偏移量
@property(nonatomic)         CGSize                       contentSize;                    // default CGSizeZero  滚动内容区域大小
@property(nonatomic)         UIEdgeInsets                 contentInset;                   // default UIEdgeInsetsZero. add additional scroll area around content在内容周围添加额外的滚动区域 内容距离上下左右间距

/* When contentInsetAdjustmentBehavior allows, UIScrollView may incorporate
 its safeAreaInsets into the adjustedContentInset.当contentInsetAdjustmentBehavior允许,UIScrollView可能合并它的安全设置进入了可调的内容设置。
在iOS11上，新增adjustedContentInset替代contentInset设置内容偏移*/
@property(nonatomic, readonly) UIEdgeInsets adjustedContentInset API_AVAILABLE(ios(11.0),tvos(11.0));

/* Also see -scrollViewDidChangeAdjustedContentInset: in the UIScrollViewDelegate protocol.也可查看iOS11UIScrollViewDelegate新增的该协议。
 */
- (void)adjustedContentInsetDidChange API_AVAILABLE(ios(11.0),tvos(11.0)) NS_REQUIRES_SUPER;

/* Configure the behavior of adjustedContentInset.
 Default is UIScrollViewContentInsetAdjustmentAutomatic.
 配置可调的contentinset的机制（11+）
 */
@property(nonatomic) UIScrollViewContentInsetAdjustmentBehavior contentInsetAdjustmentBehavior API_AVAILABLE(ios(11.0),tvos(11.0));

/* contentLayoutGuide anchors (e.g., contentLayoutGuide.centerXAnchor, etc.) refer to
 the untranslated content area of the scroll view.contentLayoutGuide
 */
@property(nonatomic,readonly,strong) UILayoutGuide *contentLayoutGuide API_AVAILABLE(ios(11.0),tvos(11.0));

/* frameLayoutGuide anchors (e.g., frameLayoutGuide.centerXAnchor) refer to
 the untransformed frame of the scroll view.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *frameLayoutGuide API_AVAILABLE(ios(11.0),tvos(11.0));

@property(nullable,nonatomic,weak) id<UIScrollViewDelegate>        delegate;                       // default nil. weak reference
//设置是否锁定某个方法滚动，默认为NO，当设置为YES时，你的滚动视图只能同一时间在一个方向上滚动，但是当你从对角线拖动时，是时刻在水平和竖直方向同时滚动的
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;         // default NO. if YES, try to lock vertical or horizontal scrolling while dragging
//滑到边缘回弹效果，默认yes，
@property(nonatomic)         BOOL                         bounces;                        // default YES. if YES, bounces past edge of content and back again
//垂直方向的回弹效果,默认NO，内容不足时滑不动;设置YES始终允许垂直弹
@property(nonatomic)         BOOL                         alwaysBounceVertical;           // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag vertically
//水平方向的回弹效果,默认NO，内容不足时滑不动;设置YES始终允许水平弹
@property(nonatomic)         BOOL                         alwaysBounceHorizontal;         // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag horizontally
//以自身宽度做分页效果,默认NO；利用代理自定义“分页”效果需要设置为NO，不然会被系统方法覆盖
@property(nonatomic,getter=isPagingEnabled) BOOL          pagingEnabled __TVOS_PROHIBITED;// default NO. if YES, stop on multiples of view bounds
//是否可以滚动，设置NO的话事件处理机制采用touch
@property(nonatomic,getter=isScrollEnabled) BOOL          scrollEnabled;                  // default YES. turn off any dragging temporarily
//是否展示水平滑动条
@property(nonatomic)         BOOL                         showsHorizontalScrollIndicator; // default YES. show indicator while we are tracking. fades out after tracking
//是否展示垂直滑动条
@property(nonatomic)         BOOL                         showsVerticalScrollIndicator;   // default YES. show indicator while we are tracking. fades out after tracking
//设置边距修改滑动条的位置
@property(nonatomic)         UIEdgeInsets                 scrollIndicatorInsets;          // default is UIEdgeInsetsZero. adjust indicators inside of insets
//设置滑动条的样式
@property(nonatomic)         UIScrollViewIndicatorStyle   indicatorStyle;                 // default is UIScrollViewIndicatorStyleDefault

//设置滑动速度
@property(nonatomic)         CGFloat                      decelerationRate NS_AVAILABLE_IOS(3_0);
//滚动条展示模式
@property(nonatomic)         UIScrollViewIndexDisplayMode indexDisplayMode API_AVAILABLE(tvos(10.2));

//设置滚动视图内容的偏移量，可以带动画效果
- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;  // animate at constant velocity to new offset
//设置滚动视图滚动到某个“可见”区域，可以带动画效果
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;         // scroll so rect is just visible (nearest edges). nothing if rect completely visible

//显示一个短暂的滚动指示器-闪一下滚动条
- (void)flashScrollIndicators;             // displays the scroll indicators for a short time. This should be done whenever you bring the scroll view to front.在短时间内显示滚动指示器。当您将滚动视图移到前面时，就应该这样做

/*
 Scrolling with no scroll bars is a bit complex. on touch down, we don't know if the user will want to scroll or track a subview like a control.
 on touch down, we start a timer and also look at any movement. if the time elapses without sufficient change in position, we start sending events to
 the hit view in the content subview. if the user then drags far enough, we switch back to dragging and cancel any tracking in the subview.
 the methods below are called by the scroll view and give subclasses override points to add in custom behaviour.
 you can remove the delay in delivery of touchesBegan:withEvent: to subviews by setting delaysContentTouches to NO.
 
 */
/**-----------scroller滚动机制------------
 从你的手指touch屏幕开始，scrollView开始一个timer，如果：
 1.  150ms内如果你的手指没有任何动作，消息就会传给subView。
 2.  150ms内手指有明显的滑动（一个swipe动作），scrollView就会滚动，消息不会传给subView，这里就是产生问题二的原因。
 3.  150ms内手指没有滑动，scrollView将消息传给subView，但是之后手指开始滑动，scrollView传送touchesCancelled消息给subView，然后开始滚动。
 
 观察下tableView的情况，你先按住一个cell，cell开始高亮，手不要放开，开始滑动，tableView开始滚动，高亮取消。
 delaysContentTouches的作用：
 这个标志默认是YES，使用上面的150ms的timer，如果设置为NO，touch事件立即传递给subView，不会有150ms的等待。
 cancelsTouches的作用：
 这个标准默认为YES，如果设置为NO，这消息一旦传递给subView，这scroll事件不会再发生
 */
//追踪-判断当前用户是否触摸视图内容，返回YES，可能还没有开始拖拽
@property(nonatomic,readonly,getter=isTracking)     BOOL tracking;        // returns YES if user has touched. may not yet have started dragging
//拖拉-判断当前是否是用户拖拽视图内容
@property(nonatomic,readonly,getter=isDragging)     BOOL dragging;        // returns YES if user has started scrolling. this may require some time and or distance to move to initiate dragging 如果用户已经开始滚动，返回YES。这可能需要一些时间和距离来启动拖拽

//判断视图是否开始减速（用户停止拖动但视图仍在滚动:惯性）
@property(nonatomic,readonly,getter=isDecelerating) BOOL decelerating;    // returns YES if user isn't dragging (touch up) but scroll view is still moving 如果用户没有拖拽(触摸)，返回YES，但是滚动视图仍然在移动

//设置视图是否延迟处理触摸事件（会将消息传递给子视图）默认YES
@property(nonatomic) BOOL delaysContentTouches;       // default is YES. if NO, we immediately call -touchesShouldBegin:withEvent:inContentView:. this has no effect on presses 默认是YES的。如果NO,我们立刻调用- touchesShouldBegin:withEvent:inContentView:.这对按压没有影响

//设置是否给子视图传递取消动作的消息（默认设置为YES，当scrollView触发事件的时候，其子视图不能触发，如果设置为NO，则子视图会继续触发事件）
@property(nonatomic) BOOL canCancelContentTouches;    // default is YES. if NO, then once we start tracking, we don't try to drag if the touch moves. this has no effect on presses 默认是YES。 如果否，那么一旦我们开始跟踪（触摸试图），如果触摸移动，我们不会尝试拖动。 这对按压没有影响

// override points for subclasses to control delivery of touch events to subviews of the scroll view
// called before touches are delivered to a subview of the scroll view. if it returns NO the touches will not be delivered to the subview
// this has no effect on presses
// default returns YES
//覆盖子类的点来控制将触摸事件传递给滚动视图的子视图
//触发之前调用被传递到滚动视图的子视图。 如果返回NO，则触摸不会被传递到子视图
//这对压力没有影响
//默认返回YES
//重写这两个方法可以控制起子视图的事件响应
- (BOOL)touchesShouldBegin:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event inContentView:(UIView *)view;
// called before scrolling begins if touches have already been delivered to a subview of the scroll view. if it returns NO the touches will continue to be delivered to the subview and scrolling will not occur
// not called if canCancelContentTouches is NO. default returns YES if view isn't a UIControl
// this has no effect on presses
//如果触摸已经传递到滚动视图的子视图，则在滚动开始之前调用。 如果返回NO，则触摸将继续传递给子视图，滚动不会发生
//如果canCancelContentTouches为NO，则不调用。 如果视图不是UIControl，则默认返回YES
//这对压力没有影响
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;

/*
 the following properties and methods are for zooming. as the user tracks with two fingers, we adjust the offset and the scale of the content. When the gesture ends, you should update the content
 as necessary. Note that the gesture can end and a finger could still be down. While the gesture is in progress, we do not send any tracking calls to the subview.
 the delegate must implement both viewForZoomingInScrollView: and scrollViewDidEndZooming:withView:atScale: in order for zooming to work and the max/min zoom scale must be different
 note that we are not scaling the actual scroll view but the 'content view' returned by the delegate. the delegate must return a subview, not the scroll view itself, from viewForZoomingInScrollview:
 以下属性和方法用于缩放。 当用户用两根手指跟踪时，我们调整内容的偏移量和比例。 当手势结束时，您应该更新内容
   有必要的。 请注意，手势可能会结束，手指仍然可能会下降。 手势正在进行中时，我们不会向子视图发送任何跟踪调用。
   委托必须实现viewForZoomingInScrollView：和scrollViewDidEndZooming：withView：atScale：为了使缩放工作，最大/最小缩放比例必须不同
   请注意，我们不是缩放实际的滚动视图，而是由委托返回的“内容视图”。 委托人必须从viewForZoomingInScrollview中返回一个子视图，而不是滚动视图本身：
 */

//设置内容最小缩放比例
@property(nonatomic) CGFloat minimumZoomScale;     // default is 1.0
//设置内容最大缩放比例
@property(nonatomic) CGFloat maximumZoomScale;     // default is 1.0. must be > minimum zoom scale to enable zooming
//设置缩放比例
@property(nonatomic) CGFloat zoomScale NS_AVAILABLE_IOS(3_0);            // default is 1.0
//设置缩放比例，可以带动画效果
- (void)setZoomScale:(CGFloat)scale animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);
//设置缩放显示到某个区域，可以带动画效果
- (void)zoomToRect:(CGRect)rect animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);

//设置是否可以缩放后回弹
@property(nonatomic) BOOL  bouncesZoom;          // default is YES. if set, user can go past min/max zoom while gesturing and the zoom will animate to the min/max value at gesture end 默认是YES。 如果设置，用户可以在手势操作时经过最小/最大缩放，缩放将在手势结束时生成最小/最大值

//获取用户是否正在缩放模式
@property(nonatomic,readonly,getter=isZooming)       BOOL zooming;       // returns YES if user in zoom gesture
//获取是否当前的缩放比例超出设置的峰值
@property(nonatomic,readonly,getter=isZoomBouncing)  BOOL zoomBouncing;  // returns YES if we are in the middle of zooming back to the min/max value 返回YES，如果我们在缩放回到最小值/最大值

// When the user taps the status bar, the scroll view beneath the touch which is closest to the status bar will be scrolled to top, but only if its `scrollsToTop` property is YES, its delegate does not return NO from `-scrollViewShouldScrollToTop:`, and it is not already at the top.
// On iPhone, we execute this gesture only if there's one on-screen scroll view with `scrollsToTop` == YES. If more than one is found, none will be scrolled.
//当用户点击状态栏时，最靠近状态栏的触摸下方的滚动视图将滚动到顶部，但只有当它的'scrollsToTop`属性为YES时，其委托才会从`-scrollViewShouldScrollToTop ：`，而且它不在顶部。
//在iPhone上，我们只有在屏幕上有一个滚动视图“scrollsToTop”== YES时才执行这个手势。 如果找到多个，则不会滚动。
@property(nonatomic) BOOL  scrollsToTop __TVOS_PROHIBITED;          // default is YES.

// Use these accessors to configure the scroll view's built-in gesture recognizers.
// Do not change the gestures' delegates or override the getters for these properties.

// Change `panGestureRecognizer.allowedTouchTypes` to limit scrolling to a particular set of touch types.
//使用这些访问器来配置滚动视图的内置手势识别器。
//不要改变手势的委托或重写这些属性的获取者。

//更改`panGestureRecognizer.allowedTouchTypes`来限制滚动到一组特定的触摸类型
@property(nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer NS_AVAILABLE_IOS(5_0);

// `pinchGestureRecognizer` will return nil when zooming is disabled.当缩放被禁用时，pinchGestureRecognizer将返回nil。
@property(nullable, nonatomic, readonly) UIPinchGestureRecognizer *pinchGestureRecognizer NS_AVAILABLE_IOS(5_0);

// `directionalPressGestureRecognizer` is disabled by default, but can be enabled to perform scrolling in response to up / down / left / right arrow button presses directly, instead of scrolling indirectly in response to focus updates.
//默认是禁用的，但是可以启用滚动来响应上/下/左/右箭头按钮直接按下，而不是间接滚动以响应焦点更新。
@property(nonatomic, readonly) UIGestureRecognizer *directionalPressGestureRecognizer API_DEPRECATED("Configuring the panGestureRecognizer for indirect scrolling automatically supports directional presses now, so this property is no longer useful.", tvos(9.0, 11.0));//为间接滚动配置panGestureRecognizer现在自动支持定向按下，所以这个属性不再有用。

//设置键盘消失的模式
@property(nonatomic) UIScrollViewKeyboardDismissMode keyboardDismissMode NS_AVAILABLE_IOS(7_0); // default is UIScrollViewKeyboardDismissModeNone

//系统下拉刷新控件，不怎么好用（10+）
@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl NS_AVAILABLE_IOS(10_0) __TVOS_PROHIBITED;

@end

@protocol UIScrollViewDelegate<NSObject>

@optional
//只要ScrollerView视图滚动就会调用，实时监测滚动变化
- (void)scrollViewDidScroll:(UIScrollView *)scrollView;                                               // any offset changes
//只要ScrollerView视图缩放就会调用，实时监测缩放变化
- (void)scrollViewDidZoom:(UIScrollView *)scrollView NS_AVAILABLE_IOS(3_2); // any zoom scale changes

// called on start of dragging (may require some time and or distance to move)调用开始拖动(可能需要一些时间和距离来移动)
//手指刚开始拖动-的时候调用
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;

// called on finger up if the user dragged. velocity is in points/millisecond. targetContentOffset may be changed to adjust where the scroll view comes to rest
//这个方法在pagingEnable==YES的时候也会调用,但是pagingEnable的效果会覆盖这个方法的效果，达不到我们想要的“刚好停到指定位置的效果”，所以还是需要注意将pagingEnable设置为NO！
//手指将要离开-的时候调用
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset NS_AVAILABLE_IOS(5_0);

// called on finger up if the user dragged. decelerate is true if it will continue moving afterwards
//手指结束拖拽已经离开-时调用,decelerate=yes它以惯性还会继续运动
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;

//将要减速时调用,由于惯性还要再滑动
- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;   // called on finger up as we are moving
//如果是人为拖拽scrollView导致滚动完毕,才会调用这个方法;结束减速，减速停止时调用
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;      // called when scroll view grinds to a halt
//如果是带动画滚动scrollView导致滚动完毕，才会调用这个方法）eg:setContentOffset/scrollRectVisible:animated:
- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView; // called when setContentOffset/scrollRectVisible:animated: finishes. not called if not animating

//返回缩放的可以子视图view
- (nullable UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;     // return a view that will be scaled. if delegate returns nil, nothing happens,需要设置代理
//开始缩放的时候调用
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view NS_AVAILABLE_IOS(3_2); // called before the scroll view begins zooming its content
//结束缩放的时候调用
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view atScale:(CGFloat)scale; // scale between minimum and maximum. called after any 'bounce' animations缩放比例在最小和最大值之间。

//用户点击状态栏时滚动到顶部，默认YES
//一个视图中，如果有多个 scrollView,只有唯一一个 scrollView 的 scrollsToTop 属性设置为 YES，才支持点击状态栏滚动到顶部
//虽然此属性默认值即为YES不过还要要设置,不然不知道点了状态栏要对那个scrollView进行滚动
- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;   // return a yes if you want to scroll to the top. if not defined, assumes YES，

//用户点击状态栏时滚动到顶部后调用
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;      // called when scrolling animation finished. may be called immediately if already at top

/* Also see -[UIScrollView adjustedContentInsetDidChange]内容自动调节改变完成的代理（11+）
 */
- (void)scrollViewDidChangeAdjustedContentInset:(UIScrollView *)scrollView API_AVAILABLE(ios(11.0), tvos(11.0));

@end


NS_ASSUME_NONNULL_END
