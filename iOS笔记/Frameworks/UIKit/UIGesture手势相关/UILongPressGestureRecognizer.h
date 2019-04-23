//
//  UILongPressGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIGestureRecognizer.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

// Begins:  when numberOfTouchesRequired have tapped numberOfTapsRequired times and been held for minumPressDuration
// Changes: when a finger moves
// Ends:    when a finger is lifted

NS_CLASS_AVAILABLE_IOS(3_2) @interface UILongPressGestureRecognizer : UIGestureRecognizer

//默认值为0 按下确认手势前需要的全部轻击次数
@property (nonatomic) NSUInteger numberOfTapsRequired;
//默认值为1 要识别手势必须按住的手指数
@property (nonatomic) NSUInteger numberOfTouchesRequired __TVOS_PROHIBITED;

//默认值为0.5。 必须按住手指才能识别手势的时间（以秒为单位）
@property (nonatomic) CFTimeInterval minimumPressDuration;

//默认值为10.手势失败前允许的最大像素移动量。 一旦识别（在minimumPressDuration之后），对于触摸跟踪的剩余部分，手指移动没有限制
@property (nonatomic) CGFloat allowableMovement;          

@end

NS_ASSUME_NONNULL_END
