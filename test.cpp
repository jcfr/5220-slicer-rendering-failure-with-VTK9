
// Qt includes
#include <QApplication>

// VTK includes
#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor2D.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageMapper.h>
#include <vtkNrrdReader.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

// STD includes
#include <iostream>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  std::string filename("MR-head.nrrd");
  vtkNew<vtkNrrdReader> reader;
  if (!reader->CanReadFile(filename.c_str()))
  {
    std::cerr << "Reader reports " << filename << " cannot be read." << std::endl;
    return 1;
  }
  reader->SetFileName(filename.c_str());
  reader->Update();

  QVTKOpenGLNativeWidget widget;

  vtkNew<vtkImageMapper> mapper;
  mapper->SetInputConnection(reader->GetOutputPort());
  mapper->SetColorWindow(255);
  mapper->SetColorLevel(127.5);

  vtkNew<vtkActor2D> actor;
  actor->SetMapper(mapper);

  vtkNew<vtkRenderer> ren;

  vtkNew<vtkGenericOpenGLRenderWindow> renWin;
  renWin->AddRenderer(ren);

  widget.setRenderWindow(renWin);

  bool withDisplayLocationToBackground = false;
  if (argc >= 2)
  {
    withDisplayLocationToBackground = true;
  }

  if (withDisplayLocationToBackground)
  {
    actor->GetProperty()->SetDisplayLocationToBackground();
  }

  ren->AddActor(actor);

  widget.show();

  return app.exec();
}
