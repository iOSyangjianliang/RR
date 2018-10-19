//
//  UITableView.h
//  UIKit
//
//  Copyright (c) 2005-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/NSIndexPath+UIKitAdditions.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UISwipeGestureRecognizer.h>
#import <UIKit/UISwipeActionsConfiguration.h>
#import <UIKit/UITableViewCell.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataSourceTranslating.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>
#import <UIKit/UIDropInteraction.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UITableViewStyle) {
    UITableViewStylePlain,          // regular table view
    UITableViewStyleGrouped         // preferences style table view
};

//ScrollPosition决定定位的相对位置
typedef NS_ENUM(NSInteger, UITableViewScrollPosition) {
    UITableViewScrollPositionNone,     //和top一样
    UITableViewScrollPositionTop,      //滚动目标行到顶部
    UITableViewScrollPositionMiddle,   //滚动目标行到中间
    UITableViewScrollPositionBottom    //滚动目标行到底部
}; //滚动以使感兴趣的行在视图的顶部/中心/底部完全可见

//行变化(插入、删除、移动)动画类型
typedef NS_ENUM(NSInteger, UITableViewRowAnimation) {
    UITableViewRowAnimationFade,            //淡入淡出
    UITableViewRowAnimationRight,           //从右侧（或从外到右）滑入
    UITableViewRowAnimationLeft,            //从左侧滑入
    UITableViewRowAnimationTop,             //从上方滑入
    UITableViewRowAnimationBottom,          //从底部滑入
    UITableViewRowAnimationNone,            // 没有动画
    UITableViewRowAnimationMiddle,          //
    UITableViewRowAnimationAutomatic = 100  // 自动选择合适动画
};


//在sectionIndexTitlesForTableView返回的字符串数组中包含此常量字符串：将导致放大镜图标显示在索引中的该位置。
//通常用于右侧索引第一个设置为搜索图标，将该字符串添加到数组第一个元素，然后在sectionIndexTitlesForTableView代理返回该数组
UIKIT_EXTERN NSString *const UITableViewIndexSearch NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;


//从tableView返回此值：heightForHeaderInSection：或tableView：heightForFooterInSection：得到一个适合从返回值返回的值的高度
// tableView：titleForHeaderInSection：或tableView：titleForFooterInSection：如果标题不是nil。
UIKIT_EXTERN const CGFloat UITableViewAutomaticDimension NS_AVAILABLE_IOS(5_0);

@class UITableView, UINib, UITableViewHeaderFooterView, UIVisualEffect;
@protocol UITableViewDataSource, UITableViewDataSourcePrefetching;
@class UIDragItem, UIDragPreviewParameters, UIDragPreviewTarget, UITableViewDropProposal, UITableViewPlaceholder, UITableViewDropPlaceholder;
@protocol UISpringLoadedInteractionContext, UIDragSession, UIDropSession;
@protocol UITableViewDragDelegate, UITableViewDropDelegate, UITableViewDropCoordinator, UITableViewDropItem, UITableViewDropPlaceholderContext;

typedef NS_ENUM(NSInteger, UITableViewRowActionStyle) {
    UITableViewRowActionStyleDefault = 0,
    UITableViewRowActionStyleDestructive = UITableViewRowActionStyleDefault,
    UITableViewRowActionStyleNormal
} NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;


//将要废弃-使用UIContextualAction而不是此类，将在以后的版本中弃用。
NS_CLASS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED
@interface UITableViewRowAction : NSObject <NSCopying>

+ (instancetype)rowActionWithStyle:(UITableViewRowActionStyle)style title:(nullable NSString *)title handler:(void (^)(UITableViewRowAction *action, NSIndexPath *indexPath))handler;

@property (nonatomic, readonly) UITableViewRowActionStyle style;
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) UIColor *backgroundColor; // default background color is dependent on style
@property (nonatomic, copy, nullable) UIVisualEffect* backgroundEffect;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface UITableViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

//_______________________________________________________________________________________________________________
//这表示单元格的显示和行为。

@protocol UITableViewDelegate<NSObject, UIScrollViewDelegate>

@optional

//cell、HeaderView、FooterView将要显示、已经显示、将要消失、已经消失代理
- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView willDisplayHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView willDisplayFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didEndDisplayingCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath*)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didEndDisplayingHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didEndDisplayingFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

