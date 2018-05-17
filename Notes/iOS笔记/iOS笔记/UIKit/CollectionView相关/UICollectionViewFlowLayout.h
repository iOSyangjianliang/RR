//
//  UICollectionViewFlowLayout.h
//  UIKit
//
//  Copyright (c) 2011-2017 Apple Inc. All rights reserved.
//

#import <UIKit/UICollectionViewLayout.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSString *const UICollectionElementKindSectionHeader NS_AVAILABLE_IOS(6_0); //组头注册kind
UIKIT_EXTERN NSString *const UICollectionElementKindSectionFooter NS_AVAILABLE_IOS(6_0); //组尾注册kind
UIKIT_EXTERN const CGSize UICollectionViewFlowLayoutAutomaticSize NS_AVAILABLE_IOS(10_0);

//滚动方向
typedef NS_ENUM(NSInteger, UICollectionViewScrollDirection) {
    UICollectionViewScrollDirectionVertical,   //垂直
    UICollectionViewScrollDirectionHorizontal  //水平
};

typedef NS_ENUM(NSInteger, UICollectionViewFlowLayoutSectionInsetReference) {
    UICollectionViewFlowLayoutSectionInsetFromContentInset,
    UICollectionViewFlowLayoutSectionInsetFromSafeArea,
    UICollectionViewFlowLayoutSectionInsetFromLayoutMargins
} API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewFlowLayoutInvalidationContext : UICollectionViewLayoutInvalidationContext
//如果设置为NO，则流布局将不会调用FlowLayoutDelegate代理的size等代理方法
@property (nonatomic) BOOL invalidateFlowLayoutDelegateMetrics; // if set to NO, flow layout will not requery the collection view delegate for size information etc.
//如果设置为NO，流布局将保留所有的布局信息，实际上不会使其无效 - 对于只使其一部分失效的子类很有用
@property (nonatomic) BOOL invalidateFlowLayoutAttributes; // if set to NO, flow layout will keep all layout information, effectively not invalidating - useful for a subclass which invalidates only a piece of itself

@end

@protocol UICollectionViewDelegateFlowLayout <UICollectionViewDelegate>
@optional

//设置具体indexPath的item大小
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath;
//设置具体section的上下左右留白，可以定义每组的组间距
- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout insetForSectionAtIndex:(NSInteger)section;
//设置行最小间隔-基于布局方向
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section;
//设置item间最小间隔
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section;
//设置头部引用视图的大小
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForHeaderInSection:(NSInteger)section;
//设置尾部引用视图的大小
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForFooterInSection:(NSInteger)section;

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewFlowLayout : UICollectionViewLayout

//设置item行之间的最小间隔，基于滚动方向上的行，非水平
@property (nonatomic) CGFloat minimumLineSpacing;
//设置item之间的最小间隔
@property (nonatomic) CGFloat minimumInteritemSpacing;
//设置item的大小
@property (nonatomic) CGSize itemSize;
//设置item大小的估算值，默认是CGSizeZero(iOS8之后有效)
@property (nonatomic) CGSize estimatedItemSize NS_AVAILABLE_IOS(8_0); // defaults to CGSizeZero - setting a non-zero size enables cells that self-size via -preferredLayoutAttributesFittingAttributes:默认为CGSizeZero - 设置非零大小可以通过-preferredLayoutAttributesFittingAttributes启用“自适应”的单元格：

//设置滚动方向-默认垂直
@property (nonatomic) UICollectionViewScrollDirection scrollDirection; // default is UICollectionViewScrollDirectionVertical
//设置头部引用视图的大小，对于垂直滚动时，宽不起作用，高度起作用
@property (nonatomic) CGSize headerReferenceSize;
//设置尾部引用视图的大小，对于垂直滚动时，高度不起作用，宽起作用
@property (nonatomic) CGSize footerReferenceSize;
//设置section的上下左右组间距
@property (nonatomic) UIEdgeInsets sectionInset;

/// The reference boundary that the section insets will be defined as relative to. Defaults to `.fromContentInset`.
/// NOTE: Content inset will always be respected at a minimum. For example, if the sectionInsetReference equals `.fromSafeArea`, but the adjusted content inset is greater that the combination of the safe area and section insets, then section content will be aligned with the content inset instead. 章节插图的参考边界将被定义为相对于。 默认为`.fromContentInset`。注：内容嵌入将始终遵守最低限度。 例如，如果sectionInsetReference等于`.fromSafeArea`，但调整后的内容插入大于安全区域和区段插入的组合，则区段内容将与内容插入对齐。
@property (nonatomic) UICollectionViewFlowLayoutSectionInsetReference sectionInsetReference API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

// Set these properties to YES to get headers that pin to the top of the screen and footers that pin to the bottom while scrolling (similar to UITableView).
//将这些属性设置为YES，以获取钉在屏幕顶部的标题和在滚动时钉住底部的页脚（类似于UITableViewPlain）（9+）
@property (nonatomic) BOOL sectionHeadersPinToVisibleBounds NS_AVAILABLE_IOS(9_0);
@property (nonatomic) BOOL sectionFootersPinToVisibleBounds NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
