//
//  UIViewController.h
//  UIKit
//
//  Copyright (c) 2007-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h> //基础框架入口
#import <Foundation/NSExtensionRequestHandling.h>
#import <UIKit/UIKitDefines.h> //宏
#import <UIKit/UIApplication.h>
#import <UIKit/UIStateRestoration.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIFocus.h>

/*
  UIViewController is a generic controller base class that manages a view.  It has methods that are called
  when a view appears or disappears.
 
  Subclasses can override -loadView to create their custom view hierarchy, or specify a nib name to be loaded
  automatically.  This class is also a good place for delegate & datasource methods, and other controller
  stuff.
 UIViewController是一个通用的控制器管理视图的基类。当一个视图出现或消失时，它有被调用的方法。
 子类可以重写loadview创建自己的自定义视图层次结构,或指定一个nib名称 自动加载。这个类也是代理和数据源方法以及其他控制器的好地方。
*/

NS_ASSUME_NONNULL_BEGIN

@class UIView;
@class UINavigationItem, UIBarButtonItem, UITabBarItem;
@class UISearchDisplayController;
@class UIPopoverController;
@class UIStoryboard, UIStoryboardSegue, UIStoryboardUnwindSegueSource;
@class UIScrollView;
@protocol UIViewControllerTransitionCoordinator;

typedef NS_ENUM(NSInteger, UIModalTransitionStyle) {
    UIModalTransitionStyleCoverVertical = 0,//从底部滑入,默认
    UIModalTransitionStyleFlipHorizontal __TVOS_PROHIBITED,//水平翻转
    UIModalTransitionStyleCrossDissolve,//交叉溶解
    UIModalTransitionStylePartialCurl NS_ENUM_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED, //翻书效果
};

typedef NS_ENUM(NSInteger, UIModalPresentationStyle) {
  
        //是弹出VC时，VC充满全屏
        UIModalPresentationFullScreen = 0,
        //如果设备横屏，VC的显示方式则从横屏下方开始
        UIModalPresentationPageSheet NS_ENUM_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED,
        //显示都是从底部，宽度和屏幕宽度一样(persent时控制键盘是否可见)
        UIModalPresentationFormSheet NS_ENUM_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED,
        //VC的弹出方式和VC父VC的弹出方式相同
        UIModalPresentationCurrentContext NS_ENUM_AVAILABLE_IOS(3_2),
        UIModalPresentationCustom NS_ENUM_AVAILABLE_IOS(7_0),
        UIModalPresentationOverFullScreen NS_ENUM_AVAILABLE_IOS(8_0),
        UIModalPresentationOverCurrentContext NS_ENUM_AVAILABLE_IOS(8_0),
        UIModalPresentationPopover NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED,
        UIModalPresentationBlurOverFullScreen __TVOS_AVAILABLE(11_0) __IOS_PROHIBITED __WATCHOS_PROHIBITED,
        UIModalPresentationNone NS_ENUM_AVAILABLE_IOS(7_0) = -1,
};

//iOS8之后，加入该协议，UIViewController对这组协议提供了默认的实现，我们自定义ViewConttroller的时候可以重写这些方法来调整视图布局。
@protocol UIContentContainer <NSObject>

@property (nonatomic, readonly) CGSize preferredContentSize NS_AVAILABLE_IOS(8_0);
//我们可以使用preferredContentSize来设置我们期望的childViewController的界面的大小
- (void)preferredContentSizeDidChangeForChildContentContainer:(id <UIContentContainer>)container NS_AVAILABLE_IOS(8_0);

/*
 Intended as a bridge for a view controller that does not use auto layout presenting a child that does use auto layout.
 
 If the child's view is using auto layout and the -systemLayoutSizeFittingSize: of the view
 changes, -systemLayoutFittingSizeDidChangeForChildContentContainer: will be sent to the view controller's parent.
 用作视图控制器的桥梁，不使用自动布局来呈现使用自动布局的子级。
  
 如果子类的视图使用视图的自动布局和-systemLayoutSizeFittingSize：来更改view。
 -systemLayoutFittingSizeDidChangeForChildContentContainer： 将被发送到视图控制器的父类。
 */
- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(id <UIContentContainer>)container NS_AVAILABLE_IOS(8_0);

/*
 When the content container forwards viewWillTransitionToSize:withTransitionCoordinator: to its children, it will call this method to determine what size to send them. 
 
 If the returned size is the same as the child container's current size, viewWillTransitionToSize:withTransitionCoordinator: will not be called.
 当内容容器将viewWillTransitionToSize：withTransitionCoordinator：转发给其子类时，它将调用此方法来确定发送它们的大小。
 如果返回的大小与子容器的当前大小相同，则不会调用viewWillTransitionToSize：withTransitionCoordinator：。
 */
//重写这些方法可以调整视图布局，一个容器viewController可以使用这个方法设置childViewController的size，当容器viewControllerViewWillTransitionTosize：withTransitionCoordinator：被调用时（我们重写这个方法时要调用super）,sizeForChildContentContainer方法将被调用。然后我们可以把需要设置desire发送给childViewController。当我们设置的这个size和当前childViewController的size一样，那么childViewController的viewWillTransitionToSize方法将不会被调用。sizeForChildContentContainer默认的实现是返回parentSize
- (CGSize)sizeForChildContentContainer:(id <UIContentContainer>)container withParentContainerSize:(CGSize)parentSize NS_AVAILABLE_IOS(8_0);

/* 
 This method is called when the view controller's view's size is changed by its parent (i.e. for the root view controller when its window rotates or is resized). 
 
 If you override this method, you should either call super to propagate the change to children or manually forward the change to children.
 当视图控制器的视图的大小被其父视图的大小改变时（即，当视图控制器的窗口旋转或调整大小时），该方法被调用。
 如果您重写此方法，则应该调用super来将更改传播给子节点或手动将更改传递给子节点。
 */
- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator NS_AVAILABLE_IOS(8_0);

/* 
 This method is called when the view controller's trait collection is changed by its parent.
 
 If you override this method, you should either call super to propagate the change to children or manually forward the change to children.
 当视图控制器的特征集合由其父级更改时，将调用此方法。
  如果您重写此方法，则应该调用super来将更改传播给子节点或手动将更改传递给子节点。
 */
- (void)willTransitionToTraitCollection:(UITraitCollection *)newCollection withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator NS_AVAILABLE_IOS(8_0);

@end

// Sometimes view controllers that are using showViewController:sender and showDetailViewController:sender: will need to know when the split view controller environment above it has changed. This notification will be posted when that happens (for example, when a split view controller is collapsing or expanding). The NSNotification's object will be the view controller that caused the change.
// 有时，使用showViewController的视图控制器：sender和showDetailViewController：sender：需要知道它上面的分割视图控制器环境何时发生更改。 此通知将在发生时发布（例如，拆分视图控制器正在崩溃或展开时）。 NSNotification的对象将是发生更改的视图控制器。
UIKIT_EXTERN NSNotificationName const UIViewControllerShowDetailTargetDidChangeNotification NS_AVAILABLE_IOS(8_0);

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIViewController : UIResponder <NSCoding, UIAppearanceContainer, UITraitEnvironment, UIContentContainer, UIFocusEnvironment>

