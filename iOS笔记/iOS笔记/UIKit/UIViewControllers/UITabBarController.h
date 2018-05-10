//
//  UITabBarController.h
//  UIKit
//
//  Copyright (c) 2007-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitioning.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITabBar.h>

NS_ASSUME_NONNULL_BEGIN

@class UIView, UIImage, UINavigationController, UITabBarItem;
@protocol UITabBarControllerDelegate;

/*!
 UITabBarController manages a button bar and transition view, for an application with multiple top-level modes.
 
 To use in your application, add its view to the view hierarchy, then add top-level view controllers in order.
 Most clients will not need to subclass UITabBarController.
 
 If more than five view controllers are added to a tab bar controller, only the first four will display.
 The rest will be accessible under an automatically generated More item.
 
 UITabBarController is rotatable if all of its view controllers are rotatable.
 */

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITabBarController : UIViewController <UITabBarDelegate, NSCoding>
//设置控制器数组
@property(nullable, nonatomic,copy) NSArray<__kindof UIViewController *> *viewControllers;
// If the number of view controllers is greater than the number displayable by a tab bar, a "More" navigation controller will automatically be shown.
// The "More" navigation controller will not be returned by -viewControllers, but it may be returned by -selectedViewController.
//如果视图控制器的数量大于选项卡栏显示的数量，那么将自动显示一个“更多”的导航控制器。
//“更多”的导航控制器将不会返回-视图控制器，但它可能由-selectedViewController返回
//设置控制器数组 设置动画
- (void)setViewControllers:(NSArray<__kindof UIViewController *> * __nullable)viewControllers animated:(BOOL)animated;
//选中的控制器
@property(nullable, nonatomic, assign) __kindof UIViewController *selectedViewController; // This may return the "More" navigation controller if it exists.
//选中索引值
@property(nonatomic) NSUInteger selectedIndex;

//当item超过五个时 就会有一个更多《只读》
@property(nonatomic, readonly) UINavigationController *moreNavigationController __TVOS_PROHIBITED; // Returns the "More" navigation controller, creating it if it does not already exist.
@property(nullable, nonatomic, copy) NSArray<__kindof UIViewController *> *customizableViewControllers __TVOS_PROHIBITED; // If non-nil, then the "More" view will include an "Edit" button that displays customization UI for the specified controllers. By default, all view controllers are customizable.如果是非nil，那么“More”视图将包含一个“Edit”按钮，该按钮将为指定的控制器显示定制UI。默认情况下，所有视图控制器都是可定制的

//tab条
@property(nonatomic,readonly) UITabBar *tabBar NS_AVAILABLE_IOS(3_0); // Provided for -[UIActionSheet showFromTabBar:]. Attempting to modify the contents of the tab bar directly will throw an exception.提供-[UIActionSheet showFromTabBar:]。试图直接修改选项卡栏的内容将会抛出一个异常。
//代理
@property(nullable, nonatomic,weak) id<UITabBarControllerDelegate> delegate;

@end

@protocol UITabBarControllerDelegate <NSObject>
@optional
//返回NO，不能显示选中的视图控制器(可在此代理present／push登录或其他页面)
- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController NS_AVAILABLE_IOS(3_0);
//视图显示后调用
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;

//将要结束自定义item时调用
- (void)tabBarController:(UITabBarController *)tabBarController willBeginCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
//将要结束自定义item时调用
- (void)tabBarController:(UITabBarController *)tabBarController willEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
//结束自定义item的顺序
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed __TVOS_PROHIBITED;

- (UIInterfaceOrientationMask)tabBarControllerSupportedInterfaceOrientations:(UITabBarController *)tabBarController NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
- (UIInterfaceOrientation)tabBarControllerPreferredInterfaceOrientationForPresentation:(UITabBarController *)tabBarController NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

- (nullable id <UIViewControllerInteractiveTransitioning>)tabBarController:(UITabBarController *)tabBarController
                               interactionControllerForAnimationController: (id <UIViewControllerAnimatedTransitioning>)animationController NS_AVAILABLE_IOS(7_0);

- (nullable id <UIViewControllerAnimatedTransitioning>)tabBarController:(UITabBarController *)tabBarController
                     animationControllerForTransitionFromViewController:(UIViewController *)fromVC
                                                       toViewController:(UIViewController *)toVC  NS_AVAILABLE_IOS(7_0);

@end

@interface UIViewController (UITabBarControllerItem)
//当前视图的UITabBarItem对象
@property(null_resettable, nonatomic, strong) UITabBarItem *tabBarItem; // Automatically created lazily with the view controller's title if it's not set explicitly.

@property(nullable, nonatomic, readonly, strong) UITabBarController *tabBarController; // If the view controller has a tab bar controller as its ancestor, return it. Returns nil otherwise.如果视图控制器有一个标签栏控制器作为它的父类，返回它。否则返回nil。

@end

NS_ASSUME_NONNULL_END
