#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/Material>
#include <osg/LightModel>
#include <osg/PolygonMode>

#include <iostream>
using namespace std;

int main()
{
    osg::Group * root = new osg::Group();
    osg::Node * model = osgDB::readNodeFile("model/level_1_0_0.obj");
    //osg::Node * model = osgDB::readNodeFile("cyt.ive");


    osg::Material* material = new osg::Material();
    material->setAmbient(osg::Material::FRONT, osg::Vec4(9.f,9.f,9.f,1.0f));
    material->setDiffuse(osg::Material::FRONT, osg::Vec4(10.0,10.0f,10.0f,1.0f));
    material->setSpecular(osg::Material::FRONT, osg::Vec4(0.0,0.0f,0.0f,1.0f));
    material->setEmission(osg::Material::FRONT, osg::Vec4(100.0,100.0f,100.0f,1.0f));
    osg::StateSet* stateset = model->getOrCreateStateSet();
    stateset->setAttributeAndModes(material,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
//    stateset->setAttributeAndModes(material, osg::StateAttribute::ON);
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF );//| osg::StateAttribute::OVERRIDE);
//    stateset->setMode( GL_RESCALE_NORMAL, osg::StateAttribute::ON );
    root->setStateSet(stateset);


    //osg::PolygonMode * pm = new osg::PolygonMode();
    //pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
//    model->getOrCreateStateSet()->setAttribute( pm );


    //root->addChild( model );




    osgViewer::Viewer viewer;
//    viewer.setLightingMode(osg::View::HEADLIGHT);
    //viewer.setSceneData( osgDB::readNodeFile("/home/mpkusex/ros_workspaces/robotic_vision/src/reference3d_srv/model/level_2_0_0.obj") );
    viewer.setSceneData( model );
    //viewer.setSceneData( osgDB::readNodeFile("./mesh/Honda-Accord.3ds") );
    viewer.realize();


    return viewer.run();


    return 0;
}

