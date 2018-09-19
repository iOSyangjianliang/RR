//
//  UICollectionViewLayout.h
//  UIKit
//
//  Copyright (c) 2011-2017 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/CATransform3D.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/UIInterface.h>

// The UICollectionViewLayout class is provided as an abstract class for subclassing to define custom collection layouts.
// Defining a custom layout is an advanced operation intended for applications with complex needs.

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, UICollectionElementCategory) {
    UICollectionElementCategoryCell,
    UICollectionElementCategorySupplementaryView,
    UICollectionElementCategoryDecorationView
};

@class UICollectionViewLayoutAttributes;
@class UICollectionView;
@class UINib;

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewLayoutAttributes : NSObject <NSCopying, UIDynamicItem>

//设置item的frame
@property (nonatomic) CGRect frame;
//设置item的center
@property (nonatomic) CGPoint center;
//设置item的size
@property (nonatomic) CGSize size;
//设置item的transform3D效果
@property (nonatomic) CATransform3D transform3D;
//设置item的bounds
@property (nonatomic) CGRect bounds NS_AVAILABLE_IOS(7_0);
//设置item的transform效果
@property (nonatomic) CGAffineTransform transform NS_AVAILABLE_IOS(7_0);
//设置item的透明度
@property (nonatomic) CGFloat alpha;
//设置item的zIndex，默认是0和其他item在同一平面；设置小于0，在其他item下面
@property (nonatomic) NSInteger zIndex; // default is 0
@property (nonatomic, getter=isHidden) BOOL hidden; // As an optimization, UICollectionView might not create a view for items whose hidden attribute is YES 作为优化，UICollectionView可能不会为隐藏属性为YES的项目创建视图
//设置item的indexPath
@property (nonatomic, strong) NSIndexPath *indexPath;

//设置当前元素的类别，是个枚举变量 cell/supplementaryView/decorationView
@property (nonatomic, readonly) UICollectionElementCategory representedElementCategory;
//展示的元素类型，如果是UICollectionElementCategoryCell,则为nil
@property (nonatomic, readonly, nullable) NSString *representedElementKind; // nil when representedElementCategory is UICollectionElementCategoryCell

//指定indexPath的cell的layoutAttributes
+ (instancetype)layoutAttributesForCellWithIndexPath:(NSIndexPath *)indexPath;
//指定indexPath的supplementaryView的layoutAttributes
+ (instancetype)layoutAttributesForSupplementaryViewOfKind:(NSString *)elementKind withIndexPath:(NSIndexPath *)indexPath;
//指定indexPath的decorationView的layoutAttributes
+ (instancetype)layoutAttributesForDecorationViewOfKind:(NSString *)decorationViewKind withIndexPath:(NSIndexPath *)indexPath;

@end

typedef NS_ENUM(NSInteger, UICollectionUpdateAction) {
    UICollectionUpdateActionInsert,
    UICollectionUpdateActionDelete,
    UICollectionUpdateActionReload,
    UICollectionUpdateActionMove,
    UICollectionUpdateActionNone
};

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewUpdateItem : NSObject

@property (nonatomic, readonly, nullable) NSIndexPath *indexPathBeforeUpdate; // nil for UICollectionUpdateActionInsert
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathAfterUpdate; // nil for UICollectionUpdateActionDelete
@property (nonatomic, readonly) UICollectionUpdateAction updateAction;

@end

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewLayoutInvalidationContext : NSObject

@property (nonatomic, readonly) BOOL invalidateEverything; // set to YES when invalidation occurs because the collection view is sent -reloadData
@property (nonatomic, readonly) BOOL invalidateDataSourceCounts; // if YES, the layout should requery section and item counts from the collection view - set to YES when the collection view is sent -reloadData and when items are inserted or deleted