/*
  The designated initializer. If you subclass UIViewController, you must call the super implementation of this
  method, even if you aren't using a NIB.  (As a convenience, the default init method will do this for you,
  and specify nil for both of this methods arguments.) In the specified NIB, the File's Owner proxy should
  have its class set to your view controller subclass, with the view outlet connected to the main view. If you
  invoke this method with a nil nib name, then this class' -loadView method will attempt to load a NIB whose
  name is the same as your view controller's class. If no such NIB in fact exists then you must either call
  -setView: before -view is invoked, or override the -loadView method to set up your views programatically.
  指定的初始化程序。 如果你继承UIViewController，重写该方法必须实现super
   方法，即使你没有使用NIB。（为了方便起见，默认的init方法会为你做这件事，
   并为这两个方法参数指定nil）。在指定的NIB中，文件的所有者代理应该
   将其类设置为您的视图控制器子类，并将视图插座连接到主视图。 如果你
   用nil nib名称调用此方法，那么此类的-loadView方法将尝试加载其NIB的NIB
   名称与视图控制器的类相同。 如果实际上不存在这样的NIB，则您必须致电
   -setView：调用之前的视图，或者重写-loadView方法以编程方式设置视图。
*/
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER; //最终都会(默认参数)调用该方法
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@property(null_resettable, nonatomic,strong) UIView *view; // The getter first invokes [self loadView] if the view hasn't been set yet. Subclasses must call super if they override the setter or getter.如果视图尚未设置，则getter首先调用[self loadView]。 如果子类重写setter或getter，子类必须调用super。
- (void)loadView; // This is where subclasses should create their custom view hierarchy if they aren't using a nib. Should never be called directly.如果是使用与VC同名的xib初始化VC.view（比如使用SB、VC自动生成的xib），重写loadView方法后，那么xib里边的视图会失效。
- (void)loadViewIfNeeded NS_AVAILABLE_IOS(9_0); // Loads the view controller's view if it has not already been set.如果视图控制器尚未设置，则加载视图控制器的视图。
@property(nullable, nonatomic, readonly, strong) UIView *viewIfLoaded NS_AVAILABLE_IOS(9_0); // Returns the view controller's view if loaded, nil if not.//如果view存在则返回视图控制器的视图，否则返回nil。

//从 iOS 6 开始，viewDidUnload 方法被废弃掉了，应用收到 memory warning 时也不会再调用 viewDidUnload 方法。
- (void)viewWillUnload NS_DEPRECATED_IOS(5_0,6_0) __TVOS_PROHIBITED;
- (void)viewDidUnload NS_DEPRECATED_IOS(3_0,6_0) __TVOS_PROHIBITED; // Called after the view controller's view is released and set to nil. For example, a memory warning which causes the view to be purged. Not invoked as a result of -dealloc.在视图控制器的视图被释放并被设置为零之后调用。 例如，导致视图被清除的内存警告。 不作为-dealloc的结果被调用。

- (void)viewDidLoad; // Called after the view has been loaded. For view controllers created in code, this is after -loadView. For view controllers unarchived from a nib, this is after the view is set.视图加载完成后调用。 对于在代码中创建的视图控制器，这是after-loadView。 视图加载完成后调用。对于代码中创建的视图控制器，这是在-loadView之后调用。
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, getter=isViewLoaded) BOOL viewLoaded NS_AVAILABLE_IOS(3_0);//view是否加载完成
#else
- (BOOL)isViewLoaded NS_AVAILABLE_IOS(3_0);
#endif
//这个UIViewController的nib名字
@property(nullable, nonatomic, readonly, copy) NSString *nibName;     // The name of the nib to be loaded to instantiate the view.
@property(nullable, nonatomic, readonly, strong) NSBundle *nibBundle; // The bundle from which to load the nib.
@property(nullable, nonatomic, readonly, strong) UIStoryboard *storyboard NS_AVAILABLE_IOS(5_0);


// Storyboar跳转摆好的界面
// identifier 设置好的界面连线（就是Storyboar中VC与VC那条线）
// sender 发送者
- (void)performSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender NS_AVAILABLE_IOS(5_0);
// 看看能不能跳转
- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender NS_AVAILABLE_IOS(6_0); // Invoked immediately prior to initiating a segue. Return NO to prevent the segue from firing. The default implementation returns YES. This method is not invoked when -performSegueWithIdentifier:sender: is used.在启动segue之前立即调用。 返回NO以防止继续发射。 默认实现返回YES。 当使用-performSegueWithIdentifier：sender：时，不会调用此方法。

//准备跳转;可以重写这个方法，在内部做一些类与类传递数据的操作
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(nullable id)sender NS_AVAILABLE_IOS(5_0);

// View controllers will receive this message during segue unwinding. The default implementation returns the result of -respondsToSelector: - controllers can override this to perform any ancillary checks, if necessary.视图控制器将在延迟展开期间收到此消息。 默认实现返回-respondsToSelector的结果： 如有必要，控制器可以重写此项以执行任何辅助检查。
// 我们一般在子控制器中通过实现canperformUnwindSegueAction：fromViewController:withSender：来决定要不要执行相应的Unwind Segue。
- (BOOL)canPerformUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController withSender:(id)sender NS_AVAILABLE_IOS(6_0);

// Returns a subset of the receiver's childViewControllers in the order they should be searched for an unwind destination.
// The default implementation first sends itself -childViewControllerContainingSegueSource:, then returns a copy of its childViewControllers array excluding that object. A custom container view controller can override this method to affect the order in which its children are searched, or to modify the result of the default implementation.
// For compatibility, if a view controller overrides the deprecated -viewControllerForUnwindSegueAction:fromViewController:sender: method, but does not override this method, it will receive the deprecated method instead of this method.
// To affect this view controller's eligibility as an unwind destination, override -canPerformUnwindSegueAction:fromViewController:withSender: instead.
//按接收者的childViewController的子集顺序搜索展开目的地。
//默认实现首先发送自己-childViewControllerContainingSegueSource：，然后返回其不包含该对象的childViewControllers数组的副本。 自定义容器视图控制器可以重写此方法，以影响其子项的搜索顺序，或者修改默认实现的结果。
//为了兼容性，如果一个视图控制器重写弃用的-viewControllerForUnwindSegueAction：fromViewController：sender：方法，但不重写此方法，它将接收已弃用的方法，而不是此方法。
//要将此视图控制器的资格作为展开目标，请重写-canPerformUnwindSegueAction：fromViewController：withSender：代替。
- (NSArray<UIViewController *> *)allowedChildViewControllersForUnwindingFromSource:(UIStoryboardUnwindSegueSource *)source NS_AVAILABLE_IOS(9_0);

