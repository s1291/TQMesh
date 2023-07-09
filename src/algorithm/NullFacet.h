/*
* This source file is part of the tqmesh library.  
* This code was written by Florian Setzwein in 2022, 
* and is covered under the MIT License
* Refer to the accompanying documentation for details
* on usage and license.
*/
#pragma once

#include "VecND.h"
#include "Geometry.h"
#include "Container.h"
#include "utils.h"

#include "Vertex.h"
#include "Facet.h"

namespace TQMesh {
namespace TQAlgorithm {

/*********************************************************************
* 
*********************************************************************/
class NullFacet : public Facet
{
public:
  /*------------------------------------------------------------------
  | Singleton: Get access to instance 
  ------------------------------------------------------------------*/
  static NullFacet& get_instance() 
  {
    static NullFacet null_facet; 
    return null_facet;
  }

  /*------------------------------------------------------------------
  | Singleton: Check if a given facet is the NullFacet
  ------------------------------------------------------------------*/
  static inline bool is_null(Facet* f) 
  { return f == &NullFacet::get_instance(); }

  static inline bool is_not_null(Facet* f) 
  { return f != &NullFacet::get_instance(); }

  /*------------------------------------------------------------------
  | Singleton: Delete copy & assignment operator
  ------------------------------------------------------------------*/
  NullFacet(const NullFacet&) = delete;
  NullFacet& operator=(const NullFacet&) = delete; 

  /*------------------------------------------------------------------
  | Getters 
  ------------------------------------------------------------------*/
  const Vertex& vertex(size_t i) const override
  { 
    ASSERT( false, "Invalid NullFacet access: vertex().");
    return dummy_; 
  }

  Vertex& vertex(size_t i) override
  { 
    ASSERT( false, "Invalid NullFacet access: vertex().");
    return dummy_; 
  }

  const Vec2d& xy() const override 
  { 
    ASSERT( false, "Invalid NullFacet access: xy()."); 
    return dummy_.xy(); 
  }

  size_t n_vertices() const override { return 0; }
  int    color() const override { return -1; }
  int    index() const override { return -1; }


  /*------------------------------------------------------------------
  | Setters 
  ------------------------------------------------------------------*/
  void color(int i) override
  { ASSERT( false, "Invalid NullFacet access: color()."); }

  void index(int i) override
  { ASSERT( false, "Invalid NullFacet access: index()."); }


  /*------------------------------------------------------------------
  | Functions to return indices of vertices, edges...
  ------------------------------------------------------------------*/
  int get_vertex_index(const Vertex& v) const override
  {
    ASSERT( false, "Invalid NullFacet access: get_vertex_index().");
    return -1;
  } 

  int get_edge_index(const Vertex& v1, const Vertex& v2) const override
  {
    ASSERT( false, "Invalid NullFacet access: get_edge_index().");
    return -1;
  }

  /*------------------------------------------------------------------
  | Set Facet neighbor 
  ------------------------------------------------------------------*/
  void neighbor(size_t i, Facet* f) override 
  { ASSERT( false, "Invalid NullFacet access: neighbor()."); }

  /*------------------------------------------------------------------
  | Facet intersection
  ------------------------------------------------------------------*/
  bool intersects_vertex(const Vertex& v) const override
  { 
    ASSERT( false, "Invalid NullFacet access: intersects_vertex()."); 
    return false;
  }

private: 
  /*------------------------------------------------------------------
  | Constructor / Destructor
  ------------------------------------------------------------------*/
  NullFacet() = default;
  ~NullFacet() {}

  /*------------------------------------------------------------------
  | Dummy attributes
  ------------------------------------------------------------------*/
  Vertex dummy_ {0.0, 0.0, 0.0, 0.0};

}; // NullFacet


} // namespace TQAlgorithm
} // namespace TQMesh