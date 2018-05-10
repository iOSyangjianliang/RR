//
//  UICollectionView.h
//  UIKit
//
//  Copyright (c) 2011-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/NSIndexPath+UIKitAdditions.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataSourceTranslating.h>
#import <UIKit/UIDropInteraction.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UICollectionViewScrollPosition) {
    //垂直布局时使用的 对应上中下
    UICollectionViewScrollPositionNone                 = 0,
    
    // The vertical positions are mutually exclusive to each other, but are bitwise or-able with the horizontal scroll positions.
    // Combining positions from the same grouping (horizontal or vertical) will result in an NSInvalidArgumentException.
    //垂直位置是相互排斥的，但是与水平滚动位置是一样的。
    //组合相同的分组（水平或垂直）的位置将导致NSInvalidArgumentException。
    UICollectionViewScrollPositionTop                  = 1 << 0,
    UICollectionViewScrollPositionCenteredVertically   = 1 << 1,
    UICollectionViewScrollPositionBottom               = 1 << 2,
    
    // Likewise, the horizontal positions are mutually exclusive to each other.同样，水平位置是相互排斥的。
     //水平布局时使用的  对应左中右
    UICollectionViewScrollPositionLeft                 = 1 << 3,
    UICollectionViewScrollPositionCenteredHorizontally = 1 << 4,
    UICollectionViewScrollPositionRight                = 1 << 5
};


typedef NS_ENUM(NSInteger, UICollectionViewReorderingCadence) {
    UICollectionViewReorderingCadenceImmediate,
    UICollectionViewReorderingCadenceFast,
    UICollectionViewReorderingCadenceSlow
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@class UICollectionView, UICollectionReusableView, UICollectionViewCell, UICollectionViewLayout, UICollectionViewTransitionLayout, UICollectionViewLayoutAttributes, UITouch, UINib;
@class UIDragItem, UIDragPreviewParameters, UIDragPreviewTarget;
@class UICollectionViewDropProposal, UICollectionViewPlaceholder, UICollectionViewDropPlaceholder;
@protocol UIDataSourceTranslating, UISpringLoadedInteractionContext;
@protocol UIDragSession, UIDropSession;
@protocol UICollectionViewDragDelegate, UICollectionViewDropDelegate, UICollectionViewDropCoordinator, UICollectionViewDropItem, UICollectionViewDropPlaceholderContext;

// layout transition block signature 布局更改后的动画进行设置
typedef void (^UICollectionViewLayoutInteractiveTransitionCompletion)(BOOL completed, BOOL finished);

NS_CLASS_AVAILABLE_IOS(9_0) @interface UICollectionViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

#park mark - UICollectionViewDataSource
@protocol UICollectionViewDataSource <NSObject>
@required
//配置UICollectionView的section对应item的数量
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section;
//配置UICollectionView的Cell，需要提前注册,调用[-dequeueReusableCellWithReuseIdentifier:forIndexPath:]从复用池获取
- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@optional
//配置UICollectionView的section数量，不执行默认一组
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView;

//配置UICollectionView的ReuseView，需要提前注册,调用[-dequeueReusableSupplementaryViewOfKind:withReuseIdentifier:forIndexPath:]从复用池获取
- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

//indexPath对应当前cell是否可以移动（9+）
- (BOOL)collectionView:(UICollectionView *)collectionView canMoveItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
//移动indexPath的item到另一个indexPath（9+）
- (void)collectionView:(UICollectionView *)collectionView moveItemAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath*)destinationIndexPath NS_AVAILABLE_IOS(9_0);

/// Returns a list of index titles to display in the index view (e.g. ["A", "B", "C" ... "Z", "#"])
// 返回在索引视图中显示的索引标题列表(例如“A”、“B”、“C”。“Z”、“#”)
- (nullable NSArray<NSString *> *)indexTitlesForCollectionView:(UICollectionView *)collectionView API_AVAILABLE(tvos(10.2));

/// Returns the index path that corresponds to the given title / index. (e.g. "B",1)
/// Return an index path with a single index to indicate an entire section, instead of a specific item.
//  右侧索引视图滑动、点击代理
// 返回一个索引路径，用一个索引来表示整个部分，而不是一个特定的项。
- (NSIndexPath *)collectionView:(UICollectionView *)collectionView indexPathForIndexTitle:(NSString *)title atIndex:(NSInteger)index API_AVAILABLE(tvos(10.2));

@end

