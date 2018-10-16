/* CoreAnimation - CATiledLayer.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

/* This is a subclass of CALayer providing a way to asynchronously
 * provide tiles of the layer's content, potentially cached at multiple
 * levels of detail.
 *
 * As more data is required by the renderer, the layer's
 * -drawInContext: method is called on one or more background threads
 * to supply the drawing operations to fill in one tile of data. The
 * clip bounds and CTM of the drawing context can be used to determine
 * the bounds and resolution of the tile being requested.
 *
 * Regions of the layer may be invalidated using the usual
 * -setNeedsDisplayInRect: method. However update will be asynchronous,
 * i.e. the next display update will most likely not contain the
 * changes, but a future update will.
 *
 * Note: do not attempt to directly modify the `contents' property of
 * an CATiledLayer object - doing so will effectively turn it into a
 * regular CALayer.

 这是CALayer的一个子类，它提供了一种异步提供图层内容切片的方法，可能会在多个细节层次上进行缓存。
 *
 *由于渲染器需要更多数据，因此在一个或多个后台线程上调用图层的-drawInContext：方法，以提供绘图操作以填充一个数据块。 绘图上下文和绘图上下文的CTM可用于确定所请求的图块的边界和分辨率。
 *
 *使用通常的-setNeedsDisplayInRect：方法可以使图层的区域无效。 但是，更新将是异步的，即下一次显示更新很可能不包含更改，但未来的更新将会。
 *
 *注意：不要试图直接修改CATiledLayer对象的`contents'属性 - 这样做会将其有效地转换为常规CALayer。
 */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CATiledLayer : CALayer

/* 新添加的图像以“淡入”为平铺图层的渲染表示的时间（以秒为单位）。 默认实现返回0.25秒。*/
+ (CFTimeInterval)fadeDuration;

/* The number of levels of detail maintained by this layer. Defaults to
 * one. Each LOD is half the resolution of the previous level. If too
 * many levels are specified for the current size of the layer, then
 * the number of levels is clamped to the maximum value (the bottom
 * most LOD must contain at least a single pixel in each dimension).
 此图层维护的详细级别数。 默认为1。 每个LOD的分辨率是前一级别的一半。
 如果为图层的当前大小指定了太多级别，则会将级别数量限制为最大值（最底部的LOD必须至少包含每个维度中的一个像素）。
 */
@property size_t levelsOfDetail;

/* The number of magnified levels of detail for this layer. Defaults to
 * zero. Each previous level of detail is twice the resolution of the
 * later. E.g. specifying 'levelsOfDetailBias' of two means that the
 * layer devotes two of its specified levels of detail to
 * magnification, i.e. 2x and 4x.

 此图层的放大细节级别数。 默认为零。 每个先前的细节级别是后者的两倍。
 例如。 指定'levelsOfDetailBias'为2意味着该层将其指定的两个细节级别用于放大，即2x和4x。
 */
@property size_t levelsOfDetailBias;

/* The maximum size of each tile used to create the layer's content.
 * Defaults to (256, 256). Note that there is a maximum tile size, and
 * requests for tiles larger than that limit will cause a suitable
 * value to be substituted.

 用于创建图层内容的每个图块的最大大小。 默认为（256,256）。
 请注意，存在最大切片大小，并且对大于该限制的切片的请求将导致替换合适的值。
 */
@property CGSize tileSize;

@end

NS_ASSUME_NONNULL_END
