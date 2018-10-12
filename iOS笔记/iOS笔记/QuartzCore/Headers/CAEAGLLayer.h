/* CoreAnimation - CAEAGLLayer.h

   Copyright (c) 2007-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <OpenGLES/EAGLDrawable.h>

NS_ASSUME_NONNULL_BEGIN

/*
 CAEAGLLayer是一个实现EAGLDrawable协议的层，允许它用作OpenGLES渲染目标。
 使用协议定义的`drawableProperties'属性来配置创建的表面。
 */

CA_CLASS_AVAILABLE_IOS(2.0, 9.0, 2.0)
@interface CAEAGLLayer : CALayer <EAGLDrawable>
{
@private
  struct _CAEAGLNativeWindow *_win;
}

/* 
 当false（默认值）更改为图层的渲染缓冲区时，屏幕上会异步显示正常的图层更新。
 如果为true，则通过标准CATransaction机制将对GLES内容的更改发送到屏幕。
 */

@property BOOL presentsWithTransaction CA_AVAILABLE_IOS_STARTING (9.0, 9.0, 2.0);

/*
 注意：此类中“opaque”属性的默认值为true，而不是CALayer中的false。
 */

@end

NS_ASSUME_NONNULL_END