@protocol UICollectionViewDataSourcePrefetching <NSObject>
@required
// indexPaths are ordered ascending by geometric distance from the collection view
- (void)collectionView:(UICollectionView *)collectionView prefetchItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(10_0);

@optional
// indexPaths that previously were considered as candidates for pre-fetching, but were not actually used; may be a subset of the previous call to -collectionView:prefetchItemsAtIndexPaths:
- (void)collectionView:(UICollectionView *)collectionView cancelPrefetchingForItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths  NS_AVAILABLE_IOS(10_0);

@end

//UICollectionViewDelegate UI交互协议
@protocol UICollectionViewDelegate <UIScrollViewDelegate>
@optional

// Methods for notification of selection/deselection and highlight/unhighlight events.
// The sequence of calls leading to selection from a user touch is:
// 用于通知/取消/取消/突出/突出事件的方法;从用户触摸中选择的调用顺序是:
// (when the touch begins)
// 1. -collectionView:shouldHighlightItemAtIndexPath:
// 2. -collectionView:didHighlightItemAtIndexPath:
//
// (when the touch lifts)
// 3. -collectionView:shouldSelectItemAtIndexPath: or -collectionView:shouldDeselectItemAtIndexPath:
// 4. -collectionView:didSelectItemAtIndexPath: or -collectionView:didDeselectItemAtIndexPath:
// 5. -collectionView:didUnhighlightItemAtIndexPath:
//是否允许高亮
- (BOOL)collectionView:(UICollectionView *)collectionView shouldHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
//已经高亮
- (void)collectionView:(UICollectionView *)collectionView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
//取消高亮
- (void)collectionView:(UICollectionView *)collectionView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath;
//是否允许选中
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSelectItemAtIndexPath:(NSIndexPath *)indexPath;
//是否允许解除选中
- (BOOL)collectionView:(UICollectionView *)collectionView shouldDeselectItemAtIndexPath:(NSIndexPath *)indexPath; // called when the user taps on an already-selected item in multi-select mode 当用户在多选择模式下点击已经选择的项目时调用
//已经选中
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath;
//已经解除选中
- (void)collectionView:(UICollectionView *)collectionView didDeselectItemAtIndexPath:(NSIndexPath *)indexPath;

//将要显示Cell
- (void)collectionView:(UICollectionView *)collectionView willDisplayCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0);
//将要显示SupplementaryView
- (void)collectionView:(UICollectionView *)collectionView willDisplaySupplementaryView:(UICollectionReusableView *)view forElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0);
//已经显示Cell
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath;
//已经显示SupplementaryView
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingSupplementaryView:(UICollectionReusableView *)view forElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;

// These methods provide support for copy/paste actions on cells.
// All three should be implemented if any are.
// 这些方法为cells的复制/粘贴操作提供支持。
// 如果有的话，这三个都应该被执行
//是否允许展示copy/paste Menu
- (BOOL)collectionView:(UICollectionView *)collectionView shouldShowMenuForItemAtIndexPath:(NSIndexPath *)indexPath;
//是否可以执行SEL-赋值粘贴等
- (BOOL)collectionView:(UICollectionView *)collectionView canPerformAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender;
//执行SEL
- (void)collectionView:(UICollectionView *)collectionView performAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender;

// support for custom transition layout 支持自定义转换
- (nonnull UICollectionViewTransitionLayout *)collectionView:(UICollectionView *)collectionView transitionLayoutForOldLayout:(UICollectionViewLayout *)fromLayout newLayout:(UICollectionViewLayout *)toLayout;

// Focus
- (BOOL)collectionView:(UICollectionView *)collectionView canFocusItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (BOOL)collectionView:(UICollectionView *)collectionView shouldUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
- (void)collectionView:(UICollectionView *)collectionView didUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInCollectionView:(UICollectionView *)collectionView NS_AVAILABLE_IOS(9_0);

- (NSIndexPath *)collectionView:(UICollectionView *)collectionView targetIndexPathForMoveFromItemAtIndexPath:(NSIndexPath *)originalIndexPath toProposedIndexPath:(NSIndexPath *)proposedIndexPath NS_AVAILABLE_IOS(9_0);

- (CGPoint)collectionView:(UICollectionView *)collectionView targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset NS_AVAILABLE_IOS(9_0); // customize the content offset to be applied during transition or update animations

// Spring Loading

