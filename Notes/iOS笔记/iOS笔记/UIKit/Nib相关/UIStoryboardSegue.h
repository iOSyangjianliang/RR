//
//  UIStoryboardSegue.h
//  UIKit
//
//  Copyright 2011-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIViewController;

NS_CLASS_AVAILABLE_IOS(5_0) @interface UIStoryboardSegue : NSObject

// Convenience constructor for returning a segue that performs a handler block in its -perform method.
// 方便的构造函数，用于返回在其-perform方法中执行处理程序块的Segue。
+ (instancetype)segueWithIdentifier:(nullable NSString *)identifier source:(UIViewController *)source destination:(UIViewController *)destination performHandler:(void (^)(void))performHandler NS_AVAILABLE_IOS(6_0);

- (instancetype)initWithIdentifier:(nullable NSString *)identifier source:(UIViewController *)source destination:(UIViewController *)destination NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (nullable, nonatomic, copy, readonly) NSString *identifier;
@property (nonatomic, readonly) __kindof UIViewController *sourceViewController;
@property (nonatomic, readonly) __kindof UIViewController *destinationViewController;

/// Subclasses can override this method to augment or replace the effect of this segue. For example, to animate alongside the effect of a Modal Presentation segue, an override of this method can call super, then send -animateAlongsideTransition:completion: to the transitionCoordinator of the destinationViewController.
/// The segue runtime will call +[UIView setAnimationsAreEnabled:] prior to invoking this method, based on the value of the Animates checkbox in the Properties Inspector for the segue.
/// 子类可以重写此方法来扩充或替换此segue的效果。 例如，要在模态演示文稿segue的效果旁边进行动画制作，可以调用super方法，然后将-animateAlongsideTransition：completion：发送到destinationViewController的transitionCoordinator。
///在执行此方法之前，segue运行时将调用+ [UIView setAnimationsAreEnabled：]，这取决于Segue属性检查器中Animates复选框的值。
- (void)perform;

@end

/// Encapsulates the source of a prospective unwind segue.
/// You do not create instances of this class directly. Instead, UIKit creates an instance of this class and sends -allowedChildViewControllersForUnwindingFromSource: to each ancestor of the sourceViewController until it finds a view controller which returns YES from -canPerformUnwindSegueAction:fromViewController:withSender:.
///封装一个预期的放松继续的来源。
///你不直接创建这个类的实例。 相反，UIKit创建此类的一个实例，并向sourceViewController的每个父类发送-allowedChildViewControllersForUnwindingFromSource：直到找到从-canPerformUnwindSegueAction：fromViewController：withSender：返回YES的视图控制器。
NS_CLASS_AVAILABLE_IOS(9_0) @interface UIStoryboardUnwindSegueSource : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (readonly) UIViewController *sourceViewController;
@property (readonly) SEL unwindAction;
@property (readonly, nullable) id sender;

@end

NS_ASSUME_NONNULL_END
