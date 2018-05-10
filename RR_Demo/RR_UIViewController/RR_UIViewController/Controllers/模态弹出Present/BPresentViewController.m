//
//  BPresentViewController.m
//  RR_UIViewController
//
//  Created by 杨建亮 on 2018/3/13.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "BPresentViewController.h"

@interface BPresentViewController ()

@end

@implementation BPresentViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
//    self.view.backgroundColor = [UIColor yellowColor];
//        self.view.alpha = 0.35;
}

- (void)viewWillLayoutSubviews
{
    
    [super viewWillLayoutSubviews];
    self.view.frame = CGRectMake(([UIScreen mainScreen].bounds.size.width-250.0)/2.0,[UIScreen mainScreen].bounds.size.height-400, 250, 300);
    self.view.backgroundColor = [UIColor colorWithRed:1 green:0 blue:0 alpha:0.868f];
}
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