//使指定indexPath数组内Item（Cell）、Supplementary View 或 Decoration View 失效：
- (void)invalidateItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(8_0);
- (void)invalidateSupplementaryElementsOfKind:(NSString *)elementKind atIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(8_0);
- (void)invalidateDecorationElementsOfKind:(NSString *)elementKind atIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *invalidatedItemIndexPaths NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, NSArray<NSIndexPath *> *> *invalidatedSupplementaryIndexPaths NS_AVAILABLE_IOS(8_0); // keys are element kind strings - values are NSArrays of NSIndexPaths
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, NSArray<NSIndexPath *> *> *invalidatedDecorationIndexPaths NS_AVAILABLE_IOS(8_0); // keys are element kind strings - values are NSArrays of NSIndexPaths

@property (nonatomic) CGPoint contentOffsetAdjustment NS_AVAILABLE_IOS(8_0); // delta to be applied to the collection view's current contentOffset - default is CGPointZero
@property (nonatomic) CGSize contentSizeAdjustment NS_AVAILABLE_IOS(8_0); // delta to be applied to the current content size - default is CGSizeZero

// Reordering support
@property (nonatomic, readonly, copy, nullable) NSArray<NSIndexPath *> *previousIndexPathsForInteractivelyMovingItems NS_AVAILABLE_IOS(9_0); // index paths of moving items prior to the invalidation
@property (nonatomic, readonly, copy, nullable) NSArray<NSIndexPath *> *targetIndexPathsForInteractivelyMovingItems NS_AVAILABLE_IOS(9_0); // index paths of moved items following the invalidation
@property (nonatomic, readonly) CGPoint interactiveMovementTarget NS_AVAILABLE_IOS(9_0);

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewLayout : NSObject <NSCoding>
//构造函数
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Methods in this class are meant to be overridden and will be called by its collection view to gather layout information.
// To get the truth on the current state of the collection view, call methods on UICollectionView rather than these.
// 这个类中的方法意味着被重写，并且会被其集合视图调用以收集布局信息。
// 要获得collectionView的当前真实状态，请调用UICollectionView上的属性方法而不是这些方法。

//当前layout服务的collectionView对象
@property (nullable, nonatomic, readonly) UICollectionView *collectionView;

// Call -invalidateLayout to indicate that the collection view needs to requery the layout information.
// Subclasses must always call super if they override.
//调用-invalidateLayout来指示集合视图需要重新查找布局信息。
//重写必须调用父类。
//使当前layout无效，会触发collectionView的reloadData
- (void)invalidateLayout;
//使当前layout无效，并且提供一个验证的上下文，也会触发collectionView的reloadData
- (void)invalidateLayoutWithContext:(UICollectionViewLayoutInvalidationContext *)context NS_AVAILABLE_IOS(7_0);

//注册decorationView用Class/nib
- (void)registerClass:(nullable Class)viewClass forDecorationViewOfKind:(NSString *)elementKind;
- (void)registerNib:(nullable UINib *)nib forDecorationViewOfKind:(NSString *)elementKind;

@end

#park mark 布局UIcollectionView子视图分类
@interface UICollectionViewLayout (UISubclassingHooks)

//在需要的时候重写自定义layoutAttributesClass和invalidationContextClass
#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) Class layoutAttributesClass; // override this method to provide a custom class to be used when instantiating instances of UICollectionViewLayoutAttributes 重写此方法以提供在实例化UICollectionViewLayoutAttributes实例时使用的自定义类
@property(class, nonatomic, readonly) Class invalidationContextClass NS_AVAILABLE_IOS(7_0); // override this method to provide a custom class to be used for invalidation contexts 重写此方法以提供用于无效上下文的自定义类
#else
//重写此方法以提供在实例化UICollectionViewLayoutAttributes实例时使用的自定义类
+ (Class)layoutAttributesClass; // override this method to provide a custom class to be used when instantiating instances of UICollectionViewLayoutAttributes
//重写此方法以提供用于无效上下文的自定义类
+ (Class)invalidationContextClass NS_AVAILABLE_IOS(7_0); // override this method to provide a custom class to be used for invalidation contexts
#endif

