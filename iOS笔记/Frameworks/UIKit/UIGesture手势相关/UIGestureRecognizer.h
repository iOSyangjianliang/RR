//
//  UIGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIGestureRecognizerDelegate;
@class UIView, UIEvent, UITouch, UIPress;

typedef NS_ENUM(NSInteger, UIGestureRecognizerState) {
    UIGestureRecognizerStatePossible,   // the recognizer has not yet recognized its gesture, but may be evaluating touch events. this is the default state
    
    UIGestureRecognizerStateBegan,      // the recognizer has received touches recognized as the gesture. the action method will be called at the next turn of the run loop
    UIGestureRecognizerStateChanged,    // the recognizer has received touches recognized as a change to the gesture. the action method will be called at the next turn of the run loop
    UIGestureRecognizerStateEnded,      // the recognizer has received touches recognized as the end of the gesture. the action method will be called at the next turn of the run loop and the recognizer will be reset to UIGestureRecognizerStatePossible
    UIGestureRecognizerStateCancelled,  // the recognizer has received touches resulting in the cancellation of the gesture. the action method will be called at the next turn of the run loop. the recognizer will be reset to UIGestureRecognizerStatePossible
    
    UIGestureRecognizerStateFailed,     // the recognizer has received a touch sequence that can not be recognized as the gesture. the action method will not be called and the recognizer will be reset to UIGestureRecognizerStatePossible
    
    // Discrete Gestures – gesture recognizers that recognize a discrete event but do not report changes (for example, a tap) do not transition through the Began and Changed states and can not fail or be cancelled
    UIGestureRecognizerStateRecognized = UIGestureRecognizerStateEnded // the recognizer has received touches recognized as the gesture. the action method will be called at the next turn of the run loop and the recognizer will be reset to UIGestureRecognizerStatePossible
};

NS_CLASS_AVAILABLE_IOS(3_2) @interface UIGestureRecognizer : NSObject

// Valid action method signatures:
//     -(void)handleGesture;
//     -(void)handleGesture:(UIGestureRecognizer*)gestureRecognizer;
- (instancetype)initWithTarget:(nullable id)target action:(nullable SEL)action NS_DESIGNATED_INITIALIZER; // designated initializer

- (void)addTarget:(id)target action:(SEL)action;    // add a target/action pair. you can call this multiple times to specify multiple target/actions
- (void)removeTarget:(nullable id)target action:(nullable SEL)action; // remove the specified target/action pair. passing nil for target matches all targets, and the same for actions

@property(nonatomic,readonly) UIGestureRecognizerState state;  // the current state of the gesture recognizer

@property(nullable,nonatomic,weak) id <UIGestureRecognizerDelegate> delegate; // the gesture recognizer's delegate

@property(nonatomic, getter=isEnabled) BOOL enabled;  // default is YES. disabled gesture recognizers will not receive touches. when changed to NO the gesture recognizer will be cancelled if it's currently recognizing a gesture

// a UIGestureRecognizer receives touches hit-tested to its view and any of that view's subviews
@property(nullable, nonatomic,readonly) UIView *view;           // the view the gesture is attached to. set by adding the recognizer to a UIView using the addGestureRecognizer: method

// 识别到手势后是否发送取消触摸消息给子视图,默认为Yes检测到手势后想取消子视图的响应
@property(nonatomic) BOOL cancelsTouchesInView;       // default is YES. causes touchesCancelled:withEvent: or pressesCancelled:withEvent: to be sent to the view for all touches or presses recognized as part of this gesture immediately before the action method is called.
// 触摸开始时而没有识别出手势时 是否等待识别失败再向子视图发送事件
@property(nonatomic) BOOL delaysTouchesBegan;         // default is NO.  causes all touch or press events to be delivered to the target view only after this gesture has failed recognition. set to YES to prevent views from processing any touches or presses that may be recognized as part of this gesture
// 正确识别结束后是否发送touchsCancelled消息到子视图
@property(nonatomic) BOOL delaysTouchesEnded;         // default is YES. causes touchesEnded or pressesEnded events to be delivered to the target view only after this gesture has failed recognition. this ensures that a touch or press that is part of the gesture can be cancelled if the gesture is recognized

@property(nonatomic, copy) NSArray<NSNumber *> *allowedTouchTypes NS_AVAILABLE_IOS(9_0); // Array of UITouchTypes as NSNumbers.
@property(nonatomic, copy) NSArray<NSNumber *> *allowedPressTypes NS_AVAILABLE_IOS(9_0); // Array of UIPressTypes as NSNumbers.

