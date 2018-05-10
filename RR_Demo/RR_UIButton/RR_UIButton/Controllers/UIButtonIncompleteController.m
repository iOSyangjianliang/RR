//
//  UIButtonIncompleteController.m
//  RR_UIButton
//
//  Created by 杨建亮 on 2018/3/8.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "UIButtonIncompleteController.h"

#import "BBShapedButton.h"
#import "BBIrregularImageButton.h"

@interface UIButtonIncompleteController ()

@end

@implementation UIButtonIncompleteController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];    
    
    //XX按钮
    BBIrregularImageButton *imageBtn = [[BBIrregularImageButton alloc] initWithFrame:CGRectMake(50,300, 100, 100)];
    imageBtn.backgroundColor=[UIColor clearColor];
    [imageBtn setImage:[UIImage imageNamed:@"button-normal"] forState:UIControlStateNormal];
    [self.view addSubview:imageBtn];
    
    
    
    BBShapedButton *btn = [BBShapedButton buttonWithType:UIButtonTypeCustom];
    btn.frame = CGRectMake(50, 150, 200, 100);
    
    UIBezierPath *path = [UIBezierPath bezierPath];
    [path moveToPoint:CGPointMake(0, 100)];
    [path addLineToPoint:CGPointMake(20, 0)];
    [path addLineToPoint:CGPointMake(45, 50)];
    [path addLineToPoint:CGPointMake(70, 0)];
    [path addLineToPoint:CGPointMake(150, 30)];
    [path addLineToPoint:CGPointMake(175, 0)];
    [path addLineToPoint:CGPointMake(200, 100)];
    [path closePath];
    btn.path = path;
    
    [btn setTitle:@"按钮" forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(btnAction:) forControlEvents:UIControlEventTouchUpInside];
    btn.backgroundColor = [UIColor greenColor];
    [self.view addSubview:btn];
    
    
    
    
}
- (void)btnAction:(UIButton *)sender
{
    sender.backgroundColor = [UIColor colorWithRed:(arc4random() % 255 + 1) / 255.0
                                             green:(arc4random() % 255 + 1) / 255.0
                                              blue:(arc4random() % 255 + 1) / 255.0
                                             alpha:1.0];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
    
    
}


@end