// The collection view calls -prepareLayout once at its first layout as the first message to the layout instance.
// The collection view calls -prepareLayout again after layout is invalidated and before requerying the layout information.
// Subclasses should always call super if they override.
//集合视图在其第一个布局中调用-prepareLayout一次，作为布局实例的第一条消息。
//集合视图在布局无效之后和重新布局信息之前再次调用-prepareLayout。
//重写必须调用父类。
//UICollectionView在第一次layout的时候会调用prepareLayout，并且在当前layout invalidated之后也会调用这个方法
- (void)prepareLayout;

// UICollectionView calls these four methods to determine the layout information.
// Implement -layoutAttributesForElementsInRect: to return layout attributes for for supplementary or decoration views, or to perform layout in an as-needed-on-screen fashion.
// Additionally, all layout subclasses should implement -layoutAttributesForItemAtIndexPath: to return layout attributes instances on demand for specific index paths.
// If the layout supports any supplementary or decoration view types, it should also implement the respective atIndexPath: methods for those types.
// UICollectionView调用这四个方法来确定布局信息。
// 实现-layoutAttributesForElementsInRect：返回补充或装饰视图的布局属性，或者按照屏幕上的方式执行布局。
// 此外，所有布局子类都应实现-layoutAttributesForItemAtIndexPath：根据需要为特定索引路径返回布局属性实例。
// 如果布局支持任何补充或装饰视图类型，则还应该为这些类型实现相应的atIndexPath：方法。

//返回给定rect内的layoutAttributes数组
//拿到UICollectionView中所有的UICollectionViewLayoutAttributes信息，可以通过CGRectIntersectsRect方法判断出屏幕上正在显示cell、header、footer的布局信息；并返回该区域内所有元素的布局信息，包括cell,追加视图和装饰视图。
- (nullable NSArray<__kindof UICollectionViewLayoutAttributes *> *)layoutAttributesForElementsInRect:(CGRect)rect; // return an array layout attributes instances for all the views in the given rect 返回给定矩形中的所有视图的数组布局属性实例
//返回给定indexPath的item的layoutAttributes
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
//返回给定indexPath的supplementaryView的layoutAttributes
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryViewOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;
//返回给定indexPath的decorationView的layoutAttributes
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForDecorationViewOfKind:(NSString*)elementKind atIndexPath:(NSIndexPath *)indexPath;

//只要UICollectionView的bounds发生了改变就会调用这个方法，内部会重新调用prepareLayout和layoutAttributesForElementsInRect方法获得所有cell的布局属性，所有是重新定义layout必须实现的方法
//是否需要更新布局。如果collection view需要重新布局返回YES,否则返回NO,默认返回值为NO。子类重载该方法的时候，基于是否collection view的bounds的改变会引发cell和view布局的改变，给出正确的返回值。
//如果collection view的bounds改变,该方法返回YES，collection view通过调用
//invalidateLayoutWithContext方法使原来的layout失效
//这些方法为collection view 在屏幕上布局提供了最基础的布局信息，如果你不想为追加视图和装饰视图布局，可以不去重载相应的方法。
//当collection view的数据发生改变的时候，比如插入或者删除 item的时候，collection view将会要求布局对象更新相应的布局信息。移动、添加、删除 items时都必须更新相应的布局信息以便反映元素最新的位置。对于移动的元素， collection view提供了标准的方法获取更新后的布局信息。而collection view删除或者添加元素的时候，将会调用一些不同的方法，你应该重载以便提供正确的布局信息
- (BOOL)shouldInvalidateLayoutForBoundsChange:(CGRect)newBounds; // return YES to cause the collection view to requery the layout for geometry information 返回YES以使集合视图重新查询几何信息的布局
//collection view 的bounds发生改变的时候返回的无效上下文，该无效上下文描述了bounds变化后需要做出改变的部分。
//该方法默认实现是，通过invalidationContextClass方法返回的类创建一个实例，并作为返回值。如果你想获得一个自定义的无效上下文对象，就要重载invalidationContextClass方法。
//你可以通过重载该方法去创建和配置自定义的无效上下文。如果你重载该方法，第一步应该调用super类获取无效上下文,在获得该无效上下文后，为它设置自定义的属性，并返回。
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForBoundsChange:(CGRect)newBounds NS_AVAILABLE_IOS(7_0);

