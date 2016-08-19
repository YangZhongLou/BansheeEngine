﻿//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using System.Runtime.CompilerServices;
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Scene-Editor
     *  @{
     */

    /// <summary>
    /// Contains information regarding object snapping.
    /// </summary>
    struct SnapData
    {
        /// <summary>
        /// The normal to the object surface at the snapping point.
        /// </summary>
        public Vector3 normal;

        /// <summary>
        /// The 3D position on the surface of the object
        /// </summary>
        public Vector3 position;
    }

    /// <summary>
    /// Handles rendering of the selection overlay and picking of objects in the target camera's view.
    /// </summary>
    internal sealed class SceneSelection : ScriptObject
    {
        /// <summary>
        /// Creates a new scene selection manager.
        /// </summary>
        /// <param name="sceneCamera">Camera into which to render the selection overlay, and perform picking from.</param>
        internal SceneSelection(Camera sceneCamera)
        {
            Internal_Create(this, sceneCamera.Native.GetCachedPtr());
        }

        /// <summary>
        /// Queues selection overlay drawing for this frame.
        /// </summary>
        internal void Draw()
        {
            Internal_Draw(mCachedPtr);
        }

        /// <summary>
        /// Attempts to select a scene object under the pointer position.
        /// </summary>
        /// <param name="pointerPos">Position of the pointer relative to the scene camera viewport.</param>
        /// <param name="controlHeld">Should this selection add to the existing selection, or replace it.</param>
        /// <param name="ignoreSceneObjects">An array of renderables that should not be rendered during scene picking.</param>
        internal void PickObject(Vector2I pointerPos, bool controlHeld, SceneObject[] ignoreSceneObjects = null)
        {
            Internal_PickObject(mCachedPtr, ref pointerPos, controlHeld, ignoreSceneObjects);
        }

        /// <summary>
        /// Attempts to select a scene object in the specified area.
        /// </summary>
        /// <param name="pointerPos">Position of the pointer relative to the scene camera viewport.</param>
        /// <param name="area">The screen area in which objects will be selected.</param>
        /// <param name="controlHeld">Should this selection add to the existing selection, or replace it.</param>
        /// <param name="ignoreSceneObjects">An array of renderables that should not be rendered during scene picking.</param>
        internal void PickObjects(Vector2I pointerPos, Vector2I area, bool controlHeld, SceneObject[] ignoreSceneObjects = null)
        {
            Internal_PickObjects(mCachedPtr, ref pointerPos, ref area, controlHeld, ignoreSceneObjects);
        }

        /// <summary>
        /// Returns the 3D position of an object under the cursor, along with the surface normal in that point.
        /// </summary>
        /// <param name="pointerPos">Position of the pointer relative to the scene camera viewport.</param>
        /// <param name="ignoreSceneObjects">An array of renderables that should not be rendered during scene picking.</param>
        /// <returns>The position on the object surface and the normal in that point.</returns>
        internal SnapData Snap(Vector2I pointerPos, SceneObject[] ignoreSceneObjects = null)
        {
            SnapData data;
            Internal_Snap(mCachedPtr, ref pointerPos, out data, ignoreSceneObjects);
            return data;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_Create(SceneSelection managedInstance, IntPtr camera);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_Draw(IntPtr thisPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_PickObject(IntPtr thisPtr, ref Vector2I pointerPos, bool controlHeld, SceneObject[] ignoreRenderables);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_PickObjects(IntPtr thisPtr, ref Vector2I pointerPos, ref Vector2I extents, bool controlHeld, SceneObject[] ignoreRenderables);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_Snap(IntPtr thisPtr, ref Vector2I pointerPos, out SnapData data, SceneObject[] ignoreRenderables);
    }

    /** @} */
}
