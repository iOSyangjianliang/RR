//
//  ARSCNView.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKit.h>
#import <ARKit/ARSession.h>
#import <ARKit/ARHitTestResult.h>

@protocol ARSCNViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 A view that integrates ARSession rendering into SceneKit.
 
 @discussion The view draws the camera background, provides and updates a camera,
 manages nodes for anchors, and updates lighting.
 
 将ARSession渲染集成到SceneKit中的视图。
  
  @discussion视图绘制相机背景，提供和更新相机，
  管理锚点的节点，并更新照明。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSCNView : SCNView

/**
 Specifies the renderer delegate.
  指定渲染器代理。
 */
@property (nonatomic, weak, nullable) id<ARSCNViewDelegate> delegate;

/**
 The session that the view uses to update the scene.
  视图用于更新场景的会话。
 */
@property (nonatomic, strong) ARSession *session;

/**
 Specifies the scene of the view.
  指定视图的场景。
 */
@property(nonatomic, strong) SCNScene *scene;

/**
 Determines whether the view will update the scene’s lighting.
 
 @discussion When set, the view will automatically create and update lighting for 
 light estimates the session provides. Defaults to YES.
  
 确定视图是否将更新场景的光照。
  @discussion设置后，视图将自动为其创建和更新照明
  光估计会话提供。默认为YES。
 */
@property(nonatomic) BOOL automaticallyUpdatesLighting;

/**
 Searches the scene hierarchy for an anchor associated with the provided node.
 @param node A node in the view’s scene.
  在场景层次结构中搜索与提供的节点关联的锚点。
  @param node视图场景中的一个节点。
 */
- (nullable ARAnchor *)anchorForNode:(SCNNode *)node;

/**
 Returns the node that has been mapped to a specific anchor.
 @param anchor An anchor with an existing node mapping.
 返回已映射到特定锚点的节点。
  @param anchor具有现有节点映射的锚点。
 */
- (nullable SCNNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches the current frame for objects corresponding to a point in the view.
 
 @discussion A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the view’s coordinate system.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
  在当前帧中搜索与视图中的点对应的对象。
  
  @discussion视图坐标空间中的2D点可以指向沿线段的任何点
  在3D坐标空间中。命中测试是在该线段中找到世界中的对象的过程。
  @param point视图坐标系中的一个点。
  @param types要搜索的结果类型。
  @return从最近到最远排序的所有命中测试结果的数组。
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types;

@end


#pragma mark - ARSCNViewDelegate


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol ARSCNViewDelegate <SCNSceneRendererDelegate, ARSessionObserver>
@optional

/**
 Implement this to provide a custom node for the given anchor.
 
 @discussion This node will automatically be added to the scene graph.
 If this method is not implemented, a node will be automatically created.
 If nil is returned the anchor will be ignored.
 @param renderer The renderer that will render the scene.
 @param anchor The added anchor.
 @return Node that will be mapped to the anchor or nil.
 
  实现此目的以为给定锚提供自定义节点。
  
  @discussion此节点将自动添加到场景图中。
  如果未实现此方法，将自动创建节点。
  如果返回nil，则将忽略锚点。
  @param渲染器将渲染场景的渲染器。
  @param anchor添加的锚点。
  @return将映射到锚点或nil的节点。
 */
- (nullable SCNNode *)renderer:(id <SCNSceneRenderer>)renderer nodeForAnchor:(ARAnchor *)anchor;

/**
 Called when a new node has been mapped to the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that maps to the anchor.
 @param anchor The added anchor.
 
 在将新节点映射到给定锚点时调用。
  
  @param渲染器将渲染场景的渲染器。
  @param node映射到锚点的节点。
  @param anchor添加的锚点。
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didAddNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node will be updated with data from the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that will be updated.
 @param anchor The anchor that was updated.
 
 在使用给定锚点的数据更新节点时调用。
  
  @param渲染器将渲染场景的渲染器。
  @param node将更新的节点。
  @param anchor已更新的锚点。
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer willUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node has been updated with data from the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that was updated.
 @param anchor The anchor that was updated.
 
  使用给定锚点的数据更新节点时调用。
  
  @param渲染器将渲染场景的渲染器。
  @param node已更新的节点。
  @param anchor已更新的锚点。
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a mapped node has been removed from the scene graph for the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that was removed.
 @param anchor The anchor that was removed.
 
 从已从给定锚点的场景图中删除映射节点时调用。
  
  @param渲染器将渲染场景的渲染器。
  @param node已删除的节点。
  @param anchor已删除的锚点。
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didRemoveNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

@end


/**
 Extended debug options for an ARSCNView
  ARSCNView的扩展调试选项
 */
struct ARSCNDebugOptions {} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/** Show the world origin in the scene.
 在场景中显示全局原点。*/
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowWorldOrigin NS_SWIFT_NAME(ARSCNDebugOptions.showWorldOrigin);

/** Show detected 3D feature points in the world.
 显示全局上检测到的3D特征点。*/
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowFeaturePoints NS_SWIFT_NAME(ARSCNDebugOptions.showFeaturePoints);

NS_ASSUME_NONNULL_END