// Returns the child view controller that contains the provided segue source.
// Custom container view controllers should call this method from their implementation of -allowedChildViewControllersForUnwindingFromSource: to exclude the result from the returned array, as well as to determine the order of the returned array's contents.
// Do not try to re-implement or override this method; it takes special care to handle situations such as unwinding from a modally-presented view controller.
//返回包含提供的segue源的子视图控制器。
//自定义容器视图控制器应该从它们的-allowedChildViewControllersForUnwindingFromSource实现中调用此方法：从返回的数组中排除结果，以及确定返回数组内容的顺序。
//不要尝试重新实现或重写此方法; 需要特别注意处理诸如从模态呈现的视图控制器展开的情况。
- (nullable UIViewController *)childViewControllerContainingSegueSource:(UIStoryboardUnwindSegueSource *)source NS_AVAILABLE_IOS(9_0);

// Deprecated. Returns a direct child of the receiver that responds YES to -canPerformUnwindSegueAction:fromViewController:withSender:, or self if no children respond YES but the receiver itself does. If this method has been overridden, UIViewController's implementation does not consult child view controllers at all, and skips straight to sending -canPerformUnwindSegueAction:... to self.
// Applications targeting iOS 9 or later should not override this method. Applications can instead override -allowedChildViewControllersForUnwindingFromSource: to guide UIKit’s search for a descendant view controller that returns YES from -canPerformUnwindSegueAction:fromViewController:withSender:.

// 这个方法用来决定哪个viewController来处理Unwind Segue action
- (nullable UIViewController *)viewControllerForUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController withSender:(nullable id)sender NS_DEPRECATED_IOS(6_0, 9_0);

// Custom container view controllers should override this method to modify themselves as part of an ongoing unwind segue. The subsequentVC is the parent, child, or presented view controller closest to the receiver in the direction of the segue's destinationViewController. For example, UINavigationController's implementation of this method will pop any necessary view controllers to reveal the subsequentVC.
- (void)unwindForSegue:(UIStoryboardSegue *)unwindSegue towardsViewController:(UIViewController *)subsequentVC NS_AVAILABLE_IOS(9_0);

// Deprecated. This method is only used for unwind segues whose destination view controller has been returned by an override of the deprecated method -viewControllerForUnwindSegueAction:fromViewController:withSender:. In that case, UIKit will choose a view controller to act as the “executor” of the unwind. If the destination view controller is being modally presented, the destination view controller itself is the executor. Otherwise, the destination view controller’s parent view controller is the executor. If the executor overrides this method, UIKit will ignore the Custom Class specified in Interface Builder and instead call this method on the executor to obtain a segue that can perform the unwind.
// The returned segue object must be able to perform all steps necessary to unwind, including dismissing any intermediate modal presentations or popping any necessary navigation items.
// Applications targeting iOS 9 or later should not override this method. Custom container view controllers should instead override -unwindForSegue:towardsViewController: to modify their local state as part of a UIKit-generated incremental unwind segue.
- (nullable UIStoryboardSegue *)segueForUnwindingToViewController:(UIViewController *)toViewController fromViewController:(UIViewController *)fromViewController identifier:(nullable NSString *)identifier NS_DEPRECATED_IOS(6_0, 9_0);

//当视图即将显示时调用。 默认什么都不做
- (void)viewWillAppear:(BOOL)animated;    // Called when the view is about to made visible. Default does nothing
//当视图完全转换到屏幕上时调用。 默认什么都不做
- (void)viewDidAppear:(BOOL)animated;     // Called when the view has been fully transitioned onto the screen. Default does nothing
//当视图被消失，覆盖或以其他方式隐藏时调用。 默认什么都不做
- (void)viewWillDisappear:(BOOL)animated; // Called when the view is dismissed, covered or otherwise hidden. Default does nothing
//在视图被消失，覆盖或以其他方式隐藏后调用。 默认什么都不做
- (void)viewDidDisappear:(BOOL)animated;  // Called after the view was dismissed, covered or otherwise hidden. Default does nothing

// Called just before the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.在视图控制器视图的layoutSubviews方法被调用之前调用。 子类可以根据需要实现。 默认值是一个nop。
- (void)viewWillLayoutSubviews NS_AVAILABLE_IOS(5_0);
// Called just after the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.在视图控制器视图的layoutSubviews方法被调用之后调用。 子类可以根据需要实现。 默认值是一个nop。
- (void)viewDidLayoutSubviews NS_AVAILABLE_IOS(5_0);

@property(nullable, nonatomic,copy) NSString *title;  // Localized title for use by a parent controller.由父控制器使用的本地化标题。

- (void)didReceiveMemoryWarning; // Called when the parent application receives a memory warning. On iOS 6.0 it will no longer clear the view by default.当父应用程序收到内存警告时调用。 在iOS 6.0上，默认情况下，它将不再清除视图。

/*
  If this view controller is a child of a containing view controller (e.g. a navigation controller or tab bar
  controller,) this is the containing view controller.  Note that as of 5.0 this no longer will return the
  presenting view controller.
 如果此视图控制器是包含视图控制器（例如导航控制器或选项卡栏控制器）的子项，则这是容器视图控制器。 请注意，从5.0开始，将不再返回presenting视图控制器
*/
//父视图控制器
@property(nullable,nonatomic,weak,readonly) UIViewController *parentViewController;

// This property has been replaced by presentedViewController.6.0开始、此属性已被presentViewController替换。
@property(nullable, nonatomic,readonly) UIViewController *modalViewController NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

// The view controller that was presented by this view controller or its nearest ancestor.该视图控制器或其最近的祖先呈现的视图控制器。
//被弹出的视图控制器B
@property(nullable, nonatomic,readonly) UIViewController *presentedViewController  NS_AVAILABLE_IOS(5_0);

// The view controller that presented this view controller (or its farthest ancestor.)呈现此视图控制器（或其最远的祖先）的视图控制器。
//执行弹出动作的控制器A
@property(nullable, nonatomic,readonly) UIViewController *presentingViewController NS_AVAILABLE_IOS(5_0);

/*
  Determines which parent view controller's view should be presented over for presentations of type
  UIModalPresentationCurrentContext.  If no ancestor view controller has this flag set, then the presenter
  will be the root view controller.确定对于UIModalPresentationCurrentContext类型的演示应该展示哪个父视图控制器的视图。 如果没有祖先视图控制器设置了该标志，则演示者将是根视图控制器。
*/
//本视图控制器的视图是否被覆盖时，视图控制器或它的子类提供了一个视图控制器;决定哪个父viewController的view应当呈现在当前，如果没有父viewController，呈现的将是根视图控制器
@property(nonatomic,assign) BOOL definesPresentationContext NS_AVAILABLE_IOS(5_0);

