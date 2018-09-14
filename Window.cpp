#include "stdafx.h"
#include "Window.h"

#include "QGuiApplication"

#include "QtCore/QByteArray"

#include "Qt3DCore/QEntity"
#include "Qt3DCore/QAspectEngine"

#include "Qt3DExtras/Qt3DWindow"
#include "Qt3DExtras/QOrbitCameraController"
#include "Qt3DExtras/QForwardRenderer"

#include "Qt3DRender/QAttribute"
#include "Qt3DRender/QBuffer"
#include "Qt3DRender/QCamera"
#include "Qt3DRender/QCameraLens"
#include "Qt3DRender/QShaderProgram"
#include "Qt3DRender/QShaderData"
#include "Qt3DRender/QRenderSettings"

#include "Qt3DInput/QInputAspect"


using namespace ModelingAndSimulation;

namespace ModelingAndSimulation
{
	struct _FWindow
	{
		_FWindow() { Scene = NullPtr; View = NullPtr; }

		~_FWindow() { delete Scene; delete View; }
		
		Qt3DRender::QShaderProgram *Shader;
		Qt3DExtras::Qt3DWindow *View;
		Qt3DExtras::QForwardRenderer *Renderer;
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
	Window.X = Window.Y = 32;
	Window.AspectRatio = static_cast<FReal>(Window.Width) / static_cast<FReal>(Window.Height);
	Window.bFullScreen = false;
	Window.bWait = false;
	Window.bPerspective = true;
	Window.Far = 0.1;
	Window.Near = 1000;
	Window.FieldOfView = 35;
	Window.LookSpeed = 180;
	Window.MoveSpeed = 50;
	Window.Color.R = Window.Color.G = Window.Color.B = 0;
	Window.Color.A = 0;
	Window.LookAt.X = Window.LookAt.Y = Window.LookAt.Z = 0;
	Window.Position.X = Window.Position.Y = 0;
	Window.Position.Z = 40;
	Window.Up.X = Window.Up.Z = 0;
	Window.Up.Y = 1;
	Window.Style = NullPtr;
	Window.Title = NullPtr;
	Window.Simulation = NullPtr;
	Window._State = NullPtr;
	return Window;
}

FWindow &FWindow::Display(const NDev::FDescriptor &Buffer, FWindow &Window)
{
	_FWindow *State;

	if (Window._State) { return Window; }
	if (!_Application) { _Application = new QGuiApplication(_ArgumentCount, _Arguments); }
	auto Application = (QGuiApplication *)_Application;
	auto Scene = new Qt3DCore::QEntity();
	auto View = new Qt3DExtras::Qt3DWindow();
	
	/* Configure Camera */
	auto Camera = View->camera();
	Camera->setPosition(QVector3D(Window.Position.X, Window.Position.Y, Window.Position.Z));
	Camera->setViewCenter(QVector3D(Window.LookAt.X, Window.LookAt.Y, Window.LookAt.Z));

	/* Configure Lens */
	auto Lens = Camera->lens();
	if (Window.bPerspective)
	{
		Lens->setProjectionType(Qt3DRender::QCameraLens::ProjectionType::PerspectiveProjection);
	}
	else
	{
		Lens->setProjectionType(Qt3DRender::QCameraLens::ProjectionType::OrthographicProjection);
	}
	Lens->setPerspectiveProjection(Window.FieldOfView, Window.AspectRatio, Window.Near, Window.Far);

	/* Configure Renderer */
	auto Renderer = new Qt3DExtras::QForwardRenderer(Scene);
	Renderer->setCamera(Camera);
	Renderer->setClearColor(QColor(Window.Color.R, Window.Color.G, Window.Color.B, Window.Color.A));

	/* Configure Shaders */
	auto Shader = new Qt3DRender::QShaderProgram(Scene);
	if (Window.Simulation)
	{ 
		Shader->setComputeShaderCode(Qt3DRender::QShaderProgram::loadSource(Window.Default + ".comp"));
	}
	if (Window.Style)
	{
		Shader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(Window.Default + ".vert"));
		Shader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(Window.Default + ".frag"));
	}

	/* Configure Data */
	auto Data = new Qt3DCore::QEntity(Scene);
	auto _Buffer = new Qt3DRender::QBuffer();
	_Buffer->setData(QByteArray(Buffer.Bytes, Buffer.Size * Buffer.SizeOf));
	auto Attribute = new Qt3DRender::QAttribute(_Buffer, Qt3DRender::QAttribute::VertexBaseType::Double, Buffer.SizeOf, Buffer.Size, Buffer.Offset, Buffer.Stride);

	/* Configure Controler */
	auto Manipulator = new Qt3DExtras::QOrbitCameraController(Scene);
	Manipulator->setLinearSpeed(Window.MoveSpeed);
	Manipulator->setLookSpeed(Window.LookSpeed);
	Manipulator->setCamera(Camera);

	/* Configure View */
	View->setActiveFrameGraph(Renderer);
	View->setTitle(Window.Title);
	View->setRootEntity(Scene);
	if (Window.bFullScreen) { View->showFullScreen(); }
	else { View->show(); }

	/* Store Window State Information */
	State = new _FWindow();
	State->Scene = Scene;
	State->View = View;
	State->Shader = Shader;
	State->Renderer = Renderer;
	Window._State = State;

	if (Window.bWait) { Window._ErrorNo = Application->exec(); }
	return Window;
}

FVoid FWindow::Update(const NDev::FDescriptor &Buffer, FWindow &Window)
{

}

FReturn FWindow::Wait()
{
	if (!_Application) { return Success; }
	auto Application = (QGuiApplication *)_Application;
	return Application->exec();
}

