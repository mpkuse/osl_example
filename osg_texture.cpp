#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

#include <iostream>
using namespace std;

osg::Geode* createPyramid()
{
   osg::Geode* pyramidGeode = new osg::Geode();
   osg::Geometry* pyramidGeometry = new osg::Geometry();
   pyramidGeode->addDrawable(pyramidGeometry);

   // Specify the vertices:
   osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
   pyramidVertices->push_back( osg::Vec3(0, 0, 0) ); // front left
   pyramidVertices->push_back( osg::Vec3(2, 0, 0) ); // front right
   pyramidVertices->push_back( osg::Vec3(2, 2, 0) ); // back right
   pyramidVertices->push_back( osg::Vec3( 0,2, 0) ); // back left
   pyramidVertices->push_back( osg::Vec3( 1, 1,2) ); // peak

   // Associate this set of vertices with the geometry associated with the
   // geode we added to the scene.
   pyramidGeometry->setVertexArray( pyramidVertices );

   // Create a QUAD primitive for the base by specifying the
   // vertices from our vertex list that make up this QUAD:
   //specify 5 pyramid-faces
   osg::DrawElementsUInt* pyramidBase =
           new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
   pyramidBase->push_back(3);
   pyramidBase->push_back(2);
   pyramidBase->push_back(1);
   pyramidBase->push_back(0);
   pyramidGeometry->addPrimitiveSet(pyramidBase);

   osg::DrawElementsUInt* pyramidFaceOne =
           new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceOne->push_back(0);
   pyramidFaceOne->push_back(1);
   pyramidFaceOne->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceOne);

   osg::DrawElementsUInt* pyramidFaceTwo =
           new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceTwo->push_back(1);
   pyramidFaceTwo->push_back(2);
   pyramidFaceTwo->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceTwo);

   osg::DrawElementsUInt* pyramidFaceThree =
           new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceThree->push_back(2);
   pyramidFaceThree->push_back(3);
   pyramidFaceThree->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

   osg::DrawElementsUInt* pyramidFaceFour =
           new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceFour->push_back(3);
   pyramidFaceFour->push_back(0);
   pyramidFaceFour->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceFour);

   // Add this primitive to the geometry: pyramidGeometry->addPrimitiveSet(pyramidBase);
   // code to create other faces goes here!
   // (removed to save space, see tutorial two)

   osg::Vec4Array* colors = new osg::Vec4Array;
   colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
   colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
   colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
   colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white
   colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 4 red

   pyramidGeometry->setColorArray(colors);
   pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

   // Since the mapping from vertices to texture coordinates is 1:1,
   // we don't need to use an index array to map vertices to texture
   // coordinates. We can do it directly with the 'setTexCoordArray'
   // method of the Geometry class.
   // This method takes a variable that is an array of two dimensional
   // vectors (osg::Vec2). This variable needs to have the same
   // number of elements as our Geometry has vertices. Each array element
   // defines the texture coordinate for the cooresponding vertex in the
   // vertex array.
   osg::Vec2Array* texcoords = new osg::Vec2Array(5);
   (*texcoords)[0].set(0.00f,0.0f); // tex coord for vertex 0
   (*texcoords)[1].set(0.25f,0.0f); // tex coord for vertex 1
   (*texcoords)[2].set(0.50f,0.0f); // ""
   (*texcoords)[3].set(0.75f,0.0f); // ""
   (*texcoords)[4].set(0.50f,1.0f); // ""
   pyramidGeometry->setTexCoordArray(0,texcoords);

   return pyramidGeode;
}


int main()
{
    osg::Group * root = new osg::Group();
    osg::Geode * pyramidGeode = createPyramid();
    root->addChild(pyramidGeode);

    //load image and set as texture
    osg::Texture2D* KLN89FaceTexture = new osg::Texture2D;

    KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC);

    osg::Image * klnFace = osgDB::readImageFile( "lena512.jpg" );

    KLN89FaceTexture->setImage(klnFace);

    osg::StateSet* stateOne = new osg::StateSet();

    stateOne->setTextureAttributeAndModes(0, KLN89FaceTexture, osg::StateAttribute::ON );

    pyramidGeode->setStateSet(stateOne);


    // viewer
    osgViewer::Viewer viewer;
    viewer.setSceneData( root );
    return viewer.run();
}
