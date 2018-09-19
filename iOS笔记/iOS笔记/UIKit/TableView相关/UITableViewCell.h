//
//  UITableViewCell.h
//  UIKit
//
//  Copyright (c) 2005-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIColor, UILabel, UIImageView, UIButton, UITextField, UITableView, UILongPressGestureRecognizer;

// 单元格风格
typedef NS_ENUM(NSInteger, UITableViewCellStyle) {
    UITableViewCellStyleDefault,    // 左侧显示textLabel（不显示detailTextLabel），imageView可选（显示在最左边）
    UITableViewCellStyleValue1,     // 左侧显示textLabel、右侧显示detailTextLabel（默认蓝色），imageView可选（显示在最左边
    UITableViewCellStyleValue2,     // 左侧依次显示textLabel(默认蓝色)和detailTextLabel，imageView可选（显示在最左边）
    UITableViewCellStyleSubtitle    // 左上方显示textLabel，左下方显示detailTextLabel（默认灰色）,imageView可选（显示在最左边）
};

// 单元格分割线样式
typedef NS_ENUM(NSInteger, UITableViewCellSeparatorStyle) {
    UITableViewCellSeparatorStyleNone, // 无
    UITableViewCellSeparatorStyleSingleLine, // 有单条分割线，默认
    UITableViewCellSeparatorStyleSingleLineEtched NS_ENUM_DEPRECATED_IOS(2_0, 11_0, "Use UITableViewCellSeparatorStyleSingleLine for a single line separator.") //废弃(两条分割线)
} __TVOS_PROHIBITED;

// 单元格选中样式
typedef NS_ENUM(NSInteger, UITableViewCellSelectionStyle) {
    UITableViewCellSelectionStyleNone, // 无
    UITableViewCellSelectionStyleBlue, // 默认选中样式
    UITableViewCellSelectionStyleGray, // 选中呈现灰色
    UITableViewCellSelectionStyleDefault NS_ENUM_AVAILABLE_IOS(7_0) // 表格单元格显示样式
};

// 聚焦样式
typedef NS_ENUM(NSInteger, UITableViewCellFocusStyle) {
    UITableViewCellFocusStyleDefault, // 当聚焦时采用系统默认样式
    UITableViewCellFocusStyleCustom // 当聚焦是采用自定义样式
} NS_ENUM_AVAILABLE_IOS(9_0);

// 编辑状态样式
typedef NS_ENUM(NSInteger, UITableViewCellEditingStyle) {
    UITableViewCellEditingStyleNone, // 无
    UITableViewCellEditingStyleDelete, // 删除
    UITableViewCellEditingStyleInsert // 插入
};

//右侧附件样式
typedef NS_ENUM(NSInteger, UITableViewCellAccessoryType) {
//    不同类型的accessoryType对应的view的宽度不同
//    UITableViewCellAccessoryDisclosureIndicator    -> view.width = 18
//    UITableViewCellAccessoryDetailDisclosureButton -> view.width = 52
//    UITableViewCellAccessoryCheckmark              -> view.width = 24
//    UITableViewCellAccessoryDetailButton           -> view.width = 32
   
    //不显示任何的accessoryView
    UITableViewCellAccessoryNone,
    //浅灰色箭头图标
    UITableViewCellAccessoryDisclosureIndicator,
    //一个箭头和显示详情的圆圈i
    UITableViewCellAccessoryDetailDisclosureButton __TVOS_PROHIBITED,
    //一个勾
    UITableViewCellAccessoryCheckmark,
    //显示详情的圆圈i
    UITableViewCellAccessoryDetailButton NS_ENUM_AVAILABLE_IOS(7_0)  __TVOS_PROHIBITED
};

// 表格状态
typedef NS_OPTIONS(NSUInteger, UITableViewCellStateMask) {
    UITableViewCellStateDefaultMask                     = 0, // 默认
    UITableViewCellStateShowingEditControlMask          = 1 << 0, // 编辑状态
    UITableViewCellStateShowingDeleteConfirmationMask   = 1 << 1 // 删除状态
};

