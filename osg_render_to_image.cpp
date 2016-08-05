#include <osg/Node>
#include <osg/Group>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgViewer/ViewerBase>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Renderer>


#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/io_utils>


#include <osg/Camera>
#include <osg/Image>

#include <iostream>
using namespace std;

class SnapCallBack : public osg::Camera::DrawCallback
{
     virtual void operator () (osg::RenderInfo& renderInfo) const
    {
//        osg::notify(osg::NOTICE)<<"Camera callback"<<std::endl;
        cout << "callbck\n";
        osg::Camera * camera = renderInfo.getCurrentCamera();
        osg::Viewport * viewport = camera ? camera->getViewport() : 0;
        osg::Image * image = new osg::Image();

        if( viewport )
        {
            cout << "take screenshot "<< viewport->width() << " " << viewport->height() << endl;
            image->readPixels(int(viewport->x()),int(viewport->y()),int(viewport->width()),int(viewport->height()),GL_RGBA,GL_UNSIGNED_BYTE);
//            osgDB::writeImageFile( *image, string("out.png") );
        }
        else
            cout << "error with viewport\n";
    }
};

int main()
{
    osg::Node * cytBuilding = osgDB::readNodeFile( "model/level_2_0_0.obj");

    osg::Group * root = new osg::Group();
    osg::PositionAttitudeTransform * scenePAT = new osg::PositionAttitudeTransform();
//    scenePAT->setAttitude(osg::Quat(osg::DegreesToRadians(90.0), osg::Vec3(1,0,0) ) );
    root->addChild(scenePAT);
    scenePAT->addChild( cytBuilding );
    root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT0, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT1, osg::StateAttribute::ON );





    // viewer
    osgViewer::Viewer viewer;
    viewer.setLightingMode(osg::View::HEADLIGHT);
    viewer.setUpViewInWindow( 50, 50, 320, 320 );
    viewer.setSceneData( root );
//    return viewer.run();
    viewer.realize();

    osgViewer::ViewerBase::Windows windows;
    viewer.getWindows( windows );
    cout << "# windows : " << windows.size() << endl;
    (windows[0])->setWindowName( string("KUSE") );






    // Set post draw call back
    osg::Camera * camera = viewer.getCamera();
    SnapCallBack * postDrawCallBack = new SnapCallBack();
    camera->setPostDrawCallback( postDrawCallBack );




    osg::Matrixd myCameraMatrix;
    float c=-20.;





    while( !viewer.done() )
    {

        cout << "viewMatrix " <<  viewer.getCamera()->getViewMatrix() << endl;
        cout << "projectionMatix " <<  viewer.getCamera()->getProjectionMatrix() << endl;
//        cout << "projectionMatix " <<  viewer.getCamera()->getViewport()->get << endl;
        cout << "Frame number: " <<  viewer.getFrameStamp()->getReferenceTime() << std::endl;

        myCameraMatrix.setRotate( osg::Quat(osg::DegreesToRadians(90.), osg::Vec3(1,0,0) ) * osg::Quat(osg::DegreesToRadians(15.), osg::Vec3(0,1,0) ) );
        myCameraMatrix.setTrans( osg::Vec3(c,-80.0f, 0) );
        viewer.getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));


        viewer.frame();
        c-=0.1;



    }

    return 0;

}
