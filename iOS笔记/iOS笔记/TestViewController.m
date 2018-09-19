//
//  TestViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/15.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import "TestViewController.h"

@interface TestViewController ()
@property (strong, nonatomic)  UIWebView *webView;
@property (strong, nonatomic)  UIButton *Selectbutton;
@property (strong, nonatomic)  UITextView *textView;
@end

@implementation TestViewController

- (void)viewDidLoad {
    [super viewDidLoad];
//    [self.Selectbutton setTitle:@"API-UIView" forState:UIControlStateNormal];
    //    self.webView.scalesPageToFit = YES;
    // 以只读方式打开文件
    NSString *path = [[NSBundle mainBundle] pathForResource:@"UIView" ofType:@"h"];
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:path];
    NSData *data = [fileHandle readDataToEndOfFile];
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    
    
    
    // 处理字符串
    NSMutableAttributedString *attributedString = [[NSMutableAttributedString alloc] initWithString:str];
    
    
    NSUInteger len = [str length];
    NSMutableArray* arrayLoc = [NSMutableArray array];
    NSMutableArray* arrayLen = [NSMutableArray array];
    
    NSUInteger pStart  ;
    NSUInteger pNext  ;
    
    for (int i=0; i<len-1; ++i) {
        pStart = i;
        pNext = pStart+1;
        
        unichar cStart = [str characterAtIndex:pStart];
        unichar cNext = [str characterAtIndex:pNext];
        NSString* CStart= [NSString stringWithFormat:@"%c",cStart];
        NSString* CNext = [NSString stringWithFormat:@"%c",cNext];
        
        if ([CStart isEqualToString:@"/"]&& [CNext isEqualToString:@"/"]) {
            NSRange rangeS =NSMakeRange(0, 1);
            
            
            [arrayLoc addObject:[NSString stringWithFormat:@"%d",i]];
        }
        NSLog(@"%c-%@",cStart,CNext);
        
        
        if ([CStart isEqualToString:@"\n"]) {
            
        }
    }
    
    NSRange rangeS =NSMakeRange(0, 1);
    
    NSRange range = [str rangeOfString:@"杨建亮"];
    [attributedString addAttribute:NSForegroundColorAttributeName value:[UIColor redColor] range:range];
    self.textView.attributedText = attributedString;
    
    
    
    
    [self loadRequestLocalText:str];
    
    
    //    [self loadRequestFileResource:@"UIIView" ofType:@"txt" MIMEType:@"txt"];
    
}

//加载本地txt文件的text文本
- (void)loadRequestLocalText:(NSString *)content
{
    // 判断是否可以无损转化编码
    if ([content canBeConvertedToEncoding:NSUTF8StringEncoding])
    {
        NSData *data = [content dataUsingEncoding:NSUTF8StringEncoding];
        NSURL *url = [NSURL fileURLWithPath: [[NSBundle mainBundle]  bundlePath]];
        
        [self.webView loadData:data MIMEType:@"text/plain" textEncodingName:@"UTF-8" baseURL:url];
    }
}

////加载本地文件资源
//- (void)loadRequestFileResource:(NSString *)name ofType:(nullable NSString *)ext MIMEType:(NSString *)mimeType
//{
//    NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:ext];
//    NSURL *url = [NSURL fileURLWithPath:path];
//    NSData *data = [NSData dataWithContentsOfFile:path];
//    [self.webView loadData:data MIMEType:mimeType textEncodingName:@"UTF-8" baseURL:url];
//
//}


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
