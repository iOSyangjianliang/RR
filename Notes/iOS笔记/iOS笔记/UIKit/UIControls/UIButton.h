//
//  UIButton.h
//  UIKit
//
//  Copyright (c) 2005-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIFont, UIColor, UIImageView, UILabel;

typedef NS_ENUM(NSInteger, UIButtonType) {
    UIButtonTypeCustom = 0,                         // 自定义风格
    UIButtonTypeSystem NS_ENUM_AVAILABLE_IOS(7_0),  // 选中状态下圆角矩形

    UIButtonTypeDetailDisclosure, // 圈圈 i 样式
    UIButtonTypeInfoLight,        // 圈圈 i 样式
    UIButtonTypeInfoDark,         // 圈圈 i 样式
    UIButtonTypeContactAdd,       // 圈圈 + 样式
    
    UIButtonTypePlain API_AVAILABLE(tvos(11.0)) __IOS_PROHIBITED __WATCHOS_PROHIBITED, // standard system button without the blurred background view
    
    UIButtonTypeRoundedRect = UIButtonTypeSystem   // Deprecated, use UIButtonTypeSystem instead淘汰，用 UIButtonTypeSystem 替代
    
};

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIButton : UIControl <NSCoding>
//按照某种风格按钮初始化
//对于注册页面定时器还有多少s可以点击，这个按秒的倒计时，System模式会有一闪一闪的隐式动画。
+ (instancetype)buttonWithType:(UIButtonType)buttonType;
// 内容的内边距
//设置按钮内容在button上的位置（上top，左left，下bottom，右right）这里可以写负值，对上写－5，那么内容就向上移动5个像素
@property(nonatomic)          UIEdgeInsets contentEdgeInsets UI_APPEARANCE_SELECTOR; //默认是UIEdgeInsetsZero。 在tvOS 10或更高版本上，除自定义按钮外，默认值不为零。
// 标题的内边距
@property(nonatomic)          UIEdgeInsets titleEdgeInsets;                // default is UIEdgeInsetsZero
@property(nonatomic)          BOOL         reversesTitleShadowWhenHighlighted; // default is NO. if YES, shadow reverses to shift between engrave and emboss appearance默认 NO. 高亮时，阴影反转
// 图片的内边距
@property(nonatomic)          UIEdgeInsets imageEdgeInsets;                // default is UIEdgeInsetsZero
@property(nonatomic)          BOOL         adjustsImageWhenHighlighted;    // 默认是YES。 高亮时，则突出显示（按下）时图像变暗
@property(nonatomic)          BOOL         adjustsImageWhenDisabled;       // 默认是YES。 如果enabled=NO，则图像变暗
@property(nonatomic)          BOOL         showsTouchWhenHighlighted __TVOS_PROHIBITED;      // 默认为NO。 YES时，则突出显示一个简单的反馈（发光高亮）
@property(null_resettable, nonatomic,strong)   UIColor     *tintColor NS_AVAILABLE_IOS(5_0); // The tintColor is inherited through the superview hierarchy. See UIView for more information.tintColor通过超级视图层次继承。 有关更多信息，请参阅UIView。
@property(nonatomic,readonly) UIButtonType buttonType;//按钮类型，只读

// you can set the image, title color, title shadow color, and background image to use for each state. you can specify data
// for a combined state by using the flags added together. in general, you should specify a value for the normal state to be used
// by other states which don't have a custom value set
//您可以设置图像，标题颜色，标题阴影颜色和背景图像以用于每个状态。 你可以指定数据
//通过使用添加在一起的标志来组合状态。 一般来说，你应该为正常状态指定一个值来使用
//由没有自定义值设置的其他状态

//默认为nil。 标题被假定为单行
- (void)setTitle:(nullable NSString *)title forState:(UIControlState)state;                     // default is nil. title is assumed to be single line
//默认为nil。 使用不透明的白色
- (void)setTitleColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default if nil. use opaque white
//默认为nil。 使用50％黑色
- (void)setTitleShadowColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use 50% black
//默认为nil。 设置不同状态图片，但应该是相同的图片大小
- (void)setImage:(nullable UIImage *)image forState:(UIControlState)state;                      // default is nil. should be same size if different for different states
//默认为nil。 设置按钮背景图
- (void)setBackgroundImage:(nullable UIImage *)image forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil
//默认是nil。标题被假定为单行。设置按钮富文本样式
- (void)setAttributedTitle:(nullable NSAttributedString *)title forState:(UIControlState)state NS_AVAILABLE_IOS(6_0); // default is nil. title is assumed to be single line