// A controller that defines the presentation context can also specify the modal transition style if this property is true.
//如果此属性为true，则定义表示上下文的控制器也可以指定模态转换样式；设定视图在present使用不同的风格
//如果这个属性是true的话，可以定义模态过渡转场的样式
@property(nonatomic,assign) BOOL providesPresentationContextTransitionStyle NS_AVAILABLE_IOS(5_0);

// If YES, when this view controller becomes visible and focusable, focus will be automatically restored to the item that was last focused. For example, when an item in this view controller is focused, and then another view controller is presented and dismissed, the original item will become focused again. Defaults to YES.如果为“是”，则此视图控制器变得可见且可对焦时，焦点将自动恢复到最后聚焦的项目。 例如，当这个视图控制器中的一个项目被聚焦，然后另一个视图控制器被呈现和解除时，原始项目将再次聚焦。 默认为YES。
@property (nonatomic) BOOL restoresFocusAfterTransition NS_AVAILABLE_IOS(10_0);

/*
  These four methods can be used in a view controller's appearance callbacks to determine if it is being
  presented, dismissed, or added or removed as a child view controller. For example, a view controller can
  check if it is disappearing because it was dismissed or popped by asking itself in its viewWillDisappear:
  method by checking the expression ([self isBeingDismissed] || [self isMovingFromParentViewController]).
  这四种方法可用于视图控制器的外观回调中，以确定它是作为子视图控制器呈现，解散还是添加或删除。 例如，视图控制器可以通过检查表达式（[self isBeingDismissed] || [self isMovingFromParentViewController]）来检查它是否正在消失，因为它是通过在viewWillDisappear：方法中询问自己而被解散或弹出的。
*/

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, getter=isBeingPresented) BOOL beingPresented NS_AVAILABLE_IOS(5_0);
@property(nonatomic, readonly, getter=isBeingDismissed) BOOL beingDismissed NS_AVAILABLE_IOS(5_0);

@property(nonatomic, readonly, getter=isMovingToParentViewController) BOOL movingToParentViewController NS_AVAILABLE_IOS(5_0);
@property(nonatomic, readonly, getter=isMovingFromParentViewController) BOOL movingFromParentViewController NS_AVAILABLE_IOS(5_0);
#else
//判断viewController是否正在展示
- (BOOL)isBeingPresented NS_AVAILABLE_IOS(5_0);
//判断viewController是否正在消失
- (BOOL)isBeingDismissed NS_AVAILABLE_IOS(5_0);

//判断是否正在加入父viewController
- (BOOL)isMovingToParentViewController NS_AVAILABLE_IOS(5_0);
//判断是否正从父viewController移除
- (BOOL)isMovingFromParentViewController NS_AVAILABLE_IOS(5_0);
#endif

/*
  The next two methods are replacements for presentModalViewController:animated and
  dismissModalViewControllerAnimated: The completion handler, if provided, will be invoked after the presented
  controllers viewDidAppear: callback is invoked.
  接下来的两个方法是presentModalViewController：animated and dismissModalViewControllerAnimated：的替代方法。
  completion完成时回调（如果block不为nil）将在调用呈现的控制器viewDidAppear:回调后调用。
*/
- (void)presentViewController:(UIViewController *)viewControllerToPresent animated: (BOOL)flag completion:(void (^ __nullable)(void))completion NS_AVAILABLE_IOS(5_0);
// The completion handler, if provided, will be invoked after the dismissed controller's viewDidDisappear: callback is invoked.
// 完成处理程序（如果提供）将在解除控制器的viewDidDisappear：回调被调用后调用。
- (void)dismissViewControllerAnimated: (BOOL)flag completion: (void (^ __nullable)(void))completion NS_AVAILABLE_IOS(5_0);

// Display another view controller as a modal child. Uses a vertical sheet transition if animated.This method has been replaced by presentViewController:animated:completion:将另一个视图控制器显示为模态子视图。 如果使用动画，则使用垂直图纸过渡。此方法已由presentViewController：animated：completion：替换
//已废弃
- (void)presentModalViewController:(UIViewController *)modalViewController animated:(BOOL)animated NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;
// Dismiss the current modal child. Uses a vertical sheet transition if animated. This method has been replaced by dismissViewControllerAnimated:completion:关闭当前的模态孩子。 如果动画，则使用垂直单张转换。 此方法已被dismissViewControllerAnimated取代
//已废弃
- (void)dismissModalViewControllerAnimated:(BOOL)animated NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

/*
  Defines the transition style that will be used for this view controller when it is presented modally. Set
  this property on the view controller to be presented, not the presenter.  Defaults to
  UIModalTransitionStyleCoverVertical.
  以模态方式呈现时，定义将用于此视图控制器的转换样式。 在被弹出的视图控制器上设置此属性，而不是演示者。 默认为
   UIModalTransitionStyleCoverVertical。
*/
// persent过渡风格，设置在被弹出的控制器
@property(nonatomic,assign) UIModalTransitionStyle modalTransitionStyle NS_AVAILABLE_IOS(3_0);
// persent弹出风格;在iPhone和iPod touch，模态视图控制器始终呈现全屏，但是在iPad上有几种不同的显示选项
@property(nonatomic,assign) UIModalPresentationStyle modalPresentationStyle NS_AVAILABLE_IOS(3_2);
// This controls whether this view controller takes over control of the status bar's appearance when presented non-full screen on another view controller. Defaults to NO.
// 这将控制此视图控制器在另一个视图控制器上呈现非全屏时是否接管"状态栏"外观的控制。 默认为NO。
// 设置状态栏是否在屏幕滚动的时候隐藏，默认是NO
@property(nonatomic,assign) BOOL modalPresentationCapturesStatusBarAppearance NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

// Presentation modes may keep the keyboard visible when not required. Default implementation affects UIModalPresentationFormSheet visibility.
// 演示模式可能会在不需要时保持键盘可见。 默认实现影响UIModalPresentationFormSheet可见性。
//这个API是于关闭键盘相关的，通常情况下单纯的使用resignFirstResponder即可关闭键盘，但是在UIModalPresentationFormSheet下的视图是无法用resignFirstResponder这个API，是因为在进入到此模式后，系统将disablesAutomaticKeyboardDismissal的方法返回值设置成了YES，所以解决方法很简单，重新实现disablesAutomaticKeyboardDismissal，如果是直接使用viewController则可以在实现文件中重新实现这个API，将返回改为NO后，即可正常使用resignFirstResponder方法隐藏键盘，但很多时候我们是把viewController放在UINavigationController中的，这种情况下直接在viewController这里面实现disablesAutomaticKeyboardDismissal依然失效，而应发iUINavigationController中实现这个API。
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL disablesAutomaticKeyboardDismissal NS_AVAILABLE_IOS(4_3);
#else
- (BOOL)disablesAutomaticKeyboardDismissal NS_AVAILABLE_IOS(4_3);
#endif

