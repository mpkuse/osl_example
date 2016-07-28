#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <iostream>
using namespace std;

int main()
{
    osgViewer::Viewer viewer;
    //viewer.setSceneData( osgDB::readNodeFile("/home/mpkusex/ros_workspaces/robotic_vision/src/reference3d_srv/model/level_2_0_0.obj") );
    viewer.setSceneData( osgDB::readNodeFile("model/level_2_0_0.obj") );
    //viewer.setSceneData( osgDB::readNodeFile("./mesh/Honda-Accord.3ds") );
    return viewer.run();

    viewer.getCamera()->setProjectionMatrixAsPerspective(40, 1.0, 1.0, 100 );

    //osg::Matrix trans;
    //trans.makeTranslate(5., 0., -90. );

    double angle = 0.;
    while( !viewer.done() )
    {
        //osg::Matrix rot;
        //rot.makeRotate( angle, osg::Vec3(0,0, 1.) );
        //angle += 0.01;
        //cout << angle << endl;

        //viewer.getCamera()->setViewMatrix( rot * trans );
        viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(0.,-90.,0), osg::Vec3(0,0,0), osg::Vec3(0,-1,0) );
        viewer.frame();
    }


    return 0;
}
