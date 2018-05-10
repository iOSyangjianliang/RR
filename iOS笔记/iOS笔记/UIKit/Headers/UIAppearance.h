//
//  UIAppearance.h
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

//
//  UIAppearance.h
//  UIKit
//
//  Copyright 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class UITraitCollection;

/* To participate in the appearance proxy API, tag your appearance property selectors in your header with UI_APPEARANCE_SELECTOR.
 
 Appearance property selectors must be of the form:
 - (void)setProperty:(PropertyType)property forAxis1:(IntegerType)axis1 axis2:(IntegerType)axis2 axisN:(IntegerType)axisN;
 - (PropertyType)propertyForAxis1:(IntegerType)axis1 axis2:(IntegerType)axis2 axisN:(IntegerType)axisN;
 You may have no axes or as many as you like for any property. PropertyType may be any standard iOS type: id, NSInteger, NSUInteger, CGFloat, CGPoint, CGSize, CGRect, UIEdgeInsets or UIOffset. IntegerType must be either NSInteger or NSUInteger; we will throw an exception if other types are used in the axes.
 */
//宏UI_APPEARANCE_SELECTOR   eg: 1.[[UIView appearance] setBackgroundColor:[UIColor redColor]];一旦这样修改，你App程序里面的所有UIView属性都会变为这个值，如果要单独修改某个2.view.backgroundColor = [UIColor blackColor],2必须在1执行之后才会有效
#define UI_APPEARANCE_SELECTOR __attribute__((annotate("ui_appearance_selector")))

@protocol UIAppearanceContainer <NSObject> @end

@protocol UIAppearance <NSObject>
/* To customize the appearance of all instances of a class, send the relevant appearance modification messages to the appearance proxy for the class. For example, to modify the bar tint color for all UINavigationBar instances:
 [[UINavigationBar appearance] setBarTintColor:myColor];
 
 Note for iOS7: On iOS7 the tintColor property has moved to UIView, and now has special inherited behavior described in UIView.h.
 This inherited behavior can conflict with the appearance proxy, and therefore tintColor is now disallowed with the appearance proxy.
 为了定制类的所有实例的外观，将相关的外观修改消息发送到类的外观代理。例如，要修改所有UINavigationBar实例的bar色调颜色:
 [[UINavigationBar appearance]setBarTintColor myColor):;
 
 注意iOS7:在iOS7上，tintColor属性已经转移到UIView，现在有了在uiviewh.h中描述的特殊的继承行为。
 这种继承行为可能与外观代理发生冲突，因此tintColor现在不允许出现在外观代理上。
 */
+ (instancetype)appearance;

/* To customize the appearances for instances of a class contained within an instance of a container class, or instances in a hierarchy, use +appearanceWhenContainedInInstancesOfClasses: for the appropriate appearance proxy. For example:
 
 [[UINavigationBar appearanceWhenContainedInInstancesOfClasses:@[[UISplitViewController class]]] setBarTintColor:myColor];
 [[UINavigationBar appearanceWhenContainedInInstancesOfClasses:@[[UITabBarController class], [UISplitViewController class]]] setBarTintColor:myTabbedNavBarColor];
 
 In any given view hierarchy the outermost appearance proxy wins. Specificity (depth of the chain) is the tie-breaker.
 
 In other words, the containment statement is treated as a partial ordering. Given a concrete ordering (actual subview hierarchy), we select the partial ordering that is the first unique match when reading the actual hierarchy from the window down.
 */
+ (instancetype)appearanceWhenContainedIn:(nullable Class <UIAppearanceContainer>)ContainerClass, ... NS_REQUIRES_NIL_TERMINATION NS_DEPRECATED_IOS(5_0, 9_0, "Use +appearanceWhenContainedInInstancesOfClasses: instead") __TVOS_PROHIBITED;
+ (instancetype)appearanceWhenContainedInInstancesOfClasses:(NSArray<Class <UIAppearanceContainer>> *)containerTypes NS_AVAILABLE_IOS(9_0);

+ (instancetype)appearanceForTraitCollection:(UITraitCollection *)trait NS_AVAILABLE_IOS(8_0);
+ (instancetype)appearanceForTraitCollection:(UITraitCollection *)trait whenContainedIn:(nullable Class <UIAppearanceContainer>)ContainerClass, ... NS_REQUIRES_NIL_TERMINATION NS_DEPRECATED_IOS(8_0, 9_0, "Use +appearanceForTraitCollection:whenContainedInInstancesOfClasses: instead") __TVOS_PROHIBITED;
+ (instancetype)appearanceForTraitCollection:(UITraitCollection *)trait whenContainedInInstancesOfClasses:(NSArray<Class <UIAppearanceContainer>> *)containerTypes  NS_AVAILABLE_IOS(9_0);

@end
NS_ASSUME_NONNULL_END