// Indicates whether the gesture recognizer will consider touches of different touch types simultaneously.
// If NO, it receives all touches that match its allowedTouchTypes.
// If YES, once it receives a touch of a certain type, it will ignore new touches of other types, until it is reset to UIGestureRecognizerStatePossible.
//表示手势识别器是否会同时考虑不同触摸类型的触摸。
//如果NO，它将接收与它的allowedtouchtype匹配的所有触摸。
//如果YES，一旦它接收到某种类型的触摸，它将忽略其他类型的新触摸，直到它被重置为UIGestureRecognizerStatePossible。
@property (nonatomic) BOOL requiresExclusiveTouchType NS_AVAILABLE_IOS(9_2); // defaults to YES

// create a relationship with another gesture recognizer that will prevent this gesture's actions from being called until otherGestureRecognizer transitions to UIGestureRecognizerStateFailed
// if otherGestureRecognizer transitions to UIGestureRecognizerStateRecognized or UIGestureRecognizerStateBegan then this recognizer will instead transition to UIGestureRecognizerStateFailed
// example usage: a single tap may require a double tap to fail
//与另一个手势识别器创建一个关系，在otherGestureRecognizer转换到uigesturerecognizerstatefered之前，该手势识别器将阻止该手势的动作被调用
//如果其他手势识别器转换到uigesturerecognizer或UIGestureRecognizerStateBegan，那么这个识别器将转换到uigesturerecognizerstatefered
//示例用法:单点可能需要双点才能失败
- (void)requireGestureRecognizerToFail:(UIGestureRecognizer *)otherGestureRecognizer;

// individual UIGestureRecognizer subclasses may provide subclass-specific location information. see individual subclasses for details
//在参数 view 上的触摸位置。如果是多点触摸则输出两点之间的位置
- (CGPoint)locationInView:(nullable UIView*)view;                                // a generic single-point location for the gesture. usually the centroid of the touches involved

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) NSUInteger numberOfTouches;                                          // number of touches involved for which locations can be queried
#else
//返回手势的触摸点数量
- (NSUInteger)numberOfTouches;                                          // number of touches involved for which locations can be queried
#endif

//返回坐标点,第一个参数为tauch数组的索引
- (CGPoint)locationOfTouch:(NSUInteger)touchIndex inView:(nullable UIView*)view; // the location of a particular touch

@property (nullable, nonatomic, copy) NSString *name API_AVAILABLE(ios(11.0), tvos(11.0)); // name for debugging to appear in logging

@end


@protocol UIGestureRecognizerDelegate <NSObject>
@optional

//当手势识别器尝试从UIGestureRecognizerStatePossible转换时调用。返回NO会导致它转换到UIGestureRecognizerStateFailed
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer;

//当识别其中一个gestureRecognizer或otherGestureRecognizer被另一个阻止时调用
//返回YES以允许两者同时识别。 默认实现返回NO（默认情况下，不能同时识别两个手势）

//注意：保证返回YES可以同时识别。 返回NO不能保证阻止同时识别，因为另一个手势的代表可能返回YES
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

// called once per attempt to recognize, so failure requirements can be determined lazily and may be set up between recognizers across view hierarchies
// return YES to set up a dynamic failure requirement between gestureRecognizer and otherGestureRecognizer
//
// note: returning YES is guaranteed to set up the failure requirement. returning NO does not guarantee that there will not be a failure requirement as the other gesture's counterpart delegate or subclass methods may return YES
//每次尝试识别时调用一次，因此可以懒惰地确定失败要求，并且可以跨视图层次结构在识别器之间建立失败要求
//返回YES以在gestureRecognizer和otherGestureRecognizer之间设置动态失败要求
//
//注意：保证返回YES已设置失败要求(调用requireGestureRecognizerToFail:设置)。 返回NO并不保证不存在失败要求，因为其他手势的对应委托或子类方法可能返回YES

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRequireFailureOfGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer NS_AVAILABLE_IOS(7_0);
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldBeRequiredToFailByGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer NS_AVAILABLE_IOS(7_0);


//在touchesBegan：withEvent：之前调用，在手势识别器上调用以获得新的触摸。 返回NO以防止手势识别器看到此触摸
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch;

//在pressBegan：withEvent：之前调用，在手势识别器上调用新的按下。 返回NO以防止手势识别器看到此按下
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceivePress:(UIPress *)press;

@end

NS_ASSUME_NONNULL_END
