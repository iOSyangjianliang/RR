//
//  ButtonBasicUseController.m
//  RR_UIButton
//
//  Created by 杨建亮 on 2018/3/8.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "ButtonBasicUseController.h"
#import "UIRRButton.h"
@interface ButtonBasicUseController ()

@end

@implementation ButtonBasicUseController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor purpleColor];
    
//    [self test_UIButtonType];
//
//    [self test_UIRRButton];
    
    [self test_UIButton_contentEdgeInsets];

}
#pragma mark -

-(void)test_UIRRButton
{
    UIRRButton *button = [[UIRRButton alloc] initWithFrame:CGRectMake(100, 200, 60, 60)];
    [button setImage:[UIImage imageNamed:@"tab_btn1_sel"] forState:UIControlStateNormal];
    
    [button setTitle:@"聊天" forState:UIControlStateNormal];
    button.titleLabel.font = [UIFont systemFontOfSize:12];
    [button setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
    
    // 设置居中
    button.imageView.contentMode = UIViewContentModeCenter;
    button.titleLabel.textAlignment = NSTextAlignmentCenter;
   
    button.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:button];
}
#pragma mark -

-(void)test_UIButtonType
{
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeSystem];
    btn.frame = CGRectMake(100, 100, 40, 40);
    [btn setTitle:@"666" forState:UIControlStateNormal];
    [btn setImage:[UIImage imageNamed:@"tab_btn1_sel"] forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
    
    btn.titleLabel.font = [UIFont systemFontOfSize:16];
    btn.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:btn];
    
    
    UIButton *btn_2 = [UIButton buttonWithType:UIButtonTypeCustom];
    btn_2.frame = CGRectMake(200, 100, 100, 100);
    [btn_2 setTitle:@"聊天" forState:UIControlStateNormal];
    [btn_2 setImage:[UIImage imageNamed:@"tab_btn1_sel"] forState:UIControlStateNormal];
    [btn_2 addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
    
    btn_2.titleLabel.font = [UIFont systemFontOfSize:12];
    
    //UIControl特性
//    btn_2.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;
//    btn_2.contentVerticalAlignment =  UIControlContentVerticalAlignmentBottom;
    
    btn_2.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:btn_2];
    
    
    UIButton *btn_3 = [[UIButton alloc] initWithFrame:CGRectMake(250, 00, 100, 40)];
//    [btn_3 setTitle:@"设置title" forState:UIControlStateNormal];
    
    //这样是设置无效的，必须使用上面有状态参数的方法
    btn_3.titleLabel.text = @"fdsfds";
    btn_3.titleLabel.textColor = [UIColor redColor];
    
    //但这些属性设置是可以的
    btn_3.titleLabel.textAlignment = NSTextAlignmentRight;
    btn_3.titleLabel.font = [UIFont systemFontOfSize:18];

    btn_3.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:btn_3];
}
-(void)click:(UIButton *)sender
{
    sender.selected = !sender.selected;
}
#pragma mark -
-(void)test_UIButton_contentEdgeInsets
{
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(100, 200, 160, 100)];
    [btn setBackgroundImage:[UIImage imageNamed:@"tab_btn1_sel"] forState:UIControlStateNormal];
    [btn setImage:[UIImage imageNamed:@"pic-jingzhenyujin"] forState:UIControlStateNormal];
    [btn setTitle:@"设置" forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    btn.backgroundColor = [UIColor redColor];
//    btn.contentEdgeInsets = UIEdgeInsetsMake(40, 40,40, 40);
    btn.contentEdgeInsets = UIEdgeInsetsMake(8, 18,8, 18);
    btn.imageView.backgroundColor = [UIColor blueColor];
    [self.view addSubview:btn];

    UIButton *btn_2 = [[UIButton alloc] initWithFrame:CGRectMake(100, 310, 160, 100)];
    [btn_2 setBackgroundImage:[UIImage imageNamed:@"tab_btn1_sel"] forState:UIControlStateNormal];
    [btn_2 setImage:[UIImage imageNamed:@"pic-jingzhenyujin"] forState:UIControlStateNormal];
    [btn_2 setTitle:@"设置" forState:UIControlStateNormal];
    [btn_2 setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    btn_2.backgroundColor = [UIColor redColor];
    btn_2.imageView.backgroundColor = [UIColor blueColor];
    [self.view addSubview:btn_2];
    
    UIButton *btn_3 = [[UIButton alloc] initWithFrame:CGRectMake(100, 420, 160, 100)];
    [btn_3 setBackgroundImage:[UIImage imageNamed:@"tab_btn1_sel"] forState:UIControlStateNormal];
    [btn_3 setImage:[UIImage imageNamed:@"pic-jingzhenyujin"] forState:UIControlStateNormal];
    [btn_3 setTitle:@"设置" forState:UIControlStateNormal];
    [btn_3 setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    btn_3.backgroundColor = [UIColor redColor];
    btn_3.imageView.backgroundColor = [UIColor blueColor];
    
    btn_3.contentHorizontalAlignment = UIControlContentHorizontalAlignmentRight; //水平居右
    btn_3.contentVerticalAlignment = UIControlContentVerticalAlignmentBottom; //垂直居底
    [self.view addSubview:btn_3];
}

//@property(nonatomic)          UIEdgeInsets contentEdgeInsets UI_APPEARANCE_SELECTOR; // default is UIEdgeInsetsZero. On tvOS 10 or later, default is nonzero except for custom buttons.
//@property(nonatomic)          UIEdgeInsets titleEdgeInsets;                // default is UIEdgeInsetsZero
//@property(nonatomic)          BOOL         reversesTitleShadowWhenHighlighted; // default is NO. if YES, shadow reverses to shift between engrave and emboss appearance
//@property(nonatomic)          UIEdgeInsets imageEdgeInsets;

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
