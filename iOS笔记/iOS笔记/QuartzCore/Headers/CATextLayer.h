/* CoreAnimation - CATextLayer.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

/*
 文本层提供简单的文本布局以及普通或属性字符串的呈现。 第一行与图层顶部对齐。
 
 注：以Retina方式来渲染，防止画出来的文本模糊self.contentsScale = [UIScreen mainScreen].scale;
 */

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CATextLayer : CALayer
{
@private
  struct CATextLayerPrivate *_state;
}



/* 要呈现的文本应该是NSString或NSAttributedString。 默认为nil. */
@property(nullable, copy) id string;

/*
 要使用的字体当前可以是CTFontRef，CGFontRef或命名字体的字符串。 默认为Helvetica字体。
 仅在`string'属性不是NSAttributedString时使用。*/
@property(nullable) CFTypeRef font;

/* 字体大小。 默认为36.仅在`string'属性不是NSAttributedString时使用。 支持动画（Mac OS X 10.6及更高版本。） */
@property CGFloat fontSize;

/*
 文本颜色。 默认为opaque white。
 仅在`string'属性不是NSAttributedString时使用。 支持动画（Mac OS X 10.6及更高版本。） */
@property(nullable) CGColorRef foregroundColor;

/* 如果为true，则将字符串包装以适合图层边界(换行)。 默认为NO。*/
@property(getter=isWrapped) BOOL wrapped;

/* 描述如何截断字符串以适合图层边界。  可能的选项是`none', `start', `middle' and `end'.  默认为“none”。*/
@property(copy) NSString *truncationMode;

/*
 描述各个文本行如何在图层边界内对齐。 可能的选择是`natural', `left', `right',`center' and `justified（对齐）'.。
 默认为“natural”。
 */
@property(copy) NSString *alignmentMode;

/*
 设置允许传递给-drawInContext：方法的CGContextRef的allowFontSubpixelQuantization参数。 默认为NO。
 */
@property BOOL allowsFontSubpixelQuantization;

@end

/* truncationMode截断模式 . */

CA_EXTERN NSString * const kCATruncationNone
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCATruncationStart
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCATruncationEnd
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCATruncationMiddle
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);

/* alignmentMode对齐模式 */

CA_EXTERN NSString * const kCAAlignmentNatural
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCAAlignmentLeft
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCAAlignmentRight
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCAAlignmentCenter
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);
CA_EXTERN NSString * const kCAAlignmentJustified
    CA_AVAILABLE_STARTING (10.5, 3.2, 9.0, 2.0);

NS_ASSUME_NONNULL_END