//cell、HeaderView、FooterView高度设置
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;

//使用estimatedHeight方法快速计算猜测值，这将使表的快速加载时间(尤其对于高度不断改变情况)。
//如果实现了这些方法，上面的-tableView：heightForXXX调用将被推迟到视图准备好显示，因此可以在那里放置更昂贵的逻辑。
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(7_0);
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForHeaderInSection:(NSInteger)section NS_AVAILABLE_IOS(7_0);
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForFooterInSection:(NSInteger)section NS_AVAILABLE_IOS(7_0);

//部分页眉和页脚信息。如果您决定同时提供视图和标题(同时实现两个代理方法)，那么视图优先于标题
//自定义视图组头、组尾视图，可return nil来展示间隙。 将被调整为默认或指定的标题高度
- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section;
- (nullable UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section;


//附件（披露）

//eg:设置右侧箭头时相关代理
- (UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

//选择-触摸高亮控制

// -tableView：shouldHighlightRowAtIndexPath：在一行触摸时调用。
//对该消息返回NO将停止选择过程，并且在触摸关闭时不会导致当前选定的行丢失其选定的外观。
- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);

//选中

//在用户更改选择之前调用。 返回一个新的indexPath或nil，以更改建议的选择。
//默认单选时点击某一个会将上一个(将要)取消选中、然后当前(将)开始选中
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willDeselectRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0);
//在用户更改选择后调用。
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0);

// Editing

// Allows customization of the editingStyle for a particular cell located at 'indexPath'. If not implemented, all editable cells will have UITableViewCellEditingStyleDelete set for them when the table has editing property set to YES.
//编辑

