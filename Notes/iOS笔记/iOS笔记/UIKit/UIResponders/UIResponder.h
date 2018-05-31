//
//  UIResponder.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIEvent.h>
#import <UIKit/UIPasteConfigurationSupporting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPress;
@class UIPressesEvent;

@protocol UIResponderStandardEditActions <NSObject>
@optional
//剪切
- (void)cut:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//复制
- (void)copy:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//粘贴
- (void)paste:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//选择
- (void)select:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//全选
- (void)selectAll:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//删除
- (void)delete:(nullable id)sender NS_AVAILABLE_IOS(3_2);
//从左到右写入字符串(居左)
- (void)makeTextWritingDirectionLeftToRight:(nullable id)sender NS_AVAILABLE_IOS(5_0);
//从右到左写入字符串(居右)
- (void)makeTextWritingDirectionRightToLeft:(nullable id)sender NS_AVAILABLE_IOS(5_0);
//切换字体为黑体(粗体)
- (void)toggleBoldface:(nullable id)sender NS_AVAILABLE_IOS(6_0);
//切换字体为斜体
- (void)toggleItalics:(nullable id)sender NS_AVAILABLE_IOS(6_0);
//给文字添加下划线
- (void)toggleUnderline:(nullable id)sender NS_AVAILABLE_IOS(6_0);
//增加字体大小
- (void)increaseSize:(nullable id)sender NS_AVAILABLE_IOS(7_0);
//减小字体大小
- (void)decreaseSize:(nullable id)sender NS_AVAILABLE_IOS(7_0);

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIResponder : NSObject <UIResponderStandardEditActions>

//响应链怎么工作的 https://www.jianshu.com/p/53100391a920
//返回接收下一个响应者，或者nil如果它有没有
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, nullable) UIResponder *nextResponder;
#else
- (nullable UIResponder*)nextResponder;
#endif

//是否可以成为第一个响应者,默认NO
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL canBecomeFirstResponder;    // default is NO
#else
- (BOOL)canBecomeFirstResponder;    // default is NO
#endif
//通知接收器，即将成为第一响应在其窗口。
- (BOOL)becomeFirstResponder;

//是否可以放弃第一响应状态。
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL canResignFirstResponder;    // default is YES
#else
- (BOOL)canResignFirstResponder;    // default is YES
#endif
//通知接收器，注销第一响应在其窗口。
- (BOOL)resignFirstResponder;

//是否是第一响应者
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL isFirstResponder;
#else
- (BOOL)isFirstResponder;
#endif

// Generally, all responders which do custom touch handling should override all four of these methods.
// Your responder will receive either touchesEnded:withEvent: or touchesCancelled:withEvent: for each
// touch it is handling (those touches it received in touchesBegan:withEvent:).
// *** You must handle cancelled touches to ensure correct behavior in your application.  Failure to
// do so is very likely to lead to incorrect behavior or crashes.
//通常，所有进行自定义触摸处理的响应者都应该重写所有这四种方法。
// ***您必须处理取消的触摸以确保应用程序中的正确行为。
//不这样做很可能导致不正确的行为或崩溃。

#pragma mark - 触摸相关方法，一般用于响应屏幕触摸
//当一个或多个手指触摸到了视图或者窗口响应。
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//当用图或窗口内的事件移动相关联的一个或更多个手指的响应者
- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//当一个或多个手指从视图或窗口所结束触摸
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//发送到应答时，系统事件(意外中断, 如:电话, 系统警告窗等)取消的触摸事件。
- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//发送到应答器时的触摸所估计的特性发生了改变，使它们不再估计或更新不再预期。
//3DTouch响应(iOS9.1后使用)
- (void)touchesEstimatedPropertiesUpdated:(NSSet<UITouch *> *)touches NS_AVAILABLE_IOS(9_1);

// Generally, all responders which do custom press handling should override all four of these methods.
// Your responder will receive either pressesEnded:withEvent or pressesCancelled:withEvent: for each
// press it is handling (those presses it received in pressesBegan:withEvent:).
// pressesChanged:withEvent: will be invoked for presses that provide an analog value
// (like thumbsticks or analog push buttons)
// *** You must handle cancelled presses to ensure correct behavior in your application.  Failure to
// do so is very likely to lead to incorrect behavior or crashes.
//通常，所有进行"自定义按压事件处理"的响应者都应该重写所有这四种方法。
// ***您必须处理取消的触摸以确保应用程序中的正确行为。
//不这样做很可能导致不正确的行为或崩溃。

