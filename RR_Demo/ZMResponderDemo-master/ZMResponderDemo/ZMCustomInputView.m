//
//  ZMCustomInputView.m
//  ZMResponderDemo
//
//  Created by ZengZhiming on 2017/5/18.
//  Copyright © 2017年 菜鸟基地. All rights reserved.
//

#import "ZMCustomInputView.h"

#define MAIN_SCREEN_WIDTH [[UIScreen mainScreen] bounds].size.width   //!< 屏幕的Width

@interface ZMCustomInputView ()

@property (nonatomic, strong) UITextField *textField;
@property (nonatomic, strong) UIView *customInputView;
@property (nonatomic, strong) UIToolbar *customAccessoryView;

@end

@implementation ZMCustomInputView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // 添加TextField
        [self addSubview:self.textField];
    }
    return self;
}

/** 懒加载textField */
- (UITextField *)textField {
    if (!_textField) {
        // 初始化textField
        _textField = [[UITextField alloc]initWithFrame:CGRectMake(50, 100, MAIN_SCREEN_WIDTH - 100, 30)];
        _textField.borderStyle = UITextBorderStyleRoundedRect;
        _textField.placeholder = @"测试";
        // 设置自定义键盘View
        _textField.inputView = self.customInputView;
        _textField.inputAccessoryView = self.customAccessoryView;

//        _textField.secureTextEntry = YES;

        _textField.autocorrectionType = UITextAutocorrectionTypeNo;

//UISegmentedControl
    }

    return _textField;
}

/** 懒加载customInputView */
- (UIView *)customInputView {
    if (!_customInputView) {
        _customInputView = [[UIView alloc]initWithFrame:CGRectMake(30, 20, MAIN_SCREEN_WIDTH, 220)];
        _customInputView.backgroundColor = [UIColor lightGrayColor];
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(0, 100, MAIN_SCREEN_WIDTH, 40)];
        label.textAlignment = NSTextAlignmentCenter;
        label.text = @"自定义inputView";
        [_customInputView addSubview:label];
    }
    return _customInputView;
}

/** 懒加载customAccessoryView */
- (UIToolbar *)customAccessoryView {
    if (!_customAccessoryView) {
        _customAccessoryView = [[UIToolbar alloc]initWithFrame:CGRectMake(30, 30, MAIN_SCREEN_WIDTH, 40)];
        _customAccessoryView.barTintColor = [UIColor orangeColor];
        UIBarButtonItem *space = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
        UIBarButtonItem *done = [[UIBarButtonItem alloc]initWithTitle:@"完成" style:UIBarButtonItemStyleDone target:self action:@selector(done)];
        [_customAccessoryView setItems:@[space, space, done]];
    }
    return _customAccessoryView;
}

/** 响应完成按钮 */
- (void)done {
    
    UIWindow *W = [UIApplication sharedApplication].delegate.window;
    UIViewController *Vc = [W rootViewController];
    
    NSArray *arr = [UIApplication sharedApplication].windows;
    UIWindow *ww= [UIApplication sharedApplication].keyWindow;
    
    [self.textField resignFirstResponder];
    
    if (_textField.inputView) {
        _textField.inputView = nil;
    }else
    {
        _textField.inputView = self.customInputView;
    }
    
    [_textField reloadInputViews];
    
}


@end
