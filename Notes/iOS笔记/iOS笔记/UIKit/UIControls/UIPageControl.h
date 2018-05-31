//
//  UIPageControl.h
//  UIKit
//
//  Copyright (c) 2008-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIPageControl : UIControl 
//默认为0
@property(nonatomic) NSInteger numberOfPages;
//默认值为0.固定值为[0 numberOfPages-1]
@property(nonatomic) NSInteger currentPage;
//如果只有一个页面，隐藏指示器。默认为NO
@property(nonatomic) BOOL hidesForSinglePage;

//如果设置，点击新页面将不会更新当前显示的页面，直到调用-updateCurrentPageDisplay才去更新。默认为NO
@property(nonatomic) BOOL defersCurrentPageDisplay;
//更新页面显示以匹配当前页面。如果defersCurrentPageDisplay为NO，则被忽略。直接设置page value将立即更新
- (void)updateCurrentPageDisplay;
//返回给定页数显示点所需的最小大小。如果页面数量可能发生变化，则可用于大小控制
- (CGSize)sizeForNumberOfPages:(NSInteger)pageCount;

//非当前Page的颜色
@property(nullable, nonatomic,strong) UIColor *pageIndicatorTintColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;
//当前Page的颜色
@property(nullable, nonatomic,strong) UIColor *currentPageIndicatorTintColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END