//已废弃；状态栏的高度就不会被算在视图里，也就是说有没有状态栏y坐标始终都是从0算起
@property(nonatomic,assign) BOOL wantsFullScreenLayout NS_DEPRECATED_IOS(3_0, 7_0) __TVOS_PROHIBITED; // Deprecated in 7_0, Replaced by the following:在7_0中弃用，替换为以下内容：

//默认值是UIRectEdgeAll，指定控制器将它的视图延伸到屏幕的边缘并在bar下面。如果属性值为：UIRectEdgeNone，控制器视图遇到bar的边界就不延伸了。
//默认值为UIRectEdgeAll，在navigationController中view的默认布局从navigationBar开始，self.edgesForExtendedLayout=UIRectEdgeNone,则布局控件从navigationBar高度下为y零点
//在iOS7中UIViewController的wantsFullScreenLayout已经被舍弃，不在提供控件自动展示到导航栏下面这个属性，所有的UIViewController创建后默认就是full Screen的，因此如果带导航栏的应用界面中的部分控件会被导航栏覆盖掉，要解决这个情况可以使用iOS7中UIVIewController新增的属性extendedLayoutIncludesOpaqueBars和edgesForExtendedLayout来解决。其中这个属性指定了当bar使用了不透明图片时，视图是否眼神至bar所在区域，默认值是NO，而edgesForExtendedLayout则是表示食欲是够覆盖到四周的区域，默认是UIRectEdgeAll，即上下左右四个方向都会覆盖，那么为让顶部不进行眼神到导航栏覆盖的区域，我们可以把顶部区域眼神去掉，实现代码如下，self.extendedLayoutIncludesOpaqueBars = NO;
//self.edgesForExtendedLayout = UIRectEdgeBottom | UIRectEdgeLeft | UIRectEdgeRight;
//
//当你在做的时候发现viewDidLoad的时候view的高度还是全屏，viewWillAppear已经去掉navigationbar了，所以frame的设置放在了viewWillAppear中比较准确。
@property(nonatomic,assign) UIRectEdge edgesForExtendedLayout NS_AVAILABLE_IOS(7_0); // Defaults to UIRectEdgeAll
//可以控制以上属性的有效性，默认值为NO,指定edgesForExtendedLayout在遇到不透明的bar时无效，即不延展。设置值为YES，则在遇到透明或不透明的bar情况下都会延展。
@property(nonatomic,assign) BOOL extendedLayoutIncludesOpaqueBars NS_AVAILABLE_IOS(7_0); // Defaults to NO, but bars are translucent by default on 7_0.默认为NO，但7_0默认为半透明。
//默认为YES,指定控制器在有UIScrollView及其子类并且在有导航栏或工具栏或标签栏情况下，会自动调整其contentInset属性。如果是导航栏contentInset.top = 64,如果是标签栏contentInset.bottom = 44.（self.view添加的第一个子视图(或遍历子链)为UIScrollView及其子类时触发）
@property(nonatomic,assign) BOOL automaticallyAdjustsScrollViewInsets API_DEPRECATED_WITH_REPLACEMENT("Use UIScrollView's contentInsetAdjustmentBehavior instead", ios(7.0,11.0),tvos(7.0,11.0)); // Defaults to YES

/* The preferredContentSize is used for any container laying out a child view controller.
   preferredContentSize用于布置子视图控制器的大小
 */
//设置我们期望的childViewController的界面的大小
@property (nonatomic) CGSize preferredContentSize NS_AVAILABLE_IOS(7_0);

// These methods control the attributes of the status bar when this view controller is shown. They can be overridden in view controller subclasses to return the desired status bar attributes.
// 显示此视图控制器时，下这些方法控制状态栏的属性。 它们可以在视图控制器子类中重写以返回所需的状态栏属性。
#if UIKIT_DEFINE_AS_PROPERTIES
//状态栏样式(黑白两种颜色)
@property(nonatomic, readonly) UIStatusBarStyle preferredStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarStyleDefault
//状态栏是否隐藏，默认NO
@property(nonatomic, readonly) BOOL prefersStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to NO
// Override to return the type of animation that should be used for status bar changes for this view controller. This currently only affects changes to prefersStatusBarHidden.
//用于此视图控制器的状态栏更改的动画类型。 目前这只会在prefersStatusBarHidden更改时起效果
@property(nonatomic, readonly) UIStatusBarAnimation preferredStatusBarUpdateAnimation NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarAnimationFade
#else
//使用下方法进行修改状态栏
- (UIStatusBarStyle)preferredStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarStyleDefault
- (BOOL)prefersStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to NO
// Override to return the type of animation that should be used for status bar changes for this view controller. This currently only affects changes to prefersStatusBarHidden.重写以返回应该用于此视图控制器的状态栏更改的动画类型。 目前这只会影响首选StatusBarHidden的更改。
- (UIStatusBarAnimation)preferredStatusBarUpdateAnimation NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarAnimationFade
#endif

// This should be called whenever the return values for the view controller's status bar attributes have changed. If it is called from within an animation block, the changes will be animated along with the rest of the animation block.
// 只要视图控制器状态栏属性的返回值已更改，调用它立刻更新。 如果从动画块内调用它，则更改将与动画块的其余部分一起动画。
- (void)setNeedsStatusBarAppearanceUpdate NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

/* This method returns either itself or the nearest ancestor that can perform the given action and, if applicable, has overridden UIViewController's default implementation of the action method. View controllers can return NO from canPerformAction:withSender: to opt out of being a target for a given action.
    此方法返回自身或最近的可以执行给定操作的父类，并且（如果适用）已重写UIViewController的操作方法的默认实现。 视图控制器可以从canPerformAction返回NO：withSender：选择不作为给定动作的目标。
 */
- (nullable UIViewController *)targetViewControllerForAction:(SEL)action sender:(nullable id)sender NS_AVAILABLE_IOS(8_0);

/* This method will show a view controller appropriately for the current size-class environment. It's implementation calls
 `[self targetViewControllerForAction:sender:]` first and redirects accordingly if the return value is not `self`, otherwise it will present the vc.
  此方法将展示一个大小适当的视图控制器。 如果返回值不是`self`，那么它会首先实现调用`[self targetViewControllerForAction：sender：]`并且相应地重定向，否则它会persent VC。
 */
- (void)showViewController:(UIViewController *)vc sender:(nullable id)sender NS_AVAILABLE_IOS(8_0);

