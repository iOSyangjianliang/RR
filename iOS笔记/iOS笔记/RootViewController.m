//
//  RootViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import "RootViewController.h"

@interface RootViewController ()
@property (weak, nonatomic) IBOutlet UITextView *mainTextView;

@end

@implementation RootViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];

    NSString *path = [[NSBundle mainBundle] pathForResource:@"QuartzCore/Headers/CALayer.h" ofType:nil];
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:path];
    NSData *data = [fileHandle readDataToEndOfFile];
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    self.mainTextView.text = str;
    self.mainTextView.textColor = [UIColor redColor];
  
    NSFileManager* fm = [NSFileManager defaultManager];
    
    NSError* error = nil;
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"QuartzCore/Headers" ofType:nil];
    NSArray* array =  [fm contentsOfDirectoryAtPath:filePath error:&error];//浅度遍历文件夹
    NSArray* array1 =[fm subpathsOfDirectoryAtPath:[[NSBundle mainBundle] pathForResource:@"QuartzCore" ofType:nil] error:&error];
    if (error) {    //遍历文件失败
        NSLog(@"未找到－－%@",error);
    }
    NSLog(@"%@==%@",array,array1);
    
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
