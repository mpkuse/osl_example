#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/TerrainManipulator>
#include <osg/ShapeDrawable>
#include <osgText/Text>
#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osg/io_utils>


#include <iostream>
using namespace std;


int main()
{
    osg::Node * cytBuilding = osgDB::readNodeFile( "model/level_2_0_0.obj");

    osg::Group * root = new osg::Group();
    root->addChild( cytBuilding );
    root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT0, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT1, osg::StateAttribute::ON );



    //lighting
    osg::Group * lightGroup = new osg::Group();

    osg::LightSource * lightSource1 = new osg::LightSource();
    osg::LightSource * lightSource2 = new osg::LightSource();

    osg::Vec4f lightPosition (osg::Vec4f(-5.0,-200.0,3.0,1.0f));
    osg::Light * myLight = new osg::Light();
    myLight->setLightNum(1);
//    myLight->setPosition(osg::Vec4(0.2f,-2000.f,0.2f,1.0f));
    myLight->setPosition(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
//    myLight->setDirection(osg::Vec3(0.0f, 1.0f, 0.0f ) );
//    myLight->setAmbient(osg::Vec4(1.0,1.0,1.0,1.0));
    myLight->setDiffuse(osg::Vec4(1.0,1.0,1.0,1.0));
//    myLight->setSpecular(osg::Vec4(1,1,1,1));
//    myLight->setConstantAttenuation(0.001f);
    lightSource1->setLight(myLight);





    // PAT
    osg::PositionAttitudeTransform * lightPAT = new osg::PositionAttitudeTransform();
    lightPAT->setPosition( osg::Vec3(0,-200,0));


    root->addChild(lightPAT);
    lightPAT->addChild(lightSource1);



    // viewer
    osgViewer::Viewer viewer;
    viewer.setLightingMode(osg::View::HEADLIGHT);
//    viewer.setUpViewInWindow( 50, 50, 320, 320 );
    viewer.setSceneData( root );
    viewer.realize();
//    viewer.setCameraManipulator(new osgGA::TerrainManipulator());
//    return viewer.run();


//    viewer.getCamera()->setProjectionMatrixAsPerspective(60., 1., 0.5, 10000 );
    osg::Matrixd myCameraMatrix;
    myCameraMatrix.makeTranslate(0,-60.,0);
    viewer.getCamera()->setViewMatrix(myCameraMatrix);
    float c=-20., d=-200.;
    int a=0;



    while( !viewer.done() )
    {
//        lightPAT->setPosition( osg::Vec3(0,-d,0));

        cout << "viewMatrix " <<  viewer.getCamera()->getViewMatrix() << endl;
        cout << "projectionMatix " <<  viewer.getCamera()->getProjectionMatrix() << endl;
//        cout << "projectionMatix " <<  viewer.getCamera()->getViewport()->get << endl;


        myCameraMatrix.makeTranslate(c,-40.f,0);
////        myCameraMatrix.makeRotate();
        viewer.getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));

//        viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(0.,-300., 0.), osg::Vec3(0.,0., 0.), osg::Vec3(0.,0., 1.) );
        viewer.frame();
        c-=0.1;



    }

    return 0;

}