/* This method will show a view controller within the semantic "detail" UI associated with the current size-class environment. It's implementation calls  `[self targetViewControllerForAction:sender:]` first and redirects accordingly if the return value is not `self`, otherwise it will present the vc.
  此方法将在与当前尺寸级环境相关联的语义“细节”UI中显示视图控制器。 如果返回值不是`self`，那么它会首先实现调用`[self targetViewControllerForAction：sender：]`并且相应地重定向，否则它会persent VC。
 */
- (void)showDetailViewController:(UIViewController *)vc sender:(nullable id)sender NS_AVAILABLE_IOS(8_0);

// Subclasses may override if they prefer a user interface style other than the one preferred by the application.
// 子类可以重写设置偏好应用程序首选的用户界面风格
@property (nonatomic, readonly) UIUserInterfaceStyle preferredUserInterfaceStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos); // Defaults to UIUserInterfaceStyleUnspecified

// This should be called whenever the view controller's preferredUserInterfaceStyle changes.
- (void)setNeedsUserInterfaceAppearanceUpdate API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

@end

#park mark - 屏幕旋转
// To make it more convenient for applications to adopt rotation, a view controller may implement the below methods. Your UIWindow's frame should use [UIScreen mainScreen].bounds as its frame.
@interface UIViewController (UIViewControllerRotation)

// call this method when your return value from shouldAutorotateToInterfaceOrientation: changes
// if the current interface orientation does not match the current device orientation, a rotation may occur provided all relevant view controllers now return YES from shouldAutorotateToInterfaceOrientation:
+ (void)attemptRotationToDeviceOrientation NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED;

// Applications should use supportedInterfaceOrientations and/or shouldAutorotate..
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

// New Autorotation support.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL shouldAutorotate NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
@property(nonatomic, readonly) UIInterfaceOrientationMask supportedInterfaceOrientations NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
// Returns interface orientation masks.
@property(nonatomic, readonly) UIInterfaceOrientation preferredInterfaceOrientationForPresentation NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
#else
- (BOOL)shouldAutorotate NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
- (UIInterfaceOrientationMask)supportedInterfaceOrientations NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
// Returns interface orientation masks.
- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
#endif

// The rotating header and footer views will slide out during the rotation and back in once it has completed.
- (nullable UIView *)rotatingHeaderView NS_DEPRECATED_IOS(2_0,8_0, "Header views are animated along with the rest of the view hierarchy") __TVOS_PROHIBITED;     // Must be in the view hierarchy. Default returns nil.
- (nullable UIView *)rotatingFooterView NS_DEPRECATED_IOS(2_0,8_0, "Footer views are animated along with the rest of the view hierarchy") __TVOS_PROHIBITED;     // Must be in the view hierarchy. Default returns nil.

@property(nonatomic,readonly) UIInterfaceOrientation interfaceOrientation NS_DEPRECATED_IOS(2_0,8_0) __TVOS_PROHIBITED;

// Notifies when rotation begins, reaches halfway point and ends.
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(2_0,8_0, "Implement viewWillTransitionToSize:withTransitionCoordinator: instead") __TVOS_PROHIBITED;
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation NS_DEPRECATED_IOS(2_0,8_0) __TVOS_PROHIBITED;

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(3_0,8_0, "Implement viewWillTransitionToSize:withTransitionCoordinator: instead") __TVOS_PROHIBITED;

- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(2_0, 5_0) __TVOS_PROHIBITED;
- (void)didAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation NS_DEPRECATED_IOS(2_0, 5_0) __TVOS_PROHIBITED; // The rotating header and footer views are offscreen.
- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(2_0, 5_0) __TVOS_PROHIBITED; // A this point, our view orientation is set to the new orientation.

@end

// Many view controllers have a view that may be in an editing state or not- for example, a UITableView.  These view
// controllers can track the editing state, and generate an Edit|Done button to be used in a navigation bar.
@interface UIViewController (UIViewControllerEditing)

@property(nonatomic,getter=isEditing) BOOL editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated; // Updates the appearance of the Edit|Done button item as necessary. Clients who override it must call super first.

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) UIBarButtonItem *editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.
#else
- (UIBarButtonItem *)editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.
#endif

@end

@interface UIViewController (UISearchDisplayControllerSupport)

@property(nullable, nonatomic, readonly, strong) UISearchDisplayController *searchDisplayController NS_DEPRECATED_IOS(3_0,8_0) __TVOS_PROHIBITED;

@end

#park mark - 容器视图
/*
  This exception is raised when a child view controller's view is added into the view hierarchy and the first
  superview of the child view controller's view that has a view controller is NOT the child view controller's
  parent.
*/
//异常。因控制器的层次与视图的层次不一致会引发该异常，当视图控制器的视图添加到视图层中，系统会遍历视图层来找到第一个拥有视图控制器的父视图。找到的该父视图控制器也必须是刚添加的视图的所对应视图控制器的父控制器。否则会抛出异常。当视图控制器通过addChildViewController方法被添加进来后，也会进行之前的一致性检测。不存在父视图控制器的视图控制器，也可以将其视图添加到视图层中。但通常极少数情况下才会用到这种方式。
UIKIT_EXTERN NSExceptionName const UIViewControllerHierarchyInconsistencyException NS_AVAILABLE_IOS(5_0);

/*
  The methods in the UIContainerViewControllerProtectedMethods and the UIContainerViewControllerCallbacks
  categories typically should only be called by subclasses which are implementing new container view
  controllers. They may be overridden but must call super.
 
  UIContainerViewControllerProtectedMethods和UIContainerViewControllerCallbacks
  类别中的方法通常只应由实施新容器视图控制器的子类调用。它们可以被重写，但必须调用父类。
*/
@interface UIViewController (UIContainerViewControllerProtectedMethods)

// An array of children view controllers. This array does not include any presented view controllers.
@property(nonatomic,readonly) NSArray<__kindof UIViewController *> *childViewControllers NS_AVAILABLE_IOS(5_0);

/*
  If the child controller has a different parent controller, it will first be removed from its current parent
  by calling removeFromParentViewController. If this method is overridden then the super implementation must
  be called.
*/
- (void)addChildViewController:(UIViewController *)childController NS_AVAILABLE_IOS(5_0);

/*
  Removes the the receiver from its parent's children controllers array. If this method is overridden then
  the super implementation must be called.
*/
- (void)removeFromParentViewController NS_AVAILABLE_IOS(5_0);

/*
  This method can be used to transition between sibling child view controllers. The receiver of this method is
  their common parent view controller. (Use [UIViewController addChildViewController:] to create the
  parent/child relationship.) This method will add the toViewController's view to the superview of the
  fromViewController's view and the fromViewController's view will be removed from its superview after the
  transition completes. It is important to allow this method to add and remove the views. The arguments to
  this method are the same as those defined by UIView's block animation API. This method will fail with an
  NSInvalidArgumentException if the parent view controllers are not the same as the receiver, or if the
  receiver explicitly forwards its appearance and rotation callbacks to its children. Finally, the receiver
  should not be a subclass of an iOS container view controller. Note also that it is possible to use the
  UIView APIs directly. If they are used it is important to ensure that the toViewController's view is added
  to the visible view hierarchy while the fromViewController's view is removed.
*/
- (void)transitionFromViewController:(UIViewController *)fromViewController toViewController:(UIViewController *)toViewController duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(5_0);

