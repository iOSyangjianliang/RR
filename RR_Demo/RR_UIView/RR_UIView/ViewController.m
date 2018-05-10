//
//  ViewController.m
//  RR_UIView
//
//  Created by 杨建亮 on 2018/4/19.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    [self testView];

}
-(void)testView
{
    UIView *window = [UIApplication sharedApplication].delegate.window;
    
    
    UIView *backView = [[UIView alloc] initWithFrame:CGRectMake(100, 100, 100, 100)];
    backView.backgroundColor = [UIColor blackColor];
    [self.view addSubview:backView];
    
    UIView *redView = [[UIView alloc] initWithFrame:CGRectMake(0, 20, 40, 40)];
    redView.backgroundColor = [UIColor redColor];
    [backView addSubview:redView];
    
    UIView *blueView = [[UIView alloc] initWithFrame:CGRectMake(0, 10, 10, 10)];
    blueView.backgroundColor = [UIColor blackColor];
    [redView addSubview:blueView];
    
    //Point
    //[sender.superview convertPoint:sender.center toView:[UIApplication sharedApplication].delegate.window];
    //view= nil时，则转换的toView坐标系就是默认它的父视图
    //eg: CGPoint P2 = [A convertPoint:P1 toView:B];
    //A:被转坐标系的视图
    //B:要转到的指定视图
    //P1:A上的点坐标
    //P2:转到B上后的点坐标
    CGPoint point1 = [redView.superview convertPoint:redView.frame.origin toView:nil];
    NSLog(@"%@",NSStringFromCGPoint(point1));
    CGPoint point2 = [redView.superview convertPoint:redView.frame.origin toView:window];
    NSLog(@"%@",NSStringFromCGPoint(point2));
    
    CGPoint point3 = [blueView.superview convertPoint:blueView.frame.origin toView:window];
    NSLog(@"%@",NSStringFromCGPoint(point3));
    CGPoint point4 = [self.view convertPoint:blueView.frame.origin toView:window];
    NSLog(@">>>%@",NSStringFromCGPoint(point4));
    
    //eg: CGPoint P2 = [A convertPoint:P1 fromView:B]; //和上相反
    //B:被转坐标系的视图
    //A:要转到的指定视图
    //P1:B上的点坐标
    //P2:转到A上后的点坐标
    CGPoint point5 = [redView convertPoint:blueView.frame.origin fromView:nil];
    NSLog(@"%@",NSStringFromCGPoint(point5));
    CGPoint point6 = [redView convertPoint:blueView.frame.origin fromView:blueView.superview];
    NSLog(@"%@",NSStringFromCGPoint(point6));
    CGPoint point7 = [window convertPoint:CGPointMake(30, 30) fromView:backView];
    NSLog(@"%@",NSStringFromCGPoint(point7));
    
    NSLog(@"==================");
    //Frame 同理
    CGRect frame1 = [redView.superview convertRect:redView.frame toView:nil];
    NSLog(@"%@",NSStringFromCGRect(frame1));
    CGRect frame2 = [redView.superview convertRect:redView.frame toView:window];
    NSLog(@"%@",NSStringFromCGRect(frame2));
    
    
    
    //    // 转换视图间坐标
    //    //eg: [sender.superview convertPoint:sender.center toView:[UIApplication sharedApplication].delegate.window];
    //    // 转换一个点从接受对象的坐标系到指定视图
    //    - (CGPoint)convertPoint:(CGPoint)point toView:(nullable UIView *)view;
    //    // 与上面相反，指定视图坐标中的一个点转换为接收对象
    //    - (CGPoint)convertPoint:(CGPoint)point fromView:(nullable UIView *)view;
    //    // 将当前的矩形坐标空间转换到指定的矩形坐标空间
    //    - (CGRect)convertRect:(CGRect)rect toView:(nullable UIView *)view;
    //    // 将指定的矩形坐标空间转换到当前的矩形坐标空间
    //    - (CGRect)convertRect:(CGRect)rect fromView:(nullable UIView *)view;
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