//允许为位于'indexPath'的特定单元格自定义editingStyle。 如果未实现，则当表的编辑属性设置为YES时，所有可编辑单元格都将为它们设置UITableViewCellEditingStyleDelete。
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath;
- (nullable NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;

//使用-tableView：trailingSwipeActionsConfigurationForRowAtIndexPath：而不是此方法，将在以后的版本中弃用。
//如果返回值为非nil，这个方法取代了上面的 -tableView:titleForDeleteConfirmationButtonForRowAtIndexPath:
- (nullable NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;

//滑动动作(11+)
//这些方法取代上面-editActionsForRowAtIndexPath：如果已实现
//返回nil以获取默认的滑动操作
- (nullable UISwipeActionsConfiguration *)tableView:(UITableView *)tableView leadingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);
- (nullable UISwipeActionsConfiguration *)tableView:(UITableView *)tableView trailingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

//控制在编辑时是否缩进背景。 如果未实现，则默认为YES。 这与下面的缩进级别无关。 此方法仅适用于分组样式表视图。
- (BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath;

//只要表格自动更改'editing'属性（允许插入/删除/移动），就会调用willBegin / didEnd方法。 这是通过滑动激活单行来完成的
- (void)tableView:(UITableView *)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath __TVOS_PROHIBITED;
- (void)tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(nullable NSIndexPath *)indexPath __TVOS_PROHIBITED;


// 移动/重新排序

//允许在移动/重新排序时自定义特定行的目标行
- (NSIndexPath *)tableView:(UITableView *)tableView targetIndexPathForMoveFromRowAtIndexPath:(NSIndexPath *)sourceIndexPath toProposedIndexPath:(NSIndexPath *)proposedDestinationIndexPath;               

// 缩进
//返回层次结构的行的“深度”
- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath;


// 复制粘贴。 所有三种方法都必须由delegate实施。
//是否需要展示menu复制控件
- (BOOL)tableView:(UITableView *)tableView shouldShowMenuForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(5_0);
//是否相应action
- (BOOL)tableView:(UITableView *)tableView canPerformAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender NS_AVAILABLE_IOS(5_0);
//响应相应action
- (void)tableView:(UITableView *)tableView performAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender NS_AVAILABLE_IOS(5_0);

// 焦点

- (BOOL)tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (BOOL)tableView:(UITableView *)tableView shouldUpdateFocusInContext:(UITableViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
- (void)tableView:(UITableView *)tableView didUpdateFocusInContext:(UITableViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInTableView:(UITableView *)tableView NS_AVAILABLE_IOS(9_0);


//弹簧加载效果（11+）

//允许选择特定行的弹簧加载。
//如果要在弹簧加载单元格的不同子视图上进行交互效果，请修改context.targetView属性。 默认值是单元格。
//如果未实现此方法，则默认值为YES，除非该行是拖动会话的一部分。
- (BOOL)tableView:(UITableView *)tableView shouldSpringLoadRowAtIndexPath:(NSIndexPath *)indexPath withContext:(id<UISpringLoadedInteractionContext>)context API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end
//TableView选中发生改变通知
UIKIT_EXTERN NSNotificationName const UITableViewSelectionDidChangeNotification;

//设置分割线偏移量
typedef NS_ENUM(NSInteger, UITableViewSeparatorInsetReference) {
    //设置为separatorInset属性的值被解释为与单元格边缘的偏移量。
    UITableViewSeparatorInsetFromCellEdges,
    
    //设置为separatorInset属性的值被解释为自动分隔符insets的偏移量。
    UITableViewSeparatorInsetFromAutomaticInsets
} API_AVAILABLE(ios(11.0), tvos(11.0));


//_______________________________________________________________________________________________________________

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableView : UIScrollView <NSCoding, UIDataSourceTranslating>

//必须在创建时指定样式。 -initWithFrame：默认使用UITableViewStylePlain调用它
- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//样式、只读不可修改
@property (nonatomic, readonly) UITableViewStyle style;

@property (nonatomic, weak, nullable) id <UITableViewDataSource> dataSource;
@property (nonatomic, weak, nullable) id <UITableViewDelegate> delegate;
@property (nonatomic, weak, nullable) id <UITableViewDataSourcePrefetching> prefetchDataSource NS_AVAILABLE_IOS(10_0);
@property (nonatomic, weak, nullable) id <UITableViewDragDelegate> dragDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);
@property (nonatomic, weak, nullable) id <UITableViewDropDelegate> dropDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

//行高 default is UITableViewAutomaticDimension
@property (nonatomic) CGFloat rowHeight;
//组头高度 default is UITableViewAutomaticDimension
@property (nonatomic) CGFloat sectionHeaderHeight;
//组尾高度 default is UITableViewAutomaticDimension
@property (nonatomic) CGFloat sectionFooterHeight;

//估算行高，需要时设置非0即可， 默认 UITableViewAutomaticDimension,设置为0表示禁用，非0时需要设置rowHeight=UITableViewAutomaticDimension，否则在iOS8上自适应无效
@property (nonatomic) CGFloat estimatedRowHeight NS_AVAILABLE_IOS(7_0);
//估算组头高度，需要时设置非0即可， 默认 UITableViewAutomaticDimension,设置为0表示禁用
@property (nonatomic) CGFloat estimatedSectionHeaderHeight NS_AVAILABLE_IOS(7_0);
//估算组尾高度，需要时设置非0即可， 默认 UITableViewAutomaticDimension,设置为0表示禁用
@property (nonatomic) CGFloat estimatedSectionFooterHeight NS_AVAILABLE_IOS(7_0);

//设置分割线上左下右间距; 另请参见separatorInsetReference属性。 使用UITableViewAutomaticDimension进行该边缘的自动插入。
@property (nonatomic) UIEdgeInsets separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;

//更改自定义separatorInset值的解释方式。 默认值为UITableViewSeparatorInsetFromCellEdges
@property (nonatomic) UITableViewSeparatorInsetReference separatorInsetReference API_AVAILABLE(ios(11.0), tvos(11.0));

//背景视图将自动调整大小以跟踪表格视图的大小。 这将作为所有单元格和页眉/页脚后面的表格视图的子视图。 某些设备的默认值可能是非nil。
@property (nonatomic, strong, nullable) UIView *backgroundView NS_AVAILABLE_IOS(3_2);


#park - mark 列表信息

@property (nonatomic, readonly) NSInteger numberOfSections;
- (NSInteger)numberOfRowsInSection:(NSInteger)section;

//包括页眉，页脚和所有行的范围区域
- (CGRect)rectForSection:(NSInteger)section;

- (CGRect)rectForHeaderInSection:(NSInteger)section;
- (CGRect)rectForFooterInSection:(NSInteger)section;
- (CGRect)rectForRowAtIndexPath:(NSIndexPath *)indexPath;

//如果point(点坐标参考系为tableView)在表中的任何行之外，则返回nil
- (nullable NSIndexPath *)indexPathForRowAtPoint:(CGPoint)point;
//如果单元格不在可视范围，则返回nil
- (nullable NSIndexPath *)indexPathForCell:(UITableViewCell *)cell;

//如果rect(参考系为tableView)无效，则返回nil
- (nullable NSArray<NSIndexPath *> *)indexPathsForRowsInRect:(CGRect)rect;

//如果单元格不可见或索引路径超出范围，则返回nil
- (nullable __kindof UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;

//获取所有可视范围cell数组
@property (nonatomic, readonly) NSArray<__kindof UITableViewCell *> *visibleCells;
//获取所有可视范围cell的IndexPath数组
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForVisibleRows;

//获取某组的组头、组尾
- (nullable UITableViewHeaderFooterView *)headerViewForSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
- (nullable UITableViewHeaderFooterView *)footerViewForSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

//滚动到指定indexPath，当使用[tableView reloadData];刷新数据时，不能直接在后面使用一下的函数(dispatch_async等带刷新完成操作)。
- (void)scrollToRowAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;
//滚动距离最近的选中行，位置由scrollPosition决定
- (void)scrollToNearestSelectedRowAtScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;

// Reloading and Updating 重新加载和更新

//允许同时为多个插入/删除/重新加载/移动调用设置动画。可嵌套。
- (void)performBatchUpdates:(void (NS_NOESCAPE ^ _Nullable)(void))updates completion:(void (^ _Nullable)(BOOL finished))completion API_AVAILABLE(ios(11.0), tvos(11.0));

// Use -performBatchUpdates:completion: instead of these methods, which will be deprecated in a future release.
//使用-performBatchUpdates：completion：而不是这些方法，这些方法将在(iOS11)以后的版本中弃用。
- (void)beginUpdates;
- (void)endUpdates;

- (void)insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)reloadSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation NS_AVAILABLE_IOS(3_0);
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection NS_AVAILABLE_IOS(5_0);

- (void)insertRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)reloadRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation NS_AVAILABLE_IOS(3_0);
- (void)moveRowAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath NS_AVAILABLE_IOS(5_0);

// Returns YES if the table view is in the middle of reordering, is displaying a drop target gap, or has drop placeholders. If possible, avoid calling -reloadData while there are uncommitted updates to avoid interfering with user-initiated interactions that have not yet completed.
//如果表视图处于重新排序的中间，显示放置目标间隙或具有放置占位符，则返回YES。 如果可能，请避免在存在未提交的更新时调用-reloadData，以避免干扰尚未完成的用户启动的交互。(11+)
@property (nonatomic, readonly) BOOL hasUncommittedUpdates API_AVAILABLE(ios(11.0), tvos(11.0));

// Reloads everything from scratch. Redisplays visible rows. Note that this will cause any existing drop placeholder rows to be removed.
//从头开始重新加载所有内容。 重新显示可见行。 请注意，这将导致删除任何现有的放置占位符行(数据源对比多出的行)。
- (void)reloadData;

//重新右侧索引栏。
- (void)reloadSectionIndexTitles NS_AVAILABLE_IOS(3_0);

// Editing. When set, rows show insert/delete/reorder controls based on data source queries
//编辑 设置时，行显示基于数据源查询的插入/删除/重新排序控件
// default is NO. 默认不带系统动画.
@property (nonatomic, getter=isEditing) BOOL editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

//默认为YES。 控制在不处于编辑模式时是否可以选择行
@property (nonatomic) BOOL allowsSelection NS_AVAILABLE_IOS(3_0);
//默认为NO。 控制在编辑模式下是否可以选择行
@property (nonatomic) BOOL allowsSelectionDuringEditing;
//默认为NO。允许选择多行
@property (nonatomic) BOOL allowsMultipleSelection NS_AVAILABLE_IOS(5_0);
//默认为NO。 控制是否可以在编辑模式下同时选择多行
@property (nonatomic) BOOL allowsMultipleSelectionDuringEditing NS_AVAILABLE_IOS(5_0);

//无选中返回nil，多选多行时返回非nil值为IndexPath最小那个
//返回nil或选中的IndexPath
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathForSelectedRow;
//无选中返回nil，最近点击排列数组最后
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedRows NS_AVAILABLE_IOS(5_0);


//选择和取消选择行。
//这些方法不会调用委托方法（-tableView：willSelectRowAtIndexPath：或tableView：didSelectRowAtIndexPath :)，也不会发出通知。
- (void)selectRowAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (void)deselectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

//支持 Appearance属性全局设置

//当行数达到此值时，在右侧显示特殊部分索引列表。 默认值为0
@property (nonatomic) NSInteger sectionIndexMinimumDisplayRowCount;                                                      // show special section index list on right when row count reaches this value. default is 0
//右侧索引标题颜色
@property (nonatomic, strong, nullable) UIColor *sectionIndexColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;
//未触摸时索引的背景颜色
@property (nonatomic, strong, nullable) UIColor *sectionIndexBackgroundColor NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;
//触摸时索引的背景颜色
@property (nonatomic, strong, nullable) UIColor *sectionIndexTrackingBackgroundColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;

//设置cell的分割线样式，默认为UITableViewCellSeparatorStyleSingleLine，可在代理方法中每行不同设置
@property (nonatomic) UITableViewCellSeparatorStyle separatorStyle __TVOS_PROHIBITED;
//设置cell的分割线颜色,默认是标准灰色分隔符
@property (nonatomic, strong, nullable) UIColor *separatorColor UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;
//模糊效果应用于表分隔符
@property (nonatomic, copy, nullable) UIVisualEffect *separatorEffect NS_AVAILABLE_IOS(8_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

//如果单元格边距是从readableContentGuide的宽度派生的。
@property (nonatomic) BOOL cellLayoutMarginsFollowReadableWidth NS_AVAILABLE_IOS(9_0);
//默认值为YES
@property (nonatomic) BOOL insetsContentViewsToSafeArea API_AVAILABLE(ios(11.0), tvos(11.0));

//UITableView头部、尾部的附件视图(不要与组头组尾混淆)。 默认值为nil。
@property (nonatomic, strong, nullable) UIView *tableHeaderView;
@property (nonatomic, strong, nullable) UIView *tableFooterView;

//通过重用标识符获取cell，由代理方法使用来获取已分配的单元格，而不是分配新单元格。
- (nullable __kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier;
//通过重用标识符获取cell，需要传入indexPath参数，较新的dequeue方法，保证在注册标识符的情况下正确返回和调整单元格大小
- (__kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
//通过重用标识符获取组头、组尾
- (nullable __kindof UITableViewHeaderFooterView *)dequeueReusableHeaderFooterViewWithIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

//从iOS 6开始，客户端可以为每个单元格注册一个nib或类。
//如果注册了所有重用标识符，请使用较新的-dequeueReusableCellWithIdentifier：forIndexPath：以保证返回单元格实例。
//返回新的dequeue方法返回的实例也会正确调整大小。
- (void)registerNib:(nullable UINib *)nib forCellReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(5_0);
- (void)registerClass:(nullable Class)cellClass forCellReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

//重用标识符注册组头组尾
- (void)registerNib:(nullable UINib *)nib forHeaderFooterViewReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);
- (void)registerClass:(nullable Class)aClass forHeaderFooterViewReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

// Focus
//是否记住最后操作的indexPath,默认NO
//默认为NO。 如果YES，则在关注表视图时，最后聚焦的索引路径将自动聚焦。 如果表视图从未被聚焦，则使用首选的聚焦索引路径。
@property (nonatomic) BOOL remembersLastFocusedIndexPath NS_AVAILABLE_IOS(9_0);


// Drag & Drop

//要在iPhone上启用应用内部拖动，请将其设置为YES。
//您还可以通过将此设置为NO来强制禁用此表视图的拖动。
//默认情况下，在iPad上返回YES，在iPhone上返回NO。
@property (nonatomic) BOOL dragInteractionEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

//如果拖动会话当前处于活动状态，则为YES。 在从表视图“提升”行之后开始拖动会话。
@property (nonatomic, readonly) BOOL hasActiveDrag API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// YES if table view is currently tracking a drop session.
//如果表视图当前正在跟踪(手指在)放置会话，则为YES。
@property (nonatomic, readonly) BOOL hasActiveDrop API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end

#if TARGET_OS_IOS
@interface UITableView (UIDragAndDrop) <UISpringLoadedInteractionSupporting>
@end
#endif

//_______________________________________________________________________________________________________________
//此协议表示数据模型对象。 因此，它不提供有关外观的信息（包括cell）

@protocol UITableViewDataSource<NSObject>

@required
//该组行数
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;

//行显示 实施者应该*总是*尝试通过设置每个单元的reuseIdentifier并使用dequeueReusableCellWithIdentifier查询可用的可重用单元来重用单元：
// Cell根据表（分隔符）和数据源（附件视图，编辑控件）自动设置各种属性
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

@optional
//默认一组
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;

//组头、组尾固定字体样式。 如果你想要不同的东西，请使用自定义视图（UILabel）
- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;
- (nullable NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;

//编辑
//单个行可以选择不为它们设置-editing属性。 如果未实现，则假定所有行都是可编辑的。
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath;

//移动/重新排序
//允许为特定行显示重新排序附件视图。 默认情况下，仅当数据源实现-tableView：moveRowAtIndexPath：toIndexPath时，才会显示重新排序控件：
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath;

//右侧索引
//返回要在节索引视图中显示的节标题列表数组（例如“ABCD ... Z＃”）
- (nullable NSArray<NSString *> *)sectionIndexTitlesForTableView:(UITableView *)tableView;
//告诉表哪个部分对应于部分标题/索引（例如“B”，1），在该代理手动滚动tableView使对应索引
- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;

//数据操作 - 插入和删除支持

//在一行调用减号或加号按钮后（基于单元格的UITableViewCellEditingStyle），dataSource数据源必须对应调整
//不使用UITableViewRowAction调用编辑操作 - 而是调用操作的处理程序
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath;

//数据操作 - 重新排序/移动支持
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

@end


// _______________________________________________________________________________________________________________
// this protocol can provide information about cells before they are displayed on screen.
//此协议可以在屏幕上显示之前(预加载)提供有关单元格的信息。

@protocol UITableViewDataSourcePrefetching <NSObject>

@required

// indexPaths are ordered ascending by geometric distance from the table view
// indexPaths按表格视图的几何距离递增
- (void)tableView:(UITableView *)tableView prefetchRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@optional

// indexPaths that previously were considered as candidates for pre-fetching, but were not actually used; may be a subset of the previous call to -tableView:prefetchRowsAtIndexPaths:
//之前被认为是预取的候选者的indexPaths，但实际上并未使用;
//可能是先前调用-tableView的一个子集：prefetchRowsAtIndexPaths：
- (void)tableView:(UITableView *)tableView cancelPrefetchingForRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@end


// _______________________________________________________________________________________________________________
// Drag & Drop

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDragDelegate <NSObject>

@required

// Provide items to begin a drag associated with a given index path.
// You can use -[session locationInView:] to do additional hit testing if desired.
// If an empty array is returned a drag session will not begin.
//提供item以开始与给定索引路径关联的拖动。
//如果需要，您可以使用 - [session locationInView：]进行额外的命中测试。
//如果返回空数组，则不会开始拖动会话。
- (NSArray<UIDragItem *> *)tableView:(UITableView *)tableView itemsForBeginningDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath;

@optional

// Called to request items to add to an existing drag session in response to the add item gesture.
// You can use the provided point (in the table view's coordinate space) to do additional hit testing if desired.
// If not implemented, or if an empty array is returned, no items will be added to the drag and the gesture
// will be handled normally.
- (NSArray<UIDragItem *> *)tableView:(UITableView *)tableView itemsForAddingToDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point;

// Allows customization of the preview used for the row when it is lifted or if the drag cancels.
// If not implemented or if nil is returned, the entire cell will be used for the preview.
- (nullable UIDragPreviewParameters *)tableView:(UITableView *)tableView dragPreviewParametersForRowAtIndexPath:(NSIndexPath *)indexPath;

// Called after the lift animation has completed to signal the start of a drag session.
// This call will always be balanced with a corresponding call to -tableView:dragSessionDidEnd:
- (void)tableView:(UITableView *)tableView dragSessionWillBegin:(id<UIDragSession>)session;

// Called to signal the end of the drag session.
- (void)tableView:(UITableView *)tableView dragSessionDidEnd:(id<UIDragSession>)session;

// Controls whether move operations are allowed for the drag session.
// If not implemented, defaults to YES.
- (BOOL)tableView:(UITableView *)tableView dragSessionAllowsMoveOperation:(id<UIDragSession>)session;

// Controls whether the drag session is restricted to the source application.
// If not implemented, defaults to NO.
- (BOOL)tableView:(UITableView *)tableView dragSessionIsRestrictedToDraggingApplication:(id<UIDragSession>)session;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropDelegate <NSObject>

@required

// Called when the user initiates the drop.
// Use the drop coordinator to access the items in the drop and the final destination index path and proposal for the drop,
// as well as specify how you wish to animate each item to its final position.
// If your implementation of this method does nothing, default drop animations will be supplied and the table view will
// revert back to its initial state before the drop session entered.
- (void)tableView:(UITableView *)tableView performDropWithCoordinator:(id<UITableViewDropCoordinator>)coordinator;

@optional

// If NO is returned no further delegate methods will be called for this drop session.
// If not implemented, a default value of YES is assumed.
- (BOOL)tableView:(UITableView *)tableView canHandleDropSession:(id<UIDropSession>)session;

// Called when the drop session begins tracking in the table view's coordinate space.
- (void)tableView:(UITableView *)tableView dropSessionDidEnter:(id<UIDropSession>)session;

// Called frequently while the drop session being tracked inside the table view's coordinate space.
// When the drop is at the end of a section, the destination index path passed will be for a row that does not yet exist (equal
// to the number of rows in that section), where an inserted row would append to the end of the section.
// The destination index path may be nil in some circumstances (e.g. when dragging over empty space where there are no cells).
// Note that in some cases your proposal may not be allowed and the system will enforce a different proposal.
// You may perform your own hit testing via -[session locationInView:]
- (UITableViewDropProposal *)tableView:(UITableView *)tableView dropSessionDidUpdate:(id<UIDropSession>)session withDestinationIndexPath:(nullable NSIndexPath *)destinationIndexPath;

// Called when the drop session is no longer being tracked inside the table view's coordinate space.
- (void)tableView:(UITableView *)tableView dropSessionDidExit:(id<UIDropSession>)session;

// Called when the drop session completed, regardless of outcome. Useful for performing any cleanup.
- (void)tableView:(UITableView *)tableView dropSessionDidEnd:(id<UIDropSession>)session;

// Allows customization of the preview used when dropping to a newly inserted row.
// If not implemented or if nil is returned, the entire cell will be used for the preview.
- (nullable UIDragPreviewParameters *)tableView:(UITableView *)tableView dropPreviewParametersForRowAtIndexPath:(NSIndexPath *)indexPath;

@end


typedef NS_ENUM(NSInteger, UITableViewDropIntent) {
    // Table view will accept the drop, but the location is not yet known and will be determined later.
    // Will not open a gap. You may wish to provide some visual treatment to communicate this to the user.
    UITableViewDropIntentUnspecified,
    
    // The drop will be placed in row(s) inserted at the destination index path.
    // Opens a gap at the specified location simulating the final dropped layout.
    UITableViewDropIntentInsertAtDestinationIndexPath,
    
    // The drop will be placed inside the row at the destination index path (e.g. the row is a container of other items).
    // Will not open a gap. Table view will highlight the row at the destination index path.
    UITableViewDropIntentInsertIntoDestinationIndexPath,
    
    // The table view will automatically choose between .insertAtDestinationIndexPath and
    // .insertIntoDestinationIndexPath depending on the position of the drop. This should be used instead
    // of .insertIntoDestinationIndexPath when the item being dropped can either be placed inside the row
    // at the destination index path or inserted in a new row at the index path of the container row.
    UITableViewDropIntentAutomatic
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UITableViewDropProposal : UIDropProposal

- (instancetype)initWithDropOperation:(UIDropOperation)operation intent:(UITableViewDropIntent)intent;

// The default is UITableViewDropIntentUnspecified.
@property (nonatomic, readonly) UITableViewDropIntent intent;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropCoordinator <NSObject>

// Ordered list of items available for this drop.
@property (nonatomic, readonly) NSArray<id<UITableViewDropItem>> *items;

// The last hit-tested index path known during the drop session.
// When the drop is at the end of a section, this index path will be for a row that does not yet exist (equal
// to the number of rows in that section), where an inserted row would append to the end of the section.
// This index path may be nil in some circumstances (e.g. when dragging over empty space where there are no cells),
// and if it is nil, the proposal's intent will always be UITableViewDropIntentUnspecified.
@property (nonatomic, readonly, nullable) NSIndexPath *destinationIndexPath;

// The current drop proposal at the time of the drop.
@property (nonatomic, readonly) UITableViewDropProposal *proposal;

// The drop session.
@property (nonatomic, readonly) id<UIDropSession> session;

// Animate the dragItem to an automatically inserted placeholder row.
// Once the dragItem data is available, you can exchange the temporary placeholder cell with the final cell using the placeholder context
// method -commitInsertionWithDataSourceUpdates:
- (id<UITableViewDropPlaceholderContext>)dropItem:(UIDragItem *)dragItem toPlaceholder:(UITableViewDropPlaceholder *)placeholder;

// Animate the dragItem to a row that you inserted at this index path.
// You must call -performBatchUpdates:completion: to update your data source and insert a new row into the table view prior to calling this method.
// If desired, use the drop delegate method -tableView:dropPreviewParametersForRowAtIndexPath: to provide preview parameters.
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toRowAtIndexPath:(NSIndexPath *)indexPath;

// Animate the dragItem to a rect inside an existing row.
// The rect is in the coordinate space of the cell at this index path.
// The item will be animated with an aspect fit scale transform to fit inside the rect. Use a rect with zero size to shrink the item to a single point.
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem intoRowAtIndexPath:(NSIndexPath *)indexPath rect:(CGRect)rect;

// Animate the dragItem to a location specified by the UIDragPreviewTarget.
// The -[UITableViewDropItem previewSize] may be helpful to compute an appropriate transform.
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toTarget:(UIDragPreviewTarget *)target;

@end


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UITableViewPlaceholder : NSObject

// A placeholder cell will be dequeued for the reuse identifier and inserted at the specified index path without requiring a data source update.
// You may use UITableViewAutomaticDimension for the rowHeight to have the placeholder cell self-size if the table view is using estimated row heights.
- (instancetype)initWithInsertionIndexPath:(NSIndexPath *)insertionIndexPath reuseIdentifier:(NSString *)reuseIdentifier rowHeight:(CGFloat)rowHeight NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Called whenever the placeholder cell is visible to update the contents of the cell.
@property (nonatomic, nullable, copy) void(^cellUpdateHandler)(__kindof UITableViewCell *);

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UITableViewDropPlaceholder : UITableViewPlaceholder

// Allows customization of the preview used when dropping to a placeholder.
// If no block is set, or if nil is returned, the entire cell will be used for the preview.
@property (nonatomic, nullable, copy) UIDragPreviewParameters * _Nullable (^previewParametersProvider)(__kindof UITableViewCell *);

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropItem <NSObject>

// Retrieve drop data from the dragItem's itemProvider.
@property (nonatomic, readonly) UIDragItem *dragItem;

// If this drop item is also from this table view this index path will specify the location of the row it came from.
// If the dragItem comes from some other source (e.g. another source inside or outside of the app), or if the source
// table view is updated or reloaded after the drag begins, this index path will be nil.
// This is useful for directly accessing the model object in your data source instead of using the item provider
// to retrieve the data.
@property (nonatomic, readonly, nullable) NSIndexPath *sourceIndexPath;

// May be useful for computing the UIDragPreviewTarget transform for UITableViewDropCoordinator dropItem:toTarget:
// Returns CGSizeZero if the dragItem does not have a visible drop preview.
@property (nonatomic, readonly) CGSize previewSize;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropPlaceholderContext <UIDragAnimating>

// The drag item this placeholder was created for.
@property (nonatomic, readonly) UIDragItem *dragItem;

// Exchange the placeholder for the final cell.
// You are only responsible for updating your data source inside the block using the provided insertionIndexPath.
// If the placeholder is no longer available (e.g. -reloadData has been called) the dataSourceUpdates block
// will not be executed and this will return NO.
- (BOOL)commitInsertionWithDataSourceUpdates:(void(NS_NOESCAPE ^)(NSIndexPath *insertionIndexPath))dataSourceUpdates;

// If the placeholder is no longer needed or you wish to manually insert a cell for the drop data, you can
// remove the placeholder via this method.
// If the placeholder is no longer available (e.g. -reloadData has been called) this will return NO.
- (BOOL)deletePlaceholder;

@end

NS_ASSUME_NONNULL_END
