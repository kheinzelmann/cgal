#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/Point_with_normal_3.h>
#include <CGAL/property_map.h>
#include <CGAL/Timer.h>
#include <CGAL/number_utils.h>

#include <CGAL/Shape_detection_3.h>

#include <iostream>
#include <fstream>

// Type declarations
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT                                          FT;
typedef CGAL::Point_with_normal_3<Kernel>                   Point_with_normal;
typedef std::vector<Point_with_normal>                      Pwn_vector;
typedef CGAL::Identity_property_map<Point_with_normal>      Point_map;
typedef CGAL::Normal_of_point_with_normal_pmap<Kernel>      Normal_map;

// In Efficient_RANSAC_traits the basic types, i.e., Point and Vector types
// as well as iterator type and property maps, are defined.
typedef CGAL::Shape_detection_3::Efficient_RANSAC_traits<Kernel,
  Pwn_vector, Point_map, Normal_map>            Traits;
typedef CGAL::Shape_detection_3::Efficient_RANSAC<Traits>   Efficient_ransac;
typedef CGAL::Shape_detection_3::Plane<Traits>              Plane;


int main()
{
  // Points with normals.
  Pwn_vector points;

  // Loads point set from a file. 
  // read_xyz_points_and_normals takes an OutputIterator for storing the points
  // and a property map to store the normal vector with each point.
  std::ifstream stream("cube.pwn");

  if (!stream ||
    !CGAL::read_xyz_points_and_normals(stream,
      std::back_inserter(points),
      Normal_map())) 
  {
      std::cerr << "Error: cannot read file cube.pwn" << std::endl;
      return EXIT_FAILURE;
  }

  // Measures time before setting up the shape detection.
  CGAL::Timer time;
  time.start();

  // Instantiates shape detection engine.
  Efficient_ransac ransac;

  // Provides the input data.
  ransac.set_input(points);

  // Registers detection of planes
  ransac.add_shape_factory<Plane>();

  // Detects shapes.
  ransac.detect();

  // Measures time after detection.
  time.stop();

  // Prints number of assigned shapes and unsassigned points.
  std::cout << "time: " << time.time() * 1000 << "ms" << std::endl;
  std::cout << ransac.shapes().size() << " primitives, "
    << ransac.number_of_unassigned_points()
    << " unassigned points" << std::endl;

  // Efficient_ransac::shapes() provides
  // an iterator range to the detected shapes.
  Efficient_ransac::Shape_range shapes = ransac.shapes();
  Efficient_ransac::Shape_range::iterator it = shapes.begin();

  while (it != shapes.end()) {
    const Efficient_ransac::Shape *shape = *it;
    // Using Shape_base::info() for printing 
    // the parameters of the detected shape.
    std::cout << (*it)->info();

    // Sums distances of points to detected shapes.
    FT sum_distances = 0;

    // Iterates through point indices assigned to each detected shape.
    std::vector<std::size_t>::const_iterator
      index_it = (*it)->assigned_point_indices().begin();

    while (index_it != (*it)->assigned_point_indices().end()) {
      
      // Retrieves point
      const Point_with_normal &p = *(points.begin() + (*index_it));

      // Adds Euclidean distance between point and shape.
      sum_distances += CGAL::sqrt((*it)->squared_distance(p));

      // Proceeds with next point.
      index_it++;
    }

    // Computes and prints average distance.
    FT average_distance = sum_distances / shape->assigned_point_indices().size();
    std::cout << " average distance: " << average_distance << std::endl;

    // Proceeds with next detected shape.
    it++;
  }

  return EXIT_SUCCESS;
}
