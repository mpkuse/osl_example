#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include <osgViewer/ViewerBase>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>

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

osgViewer::View* createView( int x, int y, int w, int h, osg::Node* scene )
{
    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
    view->setSceneData( scene );
    view->setUpViewInWindow( x, y, w, h );
    return view.release();
}


int main()
{
    osg::Node * cytBuilding = osgDB::readNodeFile( "model/level_3_0_0.obj");

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
//    osgViewer::Viewer viewer;
//    viewer.setLightingMode(osg::View::HEADLIGHT);
//    viewer.setUpViewInWindow( 50, 50, 320, 320 );

//    viewer.setSceneData( root );
//    viewer.realize();
//    viewer.setCameraManipulator(new osgGA::TerrainManipulator());
//    return viewer.run();

    // composite viewer
    osgViewer::CompositeViewer viewerComposite;
    for( int i=0 ; i<7 ; i++ )
        viewerComposite.addView( createView(i*320+20,20,320,240,root) );
//    viewerComposite.addView( createView(20,20,320,240,root) );
//    viewerComposite.addView( createView(320+20,20,320,240,root) );
//    viewerComposite.addView( createView(2*320+20,20,320,240,root) );
    cout << "# of views : " << viewerComposite.getNumViews() << endl;


    // window properties:
    osgViewer::ViewerBase::Windows windows;
    viewerComposite.getWindows(windows);
    cout << "# windows : " << windows.size() << endl;

    osg::Matrixd myCameraMatrix;
    float c=-30;
    while( !viewerComposite.done() )
    {
        for( int i=0 ; i<viewerComposite.getNumViews() ; i++ )
        {
            myCameraMatrix.makeTranslate(c,-20.f+5.0f*i,0);
            viewerComposite.getView(i)->getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));
        }
//        myCameraMatrix.makeTranslate(c,-40.f,0);
//        viewerComposite.getView(0)->getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));

//        myCameraMatrix.makeTranslate(c,-20.f,0);
//        viewerComposite.getView(1)->getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));


        cout << "Frame number: " <<  viewerComposite.getFrameStamp()->getReferenceTime() << std::endl;


        double refTime = viewerComposite.getFrameStamp()->getReferenceTime();
        double frameIndx = viewerComposite.getFrameStamp()->getFrameNumber();
        cout << "fps : " <<  frameIndx / (refTime) << endl;
        viewerComposite.frame();
        c+=0.1;
    }
    /*
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
        cout << "Frame number: " <<  viewer.getFrameStamp()->getReferenceTime() << std::endl;

        myCameraMatrix.makeTranslate(c,-40.f,0);
////        myCameraMatrix.makeRotate();
        viewer.getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));

//        viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(0.,-300., 0.), osg::Vec3(0.,0., 0.), osg::Vec3(0.,0., 1.) );
        viewer.frame();
        c-=0.1;



    }
*/
    return 0;

}