/* Allows opting-out of spring loading for an particular item.
 *
 * If you want the interaction effect on a different subview of the spring loaded cell, modify the context.targetView property.
 * The default is the cell.
 *
 * If this method is not implemented, the default is YES.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSpringLoadItemAtIndexPath:(NSIndexPath *)indexPath withContext:(id<UISpringLoadedInteractionContext>)context API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end


NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionView : UIScrollView <UIDataSourceTranslating>

- (instancetype)initWithFrame:(CGRect)frame collectionViewLayout:(UICollectionViewLayout *)layout NS_DESIGNATED_INITIALIZER;//initWithFrame:方式初始化会创建默认layout进行初始化
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;//从nib文件直接初始化

//当前Layout
@property (nonatomic, strong) UICollectionViewLayout *collectionViewLayout;
//用户交互Delegate
@property (nonatomic, weak, nullable) id <UICollectionViewDelegate> delegate;
//UI的数据源DataSource
@property (nonatomic, weak, nullable) id <UICollectionViewDataSource> dataSource;
//预加载协议（10+）
@property (nonatomic, weak, nullable) id<UICollectionViewDataSourcePrefetching> prefetchDataSource NS_AVAILABLE_IOS(10_0);
//是否允许预加载
@property (nonatomic, getter=isPrefetchingEnabled) BOOL prefetchingEnabled NS_AVAILABLE_IOS(10_0);

@property (nonatomic, weak, nullable) id <UICollectionViewDragDelegate> dragDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);
@property (nonatomic, weak, nullable) id <UICollectionViewDropDelegate> dropDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);


/* To enable intra-app drags on iPhone, set this to YES.
 * You can also force drags to be disabled for this collection view by setting this to NO.
 * By default, For iPad this will return YES and iPhone will return NO.
 */
@property (nonatomic) BOOL dragInteractionEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/* Reordering cadence affects how easily reordering occurs while dragging around a reorder-capable drop destination.
 * Default is UICollectionViewReorderingCadenceImmediate.
 */
@property (nonatomic) UICollectionViewReorderingCadence reorderingCadence API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);
//将自动调整大小以跟踪父视图的大小，并放置在所有的单元格和补充视图下面。
@property (nonatomic, strong, nullable) UIView *backgroundView; // will be automatically resized to track the size of the collection view and placed behind all cells and supplementary views.

