//
//  APresentViewController.m
//  RR_UIViewController
//
//  Created by 杨建亮 on 2018/3/13.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "APresentViewController.h"

@interface APresentViewController ()

@end

@implementation APresentViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor purpleColor];

    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(0, 100, 100, 100)];
    btn.backgroundColor = [UIColor redColor];
    [btn addTarget:self action:@selector(backDissmiss) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
    
}
-(void)backDissmiss
{
    [self dismissViewControllerAnimated:YES completion:nil];
}
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UIViewController *VC = (UIViewController *)[[NSClassFromString(@"BPresentViewController") alloc] init];
    
    VC.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;//转场动画
    VC.modalPresentationStyle = UIModalPresentationOverCurrentContext;

    
    [self presentViewController:VC animated:YES completion:nil];
    
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