//当collection view包含self-sizing (自排列)的cell时，这些cell可以在布局attributes 应用到它之前更改这些attributes。一个自排列的cell指明一个不同于布局对象给出的size的时候，就会这么做。当cell设置一系列不同的attributes时，collection view将会调用该方法判断是否需要更新布局，默认返回为NO。
- (BOOL)shouldInvalidateLayoutForPreferredLayoutAttributes:(UICollectionViewLayoutAttributes *)preferredAttributes withOriginalAttributes:(UICollectionViewLayoutAttributes *)originalAttributes NS_AVAILABLE_IOS(8_0);
//该方法返回值是一个上下文，上下文包含布局中需要改变的信息。默认的实现是，使用invalidationContextClass 方法返回的类创建一个实例，并返回。
//你可以通过重载该方法去创建和配置自定义的无效上下文。如果你重载该方法，第一步应该调用super类获取无效上下文,在获得该无效上下文后，为它设置自定义的属性，并返回。
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForPreferredLayoutAttributes:(UICollectionViewLayoutAttributes *)preferredAttributes withOriginalAttributes:(UICollectionViewLayoutAttributes *)originalAttributes NS_AVAILABLE_IOS(8_0);

- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset withScrollingVelocity:(CGPoint)velocity; // return a point at which to rest after scrolling - for layouts that want snap-to-point scrolling behavior //返回滚动后将要停止的点 - 用于需要点对点滚动行为的布局
- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset NS_AVAILABLE_IOS(7_0); // a layout can return the content offset to be applied during transition or update animations 布局可以返回在转换或更新动画期间应用的内容偏移量

//返回collectionView内容区的宽度和高度，子类必须重载该方法，返回值代表了所有内容的宽度和高度，而不仅仅是可见范围的，collectionView通过该信息配置它的滚动范围，默认返回 CGSizeZero
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) CGSize collectionViewContentSize; // Subclasses must override this method and use it to return the width and height of the collection view’s content. These values represent the width and height of all the content, not just the content that is currently visible. The collection view uses this information to configure its own content size to facilitate scrolling.子类必须重写此方法并使用它返回集合视图内容的宽度和高度。 这些值表示所有内容的宽度和高度，而不仅仅是当前可见的内容。 集合视图使用此信息来配置其自己的内容大小以方便滚动。
#else
//返回collectionView内容区的宽度和高度，子类必须重载该方法，返回值代表了所有内容的宽度和高度，而不仅仅是可见范围的，collectionView通过该信息配置它的滚动范围，默认返回 CGSizeZero。
- (CGSize)collectionViewContentSize; // Subclasses must override this method and use it to return the width and height of the collection view’s content. These values represent the width and height of all the content, not just the content that is currently visible. The collection view uses this information to configure its own content size to facilitate scrolling.子类必须重写此方法并使用它返回集合视图内容的宽度和高度。 这些值表示所有内容的宽度和高度，而不仅仅是当前可见的内容。 集合视图使用此信息来配置其自己的内容大小以方便滚动。
#endif

