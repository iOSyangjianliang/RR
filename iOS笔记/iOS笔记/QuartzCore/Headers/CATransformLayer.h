/* CoreAnimation - CATransformLayer.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

/* "Transform" layers are used to create true 3D layer hierarchies.
 *
 * Unlike normal layers, transform layers do not project (i.e. flatten)
 * their sublayers into the plane at Z=0. However due to this neither
 * do they support many features of the 2D compositing model:
 *
 * - only their sublayers are rendered (i.e. no background, contents,
 *   border)
 *
 * - filters, backgroundFilters, compositingFilter, mask, masksToBounds
 *   and shadow related properties are ignored (they all assume 2D
 *   image processing of the projected layer)
 *
 * - opacity is applied to each sublayer individually, i.e. the transform
 *   layer does not form a compositing group.
 *
 * Also, the -hitTest: method should never be called on transform
 * layers (they do not have a 2D coordinate space into which to map the
 * supplied point.) CALayer will pass over transform layers directly to
 * their sublayers, applying the effects of the transform layer's
 * geometry when hit-testing each sublayer. */

/* “变换”图层用于创建真正的3D图层层次结构。
 *
 * 不同于普通图层，变换图层不会将它们的子图层投影到Z=0的平面上。
 * 然而由于这一点，他们也不支持2D合成模型的许多特性:
 *
 * -只呈现它们的子元素(即没有背景、内容、边框)
 *
 * - filters，backgroundFilters，compositingFilter，mask，masksToBounds and shadow
   相关属性被忽略（假设它们都为2D投影层的图像处理）
 *
 * -将不透明度单独应用于每个子层，即变换图层不形成合成组。
 *
 * 同样，-hitTest:方法永远不应该在转换层上被调用(它们没有2D坐标空间来映射提供的点)。
 * CALayer将直接将转换层传递到他们的子层，在测试每个子层时应用转换层几何形状的效果。
 */

CA_CLASS_AVAILABLE (10.6, 3.0, 9.0, 2.0)
@interface CATransformLayer : CALayer
@end

NS_ASSUME_NONNULL_END
