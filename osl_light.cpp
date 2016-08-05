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

#include <osg/LightSource>
#include <osg/Material>


#include <iostream>
using namespace std;

osg::Node *  createLightSource( unsigned int num, const osg::Vec3& trans, const osg::Vec4& color )
{
    osg::Light * light = new osg::Light();
    light->setLightNum(num);

    light->setPosition(osg::Vec4(0.0f,1.0f,0.0f,0.0f));
    light->setDiffuse( color );
    light->setAmbient( osg::Vec4(0.3,0.3,0.3, 1.0));

    osg::LightSource * lightSrc = new osg::LightSource();
    lightSrc->setLight(light);

    osg::MatrixTransform * srcTransform = new osg::MatrixTransform();
    srcTransform->setMatrix( osg::Matrix::translate(trans) );
    srcTransform->addChild( lightSrc );

    osg::Sphere * unitSphere = new osg::Sphere( osg::Vec3(0,0,0), .50f );
    osg::ShapeDrawable * unitSphereDrawable = new osg::ShapeDrawable(unitSphere);
    unitSphereDrawable->setColor( color );
    srcTransform->addChild(unitSphereDrawable);
    unitSphereDrawable->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    return srcTransform;

}


int main()
{
    osg::Node *car = osgDB::readNodeFile( "mesh/2012-VW-beetle-turbo.3ds" );
    osg::Material * material = (osg::Material*) car->getOrCreateStateSet()->getAttribute( osg::StateAttribute::MATERIAL );



    osg::Group * root = new osg::Group();
    root->addChild(car);

    root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT0, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT1, osg::StateAttribute::ON );
    root->getOrCreateStateSet()->setMode( GL_LIGHT2, osg::StateAttribute::ON );


//    // a light bulb
//    osg::Light * myLight = new osg::Light();
//    myLight->setLightNum(1);
//    myLight->setPosition(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
//    myLight->setDiffuse(osg::Vec4(0.0,1.0,1.0,1.0));
//    osg::LightSource * lightSource = new osg::LightSource();
//    lightSource->setLight(myLight);

//    // PAT
//    osg::PositionAttitudeTransform * lightPAT = new osg::PositionAttitudeTransform();
//    lightPAT->setPosition( osg::Vec3(-1.0f,0.0f,0.0f));

//    root->addChild(lightPAT);
//    lightPAT->addChild(lightSource);

    root->addChild( createLightSource(0, osg::Vec3(-1.5, 0,0), osg::Vec4(0.0,0.0,1.0,1.0) ) );
    root->addChild( createLightSource(1, osg::Vec3(1.0, 0,0), osg::Vec4(1.0,0.0,1.0,1.0) ) );



    osgViewer::Viewer viewer;
//    viewer.setLightingMode(osg::View::SKY_LIGHT);
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.setUpViewInWindow( 50, 50, 320, 320 );
    viewer.setSceneData( root );
    viewer.getCamera()->getOrCreateStateSet()->setGlobalDefaults();
    return viewer.run();
    viewer.realize();
}