//默认实现返回主包的开发区域的布局方向; FlowLayout返回leftToRight。 子类可以重写这个来指定布局的实现时间布局方向。
@property (nonatomic, readonly) UIUserInterfaceLayoutDirection developmentLayoutDirection; // Default implementation returns the layout direction of the main bundle's development region; FlowLayout returns leftToRight. Subclasses may override this to specify the implementation-time layout direction of the layout.
@property(nonatomic, readonly) BOOL flipsHorizontallyInOppositeLayoutDirection; // Base implementation returns false. If your subclass’s implementation overrides this property to return true, a UICollectionView showing this layout will ensure its bounds.origin is always found at the leading edge, flipping its coordinate system horizontally if necessary.基本实现返回false。 如果你的子类的实现覆盖了这个属性返回true，那么一个显示这个布局的UICollectionView将确保它的坐标方向始终从左边开始，必要时水平地翻转其坐标系统(从右向左布局)

@end

#park mark 用来布局删除、插入动作分类
@interface UICollectionViewLayout (UIUpdateSupportHooks)

// 当删除/插入到集合视图中时，将调用此方法。
// 在调用下面的初始/最终布局属性方法之前调用它，以使布局有机会对插入和删除布局属性进行批量计算。
// updateItems参数是移动到新索引路径的每个元素的UICollectionViewUpdateItem实例数组。
// This method is called when there is an update with deletes/inserts to the collection view.
// It will be called prior to calling the initial/final layout attribute methods below to give the layout an opportunity to do batch computations for the insertion and deletion layout attributes.
// The updateItems parameter is an array of UICollectionViewUpdateItem instances for each element that is moving to a new index path.
- (void)prepareForCollectionViewUpdates:(NSArray<UICollectionViewUpdateItem *> *)updateItems;
//通过该方法添加一些动画到block，或者做一些和最终布局相关的工作。更新结束后调用
- (void)finalizeCollectionViewUpdates; // called inside an animation block after the update更新后在动画块内部调用

- (void)prepareForAnimatedBoundsChange:(CGRect)oldBounds; // UICollectionView calls this when its bounds have changed inside an animation block before displaying cells in its new bounds;UICollectionView在其边界在动画块内部发生变化之前调用它，然后在其新边界中显示单元格
- (void)finalizeAnimatedBoundsChange; // also called inside the animation block也被称为动画块内部

// UICollectionView在传入和传出布局上的布局转换动画之前调用此方法
// UICollectionView calls this when prior the layout transition animation on the incoming and outgoing layout
- (void)prepareForTransitionToLayout:(UICollectionViewLayout *)newLayout NS_AVAILABLE_IOS(7_0);
- (void)prepareForTransitionFromLayout:(UICollectionViewLayout *)oldLayout NS_AVAILABLE_IOS(7_0);
- (void)finalizeLayoutTransition NS_AVAILABLE_IOS(7_0);  // called inside an animation block after the transition在转换之后调用动画块内部

//当集合视图经历动画转换（如批量更新块或动画边界更改）时，将调用此组方法。
//对于失效之前屏幕上的每个元素，finalLayoutAttributesForDisappearingXXX将被调用，并从屏幕上的内容到最终属性进行动画设置。
//对于失效后的屏幕上的每个元素，initialLayoutAttributesForAppearingXXX将被调用，并从这些初始属性到屏幕上的动画设置。
// This set of methods is called when the collection view undergoes an animated transition such as a batch update block or an animated bounds change.
// For each element on screen before the invalidation, finalLayoutAttributesForDisappearingXXX will be called and an animation setup from what is on screen to those final attributes.
// For each element on screen after the invalidation, initialLayoutAttributesForAppearingXXX will be called and an animation setup from those initial attributes to what ends up on screen.