// If a custom container controller manually forwards its appearance callbacks, then rather than calling
// viewWillAppear:, viewDidAppear: viewWillDisappear:, or viewDidDisappear: on the children these methods
// should be used instead. This will ensure that descendent child controllers appearance methods will be
// invoked. It also enables more complex custom transitions to be implemented since the appearance callbacks are
// now tied to the final matching invocation of endAppearanceTransition.
- (void)beginAppearanceTransition:(BOOL)isAppearing animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)endAppearanceTransition __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Override to return a child view controller or nil. If non-nil, that view controller's status bar appearance attributes will be used. If nil, self is used. Whenever the return values from these methods change, -setNeedsUpdatedStatusBarAttributes should be called.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, nullable) UIViewController *childViewControllerForStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
@property(nonatomic, readonly, nullable) UIViewController *childViewControllerForStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
#else
- (nullable UIViewController *)childViewControllerForStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
- (nullable UIViewController *)childViewControllerForStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
#endif

// Call to modify the trait collection for child view controllers.
- (void)setOverrideTraitCollection:(nullable UITraitCollection *)collection forChildViewController:(UIViewController *)childViewController NS_AVAILABLE_IOS(8_0);
- (nullable UITraitCollection *)overrideTraitCollectionForChildViewController:(UIViewController *)childViewController NS_AVAILABLE_IOS(8_0);

// Override to return a child view controller or nil. If non-nil, that view controller's preferred user interface style will be used. If nil, self is used. Whenever the preferredUserInterfaceStyle for a view controller has changed setNeedsUserInterfaceAppearanceUpdate should be called.
@property (nonatomic, readonly, nullable) UIViewController *childViewControllerForUserInterfaceStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

@end

@interface UIViewController (UIContainerViewControllerCallbacks)

/*
  This method is consulted to determine if a view controller manually forwards its containment callbacks to
  any children view controllers. Subclasses of UIViewController that implement containment logic may override
  this method. The default implementation returns YES. If it is overridden and returns NO, then the subclass is
  responsible for forwarding the following methods as appropriate - viewWillAppear: viewDidAppear: viewWillDisappear:
  viewDidDisappear: willRotateToInterfaceOrientation:duration:
  willAnimateRotationToInterfaceOrientation:duration: didRotateFromInterfaceOrientation:
*/

- (BOOL)automaticallyForwardAppearanceAndRotationMethodsToChildViewControllers NS_DEPRECATED_IOS(5_0,6_0) __TVOS_PROHIBITED;
- (BOOL)shouldAutomaticallyForwardRotationMethods NS_DEPRECATED_IOS(6_0,8_0, "Manually forward viewWillTransitionToSize:withTransitionCoordinator: if necessary") __TVOS_PROHIBITED;

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL shouldAutomaticallyForwardAppearanceMethods NS_AVAILABLE_IOS(6_0);
#else
- (BOOL)shouldAutomaticallyForwardAppearanceMethods NS_AVAILABLE_IOS(6_0);
#endif


/*
  These two methods are public for container subclasses to call when transitioning between child
  controllers. If they are overridden, the overrides should ensure to call the super. The parent argument in
  both of these methods is nil when a child is being removed from its parent; otherwise it is equal to the new
  parent view controller.

  addChildViewController: will call [child willMoveToParentViewController:self] before adding the
  child. However, it will not call didMoveToParentViewController:. It is expected that a container view
  controller subclass will make this call after a transition to the new child has completed or, in the
  case of no transition, immediately after the call to addChildViewController:. Similarly,
  removeFromParentViewController does not call [self willMoveToParentViewController:nil] before removing the
  child. This is also the responsibilty of the container subclass. Container subclasses will typically define
  a method that transitions to a new child by first calling addChildViewController:, then executing a
  transition which will add the new child's view into the view hierarchy of its parent, and finally will call
  didMoveToParentViewController:. Similarly, subclasses will typically define a method that removes a child in
  the reverse manner by first calling [child willMoveToParentViewController:nil].
*/
- (void)willMoveToParentViewController:(nullable UIViewController *)parent NS_AVAILABLE_IOS(5_0);
- (void)didMoveToParentViewController:(nullable UIViewController *)parent NS_AVAILABLE_IOS(5_0);

@end

@interface UIViewController (UIStateRestoration) <UIStateRestoring>
@property (nullable, nonatomic, copy) NSString *restorationIdentifier NS_AVAILABLE_IOS(6_0);
@property (nullable, nonatomic, readwrite, assign) Class<UIViewControllerRestoration> restorationClass NS_AVAILABLE_IOS(6_0);
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (void) applicationFinishedRestoringState NS_AVAILABLE_IOS(7_0);
@end

@interface UIViewController (UIConstraintBasedLayoutCoreMethods)
/* Base implementation sends -updateConstraints to the view.
    When a view has a view controller, this message is sent to the view controller during 
     the autolayout updateConstraints pass in lieu of sending updateConstraints directly
     to the view.
    You may override this method in a UIViewController subclass for updating custom 
     constraints instead of subclassing your view and overriding -[UIView updateConstraints].
    Overrides must call super or send -updateConstraints to the view.
 */
- (void)updateViewConstraints NS_AVAILABLE_IOS(6_0);
@end

@protocol UIViewControllerTransitioningDelegate;

@interface UIViewController(UIViewControllerTransitioning)

@property (nullable, nonatomic, weak) id <UIViewControllerTransitioningDelegate> transitioningDelegate NS_AVAILABLE_IOS(7_0);

@end

@interface UIViewController (UILayoutSupport)
// These objects may be used as layout items in the NSLayoutConstraint API
@property(nonatomic,readonly,strong) id<UILayoutSupport> topLayoutGuide API_DEPRECATED_WITH_REPLACEMENT("-[UIView safeAreaLayoutGuide]", ios(7.0,11.0), tvos(7.0,11.0));
@property(nonatomic,readonly,strong) id<UILayoutSupport> bottomLayoutGuide API_DEPRECATED_WITH_REPLACEMENT("-[UIView safeAreaLayoutGuide]", ios(7.0,11.0), tvos(7.0,11.0));

/* Custom container UIViewController subclasses can use this property to add to the overlay
 that UIViewController calculates for the safeAreaInsets for contained view controllers.
 */
@property(nonatomic) UIEdgeInsets additionalSafeAreaInsets API_AVAILABLE(ios(11.0), tvos(11.0));

