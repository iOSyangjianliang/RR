//
//  UICollectionViewController.h
//  UIKit
//
//  Copyright (c) 2011-2017 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UICollectionViewLayout;
@class UICollectionViewController;

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewController : UIViewController <UICollectionViewDelegate, UICollectionViewDataSource>

//用指定的layout初始化UICollectionViewController
- (instancetype)initWithCollectionViewLayout:(UICollectionViewLayout *)layout NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

//nullable
@property (nullable, nonatomic, strong) __kindof UICollectionView *collectionView;

// Defaults to YES, and if YES, any selection is cleared in viewWillAppear:
// This property has no effect if the useLayoutToLayoutNavigationTransitions property is set to YES
// 默认为YES，如果为YES，则在viewWillAppear中清除任何选中
// 如果useLayoutToLayoutNavigationTransitions属性设置为YES，则此属性无效
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear;

// Set to YES before pushing a a UICollectionViewController onto a
// UINavigationController. The top view controller of the navigation controller
// must be a UICollectionViewController that was pushed with this property set
// to NO. This property should NOT be changed on a UICollectionViewController that
// has already been pushed onto a UINavigationController.
//在导航过渡的时候是否使用layout，在push之前设置，之后设置无效
@property (nonatomic, assign) BOOL useLayoutToLayoutNavigationTransitions NS_AVAILABLE_IOS(7_0);

// The layout object is needed when defining interactive layout to layout transitions.定义布局转换的交互式布局时需要布局对象。
//当前的collectionViewLayout，只读属性
@property (nonatomic, readonly) UICollectionViewLayout *collectionViewLayout NS_AVAILABLE_IOS(7_0);

// Defaults to YES, and if YES, a system standard reordering gesture is used to drive collection view reordering 默认为YES，如果为YES，则使用系统标准重新排序手势来驱动集合视图重新排序
//是否允许排序，默认是YES
@property (nonatomic) BOOL installsStandardGestureForInteractiveMovement NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
