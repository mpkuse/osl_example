#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

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
#include <osg/Material>
#include <osg/BoundingBox>
#include <osg/BoundingSphere>

#include <iostream>
using namespace std;


osg::Node *  createLightSource( unsigned int num, const osg::Vec3& trans, const osg::Vec4& color )
{
    osg::Light * light = new osg::Light();
    light->setLightNum(num);

    // Spot Light
    light->setPosition(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
    light->setDiffuse( color );
//    light->setAmbient( color );
    light->setDirection( osg::Vec3(1,0,0));
//    light->setSpotCutoff(40.0f);
//    light->setSpotExponent(.1f);



    osg::LightSource * lightSrc = new osg::LightSource();
    lightSrc->setLight(light);
//    lightSrc->setReferenceFrame(osg::LightSource::ReferenceFrame::ABSOLUTE_RF);



    osg::MatrixTransform * srcTransform = new osg::MatrixTransform();
    srcTransform->setMatrix( osg::Matrix::translate(trans) );
    srcTransform->addChild( lightSrc );

    osg::Sphere * unitSphere = new osg::Sphere( osg::Vec3(0,0,0), 2.0f );
    osg::ShapeDrawable * unitSphereDrawable = new osg::ShapeDrawable(unitSphere);
    unitSphereDrawable->setColor( color );
    srcTransform->addChild(unitSphereDrawable);
    unitSphereDrawable->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    return srcTransform;

}

void manipMaterial( osg::Material * material )
{
    cout << "getAmbientFrontAndBack : " << material->getAmbientFrontAndBack() << endl;
//    cout << "getColorMode() "<< material->getColorMode() << endl;
}


int main()
{
    osg::Node * cytBuilding = osgDB::readNodeFile( "model/level_2_0_0.obj");
    cout << "radious : " << cytBuilding->getBound().radius() << endl;


    osg::Group * root = new osg::Group();
    osg::PositionAttitudeTransform * scenePAT = new osg::PositionAttitudeTransform();
//    scenePAT->setAttitude(osg::Quat(osg::DegreesToRadians(90.0), osg::Vec3(1,0,0) ) );
//    root->addChild(scenePAT);
    root->addChild( cytBuilding );



    osg::Light * light = new osg::Light();
    light->setLightNum(0);

    // Spot Light
    osg::Vec4 color = osg::Vec4(1.0,0.0,0.0,1.0);
    osg::Vec3 trans = osg::Vec3(0,-40,-40);
    light->setPosition(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
    light->setDiffuse( color );
    light->setSpecular( color );
    light->setAmbient( color );
    light->setDirection( osg::Vec3(0,-10,-10));

    osg::LightSource * lightSrc = new osg::LightSource();
    lightSrc->setLight(light);

    osg::MatrixTransform * srcTransform = new osg::MatrixTransform();
    srcTransform->setMatrix( osg::Matrix::translate(trans) );
    srcTransform->addChild( lightSrc );

    osg::Sphere * unitSphere = new osg::Sphere( osg::Vec3(0,0,0), 2.0f );
    osg::ShapeDrawable * unitSphereDrawable = new osg::ShapeDrawable(unitSphere);
    unitSphereDrawable->setColor( color);
    srcTransform->addChild(unitSphereDrawable);
    unitSphereDrawable->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );


//    root->addChild( ls );
//    root->addChild( createLightSource(1, osg::Vec3(-30,-30,-30), osg::Vec4(0.0,1.0,1.0,1.0) ) );
    root->addChild(srcTransform);



    //material
    osg::Material* material = new osg::Material();
//    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.5,0.5f,0.5f,1.0f));
    material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0,1.0f,1.0f,1.0f));
    material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0,0.0f,0.0f,1.0f));
//    material->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0,1.0f,1.0f,1.0f));
    osg::StateSet* stateset = new osg::StateSet();
    //stateset->setAttributeAndModes(material,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
//    stateset->setAttribute(material);
    stateset->setMode( GL_LIGHTING,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON | osg::StateAttribute::PROTECTED );
    stateset->setMode( GL_LIGHT0, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON  );
    stateset->setMode( GL_LIGHT1, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON  );
    root->setStateSet(stateset);




    // viewer
    osgViewer::Viewer viewer;
//    viewer.setLightingMode(osg::View::HEADLIGHT);
//    viewer.setUpViewInWindow( 50, 50, 320, 320 );

    viewer.setSceneData( root );
    viewer.realize();
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
//    return viewer.run();

    float cc = -20.0f;
    while( !viewer.done() )
    {
        srcTransform->setMatrix( osg::Matrix::translate(osg::Vec3(cc,cc,-40)) );
        viewer.frame();
        cc-=0.1;
    }
    return 0;


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

        myCameraMatrix.makeTranslate(c,-90.f,0);
////        myCameraMatrix.makeRotate();
        viewer.getCamera()->setViewMatrix(osg::Matrixd::inverse(myCameraMatrix));

//        viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(0.,-300., 0.), osg::Vec3(0.,0., 0.), osg::Vec3(0.,0., 1.) );
        viewer.frame();
        c-=0.1;



    }

    return 0;

}