/* Minimum layoutMargins for the view determined by the view controller from context and hardware information.
 The view controller's view will respect these minimums unless viewRespectsSystemMinimumLayoutMargins
 (which defaults to YES) is set to NO.
 */
@property(nonatomic,readonly) NSDirectionalEdgeInsets systemMinimumLayoutMargins API_AVAILABLE(ios(11.0), tvos(11.0));

/* Default YES. The return value of the view's layoutMargins and directionalLayoutMargins properties will have
 values no smaller than the systemMinimumLayoutMargins. Set to NO for full customizability of the view's
 layoutMargins.
 */
@property(nonatomic) BOOL viewRespectsSystemMinimumLayoutMargins API_AVAILABLE(ios(11.0), tvos(11.0));

- (void)viewLayoutMarginsDidChange NS_REQUIRES_SUPER API_AVAILABLE(ios(11.0), tvos(11.0));
- (void)viewSafeAreaInsetsDidChange NS_REQUIRES_SUPER API_AVAILABLE(ios(11.0), tvos(11.0));

@end

@interface UIViewController (UIKeyCommand)

- (void)addKeyCommand:(UIKeyCommand *)keyCommand NS_AVAILABLE_IOS(9_0);
- (void)removeKeyCommand:(UIKeyCommand *)keyCommand NS_AVAILABLE_IOS(9_0);

@end

@class NSExtensionContext;

@interface UIViewController(NSExtensionAdditions) <NSExtensionRequestHandling>

// Returns the extension context. Also acts as a convenience method for a view controller to check if it participating in an extension request.
@property (nullable, nonatomic,readonly,strong) NSExtensionContext *extensionContext NS_AVAILABLE_IOS(8_0);

@end

@class UIPresentationController, UIPopoverPresentationController;

@interface UIViewController (UIAdaptivePresentations)
@property (nullable, nonatomic,readonly) UIPresentationController *presentationController NS_AVAILABLE_IOS(8_0);
@property (nullable, nonatomic,readonly) UIPopoverPresentationController *popoverPresentationController NS_AVAILABLE_IOS(8_0);
@end


@protocol UIViewControllerPreviewingDelegate;

@protocol UIViewControllerPreviewing <NSObject>

// This gesture can be used to cause the previewing presentation to wait until one of your gestures fails or to allow simultaneous recognition during the initial phase of the preview presentation.
@property (nonatomic, readonly) UIGestureRecognizer *previewingGestureRecognizerForFailureRelationship NS_AVAILABLE_IOS(9_0);

@property (nonatomic, readonly) id<UIViewControllerPreviewingDelegate> delegate NS_AVAILABLE_IOS(9_0);
@property (nonatomic, readonly) UIView *sourceView NS_AVAILABLE_IOS(9_0);

// This rect will be set to the bounds of sourceView before each call to
// -previewingContext:viewControllerForLocation:

@property (nonatomic) CGRect sourceRect NS_AVAILABLE_IOS(9_0);

@end


NS_CLASS_AVAILABLE_IOS(9_0) @protocol UIViewControllerPreviewingDelegate <NSObject>

// If you return nil, a preview presentation will not be performed
- (nullable UIViewController *)previewingContext:(id <UIViewControllerPreviewing>)previewingContext viewControllerForLocation:(CGPoint)location NS_AVAILABLE_IOS(9_0);
- (void)previewingContext:(id <UIViewControllerPreviewing>)previewingContext commitViewController:(UIViewController *)viewControllerToCommit NS_AVAILABLE_IOS(9_0);

@end

@interface UIViewController (UIViewControllerPreviewingRegistration)

// Registers a view controller to participate with 3D Touch preview (peek) and commit (pop).
- (id <UIViewControllerPreviewing>)registerForPreviewingWithDelegate:(id<UIViewControllerPreviewingDelegate>)delegate sourceView:(UIView *)sourceView NS_AVAILABLE_IOS(9_0);
- (void)unregisterForPreviewingWithContext:(id <UIViewControllerPreviewing>)previewing NS_AVAILABLE_IOS(9_0);

@end

@interface UIViewController (UIScreenEdgesDeferringSystemGestures)

// Override to return a child view controller or nil. If non-nil, that view controller's screen edges deferring system gestures will be used. If nil, self is used. Whenever the return value changes, -setNeedsScreenEdgesDeferringSystemGesturesUpdate should be called.
- (nullable UIViewController *)childViewControllerForScreenEdgesDeferringSystemGestures API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// Controls the application's preferred screen edges deferring system gestures when this view controller is shown. Default is UIRectEdgeNone.
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// This should be called whenever the return values for the view controller's screen edges deferring system gestures have changed.
- (void)setNeedsUpdateOfScreenEdgesDeferringSystemGestures API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end


@interface UIViewController (UIHomeIndicatorAutoHidden)

// Override to return a child view controller or nil. If non-nil, that view controller's home indicator auto-hiding will be used. If nil, self is used. Whenever the return value changes, -setNeedsHomeIndicatorAutoHiddenUpdate should be called.
- (nullable UIViewController *)childViewControllerForHomeIndicatorAutoHidden API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// Controls the application's preferred home indicator auto-hiding when this view controller is shown.
- (BOOL)prefersHomeIndicatorAutoHidden API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// This should be called whenever the return values for the view controller's home indicator auto-hiding have changed.
- (void)setNeedsUpdateOfHomeIndicatorAutoHidden API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end


@protocol UIPreviewActionItem;

@interface UIViewController ()

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) NSArray <id <UIPreviewActionItem>> *previewActionItems NS_AVAILABLE_IOS(9_0);
#else
- (NSArray <id <UIPreviewActionItem>> *)previewActionItems NS_AVAILABLE_IOS(9_0);
#endif

@end


NS_CLASS_AVAILABLE_IOS(9_0) @protocol UIPreviewActionItem <NSObject>
@property(nonatomic, copy, readonly) NSString *title;
@end

typedef NS_ENUM(NSInteger,UIPreviewActionStyle) {
    UIPreviewActionStyleDefault=0,
    UIPreviewActionStyleSelected,
    UIPreviewActionStyleDestructive,
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE_IOS(9_0) @interface UIPreviewAction : NSObject <NSCopying,UIPreviewActionItem>

@property(nonatomic, copy, readonly) void (^handler)(id<UIPreviewActionItem> action, UIViewController *previewViewController);

+ (instancetype)actionWithTitle:(NSString *)title style:(UIPreviewActionStyle)style handler:(void (^)(UIPreviewAction *action, UIViewController *previewViewController))handler;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface UIPreviewActionGroup : NSObject <NSCopying,UIPreviewActionItem>
+ (instancetype)actionGroupWithTitle:(NSString *)title style:(UIPreviewActionStyle)style actions:(NSArray<UIPreviewAction *> *)actions;
@end

NS_ASSUME_NONNULL_END