//在一个 item被插入到collection view 的时候，返回开始的布局信息。
//这个方法在 prepareForCollectionViewUpdates:之后和finalizeCollectionViewUpdates 之前调用。
//UICollectionView将会使用该布局信息作为动画的起点(结束点是该item在UICollectionView的最新的位置)。
//如果返回为nil，布局对象将用item的最终的attributes 作为动画的起点和终点。
- (nullable UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingItemAtIndexPath:(NSIndexPath *)itemIndexPath;
//返回值是item即将从collection view移除时候的布局信息，对即将删除的item来讲，
//该方法在 prepareForCollectionViewUpdates: 之后和finalizeCollectionViewUpdates 之前调用。
//在该方法中返回的布局信息描包含 item的状态信息和位置信息。
//UICollectionView将会把该信息作为动画的终点(起点是item当前的位置)。
//如果返回为nil的话，布局对象将会把当前的attribute，作为动画的起点和终点。
- (nullable UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingItemAtIndexPath:(NSIndexPath *)itemIndexPath;

//返回值是追加视图插入UICollectionView时的布局信息。以下方法使用同上
- (nullable UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingSupplementaryElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)elementIndexPath;
//返回值是追加视图删除UICollectionView时的布局信息
- (nullable UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingSupplementaryElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)elementIndexPath;

//返回值是装饰视图插入UICollectionView时的布局信息
- (nullable UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingDecorationElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)decorationIndexPath;
//返回值是装饰视图删除UICollectionView时的布局信息。
- (nullable UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingDecorationElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)decorationIndexPath;

// 在更新块中，这些方法由集合视图调用。
// 返回索引路径数组，以指示布局正在删除或插入以响应更新的视图。
// These methods are called by collection view during an update block.
// Return an array of index paths to indicate views that the layout is deleting or inserting in response to the update.
- (NSArray<NSIndexPath *> *)indexPathsToDeleteForSupplementaryViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
- (NSArray<NSIndexPath *> *)indexPathsToDeleteForDecorationViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
- (NSArray<NSIndexPath *> *)indexPathsToInsertForSupplementaryViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
- (NSArray<NSIndexPath *> *)indexPathsToInsertForDecorationViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);

@end

#park mark 移动动作布局分类(9+)
@interface UICollectionViewLayout (UIReorderingSupportHooks)
//根据item在UICollectionView中的位置获取该item的NSIndexPath。
//第一个参数该item原来的index path，第二个参数是item在collection view中的位置。
//在item移动的过程中，该方法将UICollectionView中的location映射成相应 NSIndexPaths。该方法的默认是显示，查找指定位置的已经存在的cell，返回该cell的NSIndexPaths 。如果在相同的位置有多个cell，该方法默认返回最上层的cell。
- (NSIndexPath *)targetIndexPathForInteractivelyMovingItem:(NSIndexPath *)previousIndexPath withPosition:(CGPoint)position NS_AVAILABLE_IOS(9_0);
//当item在手势交互下移动时，通过该方法返回这个item布局的attributes 。
//默认实现是，复制已存在的attributes，改变attributes两个值，一个是中心点center；另一个是z轴的坐标值，设置成最大值。
//所以该item在collection view的最上层。子类重载该方法，可以按照自己的需求更改attributes，
//首先需要调用super类获取attributes,然后自定义返回的数据结构。
- (UICollectionViewLayoutAttributes *)layoutAttributesForInteractivelyMovingItemAtIndexPath:(NSIndexPath *)indexPath withTargetPosition:(CGPoint)position NS_AVAILABLE_IOS(9_0);

- (UICollectionViewLayoutInvalidationContext *)invalidationContextForInteractivelyMovingItems:(NSArray<NSIndexPath *> *)targetIndexPaths withTargetPosition:(CGPoint)targetPosition previousIndexPaths:(NSArray<NSIndexPath *> *)previousIndexPaths previousPosition:(CGPoint)previousPosition NS_AVAILABLE_IOS(9_0);
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForEndingInteractiveMovementOfItemsToFinalIndexPaths:(NSArray<NSIndexPath *> *)indexPaths previousIndexPaths:(NSArray<NSIndexPath *> *)previousIndexPaths movementCancelled:(BOOL)movementCancelled NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
