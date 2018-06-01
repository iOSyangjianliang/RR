//
//  UITextView.h
//  UIKit
//
//  Copyright (c) 2007-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextDragging.h>
#import <UIKit/UITextDropping.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UITextInteraction.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UITextPasteConfigurationSupporting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIFont, UIColor, UITextView, NSTextContainer, NSLayoutManager, NSTextStorage, NSTextAttachment;

@protocol UITextViewDelegate <NSObject, UIScrollViewDelegate>

@optional

// 将要开始编辑
- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
// 将要结束编辑
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;

// 开始编辑
- (void)textViewDidBeginEditing:(UITextView *)textView;
// 结束编辑
- (void)textViewDidEndEditing:(UITextView *)textView;

// 文本将要改变
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
// 文本发生改变
- (void)textViewDidChange:(UITextView *)textView;

// 焦点发生改变
- (void)textViewDidChangeSelection:(UITextView *)textView;

// 是否允许对文本中的URL进行操作（10+）
- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction NS_AVAILABLE_IOS(10_0);
// 是否允许对文本中的富文本进行操作（10+）
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction NS_AVAILABLE_IOS(10_0);

//10+后被以上两个替换了
- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange NS_DEPRECATED_IOS(7_0, 10_0, "Use textView:shouldInteractWithURL:inRange:forInteractionType: instead");
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange NS_DEPRECATED_IOS(7_0, 10_0, "Use textView:shouldInteractWithTextAttachment:inRange:forInteractionType: instead");

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITextView : UIScrollView <UITextInput, UIContentSizeCategoryAdjusting>

@property(nullable,nonatomic,weak) id<UITextViewDelegate> delegate;

@property(null_resettable,nonatomic,copy) NSString *text;
@property(nullable,nonatomic,strong) UIFont *font;
@property(nullable,nonatomic,strong) UIColor *textColor;
@property(nonatomic) NSTextAlignment textAlignment;    // default is NSLeftTextAlignment,默认左对齐
@property(nonatomic) NSRange selectedRange; //选中范围
@property(nonatomic,getter=isEditable) BOOL editable __TVOS_PROHIBITED; //是否可以编辑
@property(nonatomic,getter=isSelectable) BOOL selectable NS_AVAILABLE_IOS(7_0); // toggle selectability, which controls the ability of the user to select content and interact with URLs & attachments. On tvOS this also makes the text view focusable.切换可选择性，控制用户选择内容并与URL和附件交互的能力。 在tvOS上，这也使文本视图可以聚焦

//属性可以设定使电话号码、网址、电子邮件和符合格式的日期等文字变为链接文字
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;

// 默认值为NO 是否允许更改字符属性字典 
@property(nonatomic) BOOL allowsEditingTextAttributes NS_AVAILABLE_IOS(6_0);
@property(null_resettable,copy) NSAttributedString *attributedText NS_AVAILABLE_IOS(6_0);
@property(nonatomic,copy) NSDictionary<NSString *, id> *typingAttributes NS_AVAILABLE_IOS(6_0); // automatically resets when the selection changes 当选择改变时自动重置

//滚动到文本的某个段
- (void)scrollRangeToVisible:(NSRange)range;

// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
//当对象成为第一响应者时呈现。 如果设置为nil，则返回到以下响应者链。 如果
//在第一个响应者时设置，直到reloadInputViews被调用才会生效
// 不弹出键盘，弹出添加的这个视图(只有height值会对视图有影响)，一般用作像银行app的自定义键盘
@property (nullable, readwrite, strong) UIView *inputView;
// 在键盘上附加一个视图，一般用于添加一个收回键盘的按钮
@property (nullable, readwrite, strong) UIView *inputAccessoryView;

@property(nonatomic) BOOL clearsOnInsertion NS_AVAILABLE_IOS(6_0); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO. 默认为NO。 如果YES，则隐藏选择UI，插入文本将替换该字段的内容。 改变选择将自动设置为NO。

// Create a new text view with the specified text container (can be nil) - this is the new designated initializer for this class
//使用指定的文本容器创建一个新的文本视图(可以为nil)——这是这个类的新指定初始化器。
- (instancetype)initWithFrame:(CGRect)frame textContainer:(nullable NSTextContainer *)textContainer NS_AVAILABLE_IOS(7_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

//获取文本视图的文本容器。 定义了一个矩形区域用于存放已经进行了排版并设置好属性的文字
@property(nonatomic,readonly) NSTextContainer *textContainer NS_AVAILABLE_IOS(7_0);
//内容边距，默认值UIEdgeInsetsMake(8, 0, 8, 0)
@property(nonatomic, assign) UIEdgeInsets textContainerInset NS_AVAILABLE_IOS(7_0);

//用于管理NSTextStorage其中的文字内容的排版布局
@property(nonatomic,readonly) NSLayoutManager *layoutManager NS_AVAILABLE_IOS(7_0);
//NSTextStorage保存并管理UITextView要展示的文字内容，该类是NSMutableAttributedString的子类，由于可以灵活地往文字添加或修改属性
@property(nonatomic,readonly,strong) NSTextStorage *textStorage NS_AVAILABLE_IOS(7_0);

//链接的样式
@property(null_resettable, nonatomic, copy) NSDictionary<NSString *, id> *linkTextAttributes NS_AVAILABLE_IOS(7_0);

@end

#if TARGET_OS_IOS

@interface UITextView () <UITextDraggable, UITextDroppable, UITextPasteConfigurationSupporting>
@end

#endif
//通知在相应代理之后执行
UIKIT_EXTERN NSNotificationName const UITextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidChangeNotification;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidEndEditingNotification;

NS_ASSUME_NONNULL_END
