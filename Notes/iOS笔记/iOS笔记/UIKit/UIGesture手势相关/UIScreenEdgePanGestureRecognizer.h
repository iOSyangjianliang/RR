//
//  UIScreenEdgePanGestureRecognizer.h
//  Copyright (c) 2012-2017 Apple Inc. All rights reserved.
//

#import <UIKit/UIGeometry.h>
#import <UIKit/UIPanGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

/*! This subclass of UIPanGestureRecognizer only recognizes if the user slides their finger
 in from the bezel on the specified edge.UIPanGestureRecognizer的这个子类只能识别用户是否滑动手指从指定边缘的挡板进入。
 */
NS_CLASS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED @interface UIScreenEdgePanGestureRecognizer : UIPanGestureRecognizer
@property (readwrite, nonatomic, assign) UIRectEdge edges; //< The edges on which this gesture recognizes, relative to the current interface orientation 此手势识别的边缘，相对于当前的界面方向
@end

NS_ASSUME_NONNULL_END