// For each reuse identifier that the collection view will use, register either a class or a nib from which to instantiate a cell.
// If a nib is registered, it must contain exactly 1 top level object which is a UICollectionViewCell.
// If a class is registered, it will be instantiated via alloc/initWithFrame:
//对于集合视图将使用的每个重用标识符，注册一个类或一个用于实例化一个单元的nib。
//如果一个nib被注册，它必须包含一个顶级的对象，它是一个UICollectionViewCell。
//如果一个类被注册，它将通过alloc/initwithframe实例化。
//注册UICollectionViewCell，或其子类，并且提供一个复用标识符，在runtime的时候会初始化这个对象
- (void)registerClass:(nullable Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;
//通过nib文件注册复用cell
- (void)registerNib:(nullable UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;

//通过Class注册补头尾视图，并且指定头尾视图的种类
- (void)registerClass:(nullable Class)viewClass forSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier;
//通过nib文件注册头尾视图
- (void)registerNib:(nullable UINib *)nib forSupplementaryViewOfKind:(NSString *)kind withReuseIdentifier:(NSString *)identifier;

//从复用队列通过指定Identifier获取复用cell
- (__kindof UICollectionViewCell *)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;
//从复用队列通过指定Identifier获取复用ReusableView
- (__kindof UICollectionReusableView *)dequeueReusableSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

// These properties control whether items can be selected, and if so, whether multiple items can be simultaneously selected.
//是否允许items选中，默认YES
@property (nonatomic) BOOL allowsSelection; // default is YES ;
//是否允许items多选，默认NO
@property (nonatomic) BOOL allowsMultipleSelection; // default is NO ;

#if UIKIT_DEFINE_AS_PROPERTIES
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedItems; // returns nil or an array of selected index paths ; //返回nil或选中的数组
#else
- (nullable NSArray<NSIndexPath *> *)indexPathsForSelectedItems; // returns nil or an array of selected index paths
#endif
//选中indexPath对应item，可指定动画和UICollectionViewScrollPosition
- (void)selectItemAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UICollectionViewScrollPosition)scrollPosition;
//取消选择indexPath对应item，
- (void)deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

// Returns YES if the collection view is reordering or has drop placeholders.如果集合视图是重新排序或有占位符，则返回YES。
@property (nonatomic, readonly) BOOL hasUncommittedUpdates API_AVAILABLE(ios(11.0));

// Note: -reloadData will discard any uncommitted updates (e.g. placeholders)注意:-reloadData将丢弃任何未提交的更新(例如占位符)
- (void)reloadData; // discard the dataSource and delegate data and requery as necessary 放弃dataSource并根据需要委托数据和查询

//切换当前collectionView的layout
- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated; // transition from one layout to another 从一种布局过渡到另一种布局
//切换当前collectionView的layout，有完成回调block
- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

//布局更改后的动画进行设置
- (UICollectionViewTransitionLayout *)startInteractiveTransitionToCollectionViewLayout:(UICollectionViewLayout *)layout completion:(nullable UICollectionViewLayoutInteractiveTransitionCompletion)completion NS_AVAILABLE_IOS(7_0);
//完成过渡切换layout;准备好动画设置后，我们需要调用下面的方法进行布局动画的展示，之后会调用上面方法的block回调
- (void)finishInteractiveTransition NS_AVAILABLE_IOS(7_0);
//取消过渡切换layout;调用这个方法取消上面的布局动画设置，之后也会进行上面方法的block回调
- (void)cancelInteractiveTransition NS_AVAILABLE_IOS(7_0);

#park mark 关于集合视图的当前状态的信息。
// Information about the current state of the collection view. 关于集合视图的当前状态的信息。
///获取section的数量
#if UIKIT_DEFINE_AS_PROPERTIES
@property (nonatomic, readonly) NSInteger numberOfSections;
#else
- (NSInteger)numberOfSections;
#endif
//获取对应section中item的数量
- (NSInteger)numberOfItemsInSection:(NSInteger)section;

//获取对应indexPath的Cell的LayoutAttributes
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
//获取对应indexPath的ReuseView的LayoutAttributes
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

//根据point点坐标获取对应的indexPath，point坐标需要转换为UICollectionView坐标:eg:[-(CGPoint)convertPoint:toView:]
- (nullable NSIndexPath *)indexPathForItemAtPoint:(CGPoint)point;
//根据cell获取对应的indexPath;只有可见范围内的cell才能获取，否则NSIndexPath=nil(0,0);
- (nullable NSIndexPath *)indexPathForCell:(UICollectionViewCell *)cell;

//根据indexPath获取对应的cell(可视范围内)，可能为空，
- (nullable UICollectionViewCell *)cellForItemAtIndexPath:(NSIndexPath *)indexPath;

///获取collectionView当前可见的item数组和可见item的indexPath数组
#if UIKIT_DEFINE_AS_PROPERTIES
@property (nonatomic, readonly) NSArray<__kindof UICollectionViewCell *> *visibleCells;
@property (nonatomic, readonly) NSArray<NSIndexPath *> *indexPathsForVisibleItems;
#else
- (NSArray<__kindof UICollectionViewCell *> *)visibleCells;
- (NSArray<NSIndexPath *> *)indexPathsForVisibleItems;
#endif

//根据indexPath获取对应的可见的ReuseView,不可见为nil(iOS9之后可用)
- (nullable UICollectionReusableView *)supplementaryViewForElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
//获取collectionView当前可见的ReuseView数组
- (NSArray<UICollectionReusableView *> *)visibleSupplementaryViewsOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(9_0);
//获取collectionView当前可见ReuseView的indexPath数组
- (NSArray<NSIndexPath *> *)indexPathsForVisibleSupplementaryElementsOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(9_0);

#park mark 与集合视图交互
// Interacting with the collection view.与集合视图交互。
//滚动到指定的indexPath
- (void)scrollToItemAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UICollectionViewScrollPosition)scrollPosition animated:(BOOL)animated;

// These methods allow dynamic modification of the current set of items in the collection view 这些方法允许在集合视图中动态修改当前的项目集
//插入一个section
- (void)insertSections:(NSIndexSet *)sections;
//删除一个section
- (void)deleteSections:(NSIndexSet *)sections;
//刷新一个section
- (void)reloadSections:(NSIndexSet *)sections;
//移动一个section到另外一个section，同时需要修改对应的数据源
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection;