#pragma mark - 深按相关方法，一般用于遥控器按键响应
//手指按压开始时响应
- (void)pressesBegan:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
//手指按压位置移动时响应
- (void)pressesChanged:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
//手指抬起结束按压时响应
- (void)pressesEnded:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
//按压取消(意外中断, 如:电话, 系统警告窗等)
- (void)pressesCancelled:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);

#pragma mark - 加速相关方法，一般用于摇一摇、运动事件监听等
//开始加速
- (void)motionBegan:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
//结束加速
- (void)motionEnded:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
//加速取消（意外中断, 如:电话, 系统警告窗等）
- (void)motionCancelled:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);

//远程控制事件
- (void)remoteControlReceivedWithEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(4_0);

//返回UIMenuController需要显示的控件(如：复制，粘贴等)
- (BOOL)canPerformAction:(SEL)action withSender:(nullable id)sender NS_AVAILABLE_IOS(3_0);
// Allows an action to be forwarded to another target. By default checks -canPerformAction:withSender: to either return self, or go up the responder chain.
//允许一个动作被转发到另一个目标。 默认情况下，检查-canPerformAction：withSender：要么返回自我，要么上级响应者链。
//返回响应操作的目标对象(标识与命令相关联的方法的选择器)
- (nullable id)targetForAction:(SEL)action withSender:(nullable id)sender NS_AVAILABLE_IOS(7_0);

//获取撤消管理器
@property(nullable, nonatomic,readonly) NSUndoManager *undoManager NS_AVAILABLE_IOS(3_0);

@end
//快捷主键枚举
typedef NS_OPTIONS(NSInteger, UIKeyModifierFlags) {
    
    UIKeyModifierAlphaShift     = 1 << 16,  //!< Alpha+Shift键.该位指示大写锁定
    UIKeyModifierShift          = 1 << 17,  //!< Shift键.
    UIKeyModifierControl        = 1 << 18,  //!< Control键.
    UIKeyModifierAlternate      = 1 << 19,  //!< Alt键.
    UIKeyModifierCommand        = 1 << 20,  //!< Command键.
    UIKeyModifierNumericPad     = 1 << 21,  //!< Num键.
} NS_ENUM_AVAILABLE_IOS(7_0);

NS_CLASS_AVAILABLE_IOS(7_0) @interface UIKeyCommand : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

//获取快捷辅键（如快捷命令【Command+A】中的 A 键）

//输入字符串
@property (nullable,nonatomic,readonly) NSString *input;
//按键调节器
@property (nonatomic,readonly) UIKeyModifierFlags modifierFlags;
//按指定调节器键输入字符串并设置事件
//一个可选的标签，用来在发现层显示快捷键命令。只有设置了标题的键盘命令才会被列出。
@property (nullable,nonatomic,copy) NSString *discoverabilityTitle NS_AVAILABLE_IOS(9_0);

// The action for UIKeyCommands should accept a single (id)sender, as do the UIResponderStandardEditActions above
// UIKeyCommands的动作应该接受一个（id）发送者，就像上面的UIResponderStandardEditActions一样

// Creates an key command that will _not_ be discoverable in the UI. 创建一个在UI中不可发现的键盘命令。
//创建一个快捷键命令
+ (UIKeyCommand *)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action;

// Key Commands with a discoverabilityTitle _will_ be discoverable in the UI. 具有可发现性标题的关键命令将在UI中被发现。
+ (UIKeyCommand *)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action discoverabilityTitle:(NSString *)discoverabilityTitle NS_AVAILABLE_IOS(9_0);

@end

@interface UIResponder (UIResponderKeyCommands)
//返回快捷键命令数组
@property (nullable,nonatomic,readonly) NSArray<UIKeyCommand *> *keyCommands NS_AVAILABLE_IOS(7_0); // returns an array of UIKeyCommand objects<
@end

@class UIInputViewController;
@class UITextInputMode;
@class UITextInputAssistantItem;

@interface UIResponder (UIResponderInputViewAdditions)

// Called and presented when object becomes first responder.  Goes up the responder chain.
// 当对象成为第一响应者时调用并呈现。 走上响应者链。

//键盘输入视图(系统默认的,可以自定义)
@property (nullable, nonatomic, readonly, strong) __kindof UIView *inputView NS_AVAILABLE_IOS(3_2);
//弹出键盘时键盘上附带的视图，即二级键盘
@property (nullable, nonatomic, readonly, strong) __kindof UIView *inputAccessoryView NS_AVAILABLE_IOS(3_2);

