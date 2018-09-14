#include "stdafx.h"
#include "Window.h"


/*
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
*/


#include "Window.h"

#include "QGuiApplication"
#include "Qt3DCore/QEntity"
#include "Qt3DExtras/Qt3DWindow"
#include "Qt3DExtras/QOrbitCameraController"
#include "Qt3DRender/QAttribute"
#include "Qt3DRender/QGeometry"
#include "Qt3DRender/QBuffer"
#include "Qt3DRender/QCamera"

using namespace ModelingAndSimulation;

namespace ModelingAndSimulation
{
	struct _FWindow
	{
		_FWindow() { Scene = NullPtr; View = NullPtr; }

		~_FWindow() { delete Scene; delete View; }

		Qt3DExtras::Qt3DWindow *View;
		Qt3DCore::QEntity *Scene;
	};
}

static char** _InitializeArguments(char** Arguments, const int &Count)
{
	const char* Name = "ModelingAndSimulation";
	FSize _Size = sizeof(Name);
	Arguments = NDev::Make<char*>(Count);
	Arguments[0] = NullPtr;
	Arguments[0] = NDev::Copy<char>(Name, NullPtr, _Size);
	return Arguments;
}

FPointer FWindow::_Application = NullPtr;
int FWindow::_ArgumentCount = 1;
char** FWindow::_Arguments = _InitializeArguments(FWindow::_Arguments, FWindow::_ArgumentCount);

FWindow FWindow::Default()
{
	FWindow Window;
	Window.Width = 1280;
	Window.Height = 720;
	Window.X = 32;
	Window.Y = 32;
	Window.AspectRatio = static_cast<FReal>(Window.Width) / static_cast<FReal>(Window.Height);
	Window.bFullScreen = false;
	Window.bWait = false;
	Window.Far = 0.1;
	Window.Near = 1000;
	Window.FieldOfView = 35;
	Window.LookSpeed = 180;
	Window.MoveSpeed = 50;
	Window.Title = NullPtr;
	Window._State = NullPtr;
	return Window;
}

FWindow &FWindow::Display(const NDev::FDescriptor &Buffer, FWindow &Window)
{
	_FWindow *State;

	if (Window._State) { return Window; }
	if (!_Application) { _Application = new QGuiApplication(_ArgumentCount, _Arguments); }
	auto Application = (QGuiApplication *)_Application;

	auto _Buffer = new Qt3DRender::QBuffer();
	_Buffer->setData(QByteArray(Buffer.Bytes, Buffer.Size * Buffer.SizeOf));
	
	auto Scene = new Qt3DCore::QEntity();
	auto Geometry = new Qt3DRender::QGeometry(Scene);
	auto Attribute = new Qt3DRender::QAttribute(_Buffer, Qt3DRender::QAttribute::VertexBaseType::Double, Buffer.SizeOf, Buffer.Size, Buffer.Offset, Buffer.Stride);
	Geometry->addAttribute(Attribute);

	auto View = new Qt3DExtras::Qt3DWindow();
	auto Camera = View->camera();
	Camera->lens()->setPerspectiveProjection(Window.FieldOfView, Window.AspectRatio, Window.Near, Window.Far);

	auto Manipulator = new Qt3DExtras::QOrbitCameraController(Scene);
	Manipulator->setLinearSpeed(Window.MoveSpeed);
	Manipulator->setLookSpeed(Window.LookSpeed);
	Manipulator->setCamera(Camera);

	View->setRootEntity(Scene);
	View->setTitle(Window.Title);
	if (Window.bFullScreen) { View->showFullScreen(); }
	else { View->show(); }

	State = new _FWindow();
	State->Scene = Scene;
	State->View = View;
	Window._State = State;

	if (Window.bWait) { Window._ErrorNo = Application->exec(); }
	return Window;
}

FReturn FWindow::Wait()
{
	if (!_Application) { return Success; }
	auto Application = (QGuiApplication *)_Application;
	return Application->exec();
}