//插入一个indexPaths组成的数组
- (void)insertItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
//删除一个indexPaths组成的数组
- (void)deleteItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
//刷新一个indexPaths组成的数组
- (void)reloadItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
//移动一个indexPath的item到另一个indexPath的item
- (void)moveItemAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;

//一次性操作插入，删除，刷新，移动操作
//允许多个插入/删除/重新加载/移动调用同时进行动画。可嵌套。
- (void)performBatchUpdates:(void (NS_NOESCAPE ^ _Nullable)(void))updates completion:(void (^ _Nullable)(BOOL finished))completion; // allows multiple insert/delete/reload/move calls to be animated simultaneously. Nestable. //允许多个插入/删除/重新加载/移动调用同时进行动画。可嵌套。

// Support for reordering 支持重新排序
//是否允许排序，默认YES(9+)
- (BOOL)beginInteractiveMovementForItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0); // returns NO if reordering was prevented from beginning - otherwise YES 如果重新排序被阻止，则返回NO，否则YES
//更新item的位置
- (void)updateInteractiveMovementTargetPosition:(CGPoint)targetPosition NS_AVAILABLE_IOS(9_0);
//移动item到新的position
- (void)endInteractiveMovement NS_AVAILABLE_IOS(9_0);
//回复item到原始的position
- (void)cancelInteractiveMovement NS_AVAILABLE_IOS(9_0);

// Support for Focus
//是否记住最后操作的indexPath,默认NO
@property (nonatomic) BOOL remembersLastFocusedIndexPath NS_AVAILABLE_IOS(9_0); // defaults to NO. If YES, when focusing on a collection view the last focused index path is focused automatically. If the collection view has never been focused, then the preferred focused index path is used.默认为NO。 如果是，则在关注集合视图时，最后聚焦的索引路径将自动聚焦。 如果集合视图从未聚焦，则使用首选聚焦索引路径。

// Drag & Drop

/* YES if a drag session is currently active. A drag session begins after items are "lifted" from the collection view.
 是，如果拖动会话当前处于活动状态。 从收集视图中“解除”项目之后，拖动会话开始。*/
@property (nonatomic, readonly) BOOL hasActiveDrag API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/* YES if collection view is currently tracking a drop session.如果collectionView当前正在跟踪放置会话，则为YES。
 */
@property (nonatomic, readonly) BOOL hasActiveDrop API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end

// _______________________________________________________________________________________________________________
// Drag & Drop


#if TARGET_OS_IOS
@interface UICollectionView (UIDragAndDrop) <UISpringLoadedInteractionSupporting>
@end
#endif

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UICollectionViewDragDelegate <NSObject>

@required

/* Provide items to begin a drag associated with a given indexPath.
 * If an empty array is returned a drag session will not begin.
 */
- (NSArray<UIDragItem *> *)collectionView:(UICollectionView *)collectionView itemsForBeginningDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath;

@optional

/* Called to request items to add to an existing drag session in response to the add item gesture.
 * You can use the provided point (in the collection view's coordinate space) to do additional hit testing if desired.
 * If not implemented, or if an empty array is returned, no items will be added to the drag and the gesture
 * will be handled normally.
 */
- (NSArray<UIDragItem *> *)collectionView:(UICollectionView *)collectionView itemsForAddingToDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point;

/* Allows customization of the preview used for the item being lifted from or cancelling back to the collection view.
 * If not implemented or if nil is returned, the entire cell will be used for the preview.
 */
- (nullable UIDragPreviewParameters *)collectionView:(UICollectionView *)collectionView dragPreviewParametersForItemAtIndexPath:(NSIndexPath *)indexPath;

/* Called after the lift animation has completed to signal the start of a drag session.
 * This call will always be balanced with a corresponding call to -collectionView:dragSessionDidEnd:
 */
- (void)collectionView:(UICollectionView *)collectionView dragSessionWillBegin:(id<UIDragSession>)session;

/* Called to signal the end of the drag session.
 */
- (void)collectionView:(UICollectionView *)collectionView dragSessionDidEnd:(id<UIDragSession>)session;


/* Controls whether move operations (see UICollectionViewDropProposal.operation) are allowed for the drag session.
 * If not implemented this will default to YES.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView dragSessionAllowsMoveOperation:(id<UIDragSession>)session;

/* Controls whether the drag session is restricted to the source application.
 * If YES the current drag session will not be permitted to drop into another application.
 * If not implemented this will default to NO.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView dragSessionIsRestrictedToDraggingApplication:(id<UIDragSession>)session;

@end

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UICollectionViewDropDelegate <NSObject>

@required

/* Called when the user initiates the drop.
 * Use the dropCoordinator to specify how you wish to animate the dropSession's items into their final position as
 * well as update the collection view's data source with data retrieved from the dropped items.
 * If the supplied method does nothing, default drop animations will be supplied and the collection view will
 * revert back to its initial pre-drop session state.
 */
