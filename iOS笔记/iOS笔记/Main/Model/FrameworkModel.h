//
//  FrameworkModel.h
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/17.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ApiModel : NSObject
@property(nonatomic ,strong) NSString *apiGroupName;   //api分组组名称
@property(nonatomic ,strong) NSMutableArray *apiNames; //该组所有api
@property(nonatomic ,assign) BOOL isDeveloped;         //该组是否折叠，
@end

@interface ApiGroupModel : NSObject
@property(nonatomic ,strong) NSString *frameworkName;    //框架名称
@property(nonatomic ,strong) NSMutableArray<ApiModel *> *apiGroups;  //框架所有api分组
@property(nonatomic ,assign) BOOL isDeveloped;           //tableView组是否折叠、默认NO，只有一组时为YES
@end

@interface FrameworkModel : NSObject
-(instancetype)initWithPath:(NSString *)path;
@property(nonatomic ,strong) NSMutableArray<ApiGroupModel *> *frameworks;
@end

NS_ASSUME_NONNULL_END
