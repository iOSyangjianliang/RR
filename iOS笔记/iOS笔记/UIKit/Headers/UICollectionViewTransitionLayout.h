//
//  UICollectionView.h
//  UIKit
//
//  Copyright (c) 2012-2017 Apple Inc. All rights reserved.
//

#import <UIKit/UICollectionViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewTransitionLayout : UICollectionViewLayout

//UICollectionView过渡的进度值
@property (assign, nonatomic) CGFloat transitionProgress;
//当前UICollectionView的layout
@property (readonly, nonatomic) UICollectionViewLayout *currentLayout;
//切换之后的layout
@property (readonly, nonatomic) UICollectionViewLayout *nextLayout;

//初始化TransitionLayout对象
- (instancetype)initWithCurrentLayout:(UICollectionViewLayout *)currentLayout nextLayout:(UICollectionViewLayout *)newLayout NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

//下面的方法用于储存过渡期LayoutAttributes的变化值,稳定值为0
- (void)updateValue:(CGFloat)value forAnimatedKey:(NSString *)key;
- (CGFloat)valueForAnimatedKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END




