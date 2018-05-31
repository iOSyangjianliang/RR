//
//  UIControl.h
//  UIKit
//
//  Copyright (c) 2005-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UIControlEvents) {
    UIControlEventTouchDown                                         = 1 <<  0,      // on all touch downs
    UIControlEventTouchDownRepeat                                   = 1 <<  1,      // on multiple touchdowns (tap count > 1)
    UIControlEventTouchDragInside                                   = 1 <<  2,
    UIControlEventTouchDragOutside                                  = 1 <<  3,
    UIControlEventTouchDragEnter                                    = 1 <<  4,
    UIControlEventTouchDragExit                                     = 1 <<  5,
    UIControlEventTouchUpInside                                     = 1 <<  6,
    UIControlEventTouchUpOutside                                    = 1 <<  7,
    UIControlEventTouchCancel                                       = 1 <<  8,

    UIControlEventValueChanged                                      = 1 << 12,     // sliders, etc.
    UIControlEventPrimaryActionTriggered NS_ENUM_AVAILABLE_IOS(9_0) = 1 << 13,     // semantic action: for buttons, etc.

    UIControlEventEditingDidBegin                                   = 1 << 16,     // UITextField
    UIControlEventEditingChanged                                    = 1 << 17,
    UIControlEventEditingDidEnd                                     = 1 << 18,
    UIControlEventEditingDidEndOnExit                               = 1 << 19,     // 'return key' ending editing

    UIControlEventAllTouchEvents                                    = 0x00000FFF,  // for touch events
    UIControlEventAllEditingEvents                                  = 0x000F0000,  // for UITextField
    UIControlEventApplicationReserved                               = 0x0F000000,  // range available for application use
    UIControlEventSystemReserved                                    = 0xF0000000,  // range reserved for internal framework use
    UIControlEventAllEvents                                         = 0xFFFFFFFF
};

typedef NS_ENUM(NSInteger, UIControlContentVerticalAlignment) {
    UIControlContentVerticalAlignmentCenter  = 0,
    UIControlContentVerticalAlignmentTop     = 1,
    UIControlContentVerticalAlignmentBottom  = 2,
    UIControlContentVerticalAlignmentFill    = 3,
};

typedef NS_ENUM(NSInteger, UIControlContentHorizontalAlignment) {
    UIControlContentHorizontalAlignmentCenter = 0,
    UIControlContentHorizontalAlignmentLeft   = 1,
    UIControlContentHorizontalAlignmentRight  = 2,
    UIControlContentHorizontalAlignmentFill   = 3,
    UIControlContentHorizontalAlignmentLeading  API_AVAILABLE(ios(11.0), tvos(11.0)) = 4,
    UIControlContentHorizontalAlignmentTrailing API_AVAILABLE(ios(11.0), tvos(11.0)) = 5,
};

typedef NS_OPTIONS(NSUInteger, UIControlState) {
    UIControlStateNormal       = 0,
    UIControlStateHighlighted  = 1 << 0,                  // used when UIControl isHighlighted is set
    UIControlStateDisabled     = 1 << 1,
    UIControlStateSelected     = 1 << 2,                  // flag usable by app (see below)
    UIControlStateFocused NS_ENUM_AVAILABLE_IOS(9_0) = 1 << 3, // Applicable only when the screen supports focus
    UIControlStateApplication  = 0x00FF0000,              // additional flags available for application use
    UIControlStateReserved     = 0xFF000000               // flags reserved for internal framework use
};

@class UITouch;
@class UIEvent;

//______________________________________________________

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIControl : UIView

//默认是YES。 如果否，则忽略触摸事件，并且子类可能以不同方式绘制
@property(nonatomic,getter=isEnabled) BOOL enabled;
//默认为NO可能会被某些子类或应用程序使用
@property(nonatomic,getter=isSelected) BOOL selected;
//默认为NO。高亮状态、在追踪期间触摸进入/退出并在清除时自动清除
@property(nonatomic,getter=isHighlighted) BOOL highlighted;
//如何在控件内部垂直放置内容。默认是居中
@property(nonatomic) UIControlContentVerticalAlignment contentVerticalAlignment;
//如何在控件内部水平放置内容。 默认是居中
@property(nonatomic) UIControlContentHorizontalAlignment contentHorizontalAlignment;
//如何在控件内部水平定位内容，保证返回任何'左对齐'或'右对齐'的'左'或'右'边
@property(nonatomic, readonly) UIControlContentHorizontalAlignment effectiveContentHorizontalAlignment;

//可以是多个状态（例如，disabled|selected）。 从其他标志合成。
@property(nonatomic,readonly) UIControlState state;
@property(nonatomic,readonly,getter=isTracking) BOOL tracking;
//仅在tracking期间有效
@property(nonatomic,readonly,getter=isTouchInside) BOOL touchInside;

- (BOOL)beginTrackingWithTouch:(UITouch *)touch withEvent:(nullable UIEvent *)event;
- (BOOL)continueTrackingWithTouch:(UITouch *)touch withEvent:(nullable UIEvent *)event;
//如果cancelTracking调用这个，touch有时为nil。
- (void)endTrackingWithTouch:(nullable UITouch *)touch withEvent:(nullable UIEvent *)event;
//如果因非事件原因而被取消，则事件可能为nil。 从窗口中移除
- (void)cancelTrackingWithEvent:(nullable UIEvent *)event;

//为特定事件添加目标target/动作action。 您可以多次调用此选项，并且您可以为特定事件指定多个目标/操作。
//当目标沿着响应者链传递时，传入nil。 该操作可以选择包括发件人和事件的顺序
//该操作不能为NULL。 请注意，目标target不会retained保留。
- (void)addTarget:(nullable id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

//为一组事件移除target/action。 action传入NULL以删除该目标的所有操作
- (void)removeTarget:(nullable id)target action:(nullable SEL)action forControlEvents:(UIControlEvents)controlEvents;

//获取有关目标和行动的信息。 这可以通过检查每个事件类型来枚举所有目标/操作
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic,readonly) NSSet *allTargets;
//有至少一个动作的所有事件的列表
@property(nonatomic,readonly) UIControlEvents allControlEvents;
#else
//set可能包含NSNull来表示至少有一个nil目标
- (NSSet *)allTargets;
//有至少一个动作的所有事件的列表
- (UIControlEvents)allControlEvents;
#endif

//单个事件。 返回NSString选择器名称的NSArray。 如果没有，则返回nil
- (nullable NSArray<NSString *> *)actionsForTarget:(nullable id)target forControlEvent:(UIControlEvents)controlEvent;

//发送操作。 第一种方法被称为事件，并且您可以观察或重写行为。 它被第二个反复调用。
- (void)sendAction:(SEL)action to:(nullable id)target forEvent:(nullable UIEvent *)event;
//发送与事件相关的所有操作
- (void)sendActionsForControlEvents:(UIControlEvents)controlEvents;

@end

NS_ASSUME_NONNULL_END
