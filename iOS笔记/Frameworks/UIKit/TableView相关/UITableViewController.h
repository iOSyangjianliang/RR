//
//  UITableViewController.h
//  UIKit
//
//  Copyright (c) 2008-2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UITableView.h>
#import <UIKit/UIKitDefines.h>

// Creates a table view with the correct dimensions and autoresizing, setting the datasource and delegate to self.
// In -viewWillAppear:, it reloads the table's data if it's empty. Otherwise, it deselects all rows (with or without animation) if clearsSelectionOnViewWillAppear is YES.
// In -viewDidAppear:, it flashes the table's scroll indicators.
// Implements -setEditing:animated: to toggle the editing state of the table.

//创建具有正确尺寸的表视图并自动调整大小，将数据源和委托设置为self。
//在-viewWillAppear：中，它重新加载表的数据，如果它是空的。 否则，如果clearsSelectionOnViewWillAppear为YES，则取消选择所有行（带或不带动画）。
//在-viewDidAppear：中，它会闪烁表格的滚动指示符。
// Implements -setEditing：animated：切换表的编辑状态。

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource>

- (instancetype)initWithStyle:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong, null_resettable) UITableView *tableView;
//默认为YES。 如果是，则在viewWillAppear中清除任何选中
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear NS_AVAILABLE_IOS(3_2);

//系统的刷新控件
@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