- (void)collectionView:(UICollectionView *)collectionView performDropWithCoordinator:(id<UICollectionViewDropCoordinator>)coordinator;

@optional

/* If NO is returned no further delegate methods will be called for this drop session.
 * If not implemented, a default value of YES is assumed.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView canHandleDropSession:(id<UIDropSession>)session;

/* Called when the drop session begins tracking in the collection view's coordinate space.
 */
- (void)collectionView:(UICollectionView *)collectionView dropSessionDidEnter:(id<UIDropSession>)session;

/* Called frequently while the drop session being tracked inside the collection view's coordinate space.
 * When the drop is at the end of a section, the destination index path passed will be for a item that does not yet exist (equal
 * to the number of items in that section), where an inserted item would append to the end of the section.
 * The destination index path may be nil in some circumstances (e.g. when dragging over empty space where there are no cells).
 * Note that in some cases your proposal may not be allowed and the system will enforce a different proposal.
 * You may perform your own hit testing via -[UIDropSession locationInView]
 */
- (UICollectionViewDropProposal *)collectionView:(UICollectionView *)collectionView dropSessionDidUpdate:(id<UIDropSession>)session withDestinationIndexPath:(nullable NSIndexPath *)destinationIndexPath;

/* Called when the drop session is no longer being tracked inside the collection view's coordinate space.
 */
- (void)collectionView:(UICollectionView *)collectionView dropSessionDidExit:(id<UIDropSession>)session;

/* Called when the drop session completed, regardless of outcome. Useful for performing any cleanup.
 */
- (void)collectionView:(UICollectionView *)collectionView dropSessionDidEnd:(id<UIDropSession>)session;

/* Allows customization of the preview used for the item being dropped.
 * If not implemented or if nil is returned, the entire cell will be used for the preview.
 *
 * This will be called as needed when animating drops via -[UICollectionViewDropCoordinator dropItem:toItemAtIndexPath:]
 * (to customize placeholder drops, please see UICollectionViewDropPlaceholder.previewParametersProvider)
 */
- (nullable UIDragPreviewParameters *)collectionView:(UICollectionView *)collectionView dropPreviewParametersForItemAtIndexPath:(NSIndexPath *)indexPath;

@end

typedef NS_ENUM(NSInteger, UICollectionViewDropIntent) {
    /* Collection view will accept the drop, but the location is not yet known and will be determined later.
     * Will not open a gap. You may wish to provide some visual treatment to communicate this to the user.
     */
    UICollectionViewDropIntentUnspecified,
    
    /* The drop will be placed in item(s) inserted at the destination index path.
     * Opens a gap at the specified location simulating the final dropped layout.
     */
    UICollectionViewDropIntentInsertAtDestinationIndexPath,
    
    /* The drop will be placed inside the item at the destination index path (e.g. the item is a container of other items).
     * Will not open a gap. Collection view will highlight the item at the destination index path.
     */
    UICollectionViewDropIntentInsertIntoDestinationIndexPath,
    
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UICollectionViewDropProposal : UIDropProposal

- (instancetype)initWithDropOperation:(UIDropOperation)operation intent:(UICollectionViewDropIntent)intent;

/* The default is UICollectionViewDropIntentUnspecified.
 */
@property (nonatomic, readonly) UICollectionViewDropIntent intent;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UICollectionViewDropCoordinator <NSObject>

/* Ordered list of items available for this drop.
 */
@property (nonatomic, readonly) NSArray<id<UICollectionViewDropItem>> *items;

/* The last hit-tested index path known during the drop session.
 * If this is nil, the proposal's intent will be .unspecified
 */
@property (nonatomic, readonly, nullable) NSIndexPath *destinationIndexPath;

/* The current drop proposal at the time of the drop.
 */
@property (nonatomic, readonly) UICollectionViewDropProposal *proposal;


@property (nonatomic, readonly) id<UIDropSession> session;

/* Animate the dragItem to an automatically inserted placeholder item.
 *
 * A placeholder cell will be created for the reuse identifier and inserted at the specified indexPath without requiring a dataSource update.
 *
 * The cellUpdateHandler will be called whenever the placeholder cell becomes visible; -collectionView:cellForItemAtIndexPath: will not be called
 * for the placeholder.
 *
 * Once the dragItem data is available, you can exchange the temporary placeholder cell with the final cell using
 * the placeholder context method -commitInsertionWithDataSourceUpdates:
 *
 * UICollectionViewDropPlaceholderContext also conforms to UIDragAnimating to allow adding alongside animations and completion handlers.
 */
- (id<UICollectionViewDropPlaceholderContext>)dropItem:(UIDragItem *)dragItem toPlaceholder:(UICollectionViewDropPlaceholder*)placeholder;

/* Animate the dragItem to a newly inserted item at the specified index path.
 * You must call -performBatchUpdates:completion: to update your data source and insert a new item into the collection view prior to calling this method.
 *
 * To tweak the appearance of the preview being dropping (e.g. supply a clipping path), see -collectionView:dropPreviewParametersForItemAtIndexPath:
 */
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toItemAtIndexPath:(NSIndexPath *)indexPath;

/* Animate the dragItem to a rect inside an existing item.
 * The rect is in the coordinate space of the cell at this index path.
 * The item will be animated with an aspect fit scale transform to fit inside the rect. Use a rect with zero size to shrink the item to a single point.
 */
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem intoItemAtIndexPath:(NSIndexPath *)indexPath rect:(CGRect)rect;

/* Animate the dragItem to a location specified by the UIDragPreviewTarget.
 */
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toTarget:(UIDragPreviewTarget *)target;

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos,watchos)
@interface UICollectionViewPlaceholder : NSObject

