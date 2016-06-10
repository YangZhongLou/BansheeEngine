//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsScriptGUICanvas.h"
#include "BsScriptMeta.h"
#include "BsScriptSpriteTexture.h"
#include "BsMonoUtil.h"
#include "BsGUILayout.h"
#include "BsGUICanvas.h"
#include "BsGUIOptions.h"
#include "BsScriptVector2I.h"
#include "BsScriptFont.h"

namespace BansheeEngine
{
	ScriptGUICanvas::ScriptGUICanvas(MonoObject* instance, GUICanvas* canvas)
		:TScriptGUIElement(instance, canvas)
	{

	}

	void ScriptGUICanvas::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", &ScriptGUICanvas::internal_createInstance);
		metaData.scriptClass->addInternalCall("Internal_DrawLine", &ScriptGUICanvas::internal_drawLine);
		metaData.scriptClass->addInternalCall("Internal_DrawPolyLine", &ScriptGUICanvas::internal_drawPolyLine);
		metaData.scriptClass->addInternalCall("Internal_DrawTexture", &ScriptGUICanvas::internal_drawTexture);
		metaData.scriptClass->addInternalCall("Internal_DrawTriangleStrip", &ScriptGUICanvas::internal_drawTriangleStrip);
		metaData.scriptClass->addInternalCall("Internal_DrawTriangleList", &ScriptGUICanvas::internal_drawTriangleList);
		metaData.scriptClass->addInternalCall("Internal_DrawText", &ScriptGUICanvas::internal_drawText);
		metaData.scriptClass->addInternalCall("Internal_Clear", &ScriptGUICanvas::internal_clear);
	}

	void ScriptGUICanvas::internal_createInstance(MonoObject* instance, MonoString* style, MonoArray* guiOptions)
	{
		GUIOptions options;

		ScriptArray scriptArray(guiOptions);
		UINT32 arrayLen = scriptArray.size();
		for (UINT32 i = 0; i < arrayLen; i++)
			options.addOption(scriptArray.get<GUIOption>(i));

		GUICanvas* guiCanvas = GUICanvas::create(options, toString(MonoUtil::monoToWString(style)));

		new (bs_alloc<ScriptGUICanvas>()) ScriptGUICanvas(instance, guiCanvas);
	}

	void ScriptGUICanvas::internal_drawLine(ScriptGUICanvas* nativeInstance, Vector2I* a, Vector2I* b, float width, Color* color)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();
		canvas->drawLine(*a, *b, width, *color);
	}

	void ScriptGUICanvas::internal_drawPolyLine(ScriptGUICanvas* nativeInstance, MonoArray* vertices, float width, 
		Color* color)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();

		ScriptArray verticesArray(vertices);
		UINT32 size = verticesArray.size();

		Vector<Vector2I> nativeVertices(size);
		memcpy(nativeVertices.data(), verticesArray.getRawPtr<ScriptVector2I>(), sizeof(Vector2));

		canvas->drawPolyLine(nativeVertices, width, *color);
	}

	void ScriptGUICanvas::internal_drawTexture(ScriptGUICanvas* nativeInstance, ScriptSpriteTexture* texture, Rect2I* area,
		TextureScaleMode scaleMode, Color* color)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();

		HSpriteTexture nativeTexture;
		if (texture != nullptr)
			nativeTexture = texture->getHandle();

		canvas->drawTexture(nativeTexture, *area, scaleMode, *color);
	}
	
	void ScriptGUICanvas::internal_drawTriangleStrip(ScriptGUICanvas* nativeInstance, MonoArray* vertices, Color* color)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();

		ScriptArray verticesArray(vertices);
		UINT32 size = verticesArray.size();

		Vector<Vector2I> nativeVertices(size);
		memcpy(nativeVertices.data(), verticesArray.getRawPtr<ScriptVector2I>(), sizeof(Vector2));

		canvas->drawTriangleStrip(nativeVertices, *color);
	}

	void ScriptGUICanvas::internal_drawTriangleList(ScriptGUICanvas* nativeInstance, MonoArray* vertices, Color* color)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();

		ScriptArray verticesArray(vertices);
		UINT32 size = verticesArray.size();

		Vector<Vector2I> nativeVertices(size);
		memcpy(nativeVertices.data(), verticesArray.getRawPtr<ScriptVector2I>(), sizeof(Vector2));

		canvas->drawTriangleList(nativeVertices, *color);
	}

	void ScriptGUICanvas::internal_drawText(ScriptGUICanvas* nativeInstance, MonoString* text, Vector2I* position,
		ScriptFont* font, UINT32 size, Color* color)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();
		WString nativeText = MonoUtil::monoToWString(text);

		HFont nativeFont;
		if (font != nullptr)
			nativeFont = font->getHandle();

		canvas->drawText(nativeText, *position, nativeFont, size, *color);
	}

	void ScriptGUICanvas::internal_clear(ScriptGUICanvas* nativeInstance)
	{
		GUICanvas* canvas = (GUICanvas*)nativeInstance->getGUIElement();
		canvas->clear();
	}
}