/// This method is for clients that wish to put buttons on the Shortcuts Bar, shown on top of the keyboard.
/// You may modify the returned inputAssistantItem to add to or replace the existing items on the bar.
/// Modifications made to the returned UITextInputAssistantItem are reflected automatically.
/// This method should not be overriden. Goes up the responder chain.
///此方法适用于希望将按钮放在快捷键栏上的客户端，如键盘上方所示。
///您可以修改返回的inputAssistantItem以添加或替换条上的现有项目。
///对返回的UITextInputAssistantItem所做的修改会自动反映出来。
///这个方法不应该被重写。 走上响应者链。
//在配置键盘快捷键时使用的输入助手
@property (nonnull, nonatomic, readonly, strong) UITextInputAssistantItem *inputAssistantItem NS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

// For viewController equivalents of -inputView and -inputAccessoryView
// Called and presented when object becomes first responder.  Goes up the responder chain.
//对于-inputView和-inputAccessoryView的viewController等价物
//当对象成为第一响应者时调用并呈现。 走上响应者链。
//自定义输入视图控制器(一般用于替换UITextField和UITextView对象呈现的系统提供的键盘)
@property (nullable, nonatomic, readonly, strong) UIInputViewController *inputViewController NS_AVAILABLE_IOS(8_0);
//自定义输入附件视图控制器(一般用于添加到UITextField和UITextView对象呈现的系统提供的键盘上)
@property (nullable, nonatomic, readonly, strong) UIInputViewController *inputAccessoryViewController NS_AVAILABLE_IOS(8_0);

/* When queried, returns the current UITextInputMode, from which the keyboard language can be determined.
 * When overridden it should return a previously-queried UITextInputMode object, which will attempt to be
 * set inside that app, but not persistently affect the user's system-wide keyboard settings. */
/* 查询时，返回当前的UITextInputMode，从中可以确定键盘语言。
 * 重写时，它应该返回先前查询的UITextInputMode对象，该对象将试图成为
 * 在该应用程序内设置，但不会持续影响用户的系统范围键盘设置。*/
//响应器对象的文本输入模式
@property (nullable, nonatomic, readonly, strong) UITextInputMode *textInputMode NS_AVAILABLE_IOS(7_0);
/* When the first responder changes and an identifier is queried, the system will establish a context to
 * track the textInputMode automatically. The system will save and restore the state of that context to
 * the user defaults via the app identifier. Use of -textInputMode above will supersede use of -textInputContextIdentifier. */
/* 当第一响应者改变并且查询标识符时，系统将建立到上下文
 * 自动跟踪textInputMode。 系统将保存并恢复该上下文的状态
 * 用户通过应用程序标识符默认。 上面的-textInputMode的使用将取代使用-textInputContextIdentifier。*/
//响应器应保存其文本输入模式信息的标识符
@property (nullable, nonatomic, readonly, strong) NSString *textInputContextIdentifier NS_AVAILABLE_IOS(7_0);
// This call is to remove stored app identifier state that is no longer needed.
//这个调用是删除不再需要的存储应用程序标识符状态。
+ (void)clearTextInputContextIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(7_0);

// If called while object is first responder, reloads inputView, inputAccessoryView, and textInputMode.  Otherwise ignored.
//如果对象是第一响应者时调用，则重新加载inputView，inputAccessoryView和textInputMode。 否则被忽略。
- (void)reloadInputViews NS_AVAILABLE_IOS(3_2);

@end

// These are pre-defined constants for use with the input property of UIKeyCommand objects.
// 这些是用于UIKeyCommand对象的输入属性的预定义常量。
//特殊快捷辅键定义
UIKIT_EXTERN NSString *const UIKeyInputUpArrow         NS_AVAILABLE_IOS(7_0);//上按键
UIKIT_EXTERN NSString *const UIKeyInputDownArrow       NS_AVAILABLE_IOS(7_0);//下按键
UIKIT_EXTERN NSString *const UIKeyInputLeftArrow       NS_AVAILABLE_IOS(7_0);//左按键
UIKIT_EXTERN NSString *const UIKeyInputRightArrow      NS_AVAILABLE_IOS(7_0);//右按键
UIKIT_EXTERN NSString *const UIKeyInputEscape          NS_AVAILABLE_IOS(7_0);//Esc按键

@interface UIResponder (ActivityContinuation)
//封装由该响应器支持的用户活动的对象
@property (nullable, nonatomic, strong) NSUserActivity *userActivity NS_AVAILABLE_IOS(8_0);
//更新给定用户活动的状态
- (void)updateUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
//恢复继续给定用户活动所需的状态
- (void)restoreUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
@end

#if TARGET_OS_IOS
@interface UIResponder (UIPasteConfigurationSupporting) <UIPasteConfigurationSupporting>
@end
#endif

NS_ASSUME_NONNULL_END