- (instancetype)initWithInsertionIndexPath:(NSIndexPath*)insertionIndexPath reuseIdentifier:(NSString *)reuseIdentifier NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/* Called whenever the placeholder cell is visible to update the contents of the cell.
 */
@property (nonatomic, nullable, copy) void(^cellUpdateHandler)(__kindof UICollectionViewCell *);

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos,watchos)
@interface UICollectionViewDropPlaceholder : UICollectionViewPlaceholder

/* If specified, will be used to modify the appearance (e.g. visiblePath to supply a "cut out" region of the placeholder cell) of the animating dropped item.
 * Handler will be called as-needed.
 */
@property (nonatomic, nullable, copy) UIDragPreviewParameters * _Nullable (^previewParametersProvider)(__kindof UICollectionViewCell *);
@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UICollectionViewDropItem <NSObject>

@property (nonatomic, readonly) UIDragItem *dragItem;

/* If this drop item is also from this collection view this indexPath will specify the location of the item.
 * If the dragItem comes from some other source (e.g. another source inside or outside of the app), it will be nil.
 * This is useful for directly accessing the model objects in the data source instead of using the item provider
 * to retrieve the data.
 */
@property (nonatomic, readonly, nullable) NSIndexPath *sourceIndexPath;

/* May be useful for computing the UIDragPreviewTarget transform for UICollectionViewDropCoordinator dropItem:toTarget:
 * Returns CGSizeZero if the dragItem does not have a visible drop preview.
 */
@property (nonatomic, readonly) CGSize previewSize;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UICollectionViewDropPlaceholderContext <UIDragAnimating>

/* Retrieve drop data from the dragItem's itemProvider.
 */
@property (nonatomic, readonly) UIDragItem *dragItem;


/* Exchange the placeholder for the final cell.
 * You are only responsible for updating your data source inside the block using the provided insertionIndexPath.
 * If the placeholder is no longer available (e.g. -reloadData has been called) the dataSourceUpdates block
 * will not be executed and this will return NO.
 */
- (BOOL)commitInsertionWithDataSourceUpdates:(void(NS_NOESCAPE ^)(NSIndexPath *insertionIndexPath))dataSourceUpdates;

/* If the placeholder is no longer needed or you wish to manually insert a cell for the drop data, you can
 * remove the placeholder via this method.
 * If the placeholder is no longer available (e.g. -reloadData has been called) this will return NO.
 */
- (BOOL)deletePlaceholder;

/* Call this method to request an update of the placeholder cell's content via the updateCellHandler.
 * This will only be called if the placeholder is visible. If the placeholder becomes visible via scrolling,
 * the updateCellHandler will automatically be called.
 */
- (void)setNeedsCellUpdate;

@end



NS_ASSUME_NONNULL_END
