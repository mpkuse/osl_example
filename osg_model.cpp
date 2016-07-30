#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>
#include <osgText/Text>
#include <osg/MatrixTransform>


#include <iostream>
using namespace std;


// custom Keyboard call back
class myKeyBoardEventHandler : public osgGA::GUIEventHandler
{
public:
    virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& );
//    virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); }
};

bool myKeyBoardEventHandler::handle(  const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
    int pressedKeyId = ea.getKey();

    if( pressedKeyId > 0 )
    {
        if( ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN )
            cout << "get button : " << ea.getKey() << endl;
    }
    return true;
}

int main()
{
    osg::Node *bike = osgDB::readNodeFile( "mesh/earth/earth.obj" );

    osg::Group * root = new osg::Group();

    // transform
    osg::PositionAttitudeTransform* xTrans = new osg::PositionAttitudeTransform();
//    xTrans->setPosition( osg::Vec3(25,0,0) );
//    xTrans->setAttitude( osg::Quat(osg::DegreesToRadians(-20.), 1.0, 0.0, 0.0) );


    root->addChild( xTrans );
    xTrans->addChild(bike);

    //
    // set up an HUD/text
    osg::Geode * HUDGeode = new osg::Geode();
    osgText::Text * textOne = new osgText::Text(); //text holder
    textOne->setText("Not so good..!");
    textOne->setAxisAlignment(osgText::Text::SCREEN);
    textOne->setColor( osg::Vec4(.9f,0.f, 1.f,1.f) );


    // projection matrix
    osg::Projection* HUDProjectionMatrix = new osg::Projection;
    HUDProjectionMatrix->setMatrix(osg::Matrix::ortho2D(0,1024,0,768));

    // model-view matrix
    osg::MatrixTransform* HUDModelViewMatrix = new osg::MatrixTransform;
    HUDModelViewMatrix->setMatrix(osg::Matrix::identity());
    HUDModelViewMatrix->setReferenceFrame(  osg::Transform::ABSOLUTE_RF);

    root->addChild( HUDProjectionMatrix );
    HUDProjectionMatrix->addChild(HUDModelViewMatrix);
    HUDModelViewMatrix->addChild(HUDGeode);
    HUDGeode->addDrawable(textOne);



    // draw sphere at origin
    osg::Sphere * unitSphere = new osg::Sphere( osg::Vec3(0,0,0), 10.f );
    osg::ShapeDrawable * unitSphereDrawable = new osg::ShapeDrawable(unitSphere);
    osg::Geode * unitSphereGeode = new osg::Geode();
    unitSphereGeode->addDrawable(unitSphereDrawable);
    root->addChild(unitSphereGeode);

    osg::Sphere * unitSphereX = new osg::Sphere( osg::Vec3(100.,0,0), 50.f );
    osg::ShapeDrawable * unitSphereDrawableX = new osg::ShapeDrawable(unitSphereX);
    unitSphereDrawableX->setColor( osg::Vec4(1.0,0.,0.,1.));
    osg::Geode * unitSphereGeodeX = new osg::Geode();
    unitSphereGeodeX->addDrawable(unitSphereDrawableX);
    root->addChild(unitSphereGeodeX);


    osg::Sphere * unitSphereY = new osg::Sphere( osg::Vec3(0,100.,0), 50.f );
    osg::ShapeDrawable * unitSphereDrawableY = new osg::ShapeDrawable(unitSphereY);
    unitSphereDrawableY->setColor( osg::Vec4(1.0,0.,0.,1.));
    osg::Geode * unitSphereGeodeY = new osg::Geode();
    unitSphereGeodeY->addDrawable(unitSphereDrawableY);
    root->addChild(unitSphereGeodeY);




    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow( 50, 50, 320, 320 );
    viewer.setSceneData( root );
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    viewer.realize();

//    return viewer.run();

    // set keyboard handler
    myKeyBoardEventHandler * keyHandler = new myKeyBoardEventHandler();
    viewer.addEventHandler(keyHandler);

    viewer.getCamera()->setProjectionMatrixAsPerspective(45., 1., 0.5, 1000 );
    viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(0,-1., -19.), osg::Vec3(0,0, 0), osg::Vec3(0,0, 1) );
    float c=100.;
    while( !viewer.done() )
    {

//        xTrans->setPosition( osg::Vec3(c,0,c));
//        xTrans->setAttitude( osg::Quat(osg::DegreesToRadians(-c), 1.0, 0.0, 0.0) );
        textOne->setText( to_string(c) );

//        osg::Matrixd myCameraMatrix;
//        myCameraMatrix.makeTranslate(0,-c,0);
        //viewer.setCamera(myCameraMatrix);
//        viewer.getCamera()->setViewMatrix( myCameraMatrix );

        viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(-1000.,-3000., 0.), osg::Vec3(0.,0., 0.), osg::Vec3(0.,0., 1.) );


        viewer.frame();
//        c+=1.;

    }

}
