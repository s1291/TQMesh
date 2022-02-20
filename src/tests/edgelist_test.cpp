#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <iomanip>   
#include <cmath>
#include <cstdlib>
#include <memory>       

#include "run_tests.h"

#include "utils.h"
#include "Vec2.h"
#include "Timer.h"
#include "Container.h"

#include "Vertex.h"
#include "Edge.h"
#include "EdgeList.h"


namespace EdgeListTests
{

using namespace TQMesh::TQUtils;
using namespace TQMesh::TQAlgorithm;


/*********************************************************************
* Test EdgeList insertion and removal
*
*   x---x---x
*   |       |
*   x---x---x
*
*********************************************************************/
void Test_EdgeList_add_remove()
{

  Container<Vertex> vertices { };

  Vertex& v1 = vertices.push_back( 1.0, 1.0 );
  Vertex& v2 = vertices.push_back( 2.0, 1.0 );
  Vertex& v3 = vertices.push_back( 3.0, 1.0 );
  Vertex& v4 = vertices.push_back( 3.0, 2.0 );
  Vertex& v5 = vertices.push_back( 2.0, 2.0 );
  Vertex& v6 = vertices.push_back( 1.0, 2.0 );

  EdgeList edges{ TQGeom::Orientation::CCW };

  Edge& e1 = edges.add_edge(v1,v2,1);
  Edge& e2 = edges.add_edge(v2,v3,1);
  Edge& e3 = edges.add_edge(v3,v4,2);
  Edge& e4 = edges.add_edge(v4,v5,3);
  Edge& e5 = edges.add_edge(v5,v6,3);
  Edge& e6 = edges.add_edge(v6,v1,4);

  // Check edge adjacency
  int nv = static_cast<int>(vertices.size());

  for (int i = 0; i < nv; i++)
  {
    ASSERT( vertices[i].is_adjacent( edges[ MOD(i-1, nv) ] ), 
            "Vertex::is_adjacent(Edge) failed." );

    ASSERT( vertices[i].is_adjacent( edges[ i ] ), 
            "Vertex::is_adjacent(Edge) failed." );

    ASSERT( (edges[i].v1() == vertices[i]),
            "Edge::v1() failed." );

    ASSERT( (edges[i].v2() == vertices[ MOD(i+1, nv) ]),
            "Edge::v1() failed." );
  }

  // Check area
  ASSERT( EQ(edges.area(),2.0) , 
          "Edge::compute_area() failed." );

  // Remove edges
  edges.remove( e3 );

  ASSERT( v2.edges().size() == 2, 
      "EdgeList::remove() failed.");
  ASSERT( v3.edges().size() == 1, 
      "EdgeList::remove() failed.");
  ASSERT( v4.edges().size() == 1, 
      "EdgeList::remove() failed.");
  ASSERT( edges.size() == 5, 
      "EdgeList::remove() failed.");

  (void) e1,e2,e3,e4,e5,e6;

  DBG_MSG("Tests for EdgeList adding / removal succeeded");

} // Test_EdgeList_add_remove()


/*********************************************************************
* Test EdgeList::is_inside() function
*
*   x---x---x
*   |       |
*   x---x---x
*
*********************************************************************/
void Test_EdgeList_is_inside()
{

  Container<Vertex> vertices { };

  Vertex& v1 = vertices.push_back( 1.0, 1.0 );
  Vertex& v2 = vertices.push_back( 2.0, 1.0 );
  Vertex& v3 = vertices.push_back( 3.0, 1.0 );
  Vertex& v4 = vertices.push_back( 3.0, 2.0 );
  Vertex& v5 = vertices.push_back( 2.0, 2.0 );
  Vertex& v6 = vertices.push_back( 1.0, 2.0 );

  EdgeList edges{ TQGeom::Orientation::CCW };

  Edge& e1 = edges.add_edge(v1,v2,1);
  Edge& e2 = edges.add_edge(v2,v3,1);
  Edge& e3 = edges.add_edge(v3,v4,2);
  Edge& e4 = edges.add_edge(v4,v5,3);
  Edge& e5 = edges.add_edge(v5,v6,3);
  Edge& e6 = edges.add_edge(v6,v1,4);


  Vertex& v7 = vertices.push_back( 2.0, 2.0 );
  Vertex& v8 = vertices.push_back( 5.0, 5.0 );

  ASSERT( edges.is_inside(v7), 
          "EdgeList::is_inside() failed." );
  
  ASSERT( !(edges.is_inside(v8)), 
          "EdgeList::is_inside() failed." );

  ASSERT( edges.is_inside(v2), 
          "EdgeList::is_inside() failed." );

  (void) e1,e2,e3,e4,e5,e6;
  (void) v7, v8;


  DBG_MSG("Tests for EdgeList::is_inside() succeeded");

} // Test_EdgeList_is_inside()


/*********************************************************************
* Test EdgeList::split_edge() function
*
*   x---x---x
*   |       |
*   x---x---x
*
*********************************************************************/
void Test_EdgeList_split_edge()
{

  Container<Vertex> vertices { };

  Vertex& v1 = vertices.push_back( 1.0, 1.0 );
  Vertex& v2 = vertices.push_back( 2.0, 1.0 );
  Vertex& v3 = vertices.push_back( 3.0, 1.0 );
  Vertex& v4 = vertices.push_back( 3.0, 2.0 );
  Vertex& v5 = vertices.push_back( 2.0, 2.0 );
  Vertex& v6 = vertices.push_back( 1.0, 2.0 );

  EdgeList edges{ TQGeom::Orientation::CCW };

  Edge& e1 = edges.add_edge(v1,v2,1);
  Edge& e2 = edges.add_edge(v2,v3,1);
  Edge& e3 = edges.add_edge(v3,v4,2);
  Edge& e4 = edges.add_edge(v4,v5,3);
  Edge& e5 = edges.add_edge(v5,v6,3);
  Edge& e6 = edges.add_edge(v6,v1,4);

  auto new_edges = edges.split_edge( e1, vertices, 0.5, true );
  Edge* e1_new = new_edges.first;
  Edge* e2_new = new_edges.second;

  ASSERT( (edges.size() == 7),
      "EdgeList::split_edge() failed.");

  ASSERT( (e1_new->v1() == v1),
      "EdgeList::split_edge() failed.");
  ASSERT( (e2_new->v2() == v2),
      "EdgeList::split_edge() failed.");

  const Vec2d xy_new = 0.5 * (v1.xy() + v2.xy());

  ASSERT( ((e1_new->v2().xy() - xy_new).length() < TQ_SMALL),
      "EdgeList::split_edge() failed.");

  ASSERT( ((e2_new->v1().xy() - xy_new).length() < TQ_SMALL),
      "EdgeList::split_edge() failed.");


  // Check for correct order of new edges
  auto pos_e2 = e2.pos();
  auto pos_e5 = e5.pos();
  auto pos_e6 = e6.pos();

  auto pos_e1_new = e1_new->pos();
  auto pos_e2_new = e2_new->pos();

  ASSERT( ((++pos_e5) == pos_e6),
      "EdgeList::split_edge() failed.");

  //ASSERT( ((++pos_e6) == pos_e1_new), // !!!!
  //    "EdgeList::split_edge() failed.");

  ASSERT( ((++pos_e1_new) == pos_e2_new),
      "EdgeList::split_edge() failed.");

  ASSERT( ((++pos_e2_new) == pos_e2),
      "EdgeList::split_edge() failed.");

  (void) e1,e2,e3,e4,e5,e6;
  (void) xy_new;
  (void) new_edges;
  (void) e1_new, e2_new;
  (void) pos_e2, pos_e5, pos_e6, pos_e1_new, pos_e2_new;


} // Test_EdgeList_split_edge()



} // namespace EdgeListTests

/*********************************************************************
* 
*********************************************************************/
void run_edgelist_tests()
{
  MSG("\n#===== EdgeList tests =====");

  EdgeListTests::Test_EdgeList_add_remove();
  EdgeListTests::Test_EdgeList_is_inside();
  EdgeListTests::Test_EdgeList_split_edge();

} // run_edge_list_tests()
