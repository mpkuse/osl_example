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


#include <iostream>
using namespace std;

int main()
{
    osg::Box * unitCube = new osg::Box( osg::Vec3(0,0,0), 1.0f );
    osg::ShapeDrawable * unitCubeDrawable = new osg::ShapeDrawable(unitCube);

    osg::Sphere * unitSphere = new osg::Sphere( osg::Vec3(0,0,0), 1.0f );
    osg::ShapeDrawable * unitSphereDrawable = new osg::ShapeDrawable(unitSphere);

    osg::Geode * basicShapesGeode = new osg::Geode();
    basicShapesGeode->addDrawable( unitCubeDrawable );

    osg::Geode * unitSphereGeode = new osg::Geode();
    unitSphereGeode->addDrawable(unitSphereDrawable);



    osg::Group * root = new osg::Group();
    root->addChild(basicShapesGeode);


    osg::PositionAttitudeTransform* sphereXForm = new osg::PositionAttitudeTransform();
    sphereXForm->setPosition( osg::Vec3(2.5,0,0) );
    root->addChild(sphereXForm);
    sphereXForm->addChild(unitSphereGeode);




    // setup viewer
    osgViewer::Viewer viewer;
    viewer.setSceneData( root );
    viewer.run();
}
