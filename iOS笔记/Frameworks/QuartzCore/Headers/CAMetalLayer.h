/* CoreAnimation - CAMetalLayer.h

   Copyright (c) 2013-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLDrawable.h>

@protocol MTLDevice;
@protocol MTLTexture;
@protocol MTLDrawable;

@class CAMetalLayer;

NS_ASSUME_NONNULL_BEGIN

/*
 CAMetalLayer 是框架QuartzCore中iOS新增的。是核心动画层使用Metal管理的一个Layer。利用Metal在应用程序的渲染，使用CAMetalLayer作为一个背层由它返回从视图的layerClass类的方法。渲染层的内容，使用nextdrawable方法检索纹理，然后用它作为Metal中的一个渲染目标渲染pipeline。渲染每一帧后，新的内容使用presentdrawable：或presentDrawable:atTime: ：方法显示用来渲染命令缓冲区。
 
 Metal和OpenGL ES相似，它也是一个底层API，负责和3D绘图硬件交互。它们之间的不同在于，Metal不是跨平台的。与之相反的，它设计的在苹果硬件上运行得极其高效，与OpenGL ES相比，它提供了更快的速度和更低的开销。
 
 注意：Metal应用不能跑在iOS模拟器上
 */


/* CAMetalDrawable represents a displayable buffer that vends an object
 * that conforms to the MTLTexture protocol that may be used to create
 * a render target for Metal.
 *
 * Note: CAMetalLayer maintains an internal pool of textures used for
 * display. In order for a texture to be re-used for a new CAMetalDrawable,
 * any prior CAMetalDrawable must have been deallocated and another
 * CAMetalDrawable presented.
 
 CAMetalDrawable表示一个可显示的缓冲区，该缓冲区出现一个符合MTLTexture协议的对象，该协议可用于为Metal创建渲染目标。
 *
 *注意：CAMetalLayer维护用于显示的内部纹理池。 为了将纹理重新用于新的CAMetalDrawable，必须释放任何先前的CAMetalDrawable并呈现另一个CAMetalDrawable。
 */

@protocol CAMetalDrawable <MTLDrawable>

/* This is an object that conforms to the MTLTexture protocol and will
 * typically be used to create an MTLRenderTargetDescriptor.
 
 这是一个符合MTLTexture协议的对象，通常用于创建MTLRenderTargetDescriptor。
 */

@property(readonly) id <MTLTexture> texture;

/* This is the CAMetalLayer responsible for displaying the drawable

 这是CAMetalLayer负责显示drawable
 */
@property(readonly) CAMetalLayer *layer;

@end

/* Note: The default value of the `opaque' property for CAMetalLayer
 * instances is true.
 注意：CAMetalLayer实例的`opaque'属性的默认值为true。
 */

CA_CLASS_AVAILABLE (10.11, 8.0, 9.0, 2.0)
@interface CAMetalLayer : CALayer
{
@private
  struct _CAMetalLayerPrivate *_priv;
}

/* This property determines which MTLDevice the MTLTexture objects for
 * the drawables will be created from.
 * On iOS this defaults to the device returned by MTLCreateSystemDefaultDevice().
 * On MacOS this defaults to nil and must be set explicitly before asking for
 * the first drawable.

 此属性确定将从哪个MTLDevice创建可绘制的MTLTexture对象。
 在iOS上，这默认为MTLCreateSystemDefaultDevice（）返回的设备。 在MacOS上，默认为nil，必须在要求第一个drawable之前明确设置。
 */
@property(nullable, retain) id <MTLDevice> device;

/* This property controls the pixel format of the MTLTexture objects.
 * The two supported values are MTLPixelFormatBGRA8Unorm and
 * MTLPixelFormatBGRA8Unorm_sRGB.
 此属性控制MTLTexture对象的像素格式。支持的两个值是MTLPixelFormatBGRA8Unorm和MTLPixelFormatBGRA8Unorm_sRGB。
 */
@property MTLPixelFormat pixelFormat;

/* This property controls whether or not the returned drawables'
 * MTLTextures may only be used for framebuffer attachments (YES) or
 * whether they may also be used for texture sampling and pixel
 * read/write operations (NO). A value of YES allows CAMetalLayer to
 * allocate the MTLTexture objects in ways that are optimized for display
 * purposes that makes them unsuitable for sampling. The recommended
 * value for most applications is YES.
 
 此属性控制返回的drawables的MTLTextures是否仅可用于帧缓冲附件（YES），或者它们是否也可用于纹理采样和像素读/写操作（NO）。
 值为YES允许CAMetalLayer以为显示目的而优化的方式分配MTLTexture对象，使其不适合采样。 大多数应用程序的建议值为YES。
 */
@property BOOL framebufferOnly;

/* This property controls the pixel dimensions of the returned drawable
 * objects. The most typical value will be the layer size multiplied by
 * the layer contentsScale property.
 此属性控制返回的可绘制对象的像素尺寸。 最典型的值是层大小乘以layer contentsScale属性。
 */
@property CGSize drawableSize;

/* Get the swap queue's next available drawable. Always blocks until a drawable is available.
 * Can return nil under the following conditions:
 *     1) The layer has an invalid combination of drawable properties.
 *     2) All drawables in the swap queue are in-use and the 1 second timeout has elapsed.
 *        (except when `allowsNextDrawableTimeout' is set to NO)
 *     3) Process is out of memory.
 
 获取交换队列的下一个可用drawable。 始终阻塞，直到有可用的绘图。
  *在以下条件下可以返回nil：
  * 1）图层具有无效的可绘制属性组合。
  * 2）交换队列中的所有drawable都在使用中，并且已经过了1秒超时。 （当'allowsNextDrawableTimeout'设置为NO时除外）
  * 3）进程内存不足。
 */
- (nullable id <CAMetalDrawable>)nextDrawable;

/* Controls the number maximum number of drawables in the swap queue. The default value is 3.
 * Values set outside of range [2, 3] are ignored and an exception will be thrown.
 控制交换队列中最大可绘制数量。 默认值为3.
 忽略设置在范围[2,3]之外的值，并抛出异常。
 */
@property NSUInteger maximumDrawableCount CA_AVAILABLE_STARTING (10.13.2, 11.2, 11.2, 4.2);

/* When false (the default value) changes to the layer's render buffer
 * appear on-screen asynchronously to normal layer updates. When true,
 * changes to the MTL content are sent to the screen via the standard
 * CATransaction mechanisms.
 
 当false（默认值）更改为图层的渲染缓冲区时，屏幕上会异步显示正常的图层更新。
 如果为true，则通过标准CATransaction机制将对MTL内容的更改发送到屏幕。
 */
@property BOOL presentsWithTransaction;




/* Controls if `-nextDrawable' is allowed to timeout after 1 second and return nil if
 * the system does not have a free drawable available. The default value is YES.
 * If set to NO, then `-nextDrawable' will block forever until a free drawable is available.
 控制是否允许`-nextDrawable'在1秒后超时，如果系统没有可用的可绘制，则返回nil。 默认值为YES。
 如果设置为NO，则`-neDrawable'将永久阻塞，直到可用的drawable可用。
 */
@property BOOL allowsNextDrawableTimeout CA_AVAILABLE_STARTING (10.13, 11.0, 11.0, 4.0);

@end

NS_ASSUME_NONNULL_END
