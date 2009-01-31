/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile: vtkSMAnimationSceneProxy.h,v $

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSMAnimationSceneProxy - proxy for vtkAnimationScene
// .SECTION Description
// Proxy for animation scene. A scene is an animation setup that can be played.
// Also supports writing out animation images (movie) and animation geometry.
// Like all animation proxies, this is a client side proxy with not server 
// side VTK objects created.
// .SECTION See Also
// vtkAnimationScene vtkSMAnimationCueProxy

#ifndef __vtkSMAnimationSceneProxy_h
#define __vtkSMAnimationSceneProxy_h

#include "vtkSMAnimationCueProxy.h"

class vtkAnimationScene;
class vtkSMViewProxy;

class VTK_EXPORT vtkSMAnimationSceneProxy : public vtkSMAnimationCueProxy
{
public:
  static vtkSMAnimationSceneProxy* New();
  vtkTypeRevisionMacro(vtkSMAnimationSceneProxy, vtkSMAnimationCueProxy);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Add view module that is involved in the animation generated by this scene.
  // When playing animation, the scene proxy will call Render()
  // and CacheUpdate() on view modules that it is aware of. Also, while saving,
  // geometry or images, the scene considers only the view modules it is aware of.
  void AddViewModule(vtkSMViewProxy*);
  void RemoveViewModule(vtkSMViewProxy*);
  void RemoveAllViewModules();

  // Description:
  // API to get the view modules.
  unsigned int GetNumberOfViewModules();
  vtkSMViewProxy* GetViewModule(unsigned int cc);
 
  // Description:
  // Method to set the current time. This updates the proxies to reflect the state
  // at the indicated time.
  void SetAnimationTime(double time);

  // Description:
  // Returns the current animation time.
  double GetAnimationTime();

  // Description:
  // Get/Set the cache limit (in kilobytes) for each process. If cache size
  // grows beyond the limit, no caching is done on any of the processes.
  vtkGetMacro(CacheLimit, int);
  vtkSetMacro(CacheLimit, int);

  // Description:
  // Set if caching is enabled.
  // This method synchronizes the cahcing flag on every cue.
  vtkSetMacro(Caching, int);
  vtkGetMacro(Caching, int);

  // Description:
  // Add/Remove animation cue proxy.
  void AddCueProxy(vtkSMAnimationCueProxy*);
  void RemoveCueProxy(vtkSMAnimationCueProxy*);

//BTX
protected:
  vtkSMAnimationSceneProxy();
  ~vtkSMAnimationSceneProxy();


  // Description:
  // Create VTK Objects.
  virtual void CreateVTKObjects();

  // Description:
  // Callbacks for corresponding Cue events. The argument must be 
  // casted to vtkAnimationCue::AnimationCueInfo.
  virtual void StartCueInternal(void* info);
  virtual void TickInternal(void* info);
  virtual void EndCueInternal(void* info);
  void CacheUpdate(void* info);

  // Description:
  // Check if the current cache size on all processes is within limits.
  bool CheckCacheSizeWithinLimit();

  int Caching;

  friend class vtkSMAnimationSceneImageWriter;
  int OverrideStillRender;
  vtkSetMacro(OverrideStillRender, int);

  int CacheLimit; // in KiloBytes.

  vtkSMProxy* AnimationPlayer;
private:
  vtkSMAnimationSceneProxy(const vtkSMAnimationSceneProxy&); // Not implemented.
  void operator=(const vtkSMAnimationSceneProxy&); // Not implemented.

  class vtkInternals;
  vtkInternals* Internals;

  class vtkPlayerObserver;
  friend class vtkPlayerObserver;
  vtkPlayerObserver* PlayerObserver;

  // Called when player begins playing animation.
  void OnStartPlay();

  // Called when player is done with playing animation.
  void OnEndPlay();

  // Used to prevent calls SetAnimationTime() during an animation tick.
  bool InTick;
//ETX
};


#endif

