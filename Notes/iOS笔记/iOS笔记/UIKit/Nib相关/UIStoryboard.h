//
//  UIStoryboard.h
//  UIKit
//
//  Copyright 2011-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIViewController;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(5_0) @interface UIStoryboard : NSObject {
}
//初始化UIStoryboard
+ (UIStoryboard *)storyboardWithName:(NSString *)name bundle:(nullable NSBundle *)storyboardBundleOrNil;

//获取SB中有箭头指向的控制器
- (nullable __kindof UIViewController *)instantiateInitialViewController;
//根据SB中注册的identifier获取控制器
- (__kindof UIViewController *)instantiateViewControllerWithIdentifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