typedef NS_ENUM(NSInteger, UITableViewCellDragState) {
    UITableViewCellDragStateNone,
    UITableViewCellDragStateLifting, // The cell is lifting from the table view before it joins the drag session.
    UITableViewCellDragStateDragging // The cell is involved in a drag session.
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

#define UITableViewCellStateEditingMask UITableViewCellStateShowingEditControlMask

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableViewCell : UIView <NSCoding, UIGestureRecognizerDelegate>

//指定的初始化程序。 如果可以重用该单元，则必须传入重用标识符。 您应该对同一种cell的所有单元使用相同的重用标识符。
- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(nullable NSString *)reuseIdentifier NS_AVAILABLE_IOS(3_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

//内容 这些属性提供对表视图单元格使用的内部标签和图像视图的直接访问。 应该使用这些代替下面的内容属性。

//默认为nil。 必要时将创建图像视图。
@property (nonatomic, readonly, strong, nullable) UIImageView *imageView NS_AVAILABLE_IOS(3_0);
//标题label
@property (nonatomic, readonly, strong, nullable) UILabel *textLabel NS_AVAILABLE_IOS(3_0);

//默认为nil。 必要时将创建标签（cell的某些UITableViewCellStyle样式才有）。
@property (nonatomic, readonly, strong, nullable) UILabel *detailTextLabel NS_AVAILABLE_IOS(3_0);

//如果您想通过简单地添加其他视图来自定义单元格，则应将它们添加到内容视图中，以便在单元格进入和退出编辑模式时将它们正确定位。
//建议将子视图加载contentView上，系统在编辑模式时会自动保证布局正确性
@property (nonatomic, readonly, strong) UIView *contentView;

//对于UITableViewStylePlain中的单元格，默认值为nil；
//对于UITableViewStyleGrouped，默认值为非nil。 'backgroundView'将作为子视图添加到所有其他视图后面。
@property (nonatomic, strong, nullable) UIView *backgroundView;


//对于UITableViewStylePlain中的单元格，默认值为nil，对于UITableViewStyleGrouped，默认值为非nil。
//如果不是nil，或者在所有其他视图后面，'selectedBackgroundView'将作为子视图直接添加到backgroundView上方。
//仅在选择单元格时才将其添加为子视图。
//调用-setSelected：animated：将导致'selectedBackgroundView'使用alpha淡入淡出进行动画处理。
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

//如果不是nil，则在使用多选时取代selectedBackgroundView。
@property (nonatomic, strong, nullable) UIView *multipleSelectionBackgroundView NS_AVAILABLE_IOS(5_0);

//重用标识符
@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;
//如果单元格是可重用的（具有重用标识符），则在从表视图方法dequeueReusableCellWithIdentifier：返回单元格之前调用它。重写必须实现父类
- (void)prepareForReuse NS_REQUIRES_SUPER;

//默认为UITableViewCellSelectionStyleDefault。
@property (nonatomic) UITableViewCellSelectionStyle   selectionStyle;

//设置选定状态（标题，图像，背景）。 默认为NO。 选择时不带动画
@property (nonatomic, getter=isSelected) BOOL         selected;
//设置突出显示的状态（标题，图像，背景）。 默认为NO。 高亮时不带动画
@property (nonatomic, getter=isHighlighted) BOOL      highlighted;
//设置选定状态、设置切换时是否需求系统动画
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;
//设置突出显示的状态、设置切换时是否需求系统动画
- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated;

//默认为UITableViewCellEditingStyleNone。 这是由UITableView使用委托的值为相应自定义其外观的单元格设置的。
@property (nonatomic, readonly) UITableViewCellEditingStyle editingStyle;
//设置重新排序控制，default is NO
@property (nonatomic) BOOL                            showsReorderControl;
//设置应该在编辑时缩进，默认为YES。 这与下面的缩进级别无关。
@property (nonatomic) BOOL                            shouldIndentWhileEditing;


//默认为UITableViewCellAccessoryNone。右侧辅助视图 eg用于设置cell右侧箭头
@property (nonatomic) UITableViewCellAccessoryType    accessoryType;
//如果设置，将忽略accessoryType，使用自定义视图(eg：放个开关代替右侧箭头)。
@property (nonatomic, strong, nullable) UIView       *accessoryView;
//默认为UITableViewCellAccessoryNone。 编辑时辅助视图样式
@property (nonatomic) UITableViewCellAccessoryType    editingAccessoryType;
//如果设置，将忽略editingAccessoryType，使用自定义视图代替右侧辅助视图
@property (nonatomic, strong, nullable) UIView       *editingAccessoryView;

//调整内容缩进。 默认值为0
@property (nonatomic) NSInteger                       indentationLevel;
//每个级别的宽度。 默认值为10.0
@property (nonatomic) CGFloat                         indentationWidth;
//允许自定义分隔符上左下右间距
@property (nonatomic) UIEdgeInsets                    separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

//显示适当的编辑控件（+/-＆reorder）。 默认情况下-setEditing：调用setEditing：animated：动画NO。
@property (nonatomic, getter=isEditing) BOOL          editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

//当前显示“删除”按钮（只读）
@property(nonatomic, readonly) BOOL                   showingDeleteConfirmation;

// 聚焦样式
@property (nonatomic) UITableViewCellFocusStyle       focusStyle NS_AVAILABLE_IOS(9_0) UI_APPEARANCE_SELECTOR;

//当单元格更改状态时，子类可以使用这些方法为单元格的其他更改设置动画
//注意，当刷单元格时，单元格将转换为UITableViewCellStateShowingDeleteConfirmationMask状态，
//但不会设置UITableViewCellStateShowingEditControlMask。
- (void)willTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);
- (void)didTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);