#pragma mark 获取某个状态下对应属性值
- (nullable NSString *)titleForState:(UIControlState)state;
- (nullable UIColor *)titleColorForState:(UIControlState)state;
- (nullable UIColor *)titleShadowColorForState:(UIControlState)state;
- (nullable UIImage *)imageForState:(UIControlState)state;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state;
- (nullable NSAttributedString *)attributedTitleForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

// these are the values that will be used for the current state. you can also use these for overrides. a heuristic will be used to
// determine what image to choose based on the explict states set. For example, the 'normal' state value will be used for all states
// that don't have their own image defined.
//这些是将用于当前状态的值。 你也可以使用这些覆盖。 启发式将用于
//根据设置的显式状态确定要选择的图像。 例如，“正常”状态值将用于所有状态
//没有定义自己的图像。

//获取当前按钮标题，只读，可能为nil
@property(nullable, nonatomic,readonly,strong) NSString *currentTitle;             // normal/highlighted/selected/disabled. can return nil
//获取当前标题颜色，只读，默认白色
@property(nonatomic,readonly,strong) UIColor  *currentTitleColor;        // normal/highlighted/selected/disabled. always returns non-nil. default is white(1,1)
//获取当前标题阴影颜色，只读
@property(nullable, nonatomic,readonly,strong) UIColor  *currentTitleShadowColor;  // normal/highlighted/selected/disabled.
//获取当前按钮图片，只读，可能为nil
@property(nullable, nonatomic,readonly,strong) UIImage  *currentImage;             // normal/highlighted/selected/disabled. can return nil
//获取当前按钮背景图片，只读，可能为nil
@property(nullable, nonatomic,readonly,strong) UIImage  *currentBackgroundImage;   // normal/highlighted/selected/disabled. can return nil
//获取当前按钮富文本，只读，可能为nil
@property(nullable, nonatomic,readonly,strong) NSAttributedString *currentAttributedTitle NS_AVAILABLE_IOS(6_0);  // normal/highlighted/selected/disabled. can return nil

// return title and image views. will always create them if necessary. always returns nil for system buttons
//返回标题和图片视图。 将在必要时始终创建它们。 系统按钮样式总是返回nil
//可以设置此类属性: button.titleLabel.font = [UIFont systemFontOfSize:16];//title字体大小
//     button.titleLabel.textAlignment = NSTextAlignmentCenter;//设置title的字体居中
//不可以这样设置下属性: button.titleLabel.text = @"设置标题";
//     button.titleLabel.textColor = [UIColor redColor];
@property(nullable, nonatomic,readonly,strong) UILabel     *titleLabel NS_AVAILABLE_IOS(3_0);
@property(nullable, nonatomic,readonly,strong) UIImageView *imageView  NS_AVAILABLE_IOS(3_0);

// these return the rectangle for the background (assumes bounds), the content (image + title) and for the image and title separately. the content rect is calculated based
// on the title and image size and padding and then adjusted based on the control content alignment. there are no draw methods since the contents
// are rendered in separate subviews (UIImageView, UILabel)
//这些返回矩形的背景（假设边界），内容（图像+标题）以及图像和标题分开。 内容rect基于计算
//标题和图像大小以及填充，然后根据控件内容对齐进行调整。 自内容以来没有绘制方法
//呈现在单独的子视图中（UIImageView，UILabel）

#pragma mark 自定义按钮，重写(继承、分类)这些方法调整按钮内部子控件的尺寸
- (CGRect)backgroundRectForBounds:(CGRect)bounds;
- (CGRect)contentRectForBounds:(CGRect)bounds;
- (CGRect)titleRectForContentRect:(CGRect)contentRect;
- (CGRect)imageRectForContentRect:(CGRect)contentRect;
@end

//3.0开始废弃了
@interface UIButton(UIButtonDeprecated)

@property(nonatomic,strong) UIFont         *font              NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
@property(nonatomic)        NSLineBreakMode lineBreakMode     NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
@property(nonatomic)        CGSize          titleShadowOffset NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

@end

#if TARGET_OS_IOS
@interface UIButton (SpringLoading) <UISpringLoadedInteractionSupporting>
@end
#endif

NS_ASSUME_NONNULL_END
