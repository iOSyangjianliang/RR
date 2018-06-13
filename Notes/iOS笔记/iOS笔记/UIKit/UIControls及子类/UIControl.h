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
    //单点触摸按下事件：用户点触屏幕，或者又有新手指落下的时候。
    UIControlEventTouchDown                                         = 1 <<  0,
    //多点触摸按下事件，点触计数大于1：用户按下第二、三、或第四根手指的时候。
    UIControlEventTouchDownRepeat                                   = 1 <<  1,
    //当一次触摸在控件窗口内拖动时,不松手就触发事件，一直触发
    UIControlEventTouchDragInside                                   = 1 <<  2,
    //当一次触摸在控件窗口之外拖动时,不松手就触发事件，一直触发
    UIControlEventTouchDragOutside                                  = 1 <<  3,
    //当一次触摸从控件窗口之外拖动到内部时。
    UIControlEventTouchDragEnter                                    = 1 <<  4,
    //当一次触摸从控件窗口内部拖动到外部时。不松手就触发事件，只触发一次
    UIControlEventTouchDragExit                                     = 1 <<  5,
    //所有在控件之内触摸抬起事件。
    UIControlEventTouchUpInside                                     = 1 <<  6,
    //所有在控件之外触摸抬起事件(点触必须开始与控件内部才会发送通知)。
    UIControlEventTouchUpOutside                                    = 1 <<  7,
    //所有触摸取消事件，即一次触摸因为放上了太多手指而被取消，或者被上锁或者电话呼叫打断。
    UIControlEventTouchCancel                                       = 1 <<  8,
    
    //当控件的值发生改变时，发送通知。用于滑块、分段控件、以及其他取值的控件。你可以配置滑块控件何时发送通知，在滑块被放下时发送，或者在被拖动时发送。
    UIControlEventValueChanged                                      = 1 << 12,
    //当控件的首要行为被触发，例如button的点击事件，slider的滑动事件。
    UIControlEventPrimaryActionTriggered NS_ENUM_AVAILABLE_IOS(9_0) = 1 << 13,

    //当文本控件中开始编辑时发送通知(UITextField)
    UIControlEventEditingDidBegin                                   = 1 << 16,
    //当文本控件中的文本被改变时发送通知。
    UIControlEventEditingChanged                                    = 1 << 17,
    //当文本控件中编辑结束时发送通知
    UIControlEventEditingDidEnd                                     = 1 << 18,
    //当文本控件内通过按下return回车键（或等价行为）结束编辑时，发送通知,
    UIControlEventEditingDidEndOnExit                               = 1 << 19,

    //通知所有触摸事件。
    UIControlEventAllTouchEvents                                    = 0x00000FFF,  // for touch events
    //通知所有关于文本编辑的事件。
    UIControlEventAllEditingEvents                                  = 0x000F0000,  // for UITextField
    //预留给application（应用）使用的事件。
    UIControlEventApplicationReserved                               = 0x0F000000,  // range available for application use
    //预留给internal framework（内部框架）使用的事件。
    UIControlEventSystemReserved                                    = 0xF0000000,  // range reserved for internal framework use
    //通知所有事件。
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
    //普通状态
    UIControlStateNormal       = 0,
    //高亮状态
    UIControlStateHighlighted  = 1 << 0,                  // used when UIControl isHighlighted is set
    //禁用状态
    UIControlStateDisabled     = 1 << 1,
    //选中状态
    UIControlStateSelected     = 1 << 2,                  // flag usable by app (see below)标志可用于应用程序（请参见下文
    //仅当屏幕支持焦点时才适用
    UIControlStateFocused NS_ENUM_AVAILABLE_IOS(9_0) = 1 << 3, // Applicable only when the screen supports focus
    //可用于应用程序的其他标志
    UIControlStateApplication  = 0x00FF0000,              // additional flags available for application use
    //标记为内部框架使用保留
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