/* Override this method to receive notifications that the cell's drag state has changed.
 * Call super if you want to apply the default appearance.
   重写此方法以接收单元格拖动状态已更改的通知。
   重写需要调用super。
 */
- (void)dragStateDidChange:(UITableViewCellDragState)dragState API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/* Controls whether the cell in the table view allows user interaction once it is part of a drag (UITableViewCellDragStateDragging).
 * Default is NO.
   控制表视图中的单元格是否允许用户在拖动（UITableViewCellDragStateDragging）的一部分时进行交互。
   *默认为NO。(11+)
 */
@property (nonatomic) BOOL userInteractionEnabledWhileDragging API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end

#pragma - mark 已经失效的方法
@interface UITableViewCell (UIDeprecated)

// Frame is ignored.  The size will be specified by the table view width and row height.
//Frame设置无效被忽略。 大小将由表视图宽度和行高指定。
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(nullable NSString *)reuseIdentifier NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// Content properties.  These properties were deprecated in iPhone OS 3.0.  The textLabel and imageView properties above should be used instead.
// For selected attributes, set the highlighted attributes on the textLabel and imageView.
@property (nonatomic, copy, nullable)   NSString *text NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                        // default is nil
@property (nonatomic, strong, nullable) UIFont   *font NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                        // default is nil (Use default font)
@property (nonatomic) NSTextAlignment   textAlignment NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is UITextAlignmentLeft
@property (nonatomic) NSLineBreakMode   lineBreakMode NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is UILineBreakModeTailTruncation
@property (nonatomic, strong, nullable) UIColor  *textColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                   // default is nil (text draws black)
@property (nonatomic, strong, nullable) UIColor  *selectedTextColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;           // default is nil (text draws white)

@property (nonatomic, strong, nullable) UIImage  *image NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                       // default is nil. appears on left next to title.
@property (nonatomic, strong, nullable) UIImage  *selectedImage NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is nil

// Use the new editingAccessoryType and editingAccessoryView instead
@property (nonatomic) BOOL              hidesAccessoryWhenEditing NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;   // default is YES

// Use the table view data source method -tableView:commitEditingStyle:forRowAtIndexPath: or the table view delegate method -tableView:accessoryButtonTappedForRowWithIndexPath: instead
@property (nonatomic, assign, nullable) id        target NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                      // target for insert/delete/accessory clicks. default is nil (i.e. go up responder chain). weak reference
@property (nonatomic, nullable) SEL               editAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                  // action to call on insert/delete call. set by UITableView
@property (nonatomic, nullable) SEL               accessoryAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;             // action to call on accessory view clicked. set by UITableView

@end

NS_ASSUME_NONNULL_END
