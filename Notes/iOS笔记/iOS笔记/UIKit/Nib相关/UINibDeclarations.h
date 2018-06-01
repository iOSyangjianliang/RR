//
//  UINibDeclarations.h
//  UIKit
//
//  Copyright (c) 2005-2017 Apple Inc. All rights reserved.
//


//IBOutlet对于编译器而言只是一个标记，也就是说，编译器会忽略这个关键字。
//需要注意的是，任何一个被声明为IBOutlet并且在Interface Builder里被连接到一个UI组件的成员变量，会被额外retain一次。????
//IBoutlet修饰的字段可以和InterfaceBuilder里相应"UI控件"相关联；
#ifndef IBOutlet
#define IBOutlet
#endif

//IBOutletCollection集合中对象的顺序是不确定的。我们通过调试方法可以看到集合中对象的顺序跟我们连接的顺序是一样的。但是这个顺序可能会因为不同版本的Xcode而有所不同。所以我们不应该试图在代码中去假定这种顺序。
//不管IBOutletCollection(ClassName)中的控件是什么，属性的类型始终是NSArray。实际上，我们可以声明是任何类型，如NSSet， NSMutableArray，甚至可以是UIColor，但不管我们在此设置的是什么类，IBOutletCollection属性总是指向一个NSArray数组。
//eg:
//@property (strong, nonatomic) IBOutletCollection(UIScrollView) NSArray *scrollViews可以拖n个控件连接加入数组;
#ifndef IBOutletCollection
#define IBOutletCollection(ClassName)
#endif


//IBaction修饰的方法可以和InterfaceBuilder里控件的"相应动作"相关联。
#ifndef IBAction
#define IBAction void
#endif


//使用IBInspectable可以将自定义属性添加到xib的属性面板上直接设置，直接直观实时展示
//eg：
//@property (nonatomic) IBInspectable CGFloat cornerRadius;
//-(void)setCornerRadius:(CGFloat)cornerRadius{
//    _cornerRadius = cornerRadius;
//    self.layer.cornerRadius = cornerRadius;
//    self.layer.masksToBounds = cornerRadius > 0?true:false;
//}
#ifndef IBInspectable
#define IBInspectable
#endif

//在.h文件#import 后面加入 IB_DESIGNABLE 可实时预览效果哦
//eg：
//#import <Foundation/Foundation.h>
//IB_DESIGNABLE
//@interface IBDesigbableImageview : UIImageView
#ifndef IB_DESIGNABLE
#define IB_DESIGNABLE
#endif

