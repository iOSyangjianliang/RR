//
//  RootViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import "RootViewController.h"

@interface RootViewController ()

@end

@implementation RootViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];

    UIView * viwq =[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 100)];
    [self.view addSubview:viwq];

//    NSIndexPath *h =[NSIndexPath indexPathForItem:1 inSection:1]
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
