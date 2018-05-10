//
//  UICollectionViewCell.h
//  UIKit
//
//  Copyright (c) 2011-2017 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UICollectionView.h>

NS_ASSUME_NONNULL_BEGIN

@class UICollectionViewLayout;
@class UICollectionView;
@class UICollectionViewLayoutAttributes;
@class UILongPressGestureRecognizer;

typedef NS_ENUM(NSInteger, UICollectionViewCellDragState) {
    UICollectionViewCellDragStateNone,
    /* The cell is in the "lifting" state.
     */
    UICollectionViewCellDragStateLifting,
    
    /* A cell in the "dragging" state is left behind with a
     * "ghosted" appearance to denote where the drag
     * started from.
     */
    UICollectionViewCellDragStateDragging
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionReusableView : UIView
//获取复用标识符reuseIdentifier
@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;

// Override point.
// Called by the collection view before the instance is returned from the reuse queue.
// Subclassers must call super.
// 重写要点
// 在实例从重用队列返回之前，由集合视图调用。
// 重写子类必须调用父类
- (void)prepareForReuse;

// Classes that want to support custom layout attributes specific to a given UICollectionViewLayout subclass can apply them here.
// This allows the view to work in conjunction with a layout class that returns a custom subclass of UICollectionViewLayoutAttributes from -layoutAttributesForItem: or the corresponding layoutAttributesForHeader/Footer methods.
// -applyLayoutAttributes: is then called after the view is added to the collection view and just before the view is returned from the reuse queue.
// Note that -applyLayoutAttributes: is only called when attributes change, as defined by -isEqual:.
// 想要支持特定于给定UICollectionViewLayout子类的自定义布局属性的类可以在这里应用它们。
// 这允许视图与布局类一起工作，该布局类从-layoutAttributesForItem：或相应的layoutAttributesForHeader / Footer方法返回UICollectionViewLayoutAttributes的自定义子类。
// -applyLayoutAttributes：然后在视图添加到集合视图之后并且在重用队列返回视图之前调用。
// 请注意，只有在属性更改时才会调用-applyLayoutAttributes：由-isEqual：定义。

//根据LayoutAttributes来布局当前View，在view被添加到collectionView上但是还没有被复用队列返回的时候调用
- (void)applyLayoutAttributes:(UICollectionViewLayoutAttributes *)layoutAttributes;

// Override these methods to provide custom UI for specific layouts.
// 重写这些方法为特定布局提供自定义UI。
- (void)willTransitionFromLayout:(UICollectionViewLayout *)oldLayout toLayout:(UICollectionViewLayout *)newLayout;
- (void)didTransitionFromLayout:(UICollectionViewLayout *)oldLayout toLayout:(UICollectionViewLayout *)newLayout;

//重写调整Size属性使自适应,需要先调用父类获取再修改后返回UICollectionViewLayoutAttributes*
- (UICollectionViewLayoutAttributes *)preferredLayoutAttributesFittingAttributes:(UICollectionViewLayoutAttributes *)layoutAttributes NS_AVAILABLE_IOS(8_0);

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewCell : UICollectionReusableView

@property (nonatomic, readonly) UIView *contentView; // add custom subviews to the cell's contentView将自定义子视图添加到cell的contentView

// Cells become highlighted when the user touches them.
// The selected state is toggled when the user lifts up from a highlighted cell.
// Override these methods to provide custom UI for a selected or highlighted state.
// The collection view may call the setters inside an animation block.
//当用户触摸它们时，单元格会变亮。
//当用户从突出显示的单元格中提起时，所选状态将被切换。
//重写这些方法来为选定或突出显示的状态提供自定义UI。
//可以在动画块中进行设置。
@property (nonatomic, getter=isSelected) BOOL selected;
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

// Override this method to modify the visual appearance for a particular
// dragState.
//
// Call super if you want to add to the existing default implementation.
//
// 重写此方法来修改特定的外观
// dragState。
//
// 如果你想添加到现有的默认实现中，请调用super。
- (void)dragStateDidChange:(UICollectionViewCellDragState)dragState API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// The background view is a subview behind all other views.
// If selectedBackgroundView is different than backgroundView, it will be placed above the background view and animated in on selection.
//backgroundView添加在所有其他视图的下面。
//如果selectedBackgroundView与backgroundView不同，它将被放置在backgroundView的上方，并在选择时进行动画处理。
@property (nonatomic, strong, nullable) UIView *backgroundView;
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

@end

NS_ASSUME_NONNULL_END
