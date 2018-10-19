//
//  FrameworkModel.m
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/17.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "FrameworkModel.h"

@implementation ApiModel
@end

@implementation ApiGroupModel
@end


@implementation FrameworkModel
-(instancetype)initWithPath:(NSString *)path
{
    if (self = [super init]) {
        NSFileManager *fileManager = [NSFileManager defaultManager];
    
        NSError* error = nil;
        NSString *filePath = [[NSBundle mainBundle] pathForResource:path ofType:nil];
        NSArray* array =  [fileManager contentsOfDirectoryAtPath:filePath error:&error];//浅度遍历Frameworks文件夹
        if (error) {
            NSLog(@"未找到%@对应资源－－%@",path,error);
        }else{
            self.frameworks = [NSMutableArray array];
            
            for (int i=0; i<array.count; ++i) {
                
                ApiGroupModel *groupModel = [[ApiGroupModel alloc] init];
                groupModel.frameworkName = array[i];
                NSString *apiGroupPath = [filePath stringByAppendingPathComponent:array[i]];
                NSArray *arrayGroup =  [fileManager contentsOfDirectoryAtPath:apiGroupPath error:nil];//浅度遍历UIKit文件夹
                BOOL isDeveloped = arrayGroup.count == 1?YES:NO;
                
                groupModel.apiGroups = [NSMutableArray array];
                for (int j=0; j<arrayGroup.count; ++j) {
                    ApiModel *model = [[ApiModel alloc] init];
                    model.apiGroupName = arrayGroup[j];
                    model.isDeveloped = isDeveloped;
                    
                    NSString *apiPath = [apiGroupPath stringByAppendingPathComponent:arrayGroup[j]];
                    NSArray *arrayApi =  [fileManager subpathsOfDirectoryAtPath:apiPath error:nil];//深度遍历
                    
                    NSSortDescriptor *descriptor = [NSSortDescriptor sortDescriptorWithKey:nil ascending:YES];
                    NSArray *descriptors = [NSArray arrayWithObject:descriptor];
                    NSArray *sortedArray = [arrayApi sortedArrayUsingDescriptors:descriptors];//排序
                    
                    model.apiNames = [NSMutableArray arrayWithArray:sortedArray];
                   
                    
                    [groupModel.apiGroups addObject:model];
                }
                
                [self.frameworks addObject:groupModel];
            }
//            NSSortDescriptor *descriptor = [NSSortDescriptor sortDescriptorWithKey:nil ascending:YES];
//            NSArray *descriptors = [NSArray arrayWithObject:descriptor];
//            NSArray *sortedArray = [arrayApi sortedArrayUsingDescriptors:descriptors];//排序
        }
    }
    return self;
}
@end
